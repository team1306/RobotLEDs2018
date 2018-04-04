#include <FastLED.h>

#define LED_PIN     6
#define NUM_LEDS    142
#define BRIGHTNESS  64
#define LED_TYPE    NEOPIXEL

const int TYPE_SWITCH_PIN = 12;
const int ALLIANCE_PIN = 10;

// Comment out for prod to save memory
//#define DEBUG 1

CRGB leds[NUM_LEDS];

// This example shows several ways to set up and use 'palettes' of colors
// with FastLED.

void setup() {
  #ifdef DEBUG
    Serial.begin(9600);
    Serial.println("2018 Robot LEDs starting");
  #endif
  FastLED.addLeds<LED_TYPE, LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  setAll(CRGB(0,0,0));
  pinMode(TYPE_SWITCH_PIN, INPUT);
  pinMode(ALLIANCE_PIN, INPUT);
}


void loop() {
  if (digitalRead(TYPE_SWITCH_PIN)) {
//    rainbowSingle(35);
    rainbowDouble(35);
  } else {
    setAll(CRGB(0,0,0));
    if (digitalRead(ALLIANCE_PIN)) {
      // Blue
      nightRiderSides(CRGB(0, 0, 255), CRGB(0,0,0), 3, 10, 0);
    } else {
      // Red
      nightRiderSides(CRGB(255, 0, 0), CRGB(0,0,0), 3, 10, 0);
    }
//    nightRider(CRGB(255, 0, 0), CRGB(0, 0, 0), 3, 50);
  }
//  rainbowDouble(35);
//  nightRider(CRGB(255, 0, 0), CRGB(255, 255, 255), 3, 50);
//  nightRiderSides(CRGB(255, 0, 0), CRGB(0, 0, 0), 3, 1000);
//  nightRiderSidesOneWayOpp(CRGB(255, 0, 0), CRGB(0, 0, 0), 3, random(20, 70));
}

void setAll(CRGB c) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = c;
  }
  FastLED.show();
}

void setDoubleSide(int i, CRGB c) {
  if (i < 23) {
    // Bottom
    leds[22-i] = c;
    leds[23+i] = c;
  } else if (i < 71) {
    // Top
    leds[142-i+22] = c;
    leds[46+i-23] = c;
  }
  FastLED.show();
}

void nightRiderSidesOneWay(CRGB c, CRGB c2, int len, int delayTime) {
  int i=0;
  for (int i=0; i < NUM_LEDS/2; i++) {  // Forward
    leds[i] = c;
    leds[(NUM_LEDS/2) + i] = c;
    if (i - len >= 0) {
      leds[i - len] = c2;
      leds[((NUM_LEDS/2) + i) - len] = c2;
    }
    FastLED.show();
    delay(delayTime);
  }
  for (int i = len; i >= 0; i--) {
    leds[NUM_LEDS - i] = c2;
    leds[(NUM_LEDS/2) - i] = c2;
    FastLED.show();
    delay(delayTime);
  }
}

/**
 * Nightrider effect
 * CRGB c - color
 * CRGB c2 - background color
 * int len - length
 * int delayTime - delay time
 * int dir - direction
 *  0 = both ways
 *  1 = up
 *  2 = down
 */
void nightRiderSides(CRGB c, CRGB c2, int len, int delayTime, int dir) {
  if (dir == 0 || dir == 1) {
    // Up
    for (int i = 0; i < NUM_LEDS/2; i++) {
      setDoubleSide(i, c);
      if (i > len-1) {
        setDoubleSide(i-len, c2);
      }
      delay(delayTime);
    }
  }
  if (dir == 0 || dir == 2) {
    // Down
    for (int i = 0; i < NUM_LEDS/2; i++) {
      setDoubleSide((NUM_LEDS/2) - i, c);
      if ((NUM_LEDS/2) - i > len-1) {
        setDoubleSide((NUM_LEDS/2) - i + len, c2);
      }
      delay(delayTime);
    }
  }
}

void rainbowSingle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<NUM_LEDS; i++) {
      leds[i] = Wheel((i+j) & 255);
    }
    FastLED.show();
    delay(wait);
  }
}

void rainbowDouble(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<NUM_LEDS/2; i++) {
      setDoubleSide(i, Wheel((i+j) & 255));
    }
    FastLED.show();
    delay(wait);
  }
}

CRGB Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return CRGB(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return CRGB(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return CRGB(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void nightRider(CRGB c, CRGB c2, int len, int delayTime) {
  int i=0;
  for (int i=0; i<NUM_LEDS; i++) {  //FORWARD
    leds[i] = c;
    if (i-len >= 0) {
      leds[i-len] = c2;
    }
    FastLED.show();
    delay(delayTime);
  }
  for (int i=0; i<NUM_LEDS; i++) {  //BACKWARD
    leds[NUM_LEDS-i] = c;
    if ((NUM_LEDS-i) <= NUM_LEDS-len) {
      leds[(NUM_LEDS-i) + len - 1] = c2;
    }
    FastLED.show();
    delay(delayTime);
  }
}

CRGB wheel(int WheelPos, int dim) {
  CRGB color;
  if (85 > WheelPos) {
   color.r=0;
   color.g=WheelPos * 3/dim;
   color.b=(255 - WheelPos * 3)/dim;;
  } 
  else if (170 > WheelPos) {
   color.r=WheelPos * 3/dim;
   color.g=(255 - WheelPos * 3)/dim;
   color.b=0;
  }
  else {
   color.r=(255 - WheelPos * 3)/dim;
   color.g=0;
   color.b=WheelPos * 3/dim;
  }
  return color;
}
