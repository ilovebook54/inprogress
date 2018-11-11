#include <ESP8266WiFi.h>
int RELAY_PIN = 12;
const char* password = "";
const char* ssid = "default";
const int port = 8181;

WiFiServer server(port);

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {

  WiFiClient client = server.available();
  while(client.connected()) {
    
    if (client.available()) {
    
      uint8_t buf;
      size_t length = 1;
      client.read(&buf, length);
      client.write(handleCmd(buf));
    }
  }
}

char* handleCmd(uint8_t cmd) {
  Serial.print("Value in ASCII ," );
  Serial.println(cmd);
  Serial.print("Value in Character ,");
  Serial.println(char(cmd));
  switch(cmd) {
    case 49:
   //     Serial.println("In Case 49");
        digitalWrite(RELAY_PIN, HIGH);
        return "ON";
    case 48:
   //     Serial.println("In Case 48");
        digitalWrite(RELAY_PIN, LOW);
        return "OFF";
    default:
        return ".";
  }
}


