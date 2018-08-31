/* ****************************************************************
 * barcode.c
 *                                                                
 * Display a bar graph on the LCD
 *
 * History
 * 
 * Who  When      What
 * rmb  8/29/18   First commit. 
 * rmb  8/30/18   Final tidy before closing and forking to amp controller
 * 
 */

#include "vu.h"


int bargraph(unsigned int bx, unsigned int by, unsigned int height, unsigned int width, unsigned int color, bool border, unsigned int level, unsigned int prev_level)
{
  int i, warning_level, overload_level;

  warning_level = width * .66;
  overload_level = width * .8;

  tft.setRotation(1);

  if (border == TRUE)                                             // If called for ...
    tft.drawRect(bx, by, width, height, color);               // draw the outline

  if (level == prev_level)
    return (0);

  if ((level > width))
    return (-1);
  else if ((bx + width) >= DISPLAY_WIDTH)
    return (-2);
  else if ((by + height) >= DISPLAY_HEIGHT)
    return (-3);


  if (level < prev_level) {                                  // went down
    tft.fillRect(bx + GAP + level, by + GAP, width - level - (GAP * 2), height - (GAP * 2), background_color); // blank out the rest
    return (0);
  }
  else if (level <= warning_level) {                            // all green
    tft.fillRect(bx + GAP, by + GAP, level, height - (GAP * 2 ), color);
    tft.fillRect(bx + level + GAP, by + GAP, width - level - (GAP * 2), height - (GAP * 2), background_color); // blank out the rest
    return (1);
  }
  else if (level <= overload_level) {                           // base color+warning
    tft.fillRect(bx + GAP, by + GAP, warning_level - 1, height - (GAP * 2), color);      // fill up the base
    tft.fillRect(bx + GAP + warning_level, by + GAP, level - warning_level -1, height - (GAP * 2), WARNING);       // fill up the warning
    tft.fillRect(bx + GAP + level, by + GAP, width - level - (GAP * 2), height - (GAP * 2), background_color); // blank out the rest
    return (2);
  }
  else if ( level > overload_level ) {
    tft.fillRect(bx + GAP, by + GAP, warning_level-1, height - (GAP * 2), color);       // fill up the base
    tft.fillRect(bx + GAP + warning_level, by + GAP, overload_level - warning_level-1, height - (GAP * 2), WARNING);     // fill up the warning
    tft.fillRect(bx + GAP + overload_level, by + GAP, level - overload_level , height - (GAP * 2), OVERLOAD);     // fill up the overload
    if((width - level - (GAP * 2)) > 1) 
      tft.fillRect(bx + GAP + level, by + GAP, width - level - (GAP * 2), height - (GAP * 2), background_color); // blank out the rest
    return (3);
  }

  return (-4); // go back to text mode

}

