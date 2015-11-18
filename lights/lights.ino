#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6
#define BLUE

double percentForShooter = 0.0;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(70, PIN, NEO_GRB + NEO_KHZ800);
uint32_t lightColor = 0;
uint32_t darkColor = 0;
uint32_t green = strip.Color(0, 250, 0);
void setup()
{
  strip.begin();
  strip.show();

  lightBottomLights();
}

String getCommand()
{

  String output;
  output = Serial.readString();

  return output;

}

uint32_t getBaseColor(int brightness) {
#ifdef RED

  lightColor = strip.Color(150, 0, 90);
  darkColor = strip.Color(176, 0, 0);
  return strip.Color(brightness, 0 , 0);
#else
  lightColor = strip.Color(30, 144, 200);
  darkColor = strip.Color(16, 60, 90);
  return strip.Color(0, 0, brightness);
#endif
}

void lightBottomLights() {
  uint32_t c = getBaseColor(200);
  for (uint16_t i = 46; i < 70; i++) {
    strip.setPixelColor(i, c);
    strip.show();
  }
}

void loop()
{
  // Time for a show!
  colorWipe(getBaseColor(150), 110);
  int time = 30;
  for (int i = 0; i < 30; i++) {
    if (i % 2 == 0) {
      colorWipe(green, time);
    } else {
      colorWipe(darkColor, time);
    }
    time = time - 1;
  }
  colorWipe(getBaseColor(150), 0);
  fade();
  // Bouncy thing
  bounceAround(4);
  bounceAroundOp(2);
  bounceAroundOpCont(3);
  fadeInAndOut(6);
  theaterChase(getBaseColor(150), 3000);
  /*
  strip.show();
  //Serial.print("listen");
  if (Serial.available())
  {
    String x = getCommand();
    if ( x == "Shoot" )
    {

    }else
    {
      percentForShooter = x.toInt();
    }
    Serial.println(x);
  }*/
}

// Fill the dots one after the other with a color
void colorWipeMax(uint32_t c, uint8_t wait, uint8_t maxVal) {
  for (uint16_t i = 0; i < maxVal; i++) {
    strip.setPixelColor(i, c);
    strip.setPixelColor(45 - i, c);
    strip.show();
    delay(wait);
  }
}

void fadeInAndOut(int cycles) {
  for (int x = 0; x < cycles; x++) {
    fade();
    for (int i = 0; i > 150; i += 3) { // Fade
      colorWipe(getBaseColor(i), 0);
      delay(10);
    }
  }
}

void fade() {
  for (int i = 150; i > 0; i -= 4) { // Fade
    colorWipe(getBaseColor(i), 0);
  }
}
void bounceAroundOp(int cycles) {
  for (int i = 0; i < cycles; i++) {
    // Way Up
    for (int x = 0; x < 23; x++) {
      colorWipe(getBaseColor(150), 0);
      strip.setPixelColor(x, green);
      strip.setPixelColor(x + 23, green);
      strip.setPixelColor(x + 1, green );
      strip.setPixelColor(23 +  x + 1, green);
      strip.setPixelColor(x - 1, green );
      strip.setPixelColor(23 +  x - 1, green );
      strip.show();
      delay(20);
    }
    for (int x = 23; x > 0; x--) { // Way down
      colorWipe(getBaseColor(150), 0);
      strip.setPixelColor(x, green);
      strip.setPixelColor(23 +  x, green);
      strip.setPixelColor(x + 1, green );
      strip.setPixelColor(23 + x + 1, green);
      strip.setPixelColor(x - 1, green );
      strip.setPixelColor(23 +  x - 1, green );
      strip.show();
      delay(20);
    }
  }
}
void bounceAroundOpCont(int cycles) {
  for (int i = 0; i < cycles; i++) {
    // Way Up
    for (int x = 0; x < 46; x++) {
      colorWipe(getBaseColor(150), 0);
      strip.setPixelColor(x, green);
      strip.setPixelColor(x + 1, green );
      strip.setPixelColor(x - 1, green );
      strip.show();
      delay(20);
    }
    for (int x = 46; x > 0; x--) { // Way down
      colorWipe(getBaseColor(150), 0);
      strip.setPixelColor(x, green);
      strip.setPixelColor(x + 1, green );
      strip.setPixelColor(x - 1, green );
      strip.show();
      delay(20);
    }
  }
}
void bounceAround(int cycles) {
  for (int i = 0; i < cycles; i++) {
    // Way Up
    for (int x = 0; x < 23; x++) {
      colorWipe(getBaseColor(150), 0);
      strip.setPixelColor(x, green);
      strip.setPixelColor(45 - x, green);
      strip.setPixelColor(x + 1, green );
      strip.setPixelColor(45 - x + 1, green);
      strip.setPixelColor(x - 1, green );
      strip.setPixelColor(45 - x - 1, green );
      strip.show();
      delay(20);
    }
    for (int x = 23; x > 0; x--) { // Way down
      colorWipe(getBaseColor(150), 0);
      strip.setPixelColor(x, green);
      strip.setPixelColor(45 - x, green);
      strip.setPixelColor(x + 1, green );
      strip.setPixelColor(45 - x + 1, green);
      strip.setPixelColor(x - 1, green );
      strip.setPixelColor(45 - x - 1, green );
      strip.show();
      delay(20);
    }
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < 23; i++) {
    strip.setPixelColor(i, c);
    strip.setPixelColor(45 - i, c);
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}



