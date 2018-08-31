/***************************************************

   vu_meter3

   Crude vu meter

 ****************************************************/

#include "vu.h"

void setup() {

    tft.begin(HX8357D);

#ifdef DEBUG
  Serial.begin(9600);
  Serial.println("HX8357D Test!");
#endif

  // read diagnostics (optional but can help debug problems)
  uint8_t x = tft.readcommand8(HX8357_RDPOWMODE);
  Serial.print("Display Power Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(HX8357_RDMADCTL);
  Serial.print("MADCTL Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(HX8357_RDCOLMOD);
  Serial.print("Pixel Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(HX8357_RDDIM);
  Serial.print("Image Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(HX8357_RDDSDR);
  Serial.print("Self Diagnostic: 0x"); Serial.println(x, HEX);

  Serial.println(F("Benchmark                Time (microseconds)"));

  tft.setRotation(0);

  testFillScreen();
  tft.fillScreen(colors.background);

}


////////////////////////////////////////////////// main


void loop()
{
  unsigned int i, j, basex, basey, height, width;
  byte r, g, b;
  int rvalue, rvalue1, color, prev_level, prev_level1;
  char str[20], str2[20];
  prev_level = 0;
  prev_level1 = 0;
  basex = 50;
  basey = 15;
  height = 30;
  width = 405;



  tft.setRotation(1);
  tft.setCursor(10, 20);
  tft.setTextColor(WHITE, BLACK);  tft.setTextSize(2);
  tft.println("FWD");

  tft.setCursor(10, 60);

  tft.println("REV");

  tft.setTextColor(colors.text, colors.background);  tft.setTextSize(2);

  tft.drawRect(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, colors.border);

  while (TRUE) {
                                                  // read the analog in value:
    sensorValue = analogRead(analogInPin0);
    sensorValue1 = analogRead(analogInPin1);
                                                 // map it to the range of the analog out:
    outputValue = constrain(map(sensorValue, 0, 1023, 0, width), 1, width - GAP * 2);
    outputValue1 = constrain(map(sensorValue1, 0, 1023, 0, width), 1, width - GAP * 2);

    TSPoint p = ts.getPoint();

    rvalue = bargraph(basex, basey, height, width, colors.meter1, TRUE, outputValue, prev_level);
    rvalue1 = bargraph(basex, basey + height + 10, height, width, colors.meter2, TRUE, outputValue1, prev_level1);

#ifdef DEBUG
    tft.setRotation(1);
    tft.setCursor(10, 100);
    tft.print(outputValue);
    tft.setCursor(60, 100);
    tft.print(outputValue1);
    tft.setCursor(200, 100);
    tft.print(p.x);
    tft.setCursor(250, 100);
    tft.print(p.y);
    tft.setCursor(300, 100);
    tft.print(p.z);
#endif

    prev_level = outputValue;
    prev_level1 = outputValue1;
  }

}


