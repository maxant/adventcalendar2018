#include <rgbled.h>

void setup() {
  RgbLed(4, 2, 0).write(256, 256, 250);
  Serial.begin(115200);

  for(int i = 32; i < 40; i++) {
    pinMode(i, INPUT);
  }
}

void loop() {
  Serial.printf("\n");
  for(int i = 32; i < 40; i++) {
    Serial.printf("%02d: %09d\t\n", i, analogRead(i));
  }
  delay(2000);
}
