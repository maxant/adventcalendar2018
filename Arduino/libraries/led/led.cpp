#include "Arduino.h"
#include "led.h"

Led::Led(int pin, int frequency, int resolution)
{
  _ledChannel = pin; // just reuse it
  _pin = pin;
  ledcSetup(_ledChannel, frequency, resolution);
  ledcAttachPin(_pin, _ledChannel);
}

void Led::write(int value)
{
  ledcWrite(_ledChannel, value);
}

void Led::off()
{
    this->write(OFF);
}

