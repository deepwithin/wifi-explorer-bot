#include <ESP8266WiFi.h>

const char* ssid = "explorer";
const char* password = "12345678";
WiFiServer server(1337);
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  server.begin();

}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }

  WiFiClient client = server.available();

  if (client) {
    Serial.println("Client connected.");

    while (client.connected()) {

      //MAIN CODE GOES HERE FOR LOOP SEQUENCE

      if (client.available()) {



        char command = client.read();
        if (command == 'H') {

          //if statement commands goes over here.

        }
      }
    }
  }
}
