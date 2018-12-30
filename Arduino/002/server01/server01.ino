#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "src/passwords.h"

#ifdef __cplusplus
extern "C" {
#endif
uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif
uint8_t temprature_sens_read();


const int PORT = 80;
const int pinLedOut = 22;
const int pinVarResistorIn = 35;
const int LED_BUILTIN = 2;
const int pinButtonIn = 18;

int ledstate = 0;
int ledTimerUntil = 0;

WebServer server(PORT);

void setup(void) {
  Serial.begin(115200);
  Serial.print("setting up wifi...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("connecting to wifi...");
  }
  Serial.print("connected to " + String(ssid) + " at ");
  Serial.println(WiFi.localIP());
  Serial.println("mdns: " + String(MDNS.begin("antsboard")) + "; if available, try http://antsboard.local/");
WiFi.setHostname("antsboard");
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started, listening on port " + PORT);

  pinMode(pinVarResistorIn, INPUT);
  pinMode(pinLedOut, OUTPUT);
  pinMode(pinButtonIn, INPUT_PULLUP);

// configure onboard led (turn off with 2, 3 and 4 to high; red is 2=high; pin3 doesnt seem to have an effect; just pin4=high is green;
pinMode(LED_BUILTIN, OUTPUT);
digitalWrite(LED_BUILTIN, 1);
//pinMode(3, OUTPUT);
//digitalWrite(3, 1);
pinMode(4, OUTPUT);
digitalWrite(4, 1);
}

void loop(void) {
  int button = digitalRead(pinButtonIn);
  if(button == LOW) {
    //button is pushed => extend timer
    int length = analogRead(pinVarResistorIn);
    if(length > 4000) length = 10000000;
    ledTimerUntil = millis() + 1000 + length; // a second plus 0-4000ms depending on variable resistor, or indefinite if variable resistor is at max
    digitalWrite(pinLedOut, 1);
  }

  if(millis() > ledTimerUntil) {
    digitalWrite(pinLedOut, 0);
  }
  
  server.handleClient();
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
}

void handleRoot() {
  char temp[400];

  int val = analogRead(pinVarResistorIn);
  int ledOn = digitalRead(pinLedOut);
  double h = hallRead();
  double t = (temprature_sens_read() - 32) / 1.8;

  snprintf(temp, 400,
           "<html>\
              <body>\
                <p>length: %09d</p>\
                <p>led on? %09d</p>\
                <p>hall: %09f</p>\
                <p>temp C: %09f</p>\
              </body>\
            </html>"
            ,val, ledOn, h, t);
  server.send(200, "text/html", temp);
}

/*
snippets
========
const int led = 13;
  pinMode(led, OUTPUT);
  digitalWrite(led, 1);
  digitalWrite(led, 0);


  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });




  for(int i = 0; i < 40; i++) {
    int pin = analogRead(i);
    if(pin > 0) {
      Serial.println("pin " + String(i) + " -" + String(pin) + "-");
    }
  }
  delay(1000);


TODO
========
- fix error relating to wifi connect that seems to come when we make an http request
- reconnect if wifi lost?
- https://www.arduino.cc/en/Reference/EEPROM
- get temp to work
- get hall sensor to work

 */
