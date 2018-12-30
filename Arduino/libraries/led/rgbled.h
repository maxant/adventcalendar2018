/*
  ledrgb.h - Library for controling RGB leds more easily.
  Created by Ant.
*/
#ifndef rgbled_h
#define rgbled_h

#include "Arduino.h"
#include "led.h"

class RgbLed
{
  public:
    RgbLed(int pinRed, int pinGreen, int pinBlue);
    void write(int red, int green, int blue);
    void off();
  private:
    Led _red;
    Led _green;
    Led _blue;
};

#endif
