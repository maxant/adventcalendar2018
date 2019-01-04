#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

#include <IRremote.h>

#include <rgbled.h>
#include "src/passwords.h"

#ifdef __cplusplus
extern "C" {
#endif
uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif
uint8_t temprature_sens_read();

RgbLed onboardLed = RgbLed(4, 2, 0);
const int PORT = 80;
const int pinLedOut = 22;
const int pinVarResistorIn = 35;
const int pinAdcIn = 36;
const int pinButtonIn = 18;

// infrared 
const int pinIrRecv = 21;
const int pinIrSend = 17;
IRrecv irrecv(pinIrRecv);
decode_results results;
//IRsend irsend(pinIrSend);

int onboardLedState = 240;
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
  pinMode(pinAdcIn, INPUT);
  pinMode(pinLedOut, OUTPUT);
  pinMode(pinButtonIn, INPUT_PULLUP);

  // IR receiver
  pinMode(pinIrRecv, INPUT);
  irrecv.enableIRIn();
}

void loop(void) {

  {
    unsigned int rawCodes[RAWBUF];
    int codeLen = 32;
    rawCodes[0] = 1;
    //irsend.sendRaw(rawCodes, codeLen, 38); //assume 38KHz
  }
  
  if (irrecv.decode(&results)) {
    Serial.printf("ir received\n");
    Serial.println(results.value, HEX); //eg 68733A46
    //Serial.println(results->value); as a number eg 1752382022
    //handleIrResults(&results);
    irrecv.resume();
  }

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

  onboardLedState++; // += 2;
  if(onboardLedState > 256) onboardLedState = 240;
  onboardLed.write(Led::OFF, Led::OFF, onboardLedState);

  delay(200);
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
  int voltage = analogRead(pinAdcIn);
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
                <p>voltage: %09d</p>\
              </body>\
            </html>"
            ,val, ledOn, h, t, voltage);
  server.send(200, "text/html", temp);
}

void handleIrResults(decode_results *results) {
  char buf[10];
  String cType = "";
  String IRcommand = "";

  int codeType = results->decode_type;
  int codeLen = results->rawlen - 1;
  unsigned int rawCodes[RAWBUF]; // The durations
  // To store raw codes:
  // Drop first value (gap)
  // Convert from ticks to microseconds
  // Tweak marks shorter, and spaces longer to cancel out IR receiver distortion
  for (int i = 1; i <= codeLen; i++) {
    if (i % 2) {
      // Mark
      rawCodes[i - 1] = results->rawbuf[i] * USECPERTICK - MARK_EXCESS;
      //Serial.print(" m");
    }
    else {
      // Space
      rawCodes[i - 1] = results->rawbuf[i] * USECPERTICK + MARK_EXCESS;
      //Serial.print(" s");
    }
    //Serial.print(rawCodes[i - 1], DEC);
  }

  unsigned long codeValue = results->value;
  codeLen = results->bits;
  Serial.println(results->value, HEX);
  Serial.println(results->bits);
  Serial.println(codeType);
  Serial.println(results->value);
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
