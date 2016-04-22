#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>

#define PIN 13

SoftwareSerial mySerial(2, 3); // RX, TX
Adafruit_NeoPixel strip = Adafruit_NeoPixel(30, PIN, NEO_GRB + NEO_KHZ800);

String input;
String brightnessString;
String program;
String color;
int brightnessPercentage;
int brightnessValue;

long long rgb;
long long r;
long long g;
long long b;


void setup() {
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);

  Serial.begin(9600);
  mySerial.begin(9600);

  strip.begin();
  strip.show();
}

void loop() {
  if (mySerial.available() > 0) {
    input = mySerial.readString();
    parseString(input);

    while (program == "program1")
    {
      strip.setBrightness(brightnessValue);
      flashAll(strip.Color(r, g, b));
      if (mySerial.available() > 0) {
        input = mySerial.readString();
        parseString(input);
      }
    }

    while (program == "program2")
    {
      strip.setBrightness(brightnessValue);
      theaterChase(strip.Color(r, g, b), 180);
      if (mySerial.available() > 0) {
        input = mySerial.readString();
        parseString(input);
      }
    }

    while (program == "program3")
    {
      strip.setBrightness(brightnessValue);
      upAndDown(strip.Color(r, g, b), 40);
      if (mySerial.available() > 0) {
        input = mySerial.readString();
        parseString(input);
      }
    }

    while (program == "program4")
    {
      strip.setBrightness(brightnessValue);
      snake(strip.Color(r, g, b), 250);
      if (mySerial.available() > 0) {
        input = mySerial.readString();
        parseString(input);
      }
    }
    
    while (program == "program5")
    {
      strip.setBrightness(brightnessValue);
      crazyRainbowCycle(1);
      if (mySerial.available() > 0) {
        input = mySerial.readString();
        parseString(input);
      }
    }
        while (program == "program6")
    {
      strip.setBrightness(brightnessValue);
      theaterChaseRainbow(50);
      if (mySerial.available() > 0) {
        input = mySerial.readString();
        parseString(input);
      }
    }
  }
}

void parseString(String inputString)
{
  int commaIndex = inputString.indexOf(',');
  int secondCommaIndex = inputString.indexOf(',', commaIndex + 1);

  brightnessString = inputString.substring(0, commaIndex);
  program = inputString.substring(commaIndex + 1, secondCommaIndex);
  color = inputString.substring(secondCommaIndex + 1);

  calcBrightness(brightnessString);
  hexToRgb(color);
}

void calcBrightness(String brightnessString)
{
  brightnessPercentage = brightnessString.toInt();

  brightnessValue = (int) (255 * brightnessPercentage) / 100;
}

void hexToRgb(String hex)
{
  rgb = strtol( &hex[1], NULL, 16);
  r = rgb >> 16;
  g = rgb >> 8 & 0xFF;
  b = rgb & 0xFF;
}

void theaterChase(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) { //10 x doorlopen
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, c);  //zet elke 3de RGD LED aan
      }
      strip.show();

      delay(wait);
      delay(wait);

      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //zet elke 3de RGB LED uit
      }
    }
  }
}


void flashAll(uint32_t c) {
  // Do a quick test/demo to show that things are working
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
}

void upAndDown(uint32_t c, uint8_t wait)
{
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }

  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, 0, 0, 0);
    strip.show();
    delay(wait);
  }

  for (uint16_t y = strip.numPixels(); y >= 1; y -= 1) {
    strip.setPixelColor(y, c);
    strip.show();
    delay(wait);
  }

  for (uint16_t y = strip.numPixels(); y >= 1; y -= 1) {
    strip.setPixelColor(y, 0, 0, 0);
    strip.show();
    delay(wait);
  }
}

void snake(uint32_t c, uint8_t wait)
{
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.setPixelColor(i + 1, c);
    strip.setPixelColor(i + 2, c);
    strip.setPixelColor(i + 3, c);
    strip.setPixelColor(i + 4, c);

    strip.setPixelColor(i - 1, 0, 0, 0);
    strip.setPixelColor(i - 2, 0, 0, 0);
    strip.setPixelColor(i - 3, 0, 0, 0);
    strip.setPixelColor(i - 4, 0, 0, 0);

    strip.show();
    delay(wait);
  }
}

void crazyRainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

void theaterChaseRainbow(uint8_t wait) {
  for (int j = 0; j < 256; j++) {   // gebruik alle 256 kleuren in het wiel
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, Wheel( (i + j) % 255)); //zet elke 3de LED aan
      }
      strip.show();

      delay(wait);

      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //zet elke 3de LED uit
      }
    }
  }
}

uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
