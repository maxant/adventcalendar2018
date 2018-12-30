/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 27
 * LCD Enable pin to digital pin 14
 * LCD D4 pin to digital pin 22
 * LCD D5 pin to digital pin 21
 * LCD D6 pin to digital pin 17
 * LCD D7 pin to digital pin 16
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * LCD led 16 => gnd
 * LCD led 15 => 26 (DAC2 set to 240)
 * LCD VO pin (pin 3, contrast) => 25 (DAC1 set to ??)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 27, en = 14, d4 = 22, d5 = 21, d6 = 17, d7 = 16;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(115200);

  lcd.begin(16, 2);

  // set onboard led
  analogWrite(4, 256); // R, off
  analogWrite(2, 256); // G, off
  analogWrite(0, 255); // B

  dacWrite(26, 240); // lcd backlight
  dacWrite(25, 20); // lcd contrast - not working :-( https://arduino.stackexchange.com/questions/60006/unable-to-set-lcd-contrast-using-dac-pin-on-esp32

  pinMode(25, INPUT);

}
uint i = 0;
void loop() {
  lcd.setCursor(0, 0);
  lcd.printf("%7.1f", millis() / 1000.0);
  lcd.setCursor(10, 1);
  lcd.print("fdsa");

  delay(1000);

  i += 10;
  if(i > 256) i = 0;
  Serial.println(i);
  dacWrite(25, i); // lcd backlight

}

// uses pwm to write analog voltage at 5000 hz. works for LEDs. doesnt seem to work for lcd contrast.
void analogWrite(int pin, int value) {
  int ch = pin; // has to be unique channel? just use pin number
  ledcSetup(ch, 5000, 8);
  ledcAttachPin(pin, ch);
  ledcWrite(ch, value);
}
