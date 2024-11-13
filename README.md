Autores:

Brayan Israel Lira Gutiérrez bi.liragutierrez@ugto.mx

Ponce Ruiz Angel Mario am.ponceruiz@ugto.mx

Jorge Andrés Jiménez Salazar ja.jimenez.salazar@ugto.mx

Eduardo Ramírez de la Fuente e.ramirezdelafuente@ugto.mx

Profesor: Huetzin Aaron Pérez Olivas

Descripción del proyecto:

Introducción

La función Bluetooth es una tecnología de comunicación inalámbrica que puede ser usada para transmisión de datos de corto alcance de un dispositivo digital a otro. Bluetooth es esencialmente una conexión inalámbrica uno a uno que usa ondas de radio de banda de 2,4 GHz.

Bluetooth Low Energy (BLE) en el ESP32

El Bluetooth Low Energy (BLE) en el ESP32 es una tecnología revolucionaria que ha transformado la manera en que los dispositivos se comunican entre sí. Diseñado para aplicaciones que requieren un consumo de energía extremadamente bajo, BLE permite la transmisión eficiente de datos en dispositivos como wearables, sensores de salud, sistemas de automatización del hogar y más. El ESP32, con su capacidad de actuar tanto como servidor como cliente BLE, ofrece una flexibilidad impresionante para desarrolladores y entusiastas de la tecnología. Esta tecnología no solo mejora la eficiencia energética, sino que también proporciona una comunicación segura y confiable, haciendo posible una amplia gama de aplicaciones innovadoras en el mundo de la Internet de las Cosas (IoT).

Android Studio

En el dinámico mundo del desarrollo de aplicaciones móviles, Android Studio se ha consolidado como la herramienta esencial para los desarrolladores que buscan crear aplicaciones nativas para la plataforma Android. Lanzado oficialmente por Google en 2013, Android Studio está basado en IntelliJ IDEA de JetBrains, lo que le proporciona una sólida base de funcionalidades avanzadas. Este entorno de desarrollo integrado (IDE) ofrece un conjunto completo de herramientas que abarcan desde la edición y depuración de código hasta el diseño de interfaces de usuario y la gestión de dependencias mediante Gradle. Además, su emulador integrado permite probar y optimizar aplicaciones en una amplia variedad de dispositivos virtuales, garantizando compatibilidad y rendimiento en múltiples versiones de Android. Gracias a su interfaz intuitiva y sus potentes capacidades, Android Studio facilita tanto a principiantes como a desarrolladores experimentados la creación de aplicaciones robustas, eficientes y atractivas, impulsando así la innovación en el ecosistema Android.

Algunas características principales de Android Studio incluyen:

Editor de Código: Ofrece herramientas avanzadas de edición de código, incluyendo resaltado de sintaxis, autocompletado y refactorización.

Emulador de Android: Permite probar aplicaciones en un dispositivo virtual que emula un dispositivo Android real.

Depuración y Perfilado: Facilita la depuración de errores y el análisis del rendimiento de la aplicación con herramientas integradas.

Diseñador de Interfaz Gráfica: Incluye un editor visual para diseñar las interfaces de usuario, donde se pueden arrastrar y soltar elementos.

Compatibilidad con múltiples dispositivos y versiones de Android: Permite crear aplicaciones que funcionen en distintos tipos de dispositivos y versiones de Android.

Gestión de dependencias: Utiliza Gradle como sistema de compilación para gestionar dependencias y construir la aplicación.

Deep sleep

El deep sleep (sueño profundo) es un modo de bajo consumo de energía en el microcontrolador ESP32, diseñado para reducir al mínimo el consumo eléctrico mientras el dispositivo está inactivo. Este modo es ideal para aplicaciones que necesitan prolongar la duración de la batería, como dispositivos IoT (Internet de las cosas) que pasan mucho tiempo inactivos y solo se activan de forma periódica para realizar tareas específicas, como tomar una medición o enviar datos.

Algunas características clave del modo deep sleep en el ESP32 incluyen:

Desactivación de la CPU: Durante el deep sleep, la CPU y la mayoría de los componentes del sistema están apagados, lo que reduce considerablemente el consumo de energía.

Uso de memoria RTC: El ESP32 mantiene una pequeña porción de su memoria RTC (Real-Time Clock) activa, lo que permite almacenar datos que estarán disponibles al despertar. Esto es útil para conservar variables o estados importantes.

Periféricos en bajo consumo: En este modo, solo ciertos periféricos pueden permanecer activos, como el reloj en tiempo real, los temporizadores de baja potencia, o algunos pines de entrada/salida que pueden generar una señal de activación.

Métodos de activación (wake-up): El ESP32 puede salir del modo deep sleep usando diversos métodos de activación, como temporizadores (para despertar después de un tiempo determinado), el cambio de estado de pines específicos, o señales externas, como un botón o sensor.

Consumo de energía mínimo: Este modo permite reducir el consumo hasta unos pocos microamperios, lo que resulta extremadamente bajo en comparación con los modos de funcionamiento normal.

En el modo deep sleep, el ESP32 está inactivo hasta que una condición específica de activación lo "despierta". Al reactivarse, el microcontrolador puede retomar sus funciones con un consumo de energía normal, realizar la tarea necesaria, y luego volver al modo de bajo consumo.
