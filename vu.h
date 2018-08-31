
/************************************************************
 *                                                          *
 *  vu.h      Includes for  vu meter project                *
 *                                                          *
 *                                                          *
 ************************************************************/
 
#include <SPI.h>

#include <stdint.h>
#include <TouchScreen.h>
#include "Adafruit_GFX.h"
#include "Adafruit_HX8357.h"

// These are 'flexible' lines that can be changed

#define TFT_CS 10     // tft chip select
#define TFT_DC 9      // DC
#define TFT_RST 8 // RST can be set to -1 if you tie it to Arduino's reset

#ifndef VU_H

#define VU_H

extern word ConvertRGB(byte R, byte G, byte B);

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC

Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, TFT_RST);

#define RED HX8357_RED
#define GREEN HX8357_GREEN
#define BLUE HX8357_BLUE
#define WHITE HX8357_WHITE
#define BLACK HX8357_BLACK
#define CYAN HX8357_CYAN
#define YELLOW HX8357_YELLOW
#define ORANGE ConvertRGB(0xFF,0xA5, 0x00)
#define DARKORANGE ConvertRGB(0xFF, 0x8C, 0x00);
#define VIOLET ConvertRGB(255, 0, 255)
#define GREY HX8357_GREY
#define BROWN HX8357_BROWN


// #define DEBUG


// These are the four touchscreen analog pins
#define YP A2  // must be an analog pin, use "An" notation!
#define XM A3  // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 8   // can be a digital pin

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 110
#define TS_MINY 80
#define TS_MAXX 900
#define TS_MAXY 940

#define MINPRESSURE 10
#define MAXPRESSURE 1000

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300); //init TouchScreen port pins

#define DISPLAY_WIDTH 480
#define DISPLAY_HEIGHT 320

#define TRUE 1
#define FALSE 0

// Globals - Yes, they are to be avoided, but they make life a bit easier now and then.
const int analogInPin0 = A4;  // Analog input pin that the potentiometer is attached to
const int analogInPin1 = A5;  // Analog input pin that the potentiometer is attached to

const int analogOutPin = LED_BUILTIN; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)
int sensorValue1 = 0;        // value read from the pot
int outputValue1 = 0;        // value output to the PWM (analog out)

// default colors. Compiled in to save variable space.
#define WARNING     YELLOW
#define OVERLOAD    RED
#define BACKGROUND_COLOR  BLACK

unsigned int background_color = BLACK;

struct colorpallet {
  unsigned int text = WHITE;
  unsigned int background = BLACK;
  unsigned int border = CYAN;
  unsigned int meter1 = CYAN;
  unsigned int meter2 = GREEN;
  unsigned int warning = YELLOW;
  unsigned int overload = RED;
  unsigned int button = ORANGE;
  unsigned int button_border = DARKORANGE;
  unsigned int button_text = BLACK;
} colors;

// default spacings. Could be variables, but are not
#define GAP 2

#endif
