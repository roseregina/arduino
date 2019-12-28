#include <Adafruit_NeoPixel.h>

#define BUTTON_PIN   3 
#define PIXEL_PIN    7

#define PIXEL_COUNT 25  // 24 days of advent, plus one more
// do I want to relocate this value into the loop? 
// I don't think I have to because I can imlluminate only part of the strip now

// this is the line to change for different strips
Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

//this is for the button and defining the starting value for the mode counter
boolean oldState = HIGH;
int     mode        = 29;    // animation count, since cycle through doesn't work 
                             // start on last (all black since mode 0 turns on LED 0
                             // and 29 == -1 

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);  //button
  strip.begin(); // Initialize NeoPixel strip object (REQUIRED)
  strip.show();  // Initialize all pixels to 'off'
}

void loop() {
  // Get current button state.
  boolean newState = digitalRead(BUTTON_PIN);

  // Check if state changed from high to low (button press).
  if((newState == LOW) && (oldState == HIGH)) {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still low after debounce. value can be changed to prevent misfires
    newState = digitalRead(BUTTON_PIN);
    if(newState == LOW) {      // Yes, still low
      if(++mode > 29) mode = 0; // Advance to next mode, wrap around after #29
      switch(mode) {           // Start the new animation...
        case  0: dayLight(strip.Color(random(10,255), random(10,255), random(10,255)), 50); // first light
          break;                                                                            // I feel like there is a way to cover 0-24
        case  1: dayLight(strip.Color(random(10,255), random(10,255), random(10,255)), 10); // at one go more elegently, maybe with if statement
          break;                                                                            // also probably to move the random into dayLight
        case  2: dayLight(strip.Color(random(10,255), random(10,255), random(10,255)), 10);
          break;
        case  3: dayLight(strip.Color(random(10,255), random(10,255), random(10,255)), 10);
          break;
        case  4: dayLight(strip.Color(random(10,255), random(10,255), random(10,255)), 10);
          break;
        case  5: dayLight(strip.Color(random(10,255), random(10,255), random(10,255)), 10);
          break;
        case  6: dayLight(strip.Color(random(10,255), random(10,255), random(10,255)), 10);
          break;
        case  7: dayLight(strip.Color(random(10,255), random(10,255), random(10,255)), 10);
          break;
        case  8: dayLight(strip.Color(random(10,255), random(10,255), random(10,255)), 10);
          break;
        case  9: dayLight(strip.Color(random(10,255), random(10,255), random(10,255)), 10); //10th light
          break;
        case 10: dayLight(strip.Color(random(10,255), random(10,255), random(10,255)), 10);  
          break;
        case 11: dayLight(strip.Color(random(10,255), random(10,255), random(10,255)), 10);
          break;
        case 12: dayLight(strip.Color(random(10,255), random(10,255), random(10,255)), 10);
          break;
        case 13: dayLight(strip.Color(random(10,255), random(10,255), random(10,255)), 10);
          break;
        case 14: dayLight(strip.Color(random(10,255), random(10,255), random(10,255)), 10);
          break;
        case 15: dayLight(strip.Color(random(10,255), random(10,255), random(10,255)), 10);
          break;
        case 16: dayLight(strip.Color(random(10,255), random(10,255), random(10,255)), 10);
          break;
        case 17: dayLight(strip.Color(random(10,255), random(10,255), random(10,255)), 10);
          break;
        case 18: dayLight(strip.Color(random(10,255), random(10,255), random(10,255)), 10);
          break;
        case 19: dayLight(strip.Color(random(10,255), random(10,255), random(10,255)), 10); //20th light
          break;
        case 20: dayLight(strip.Color(random(10,255), random(10,255), random(10,255)), 10);  
          break;
        case 21: dayLight(strip.Color(random(10,255), random(10,255), random(10,255)), 10);
          break;
        case 22: dayLight(strip.Color(random(10,255), random(10,255), random(10,255)), 10);
          break;
        case 23: dayLight(strip.Color(random(10,255), random(10,255), random(10,255)), 10);
          break;
        case 24: dayLight(strip.Color(random(10,255), random(10,255), random(10,255)), 10); //25th (last) light
          break;
        case 25: colorWipe(strip.Color(0, 0, 0), 50); // clears strip, not needed, but I like how it looks and made QA easier
          break;
        case 26: rainbow(10); // rainbow effect
          break;
        case 27: colorWipe(strip.Color(0, 0, 0), 50); // clears strip
          break;
        case 28: flickerLight(strip.Color(0, 0, 0), 10);
          break;
        case 29: colorWipe(strip.Color(0, 0, 0), 50); // all dark, starting "animation"
          break;
      }
    }
  }

  // Set the last-read button state to the old state.
  oldState = newState;
}

