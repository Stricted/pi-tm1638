/**
 *
 * @file 
 * @brief   Digital clock for TM1638 based displays
 * @author  Martin Oldfield <ex-tm1638@mjo.tc>
 * @version 0.1
 *
 * @section DESCRIPTION
 *
 * A simple digital clock
 *
 * @section HARDWARE
 *
 * The code hard wires pin connections:
 *
 *    * data: wiringPi 8 = GPIO 2 = PIN 3
 *    * clock: wiringPi 9 = GPIO 3 = PIN 5
 *    * strobe: wiringPi 7 = GPIO 4 = PIN 7
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 */

/** @cond NEVER */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

#include <wiringPi.h>
#include <tm1638.h>

int main(int argc, char *argv[])
{
  tm1638_p t;

  if (wiringPiSetup() == -1) {
      printf("Unable to initialize wiringPi library\n");
      return -1;
  }

  t = tm1638_alloc(8, 9, 7);
  if (!t)
    {
      printf("Unable to allocate TM1638\n");
      return -2;
    }

  while(1)
    {
      time_t now    = time(NULL);
      struct tm *tm = localtime(&now);

      char text[10];
      snprintf(text, 9, "%02d %02d %02d", tm->tm_hour, tm->tm_min, tm->tm_sec);

      tm1638_set_7seg_text(t, text, 0);
      delay(100);
    }

  tm1638_free(&t);

  return 0;
}
