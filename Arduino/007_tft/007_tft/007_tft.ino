/***************************************************
  This is our GFX example for the Adafruit ILI9341 Breakout and Shield
  ----> http://www.adafruit.com/products/1651

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

//https://github.com/adafruit/Adafruit_ILI9341/blob/master/examples/graphicstest/graphicstest.ino

#include "SPI.h"

//https://github.com/adafruit/Adafruit-GFX-Library
#include "Adafruit_GFX.h"

//https://github.com/adafruit/Adafruit_ILI9341
#include "Adafruit_ILI9341.h"

//https://github.com/adafruit/Adafruit_TouchScreen/blob/master/examples/touchscreendemoshield/touchscreendemoshield.ino
#include <stdint.h>
#include "TouchScreen.h"

// http://pub.ucpros.com/download/tft_320_240_mi0283qt_9a_v1_3_spec.pdf
// https://www.watterott.com/media/files_public/dwqfttfjoim/MI0283QT-9A_Datasheet.pdf
// https://github.com/watterott/RPi-Display/blob/master/hardware/RPi-Display_v10.pdf
// asked here: https://arduino.stackexchange.com/questions/60441/connecting-tft-display-mi0283qt-9a-to-esp32
#define _DC_WR      12 // WR   X 
#define _CLK_RS_SCL 18 // RS   X (G6EJD uses nomenclature SCK/CLK)
#define _CS_CS      15 // CS   X chip select
#define _MOSI_SDI   23 // SDI  X
#define _RST_RST    14 // RST  X (G6EJD says ESP RST to TFT RESET. but he has it on pin 13! SO says plug it into pin of own choice)
#define _MISO_SDO   19 // SDO  X (G6EJD says not connected => but it IS!)
//#define _RD         98 // read enable? no idea what it is. no one talks about using it. in rpiv10 this pin goes to ground!
//#define _TCS        99 // TCS ???
//LED-K - Connected to the backlight circuit and further connected to the GPIO pin of the microntroller, so it can be toggled from the code.
//LED-A - Connected to the voltage of the system (VCC-SYS) on which the TFT proto board is connected (3.3V - 5V).
//
// TFT Pin36: WRX//D/CX) Write execution control pin ; Serial Register select s Signal; rpiv10Pdf: WR/D/CX     => this is the WR pin on the TFT board
// TFT Pin37: D/CX(SCL)  Register select signal; Serial Interface Clock;                rpiv10Pdf: SCK;D/CX/SCL => none of those names are on TFT board. but we do have RS = Register Select!
//
// note 1:
//
// not using Data pins => leaves:
// - 0101 3 wire 9 bit serial interface I:  SCL, SDA, CSX
// - 0110 4 wire 8 bit serial interface I:  SCL, SDA, D/CX, CSX
// - 1101 3 wire 9 bit serial interface II: SCL, SDI, SDO, CSX
// - 1110 4 wire 8 bit serial interface II: SCL, SDI, D/CX, SDO, CSX 
// i'd bet we're using the last one, as all are used. altho G6EJD says we don't use SDO, but that isnt an option in note 1. SDA is pin 21 on ESP32, but that seems to be related to I2C not SPI.
// although, according to rpiv10 pdf, SDA is SDI
// anyway... we need to connect SCL(RS), SDI, DC(WR), SDO, CS => connect them to ADC I/O pins, and configure above
//
// working with:
// tft -> esp32
// --------------------------
// gnd -> gnd
// v33 -> v33
// rs  -> 18  spi HW and this is the serial clock
// sdo -> 19  spi HW miso
// rst -> 14
// im2 -> v33
// im0 -> gnd
// ledk-> output of poti. inputs to poti are gnd and v33, make sure they are the right way round
// leda-> v33
// im3 -> v33
// im1 -> v33
// sdi -> 23  spi HW mosi
// wr  -> 12
// cs  -> 15
//
// just found this: https://learn.adafruit.com/adafruit-2-4-color-tft-touchscreen-breakout/pinouts
//
// TODO how to make sd card work with display at same time? chip select call before doing something?? could be as simple as pin5 is chip select for SD, and cs is 15 for led.
// TODO how to make touch work? https://learn.adafruit.com/adafruit-2-4-color-tft-touchscreen-breakout/resistive-touchscreen
// TODO fonts and other stuff: https://learn.adafruit.com/adafruit-gfx-graphics-library/using-fonts
//

// TOUCH
#define YP 33 // must be analog in
#define XM 27 //must be analog in
#define YM 16 // can be a digital pin
#define XP 17 // can be a digital pin
#define TS_MINX 150
#define TS_MINY 130
#define TS_MAXX 3800
#define TS_MAXY 4000

// UART
#include <HardwareSerial.h>
HardwareSerial gpsSerial(1);

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 1500 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 1500);

// using software spi
Adafruit_ILI9341 tft = Adafruit_ILI9341(_CS_CS, _DC_WR, _MOSI_SDI, _CLK_RS_SCL, _RST_RST, _MISO_SDO);

void setup() {

  gpsSerial.begin(115200, SERIAL_8N1, 3, 1); //Baud rate, parity mode, RX, TX
 
  Serial.begin(115200);
  Serial.println("ILI9341 Test!"); 
  tft.begin();

  // read diagnostics (optional but can help debug problems)
  uint8_t x = tft.readcommand8(ILI9341_RDMODE);
  Serial.print("Display Power Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDMADCTL);
  Serial.print("MADCTL Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDPIXFMT);
  Serial.print("Pixel Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDIMGFMT);
  Serial.print("Image Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDSELFDIAG);
  Serial.print("Self Diagnostic: 0x"); Serial.println(x, HEX); 
  
  Serial.println(F("Benchmark                Time (microseconds)"));
  delay(10);
  Serial.print(F("Screen fill              "));
  Serial.println(testFillScreen());
  delay(500);

return; // skip tests and checkout touch
  Serial.print(F("Text                     "));
  Serial.println(testText());
  delay(3000);

  Serial.print(F("Lines                    "));
  Serial.println(testLines(ILI9341_CYAN));
  delay(500);

  Serial.print(F("Horiz/Vert Lines         "));
  Serial.println(testFastLines(ILI9341_RED, ILI9341_BLUE));
  delay(500);

  Serial.print(F("Rectangles (outline)     "));
  Serial.println(testRects(ILI9341_GREEN));
  delay(500);

  Serial.print(F("Rectangles (filled)      "));
  Serial.println(testFilledRects(ILI9341_YELLOW, ILI9341_MAGENTA));
  delay(500);

  Serial.print(F("Circles (filled)         "));
  Serial.println(testFilledCircles(10, ILI9341_MAGENTA));

  Serial.print(F("Circles (outline)        "));
  Serial.println(testCircles(10, ILI9341_WHITE));
  delay(500);

  Serial.print(F("Triangles (outline)      "));
  Serial.println(testTriangles());
  delay(500);

  Serial.print(F("Triangles (filled)       "));
  Serial.println(testFilledTriangles());
  delay(500);

  Serial.print(F("Rounded rects (outline)  "));
  Serial.println(testRoundRects());
  delay(500);

  Serial.print(F("Rounded rects (filled)   "));
  Serial.println(testFilledRoundRects());
  delay(500);

  Serial.println(F("Done!"));

}

uint8_t rotation = 0;

void loop(void) {
  if(rotation >= 4) rotation = 0;
  tft.setRotation(rotation++);
  testText();

  // a point object holds x y and z coordinates
  TSPoint p = ts.getPoint();
  
  // pressure of 0 means no pressing!
  if (p.z != 0) {

    Serial.print("X = "); Serial.print(p.x);
    Serial.print("\tY = "); Serial.print(p.y);
    Serial.print("\tPressure = "); Serial.println(p.z);

/*    p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());
     
    Serial.print("X = "); Serial.print(p.x);
    Serial.print("\tY = "); Serial.print(p.y);
    Serial.print("\tPressure = "); Serial.println(p.z);
TODO why does it wait so long? is it just because drawing and delay takes so long? how to make faster? read from buffer??? see other lib with 
21:13:21.410 -> X = 203  Y = 349 Pressure = 244         => near gnd/v33
21:13:26.458 -> X = -2004 Y = 591 Pressure = -15130     => clockwise 90%
21:13:29.787 -> X = -1976 Y = -2456 Pressure = -14488   => clockwise 90%
21:13:33.139 -> X = 273 Y = -2280 Pressure = 436        => clockwise 90%
21:13:36.492 -> X = -897  Y = -511  Pressure = -2072    => centre

*/

  }

