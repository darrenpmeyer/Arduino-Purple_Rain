/* Copyright (C) 2016 Darren P Meyer, LGPL 2.1 (see bottom) */
#include <FastLED.h> // see http://fastled.io; uses branch FastLED3.1

// Configure LED driver
#define DATA_PIN 1        // digital pin used for LED strip/ring data line
#define LED_COUNT 12      // how many LEDs in the strip/ring
#define DRIVER NEOPIXEL   // which FastLED driver to use

// Configure behavior
#define DECAY_DELAY 20    // delay between each tick
#define BRIGHT_BASE 128   // minimum brightness for a fresh drop
#define BRIGHT_ADD 127    // add this to above for maximum brightness of a fresh drop
#define CHANCE_OF_DROP 10 // the percent chance a dark drop will become fresh
#define DIM_RATE 8        // max amount to dim on each tick

// global variables
CRGB led[LED_COUNT];     // Addresses the pixels via FastLED, must be RGB space
CHSV drops[LED_COUNT];   // Addresses the colors using HSV space; must map to led[] to display


/* seed_drop() - a rain drop "hits" a pixel
 * note that this function doesn't specify which pixel, that's on you
 */
CHSV seed_drop() {
    CHSV drop = CHSV(HUE_PURPLE, 255, random8(BRIGHT_BASE)+BRIGHT_ADD);
    return(drop);
}

/* In the Arduino setup phase, configure the driver, seed the first drops, and
 * show a black strip
 */
void setup() {
    delay(250);  // on some boards, this _really_ helps with catching the reset for re-programming

    // Add LEDs, set the color correction profile, and set all pixels black
    FastLED.addLeds<DRIVER, DATA_PIN>(led, LED_COUNT).setCorrection(TypicalLEDStrip);
    fill_solid(led, LED_COUNT, CRGB::Black);

    // Seed first rain drops
    uint8_t numdrops = random8(LED_COUNT / 2 * 3);
    for (uint8_t i = 0; i < numdrops; i++) {
        drops[i] = seed_drop();
    }
    FastLED.show(); // this will show all black, because led[] is still all black
}


/* In the Arduino loop phase, each tick dims bright drops and has a chance to
 * make fresh drops out of dim/dark pixels
 */
void loop() {
    for (uint8_t i = 0; i < LED_COUNT; i++) {
        // if the drops are very dim or off, there's a chance to make them fresh drops on this tick
        if (drops[i].v <= 10) {
            if (random8(100) < CHANCE_OF_DROP) {
                drops[i] = seed_drop();
            }
        }

        // if they are lit *at all*, dim them by 0..DIM_RATE
        if (drops[i].v > 0) {
            drops[i].v = drops[i].v-random8(DIM_RATE);
        }

        led[i] = drops[i]; // Map to CRGB space for display
        /* TODO: use a FastLED fade function
         * the fade functions can work on RGB space, avoid mapping, and that
         * would improve performance and shrink the compiled sketch (proabably)
         */
    }

    // Show, then wait for next tick. Personal preference, you could reverse these
    FastLED.show();
    FastLED.delay(DECAY_DELAY);
}

/*
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
    USA
*/