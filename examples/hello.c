/**
 *
 * @file 
 * @brief   Hello World for TM1638 based displays
 * @author  Martin Oldfield <ex-tm1638@mjo.tc>
 * @version 0.1
 *
 * @section DESCRIPTION
 *
 * A simple "Hello World" example program for the TM1638.
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

#include <wiringPi.h>
#include <tm1638.h>

static void knight_rider(tm1638_p t, int n);
static void flashy(tm1638_p t);

int main(int argc, char *argv[]) {
	tm1638_p t;

	if (wiringPiSetup() == -1) {
		printf("Unable to initialize wiringPi library\n");
		return -1;
	}

	t = tm1638_alloc(8, 9, 7);
	if (!t) {
		printf("Unable to allocate TM1638\n");
		return -2;
	}

	tm1638_set_7seg_text(t, "Hello !", 0x00);
	delay(5000);

	tm1638_send_cls(t);

	knight_rider(t,2);

	tm1638_send_cls(t);

	flashy(t);

	tm1638_send_cls(t);

	knight_rider(t,2);

	tm1638_send_cls(t);

	tm1638_set_7seg_text(t, "Goodbye!", 0x00);

	tm1638_free(&t);

	return 0;
}

static void knight_rider(tm1638_p t, int n) {
	for(int i = 0; i < n; i++) 	{
		for(int j = 0; j < 8; j++) {
			uint8_t m = 128 >> j;
			tm1638_set_8leds(t, m);
			tm1638_set_7seg_text(t, "", m);
			delay(25);
		}

		for(int j = 0; j < 8; j++) {
			uint8_t m = 1 << j;
			tm1638_set_8leds(t, m);
			tm1638_set_7seg_text(t, "", m);
			delay(25);
		}
	}
}

static void flashy(tm1638_p t) {
	uint8_t red = 0;

	for(int i = 0; i < 8; i++) {
		uint8_t mask = (128 >> i);

		tm1638_set_8leds(t, mask);

		for(int j = 0; j < 8; j++) {
			tm1638_set_7seg_raw(t, i, (1 << j));
			delay(50);
		}

		red |= mask;
		tm1638_set_8leds(t, red);
	}
}


/** @endcond */
