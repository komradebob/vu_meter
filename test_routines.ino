#include "vu.h"


unsigned long testFillScreen() {
  unsigned long start = micros();
  tft.fillScreen(RED);
  tft.fillScreen(ORANGE);
  tft.fillScreen(YELLOW);
  tft.fillScreen(GREEN);
  tft.fillScreen(BLUE);
  tft.fillScreen(VIOLET);
  tft.fillScreen(WHITE);
  return micros() - start;
}

// Convert 3 bytes of RGB to 565 code
word ConvertRGB( byte R, byte G, byte B)
{
  return ( ((R & 0xF8) << 8) | ((G & 0xFC) << 3) | (B >> 3) );
}



