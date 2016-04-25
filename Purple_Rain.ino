#include <FastLED.h>
#undef DEBUG

#ifdef DEBUG
    void start_debugging() {
        Serial.begin(9600);
    }
#endif

#undef STRIP
#define BADGE

#ifdef STRIP
#define DATA_PIN 11
#define LED_COUNT 30
#endif

#ifdef BADGE
#define DATA_PIN 1
#define LED_COUNT 12
#endif

#define DRIVER NEOPIXEL

#define DECAY_DELAY 20

CRGB led[LED_COUNT];
CHSV drops[LED_COUNT];

CHSV seed_drop() {
    CHSV drop = CHSV(HUE_PURPLE, 255, random8(128)+127);
    return(drop);
}



void setup() {
    delay(250);

    #ifdef DEBUG
        start_debugging();
    #endif

    FastLED.addLeds<DRIVER, DATA_PIN>(led, LED_COUNT).setCorrection(TypicalLEDStrip);
    fill_solid(led, LED_COUNT, CRGB::Black);

    // Seed first rain drops
    uint8_t numdrops = random8(LED_COUNT / 2 * 3);
    for (uint8_t i = 0; i < numdrops; i++) {
        drops[i] = seed_drop();
    }
    FastLED.show();
}

void loop() {
    for (uint8_t i = 0; i < LED_COUNT; i++) {
        if (drops[i].v <= 10) {
            if (random8(100) < 10) {
                // chance that dim/off becomes lit
                drops[i] = seed_drop();
            }
        }

        if (drops[i].v > 0) {
            drops[i].v = drops[i].v-random8(8);
        }

        led[i] = drops[i]; // Map to CRGB space for display
    }

    FastLED.show();
    FastLED.delay(DECAY_DELAY);

    #ifdef DEBUG
        Serial.println("tick");
    #endif
}
