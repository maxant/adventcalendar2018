
int freqR = 5000;
int ledChannelR = 0;
int resolutionR = 8;
int freqG = 5000;
int ledChannelG = 1;
int resolutionG = 8;
int freqB = 5000;
int ledChannelB = 2;
int resolutionB = 8;

void setup() {

  Serial.begin(115200);

  ledcSetup(ledChannelR, freqR, resolutionR);
  ledcAttachPin(4, ledChannelR);
  ledcSetup(ledChannelG, freqG, resolutionG);
  ledcAttachPin(2, ledChannelG);
  ledcSetup(ledChannelB, freqB, resolutionB);
  ledcAttachPin(0, ledChannelB);

// 0 is on, 1 is off
/*
pinMode(4, OUTPUT); //red
digitalWrite(4, 0);
pinMode(2, OUTPUT); //green
digitalWrite(2, 1);
pinMode(0, OUTPUT); //blue
digitalWrite(0, 0);
*/
}

void loop() {

  // 256 if off
  ledcWrite(ledChannelR, 254);
  ledcWrite(ledChannelG, 256);
  ledcWrite(ledChannelB, 250);
  
/*);
    Serial.println(dutyCycle);
    delay(10);
  }
 
  for (int dutyCycle = 255; dutyCycle >= 0; dutyCycle--) {
//    ledcWrite(ledChannel1, dutyCycle);
//    Serial.println(dutyCycle);
    ledcWrite(ledChannel2, dutyCycle);
    delay(10);
  }
*/

}
