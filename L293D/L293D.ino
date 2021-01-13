#include <ESP8266WiFi.h>

const int rb = D7;            //declaring motor pins
const int rf = D8;
const int lb = D3;
const int lf = D4;
void setup() {
  // put your setup code here, to run once:
  pinMode(rb, OUTPUT);
  pinMode(rf, OUTPUT);
  pinMode(lb, OUTPUT);
  pinMode(lf, OUTPUT);
  digitalWrite(rb, LOW);              //initial states declaration
  digitalWrite(rf, LOW);
  digitalWrite(lb, LOW);
  digitalWrite(lf, LOW);


  // Start TCP server.
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
        char command = client.read();         //getting input from user
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

}
