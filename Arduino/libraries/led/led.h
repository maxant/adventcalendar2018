/*
  https://www.arduino.cc/en/Hacking/LibraryTutorial
  led.h - Library for controling leds more easily.
  Created by Ant.
*/
#ifndef led_h
#define led_h

#include "Arduino.h"

class Led
{
  public:
    Led(int pin, int frequency = 5000, int resolution = 8);
    void write(int value);
    void off();
    static const int OFF = 256;
  private:
    int _pin;
    int _ledChannel;
};

#endif
