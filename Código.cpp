#include <Wire.h>
#include <MPU6050_tockn.h>
#include <Adafruit_BME280.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <esp_sleep.h>

MPU6050 mpu(Wire);
Adafruit_BME280 bmp;

#define SERVICE_UUID        "12345678-1234-1234-1234-1234567890ab"
#define CHARACTERISTIC_UUID "87654321-4321-4321-4321-1234567890ab"
#define BUTTON_PIN 23  // Pin del botón

BLECharacteristic *pCharacteristic;
bool deviceConnected = false;

unsigned long lastTime = 0;
const int dataInterval = 5000; // Intervalo de almacenamiento
int currentIndex = 0;
const int dataBufferSize = 1; // Tamaño del buffer para guardar 1 muestra

struct SensorData {
  float gyroX, gyroY, gyroZ;    // Inclinación en cada eje
  float temp;                   // Temperatura del BMP280
};

SensorData dataBuffer[dataBufferSize];

class MyCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    deviceConnected = true;
  };

  void onDisconnect(BLEServer* pServer) {
    deviceConnected = false;
  }
};

// Función para entrar en modo de sueño profundo
void enterDeepSleep() {
  Serial.println("Entrando en modo de sueño profundo...");

  // Detener BLE para evitar que continúe funcionando en modo de sueño
  BLEDevice::deinit(true);

  // Configura para despertar cuando el botón se presione (pin 23)
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_23, 0);  // 0 = Low, 1 = High
  
  // Mantener el RTC encendido para permitir el despertar
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON);

  // Entrar en modo de sueño profundo
  esp_deep_sleep_start();
}

// Función para inicializar la conexión BLE y realizar las lecturas después del despertar
void setup() {
  // Verificamos si el ESP32 ha despertado del sueño profundo
  if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_EXT0) {
    Serial.println("Despertado por el botón");
  } else {
    Serial.println("Inicio normal");
  }

  Serial.begin(9600);
  Wire.begin();
  
  // Inicializa el MPU6050
  mpu.begin();
  mpu.calcGyroOffsets(true);

  if (!bmp.begin(0x76)) {
    Serial.println("Error al iniciar BME280");
    while (1);
  }

  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Configura el pin del botón con pull-up interno

  // Configuración BLE
  BLEDevice::init("ESP32_Sensor");
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyCallbacks());

  BLEService *pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_NOTIFY
                    );
  pCharacteristic->addDescriptor(new BLE2902());
  pService->start();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x06);
  BLEDevice::startAdvertising();

  Serial.println("Esperando conexión BLE...");
}

void loop() {
  // Revisa si el botón ha sido presionado para entrar en modo de sueño
  if (digitalRead(BUTTON_PIN) == LOW) {
    delay(50);  // Debounce
    if (digitalRead(BUTTON_PIN) == LOW) {
      enterDeepSleep();
    }
  } else {
    // Si está conectado, podemos continuar con el proceso de lectura de sensores y actualización BLE
    unsigned long currentTime = millis();

    if (currentTime - lastTime > dataInterval) {
      // Lee y calcula inclinación del giroscopio
      mpu.update();
      float gyroX = atan2(mpu.getAccY(), mpu.getAccZ()) * 180 / PI;
      float gyroY = atan2(-mpu.getAccX(), sqrt(mpu.getAccY() * mpu.getAccY() + mpu.getAccZ() * mpu.getAccZ())) * 180 / PI;
      float gyroZ = mpu.getGyroZ();

      // Lee la temperatura del BMP280
      float temp = bmp.readTemperature();

      // Almacena datos en el buffer
      dataBuffer[currentIndex] = { gyroX, gyroY, gyroZ, temp };
      currentIndex = (currentIndex + 1) % dataBufferSize;

      // Imprime los datos en el monitor serial
      Serial.print("GyroX: "); Serial.print(gyroX);
      Serial.print(" | GyroY: "); Serial.print(gyroY);
      Serial.print(" | GyroZ: "); Serial.print(gyroZ);
      Serial.print(" | Temp: "); Serial.println(temp);

      lastTime = currentTime;
    }

    // Si está conectado, envía el buffer completo
    if (deviceConnected) {
      String jsonData = "["; 
      for (int i = 0; i < dataBufferSize; i++) {
        jsonData += "{\"gyroX\":" + String(dataBuffer[i].gyroX) + ",\"gyroY\":" + String(dataBuffer[i].gyroY) +
                    ",\"gyroZ\":" + String(dataBuffer[i].gyroZ) + ",\"temp\":" + String(dataBuffer[i].temp) + "}";
        if (i < dataBufferSize - 1) jsonData += ","; // No agregar coma al final del JSON
      }
      jsonData += "]";
      pCharacteristic->setValue(jsonData.c_str());
      pCharacteristic->notify();
      
      delay(2000); // Pausa para evitar saturar la conexión BLE
    }
  }
}
