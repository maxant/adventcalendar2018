#include <rgbled.h>
#include "src/filesystem/filesystem.h"

void setup(){
  Serial.begin(115200);
  initCard();

RgbLed onboardLed = RgbLed(4, 2, 0);
onboardLed.write(254, Led::OFF, Led::OFF);

//deleteFile(SD, "/data/log.txt");
  createDir(SD, "/data");
  listDir(SD, "/", 10);

  appendToFileAndClose(SD, "/data/log.txt", "restart\n");
  /*
  File file = SD.open("/data/log.txt");
  if(file){
    char current = file.read();
    while(current > -1) {
        Serial.write(current);
    }
    file.close();
    Serial.println("done");
  }
  */
  File file = SD.open("/data/log.txt");
  Serial.println("opened");
  while(file.available()){
      Serial.write(file.read());
  }
  file.close();

}

void initCard() {
    if(!SD.begin()){
        Serial.println("Card Mount Failed");
        return;
    }
    uint8_t cardType = SD.cardType();
    if(cardType == CARD_NONE){
        Serial.println("No SD card attached");
        return;
    }

    Serial.print("SD Card Type: ");
    if(cardType == CARD_MMC){
        Serial.println("MMC");
    } else if(cardType == CARD_SD){
        Serial.println("SDSC");
    } else if(cardType == CARD_SDHC){
        Serial.println("SDHC");
    } else {
        Serial.println("UNKNOWN");
    }

    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    Serial.printf("SD Card Size: %lluMB\n", cardSize);
    Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
    Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));

}

void loop(){
  Serial.println("in loop");
  delay(1000);
}
