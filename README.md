# MQTT ESP32 Client

## Description
This project implements an MQTT client on an ESP32 microcontroller using the Arduino framework. The client connects to the MQTT broker at `test.mosquitto.org` and publishes messages to the topic `/test/topic`. Additionally, it subscribes to the topic `esp32/test` to receive messages from the broker.

## Setup Instructions
### Hardware Requirements
- ESP32 microcontroller board
- USB cable for programming and power

### Software Setup
1. Install the Arduino IDE.
2. Install the ESP32 board support package in the Arduino IDE.
3. Import the necessary libraries: `WiFi.h` and `PubSubClient.h`. These can be installed through the Library Manager in the Arduino IDE.

### Configuration
- Open the sketch file `mqtt.ino`.
- Modify the following constants according to your network configuration:
  - `WIFI_SSID`: SSID of your WiFi network.
  - `WIFI_PASSWORD`: Password of your WiFi network.
  - `MQTT_SERVER`: MQTT broker address (e.g., `test.mosquitto.org`).
  - `MQTT_PORT`: Port number of the MQTT broker (usually `1883`).
  - `OUT`: Topic to which the client publishes messages (e.g., `/test/topic`).

### Upload and Run
- Connect the ESP32 board to your computer via USB.
- Select the appropriate board and port from the Arduino IDE.
- Click on the "Upload" button to compile and upload the code to the ESP32 board.

## Usage
- Once the code is uploaded, open the Serial Monitor in the Arduino IDE (or any other serial monitor tool) to view the output.
- The ESP32 will connect to the configured WiFi network and then attempt to establish a connection to the MQTT broker.
- Messages will be published to the specified topic every 2 seconds, indicating the count of messages sent.
- Received messages from the topic `esp32/test` will be displayed on the Serial Monitor.

### Additional Command (for checking subscribed topic)
To monitor messages published to the topic `/test/topic` on the MQTT broker `test.mosquitto.org`, you can use the following command:
```shell
mosquitto_sub -h test.mosquitto.org -p 1883 -t "/test/topic"
