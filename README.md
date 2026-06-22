<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Proyecto comedero de pecera automatizado</title>
    <style>
        body {
            font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Helvetica, Arial, sans-serif;
            line-height: 1.6;
            color: #333;
            max-width: 900px;
            margin: 0 auto;
            padding: 2rem;
            background-color: #f9f9f9;
        }
        .container {
            background-color: #fff;
            padding: 2rem 3rem;
            border-radius: 8px;
            box-shadow: 0 4px 6px rgba(0,0,0,0.1);
        }
        h1, h2, h3 {
            border-bottom: 1px solid #eaecef;
            padding-bottom: 0.3em;
            margin-top: 1.5em;
        }
        h1 { text-align: center; border-bottom: none; margin-bottom: 0.2em; }
        .subtitle { text-align: center; color: #666; font-size: 1.2em; margin-bottom: 1.5em; }
        .badges { text-align: center; margin-bottom: 2em; }
        .badges img { margin: 0 5px; }
        .center-img {
            display: block;
            margin: 1.5rem auto;
            max-width: 100%;
            border-radius: 6px;
            box-shadow: 0 4px 8px rgba(0,0,0,0.1);
        }
        .gallery {
            display: flex;
            gap: 15px;
            justify-content: center;
            flex-wrap: wrap;
            margin: 1.5rem 0;
        }
        .gallery img {
            width: calc(33% - 10px);
            border-radius: 6px;
            box-shadow: 0 2px 4px rgba(0,0,0,0.1);
            object-fit: cover;
        }
        .gallery-2 {
            display: flex;
            gap: 15px;
            justify-content: center;
            flex-wrap: wrap;
            margin: 1.5rem 0;
        }
        .gallery-2 img {
            width: calc(50% - 10px);
            border-radius: 6px;
            box-shadow: 0 2px 4px rgba(0,0,0,0.1);
            object-fit: cover;
        }
        .img-caption { text-align: center; font-style: italic; color: #666; font-size: 0.9em; margin-bottom: 1.5rem; }
        table {
            width: 100%;
            border-collapse: collapse;
            margin: 1.5rem 0;
        }
        th, td {
            padding: 12px;
            border: 1px solid #dfe2e5;
            text-align: left;
        }
        th { background-color: #f6f8fa; }
        code {
            background-color: #f6f8fa;
            padding: 0.2em 0.4em;
            border-radius: 3px;
            font-family: monospace;
        }
        pre {
            background-color: #f6f8fa;
            padding: 16px;
            border-radius: 6px;
            overflow: auto;
        }
        pre code { background-color: transparent; padding: 0; }
        blockquote {
            border-left: 4px solid #dfe2e5;
            color: #6a737d;
            padding: 0 1em;
            margin: 1.5rem 0;
            background-color: #fff;
        }
        hr { border: 0; height: 1px; background: #eaecef; margin: 2rem 0; }
        .footer { text-align: center; margin-top: 3rem; color: #666; font-size: 0.9em; }
    </style>
</head>
<body>

<div class="container">

    <h1>Proyecto comedero de pecera automatizado</h1>
    <div class="subtitle">Sistema Automatizado para el Cuidado de Peceras</div>

    <div class="badges">
        <img src="https://img.shields.io/badge/Status-Completado-success?style=for-the-badge" alt="Status">
        <img src="https://img.shields.io/badge/Plataforma-ESP32%20%7C%20Raspberry%20Pi-blue?style=for-the-badge" alt="Plataforma">
        <img src="https://img.shields.io/badge/Protocolo-MQTT-orange?style=for-the-badge" alt="Protocolo">
    </div>

    <img src="assets/IMG_1502.jpg" alt="Vista general del proyecto AquaSmart" class="center-img" style="max-width: 800px;">
    
    <p style="text-align: center;"><em>Proyecto de Internet de las Cosas (IoT) diseñado para automatizar el cuidado de una pecera. El sistema controla una bomba de agua, automatiza un dispensador de comida casero y monitorea la temperatura del agua en tiempo real mediante un panel web.</em></p>

    <hr>

    <h2>Características Principales</h2>
    <ul>
        <li><strong>Monitoreo de Temperatura:</strong> Lectura en tiempo real del agua usando una sonda sumergible DS18B20.</li>
        <li><strong>Alimentación Automatizada:</strong> Control de un servomotor integrado a un dispensador casero para suministrar raciones exactas de comida.</li>
        <li><strong>Control de Filtrado:</strong> Gestión del encendido/apagado de la bomba de agua mediante un módulo relevador.</li>
        <li><strong>Arquitectura Local Segura:</strong> Toda la comunicación ocurre de forma local (LAN) usando un servidor MQTT (Mosquitto) y Node-RED ejecutados en contenedores Docker sobre una Raspberry Pi 3.</li>
    </ul>

    <hr>

    <h2>Arquitectura y Software</h2>
    <p>El diseño se basa en un modelo descentralizado de publicación/suscripción mediante el protocolo <strong>MQTT</strong>.</p>

    <img src="assets/Captura de pantalla 2026-06-21 213631.png" alt="Flujo de Node-RED" class="center-img" style="max-width: 800px;">
    <div class="img-caption">Panel de control y orquestación lógica en Node-RED</div>

    <ol>
        <li><strong>Cerebro (Servidor):</strong> Una Raspberry Pi 3 ejecuta Docker. Hospeda el broker <em>Eclipse Mosquitto</em> para la mensajería y <em>Node-RED</em> para la orquestación lógica y la interfaz de usuario.</li>
        <li><strong>Músculo (Cliente):</strong> Un ESP32 conectado por Wi-Fi se encarga de interactuar físicamente con los sensores y actuadores.</li>
    </ol>

    <hr>

    <h2>Hardware y Circuito</h2>

    <img src="assets/IMG_1503.jpg" alt="Conexiones electrónicas generales" class="center-img" style="max-width: 700px;">
    <div class="img-caption">Circuito principal de control y etapa de potencia montados en la pared</div>

    <div class="gallery-2">
        <img src="assets/IMG_1506.jpg" alt="ESP32 encendido">
        <img src="assets/IMG_1505.jpg" alt="Conexiones en protoboard con resistencia Pull-Up">
    </div>
    <div class="img-caption">Detalle del microcontrolador ESP32 y el circuito del sensor DS18B20</div>

    <img src="assets/IMG_1504.jpg" alt="Módulo Relevador" class="center-img" style="max-width: 400px;">
    <div class="img-caption">Etapa de potencia: Módulo Relevador controlando la bomba</div>

    <h3>Lista de Materiales (BOM)</h3>
    <ul>
        <li>1x Tarjeta de desarrollo ESP32.</li>
        <li>1x Placa de expansión (Shield) para ESP32.</li>
        <li>1x Protoboard de media galleta.</li>
        <li>1x Raspberry Pi 3 Model B con tarjeta MicroSD.</li>
        <li>1x Módulo Relevador de 5V (SRD-05VDC-SL-C).</li>
        <li>1x Sonda de Temperatura Sumergible DS18B20.</li>
        <li>1x Resistencia de 4.7kΩ (Pull-up).</li>
        <li>1x Bomba de agua sumergible.</li>
    </ul>

    <blockquote>
        <strong>Requisito Crítico de Alimentación:</strong><br>
        Debido al consumo síncrono del módulo Wi-Fi, la bobina del relevador y el servomotor (~1.5A pico), el circuito del ESP32 <strong>debe ser alimentado por una fuente dedicada de 5V a 2A</strong> (Mínimo). Alimentar el sistema a través del puerto USB de la PC provocará caídas de voltaje.
    </blockquote>

    <h3>Diagrama de Conexiones (Pinout ESP32)</h3>
    <table>
        <thead>
            <tr>
                <th>Componente</th>
                <th>Pin ESP32</th>
                <th>Alimentación</th>
                <th>Tierra (GND)</th>
                <th>Notas Adicionales</th>
            </tr>
        </thead>
        <tbody>
            <tr>
                <td><strong>Módulo Relevador (IN1)</strong></td>
                <td><code>D26</code></td>
                <td><code>VIN</code> (5V)</td>
                <td><code>GND</code></td>
                <td>Conexión a la bomba en pines COM y NO.</td>
            </tr>
            <tr>
                <td><strong>Servomotor SG90 (Señal)</strong></td>
                <td><code>D27</code></td>
                <td><code>VIN</code> (5V)</td>
                <td><code>GND</code></td>
                <td>Control de pulsos por ancho de banda.</td>
            </tr>
            <tr>
                <td><strong>Sensor DS18B20 (Datos)</strong></td>
                <td><code>D4</code></td>
                <td><code>3V3</code> (3.3V)</td>
                <td><code>GND</code></td>
                <td>Requiere resistencia de <strong>4.7kΩ</strong> entre <code>D4</code> y <code>3V3</code>.</td>
            </tr>
        </tbody>
    </table>

    <hr>

    <h2>Dispensador Casero de Alimento</h2>
    <p>Para resolver la dosificación sin usar impresión 3D, se diseñó un ingenioso mecanismo utilizando tubería de PVC y la tapa plástica fijada al aspa del motor.</p>

    <div class="gallery">
        <img src="assets/IMG_1507.jpg" alt="Fijación del Servomotor">
        <img src="assets/IMG_1508.jpg" alt="Acoplamiento del bote de PVC">
        <img src="assets/IMG_1509.jpg" alt="Dispensador finalizado">
    </div>
    <div class="img-caption">Proceso de acoplamiento del motor a la estructura del dispensador</div>

    <ol>
        <li>El Servomotor SG90 se fija a la estructura cerca del área de alimentación.</li>
        <li>Se utiliza un tubo de PVC cerrado con un orificio inferior dimensionado para las raciones.</li>
        <li>Se acopla mecánicamente el aspa del servo a la tapa del dispensador.</li>
        <li><strong>Lógica de Software:</strong> El código gira el servo 90° y regresa a 0°, destapando el orificio lateral por una fracción de segundo y permitiendo la caída por gravedad de una ración exacta a la pecera.</li>
    </ol>

    <hr>

    <h2>Configuración y Despliegue</h2>

    <h3>1. Servidor Docker (Raspberry Pi)</h3>
    <p>Clona este repositorio en tu Raspberry Pi y levanta la infraestructura de red ejecutando:</p>
<pre><code>sudo docker compose up -d</code></pre>

    <h3>2. Firmware del Nodo (ESP32)</h3>
    <ol>
        <li>Abre el archivo localizado en <code>src/codigo_pecera/codigo_pecera.ino</code> mediante Arduino IDE.</li>
        <li>Instala las dependencias: <code>PubSubClient</code>, <code>ESP32Servo</code>, <code>OneWire</code> y <code>DallasTemperature</code>.</li>
        <li>Actualiza las constantes de red (<code>ssid</code>, <code>password</code>) y la dirección IP estática del broker MQTT (<code>mqtt_server</code>).</li>
        <li>Realiza la carga del programa al microcontrolador.</li>
    </ol>

    <h3>3. Interfaz de Control</h3>
    <p>Accede al entorno de desarrollo web a través del puerto de Node-RED (<code>http://&lt;IP_DE_TU_RASPBERRY&gt;:1880</code>), importa el flujo y presiona <strong>Deploy</strong>.</p>

    <div class="footer">
        <hr>
        <p>Desarrollado por <strong>Diego Aarón Cárdenas Mendoza</strong><br>
        <p>Video de funcionamiento: https://drive.google.com/drive/folders/1H6vibHPFN_1VaHEIQuGd3jOt_XLSVmgq</strong><br>
        Escuela Superior de Cómputo (ESCOM) - IPN</p>
    </div>

</div>

</body>
</html>