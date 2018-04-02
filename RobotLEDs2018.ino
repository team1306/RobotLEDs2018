#include <FastLED.h>

#define LED_PIN     6
#define NUM_LEDS    46
#define BRIGHTNESS  64
#define LED_TYPE    NEOPIXEL

// Comment out for prod to save memory
#define DEBUG 1

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
}


void loop() {
//  rainbowSingle(35);
//  rainbowDouble(35);
//  nightRider(CRGB(255, 0, 0), CRGB(255, 255, 255), 3, 50);
//  nightRiderSides(CRGB(255, 0, 0), CRGB(0, 0, 0), 3, 1000);
  nightRiderSidesOneWay(CRGB(255, 0, 0), CRGB(0, 0, 0), 3, random(20, 70));
}

void setAll(CRGB c) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = c;
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
void nightRiderSides(CRGB c, CRGB c2, int len, int delayTime) {
//  int i=0;
//  for (int i=0; i < NUM_LEDS/2; i++) {  // Forward
//    leds[i] = c;
//    leds[(NUM_LEDS/2) + i] = c;
//    if (i - len >= 0) {
//      leds[i - len] = c2;
//      leds[((NUM_LEDS/2) + i) - len] = c2;
//    }
//    FastLED.show();
//    delay(delayTime);
//  }
//  for (int i = len; i >= 0; i--) {
//    leds[NUM_LEDS - i] = c2;
//    leds[(NUM_LEDS/2) - i] = c2;
//    FastLED.show();
//    delay(delayTime);
//  }

  int i=0;
  for (int i=(NUM_LEDS/2); i > 0; i--) {  // Forward
    leds[i] = c;
    leds[(NUM_LEDS/2) + i] = c;
    if (i - len >= 0) {
      leds[i - len] = c2;
      leds[((NUM_LEDS/2) + i) - len] = c2;
    }
    FastLED.show();
    delay(delayTime);
  }
  for (int i = 0; i < len; i++) {
    leds[NUM_LEDS - i] = c2;
    leds[(NUM_LEDS/2) - i] = c2;
    FastLED.show();
    delay(delayTime);
  }
  
//  for (int i=0; i < NUM_LEDS/2; i++) {  // Backward
//    leds[NUM_LEDS - i] = c;
//    leds[(NUM_LEDS/2) - i] = c;
//    if ((NUM_LEDS-i) <= NUM_LEDS-len) {
//      leds[(NUM_LEDS-i) + len] = c2;
//      leds[((NUM_LEDS/2)-i) + len] = c2;
//    }
//    FastLED.show();
//    delay(delayTime);
//  }
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
      leds[i] = Wheel((i+j) & 255);
    }
    for(i=(NUM_LEDS/2); i<NUM_LEDS; i++) {
      leds[i] = Wheel((i+j - (NUM_LEDS/2)) & 255);
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
