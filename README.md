# Sistema Automatizado para Pecera para IoT

Este proyecto implementa un sistema robusto de Internet de las Cosas (IoT) para automatizar los cuidados básicos de una pecera. A través de una arquitectura local, el sistema gestiona los ciclos de filtrado de agua, la dosificación de alimento y el monitoreo térmico constante del entorno acuático.

##  Arquitectura y Funcionamiento

El diseño se basa en un modelo descentralizado de publicación/suscripción mediante el protocolo **MQTT**:
* **Servidor Central (Raspberry Pi 3):** Coordina los servicios mediante contenedores Docker. Hospeda el broker *Eclipse Mosquitto* para la mensajería y *Node-RED* para la orquestación lógica del flujo y la interfaz de usuario.
* **Nodo de Control (ESP32):** Actúa como el cliente físico en campo, recopilando lecturas del sensor y accionando los componentes mecánicos según las instrucciones recibidas de la red.

##  Especificaciones de Hardware

* **Microcontrolador:** Tarjeta de desarrollo ESP32 (con placa de expansión Shield de bornes de tornillo).
* **Servidor:** Raspberry Pi 3 Model B (operando en modo headless vía SSH).
* **Sensor de Temperatura:** Sonda digital sumergible DS18B20 (Protocolo 1-Wire).
* **Actuador de Filtrado:** Módulo Relevador de 5V (Bobina SRD-05VDC-SL-C).
* **Actuador de Alimentación:** Servomotor SG90 acoplado a un contenedor plástico casero con apertura inferior regulada por pulsos mecánicos.

###  Requisito Crítico de Alimentación
Debido al consumo síncrono del módulo Wi-Fi, la bobina del relevador y la demanda de corriente de arranque del servomotor (~1.5A pico), el circuito del ESP32 **debe ser alimentado estrictamente por una fuente externa regulada de 5V a 2A**. Alimentar el sistema a través del puerto USB de la computadora o fuentes de menor amperaje provocará caídas bruscas de voltaje y reinicios intermitentes del microcontrolador.

##  Distribución de Pines (Pinout)

| Componente | Pin Digital ESP32 | Línea de Voltaje | Tierra | Configuración Adicional |
| :--- | :--- | :--- | :--- | :--- |
| **Módulo Relevador (IN1)** | `D26` | `VIN` (5V) | `GND` | Conexión en puerto COM y pin NO (Normalmente Abierto) |
| **Servomotor SG90 (Señal)** | `D27` | `VIN` (5V) | `GND` | Control de pulsos por ancho de banda |
| **Sensor DS18B20 (Datos)** | `D4` | `3V3` (3.3V) | `GND` | Requiere resistencia Pull-Up de **4.7kΩ** entre `D4` y `3V3` |

##  Instrucciones de Despliegue

### 1. Servidor Docker
Clona este repositorio en tu Raspberry Pi y levanta la infraestructura de red ejecutando:
```bash
sudo docker compose up -d