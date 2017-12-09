#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6
#define NUM_LEDS 12
#define BRIGHTNESS 50

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

// the original levels for the leds (mix of yellow and red) that we define in setup()
unsigned int r[NUM_LEDS];
unsigned int g[NUM_LEDS];
unsigned int b[NUM_LEDS];

// the new levels we randomized
unsigned int rx[NUM_LEDS];
unsigned int gx[NUM_LEDS];
unsigned int bx[NUM_LEDS];

// the levels to approach the new levels by tweaning (these we use to set the neopixels)
double rz[NUM_LEDS];
double gz[NUM_LEDS];
double bz[NUM_LEDS];

// the diff to the new levels to twean to them in 10 steps
double dr[NUM_LEDS];
double dg[NUM_LEDS];
double db[NUM_LEDS];

int count = 0;

void setup() {
  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  // set the original candle led levels; 3 groups of colors
  for (int i=0; i<NUM_LEDS; i++) {
    if (i%3==0) {
      r[i] = 90;
      g[i] = 0;
      b[i] = 0;
    }
    if (i%3==1) {
      r[i] = 128;
      g[i] = 128;
      b[i] = 0;
    }
    if (i%3==2) {
      r[i] = 160;
      g[i] = 160;
      b[i] = 0;
    }
  }        
}

void loop() {
  // twean to the new values all the time
  for (int i=0; i<NUM_LEDS; i++) {
    rz[i] += dr[i];
    gz[i] += dg[i];
    bz[i] += db[i];

    // to guard from overflow or accidental unwanted flickering
    if (rz[i]<0) rz[i] = 0;
    if (rz[i]>255) rz[i] = 255;
    if (gz[i]<0) gz[i] = 0;
    if (gz[i]>255) gz[i] = 255;
    if (bz[i]<0) bz[i] = 0;
    if (bz[i]>255) bz[i] = 255;
  }

  count++;
  if (count>9) {   // we set new levels now after 10 iterations
    count = 0;

    // set new levels based on a factor, and this in those 3 'groups' of leds
    for (int j=0; j<3; j++) {
      float z = 10.0/random(4, 11);   // min is inclusive, max is exclusive (giving range from 0.4 to 1.0)
      for (int i=0; i<4; i++) {
        int idx = j*4+i;
        rx[idx] = (int) (r[idx] * z);
        gx[idx] = (int) (g[idx] * z);
        bx[idx] = (int) (b[idx] * z);
      }
    }

    // calculate the diff values (1/10th step)
    for (int i=0; i<NUM_LEDS; i++) {
      dr[i] = (rx[i] - rz[i])/10;
      dg[i] = (gx[i] - gz[i])/10;
      db[i] = (bx[i] - bz[i])/10;
    }
  }

  // update the leds
  for (int i=0; i<NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Color((int)rz[i], (int)gz[i], (int)bz[i], 255) );
  }
  strip.show();

  delay(10);    // run our loop at approx 100Hz; so new LED levels reach every ~100 ms (~10Hz)
}

