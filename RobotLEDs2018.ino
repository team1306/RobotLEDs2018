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
  delay(3000);
  Serial.begin(9600);
  Serial.println("2018 Robot LEDs starting");
  FastLED.addLeds<LED_TYPE, LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}


void loop() {
//  randomSeed(millis());
//   
//  int wait=random(10,30);
//  int dim=random(4,6);
//  int max_cycles=8;
//  int cycles=random(1,max_cycles+1);
//   
//  rainbowCycle(wait, cycles, dim);

  
//  nightRider(CRGB(255, 0, 0), CRGB(255, 255, 255), 3, 50);
//  rainbow(35);
//  police(1000);
}

void police(int wait) {
  fill_solid( &(leds[0]), NUM_LEDS/2, CRGB( 255, 0, 0) );
  fill_solid( &(leds[NUM_LEDS/2 + 1]), NUM_LEDS, CRGB( 0, 0, 255) );
  FastLED.show();
  Serial.println("Wait");
  delay(wait);
  Serial.println("End Wait");
  fill_solid( &(leds[0]), NUM_LEDS/2, CRGB( 0, 0, 255) );
  fill_solid( &(leds[NUM_LEDS/2 + 1]), NUM_LEDS, CRGB( 255, 0, 0) );
  FastLED.show();
  delay(wait);
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<NUM_LEDS; i++) {
      leds[i] = Wheel((i+j) & 255);
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

void rainbowCycle(int wait, int cycles, int dim) {

  //loop several times with same configurations and same delay
  for(int cycle=0; cycle < cycles; cycle++){
  
    byte dir=random(0,2);
    int k=255;
    
    //loop through all colors in the wheel
    for (int j=0; j < 256; j++,k--) { 
      
      if(k<0) {
        k=255;
      }
      
      //Set RGB color of each LED
      for(int i=0; i<NUM_LEDS; i++) {
        
        CRGB ledColor = wheel(((i * 256 / NUM_LEDS) + (dir==0?j:k)) % 256,dim);        
        leds[i]=ledColor;
        
      }
      
      FastLED.show();
      FastLED.delay(wait);
    }
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
