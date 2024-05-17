#include <WiFi.h>
#include <PubSubClient.h>

#define WIFI_SSID "CACTUS_AP"
#define WIFI_PASSWORD "Admin$cactus$"

#define MQTT_SERVER "test.mosquitto.org"
#define MQTT_PORT 1883
#define MQTT_USERNAME "" // No username required
#define MQTT_PASSWORD "" // No password required
#define OUT "/test/topic"


WiFiClient espClient;
PubSubClient client(espClient);

long currentTime, lastTime = 0;
int count = 0;
char messages[50]; // Adjust buffer size to match the size needed

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("WiFi connected - IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("nish", MQTT_USERNAME, MQTT_PASSWORD)) {
      Serial.println("connected");
      client.subscribe("esp32/test");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  currentTime = millis();
  if (currentTime - lastTime > 2000) {
    count++;
    snprintf(messages, sizeof(messages), "%d", count);
    Serial.println(messages);
    client.publish(OUT, messages);
    lastTime = currentTime;
  }
}