Serial.println("a");
Serial.println(gpsSerial.available());
  if (gpsSerial.available() > 0) { // see https://github.com/DzikuVx/esp32_gps_thingy/blob/master/gps_logger.ino
    Serial.write(gpsSerial.read());
    Serial.flush();
  }
Serial.println("a");


  delay(250);
}

unsigned long testFillScreen() {
  unsigned long start = micros();
  tft.fillScreen(ILI9341_BLACK);
  yield();
  tft.fillScreen(ILI9341_RED);
  yield();
  tft.fillScreen(ILI9341_GREEN);
  yield();
  tft.fillScreen(ILI9341_BLUE);
  yield();
  tft.fillScreen(ILI9341_BLACK);
  yield();
  return micros() - start;
}

unsigned long testText() {
  tft.fillScreen(ILI9341_BLACK);
  unsigned long start = micros();
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(ILI9341_YELLOW); tft.setTextSize(2);
  tft.println(1234.56);
  tft.setTextColor(ILI9341_RED);    tft.setTextSize(3);
  tft.println(0xDEADBEEF, HEX);
  tft.println();
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(5);
  tft.println("Groop");
  tft.setTextSize(2);
  tft.println("I implore thee,");
  tft.setTextSize(1);
  tft.println("my foonting turlingdromes.");
  tft.println("And hooptiously drangle me");
  tft.println("with crinkly bindlewurdles,");
  tft.println("Or I will rend thee");
  tft.println("in the gobberwarts");
  tft.println("with my blurglecruncheon,");
  tft.println("see if I don't!");
  return micros() - start;
}

