#include "Arduino.h"
#include "rgbled.h"
#include "led.h"

RgbLed::RgbLed(int pinRed, int pinGreen, int pinBlue) : 
  // https://isocpp.org/wiki/faq/ctors#init-lists
  _red(pinRed), _green(pinGreen), _blue(pinBlue)
{
}

void RgbLed::write(int r, int g, int b)
{
  _red.write(r);
  _green.write(g);
  _blue.write(b);
}

void RgbLed::off()
{
    this->write(Led::OFF, Led::OFF, Led::OFF);
}

