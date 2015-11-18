#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(70, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  //Serial.begin(115200);
   // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code
  strip.begin();
  strip.show(); // Initialize all pixels to 'of
  colorWipe(strip.Color(100, 0, 0), 50);
}

String getCommand()
{
  String output;
  while(Serial.available())
  {
    delay(5);
    output += char(Serial.read());
  }
  return output;
}

void loop() {
  colorWipe(strip.Color(100, 0, 0), 1);
  colorWipeMax(strip.Color(0, 100, 0), 1, 10);
  colorWipeMax(strip.Color(0, 0, 100), 1, 15);
  colorWipeMax(strip.Color(0, 100, 100), 1, 20);
  if(Serial.available()) 
  {
    String x = getCommand();
    //Serial.println(x);
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<23; i++) {
    strip.setPixelColor(i, c);
    strip.setPixelColor(45 - i, c);
    strip.show();
    delay(wait);
  }
}
// Fill the dots one after the other with a color
void colorWipeMax(uint32_t c, uint8_t wait, uint8_t maxVal) {
  for(uint16_t i=0; i<maxVal; i++) {
    strip.setPixelColor(i, c);
    strip.setPixelColor(45 - i, c);
    strip.show();
    delay(wait);
  }
}