// from buttoncycler 
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

// this is mine. it works, but is not as tidy as I would like. 
// I think the 'for' parameters are bulk but I ran out of determination to replace them
// once the pixel matching the mode number is effected (no wiping or back fill)
// this means that ear pixel colour is independent from the others
// I think there should be a way in specify the 'strip.fill' parameters in the cases, but I didn't figure out how
// that would allow for out of order illuminations, though I think that might also be able to be done through defining a matrix?
void dayLight(uint32_t color, int wait) {  // I want random color in all of them, but I coudn't figure out where toput that here instead of above 
  for(int i=0; i<strip.numPixels(); i++) { // this could be more aproriate, but it works
    strip.fill(color, mode, 1);         //  turns on 1 LED with the same number (0-24) as the mode
    strip.show();                           
    // delay(wait);                          
  }
}

// from buttoncycler 
// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 3 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 3*65536. Adding 256 to firstPixelHue each time
  // means we'll make 3*65536/256 = 768 passes through this outer loop:
  for(long firstPixelHue = 0; firstPixelHue < 3*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(50);  // Pause for a moment
  }
}

// adapted from Neopixel Flames by Simon Cleveland (mysecretstache) 
// https://codebender.cc/sketch:271084#Neopixel%20Flames.ino
void flickerLight(uint32_t color, int wait) {
  while(mode == 28) { // this keeps the animation going; otherwise, the pixels are drawn only once
  for(int i=0; i<40; i++) {
    int r = 200, g = 121, b = 75;  // base colour (warm pink) is set here. I tried using random and didn't get it to work here or in 'case'
    int flicker = random(0,60); 
    int r1 = r-flicker; // if I were to rewrite this part, I think I would want the colour value changes to be
    int g1 = g-flicker; // proportional to the initial value instead of a set range
    int b1 = b-flicker;
    if(g1<0) g1=0;
    if(r1<0) r1=0;
    if(b1<0) b1=0;
    strip.setPixelColor(i,r1,g1,b1);
  }
  strip.show();
  
  //  Adjust the delay here, if you'd like.  Right now, it randomizes the 
  //  color switch delay to give a sense of realism
  delay(random(10,113));
  
/* I tried to add some kind of check here to tell if it should continue or not, 
 * but because of how the button works, it would have been rather complicated to add 
 * and I was beyond out out of time. 
 * I think that the answer is to work through all of the information from 
 * Nick Gammon's _ow to process incoming serial data without blocking_ 
 * http://www.gammon.com.au/serial
 * and to integrate that in to what I already have. Next steps :) 
 */
  }
}

/*
Project info: 
This project was inspired by Helen Ward's Knitted Fairy Lights Advent Calendar
https://birdface.net/2012/11/06/knitted-fairy-lights-advent-calendar-pattern-and-tutorial/
and Bob Clagett's Advent Calendar Christmas Tree project
https://iliketomakestuff.com/make-arduino-powered-advent-calendar/
I could not get any of Bob's code to work with the LEDs I had, but without 
thinking that I could just use that, I wouldn't have tried. 

License info: 
I started with the Adafruit Neopixel library's buttoncycler sample code
https://github.com/adafruit/Adafruit_NeoPixel/blob/master/examples/buttoncycler/buttoncycler.ino
I believe that it is GPL 3.0+ (https://www.gnu.org/licenses/lgpl-3.0.en.html) 

I could not determine the licence for Simon Cleveland's Neopixel Flames
https://codebender.cc/sketch:271084#Neopixel%20Flames.ino

The parts that I wrote are small enough that any licence over than CC-0 seems overkill
Enjoy. 
 */
