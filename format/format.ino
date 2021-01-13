#include <ESP8266WiFi.h>
#include <Servo.h>
Servo myservo;


int trigPin = D1;    // Trigger
int echoPin = D2;    // Echo

const int rb = D4;
const int rf = D3;
const int lb = D8;
const int lf = D7;


const char* ssid = "explorer";
const char* password = "12345678";
const int ledPin = 2;
WiFiServer server(1337);

//int trigPin = D1;    // Trigger
//int echoPin = D2;    // Echo
float duration, cm, inches;

void printWiFiStatus();

void setup() {
    myservo.attach(D5);



  pinMode(0, INPUT_PULLUP);
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  // Configure GPIO2 as OUTPUT.
  pinMode(ledPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(rb, OUTPUT);
  pinMode(rf, OUTPUT);
  pinMode(lb, OUTPUT);
  pinMode(lf, OUTPUT);
  digitalWrite(rb, LOW);
  digitalWrite(rf, LOW);
  digitalWrite(lb, LOW);
  digitalWrite(lf, LOW);

  // Start TCP server.
  server.begin();
}

void loop() {

  // Check if module is still connected to WiFi.
  if (WiFi.status() != WL_CONNECTED) {
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
    }
    // Print the new IP to Serial.
    printWiFiStatus();
  }

  WiFiClient client = server.available();

  if (client) {
    Serial.println("Client connected.");

    while (client.connected()) {

      digitalWrite(trigPin, LOW);
      delayMicroseconds(5);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);

      pinMode(echoPin, INPUT);
      duration = pulseIn(echoPin, HIGH);

      // Convert the time into a distance
      cm = (duration / 2.0) / 29.1;   // Divide by 29.1 or multiply by 0.0343
      inches = (duration / 2.0) / 74.0; // Divide by 74 or multiply by 0.0135

      Serial.print(inches);
      Serial.print("in, ");
      Serial.print(cm);
      Serial.print("cm");
      Serial.println();

      if (client.available()) {

        client.print(cm);


        char command = client.read();
        if (command == 'F') {
          digitalWrite(rb, LOW);
          digitalWrite(rf, HIGH);
          digitalWrite(lb, LOW);
          digitalWrite(lf, HIGH);
        }
        if (command == 'B') {
          digitalWrite(rb, HIGH);
          digitalWrite(rf, LOW);
          digitalWrite(lb, HIGH);
          digitalWrite(lf, LOW);
        }
        if (command == 'L') {
          digitalWrite(rb, LOW);
          digitalWrite(rf, HIGH);
          digitalWrite(lb, HIGH);
          digitalWrite(lf, LOW);
        }
        if (command == 'R') {
          digitalWrite(rb, HIGH);
          digitalWrite(rf, LOW);
          digitalWrite(lb, LOW);
          digitalWrite(lf, HIGH);
        }
        if (command == 'S') {
          digitalWrite(rb, HIGH);
          digitalWrite(rf, HIGH);
          digitalWrite(lb, HIGH);
          digitalWrite(lf, HIGH);
        }
        if (command == 'X') {
          myservo.write(0);
        }
        if (command == 'Y') {
          myservo.write(90);
        }
        if (command == 'Z') {
          myservo.write(180);
        }
      }
    }
    Serial.println("Client disconnected.");
    client.stop();
  }
}

void printWiFiStatus() {
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