unsigned long testLines(uint16_t color) {
  unsigned long start, t;
  int           x1, y1, x2, y2,
                w = tft.width(),
                h = tft.height();

  tft.fillScreen(ILI9341_BLACK);
  yield();
  
  x1 = y1 = 0;
  y2    = h - 1;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
  t     = micros() - start; // fillScreen doesn't count against timing

  yield();
  tft.fillScreen(ILI9341_BLACK);
  yield();

  x1    = w - 1;
  y1    = 0;
  y2    = h - 1;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;

  yield();
  tft.fillScreen(ILI9341_BLACK);
  yield();

  x1    = 0;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;

  yield();
  tft.fillScreen(ILI9341_BLACK);
  yield();

  x1    = w - 1;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);

  yield();
  return micros() - start;
}

unsigned long testFastLines(uint16_t color1, uint16_t color2) {
  unsigned long start;
  int           x, y, w = tft.width(), h = tft.height();

  tft.fillScreen(ILI9341_BLACK);
  start = micros();
  for(y=0; y<h; y+=5) tft.drawFastHLine(0, y, w, color1);
  for(x=0; x<w; x+=5) tft.drawFastVLine(x, 0, h, color2);

  return micros() - start;
}

unsigned long testRects(uint16_t color) {
  unsigned long start;
  int           n, i, i2,
                cx = tft.width()  / 2,
                cy = tft.height() / 2;

  tft.fillScreen(ILI9341_BLACK);
  n     = min(tft.width(), tft.height());
  start = micros();
  for(i=2; i<n; i+=6) {
    i2 = i / 2;
    tft.drawRect(cx-i2, cy-i2, i, i, color);
  }

  return micros() - start;
}

unsigned long testFilledRects(uint16_t color1, uint16_t color2) {
  unsigned long start, t = 0;
  int           n, i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9341_BLACK);
  n = min(tft.width(), tft.height());
  for(i=n; i>0; i-=6) {
    i2    = i / 2;
    start = micros();
    tft.fillRect(cx-i2, cy-i2, i, i, color1);
    t    += micros() - start;
    // Outlines are not included in timing results
    tft.drawRect(cx-i2, cy-i2, i, i, color2);
    yield();
  }

  return t;
}

unsigned long testFilledCircles(uint8_t radius, uint16_t color) {
  unsigned long start;
  int x, y, w = tft.width(), h = tft.height(), r2 = radius * 2;

  tft.fillScreen(ILI9341_BLACK);
  start = micros();
  for(x=radius; x<w; x+=r2) {
    for(y=radius; y<h; y+=r2) {
      tft.fillCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}

unsigned long testCircles(uint8_t radius, uint16_t color) {
  unsigned long start;
  int           x, y, r2 = radius * 2,
                w = tft.width()  + radius,
                h = tft.height() + radius;

  // Screen is not cleared for this one -- this is
  // intentional and does not affect the reported time.
  start = micros();
  for(x=0; x<w; x+=r2) {
    for(y=0; y<h; y+=r2) {
      tft.drawCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}

unsigned long testTriangles() {
  unsigned long start;
  int           n, i, cx = tft.width()  / 2 - 1,
                      cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9341_BLACK);
  n     = min(cx, cy);
  start = micros();
  for(i=0; i<n; i+=5) {
    tft.drawTriangle(
      cx    , cy - i, // peak
      cx - i, cy + i, // bottom left
      cx + i, cy + i, // bottom right
      tft.color565(i, i, i));
  }

  return micros() - start;
}

unsigned long testFilledTriangles() {
  unsigned long start, t = 0;
  int           i, cx = tft.width()  / 2 - 1,
                   cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9341_BLACK);
  start = micros();
  for(i=min(cx,cy); i>10; i-=5) {
    start = micros();
    tft.fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      tft.color565(0, i*10, i*10));
    t += micros() - start;
    tft.drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      tft.color565(i*10, i*10, 0));
    yield();
  }

  return t;
}

unsigned long testRoundRects() {
  unsigned long start;
  int           w, i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9341_BLACK);
  w     = min(tft.width(), tft.height());
  start = micros();
  for(i=0; i<w; i+=6) {
    i2 = i / 2;
    tft.drawRoundRect(cx-i2, cy-i2, i, i, i/8, tft.color565(i, 0, 0));
  }

  return micros() - start;
}

unsigned long testFilledRoundRects() {
  unsigned long start;
  int           i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9341_BLACK);
  start = micros();
  for(i=min(tft.width(), tft.height()); i>20; i-=6) {
    i2 = i / 2;
    tft.fillRoundRect(cx-i2, cy-i2, i, i, i/8, tft.color565(0, i, 0));
    yield();
  }

  return micros() - start;
}
