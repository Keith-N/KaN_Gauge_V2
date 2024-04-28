/*
  'led.h'

  Setup for LED strips and functions for turning them on.


*/

#pragma once

#include <Adafruit_NeoPixel.h>
#include "wifi.h"
#include "display.h"
#include "pinMap.h"
#include "DataFunctions.h"
#include "SensorData.h"
#include "config.h"
#include "nvs.h"

#define LED_PIN 14
#define LED_PIN2 21
#define LED_COUNT 3

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(LED_COUNT, LED_PIN2, NEO_GRB + NEO_KHZ800);

int LED_Order[] = {2, 1, 0, 0, 1, 2};

int RED[] = {0, 100, 150, 255, 255, 255};  // RED
int GREEN[] = {100, 200, 255, 150, 50, 0}; // GREEN
int BLUE[] = {150, 40, 0, 0, 0, 0};        // BLUE


int ledRed = 100;
int ledGreen = 50;
int ledBlue = 0;
int prevLed = 0;

bool ledEnabled = true;

void ledOff()
{

  for (int led = 0; led < 7; led++)
  {

    if (led == 0)
    {
    }

    else if (led < 4)
    {
      strip.setPixelColor(LED_Order[led - 1], strip.Color(0, 0, 0)); //  Set pixel's color (in RAM)
    }

    else if (led < 7)
    {
      strip2.setPixelColor(LED_Order[led - 1], strip.Color(0, 0, 0)); //  Set pixel's color (in RAM)
    }
  }
}

void ledInit()
{

  // Init LED object
  strip.begin();
  strip2.begin();

  // Set LEDs off
  strip.clear();
  strip2.clear();

  strip.show();
  strip2.show();
}

void setLed(int set, int count, uint32_t color)
{

  if (set == 0)
  {
    strip.setPixelColor(count, color); //  Set pixel's color (in RAM)
  }

  if (set == 1)
  {
    strip2.setPixelColor(count, color); //  Set pixel's color (in RAM)
  }
}

void ledSingle(int led, int r, int g, int b, int brightness)
{

  // Bound values to expected range
  if (led > 6)
  {
    led = 6;
  }
  if (led < 0)
  {
    led = 0;
  }
  if (brightness > 100)
  {
    brightness = 100;
  }
  if (brightness < 0)
  {
    brightness = 0;
  }

  // Turn off all LEDs before turning on the new config
  ledOff();

  if (led == 0)
  {
  }
  else if (led < 4)
  {
    setLed(0, LED_Order[led - 1], strip.Color(r * brightness / 100, g * brightness / 100, b * brightness / 100));
  }

  else if (led < 7)
  {
    setLed(1, LED_Order[led - 1], strip.Color(r * brightness / 100, g * brightness / 100, b * brightness / 100));
  }

  strip.show();
  strip2.show();
}

void ledSeries(int led, int r, int g, int b, int brightness)
{

  // Bound values to expected range
  if (led > 6)
  {
    led = 6;
  }
  if (led < 0)
  {
    led = 0;
  }

  if (brightness > 100)
  {
    brightness = 100;
  }
  if (brightness < 0)
  {
    brightness = 0;
  }

  // Turn off all LEDs before turning on the new config
  ledOff();

  for (int cLed = 0; cLed < led + 1; cLed++)
  {
    if (cLed == 0)
    {
    }

    else if (cLed < 4)
    {
      setLed(0, LED_Order[cLed - 1], strip.Color(r * brightness / 100, g * brightness / 100, b * brightness / 100));
    }

    else if (cLed < 7)
    {
      setLed(1, LED_Order[cLed - 1], strip.Color(r * brightness / 100, g * brightness / 100, b * brightness / 100));
    }
  }

  strip.show();
  strip2.show();
}

void ledSeriesMulticolor(int led, int r, int g, int b, int brightness)
{

  // Bound values to expected range
  if (led > 6)
  {
    led = 6;
  }
  if (led < 0)
  {
    led = 0;
  }

  if (brightness > 100)
  {
    brightness = 100;
  }
  if (brightness < 0)
  {
    brightness = 0;
  }

  // Turn off all LEDs before turning on the new config
  ledOff();

  for (int cLed = 0; cLed < led + 1; cLed++)
  {
    if (cLed == 0)
    {
    }

    else if (cLed < 4)
    {
      setLed(0, LED_Order[cLed - 1], strip.Color(LEDred[LEDcolor][cLed-1] * brightness / 100, LEDgreen[LEDcolor][cLed-1] * brightness / 100, LEDblue[LEDcolor][cLed-1] * brightness / 100));
    }

    else if (cLed < 7)
    {
     setLed(1, LED_Order[cLed - 1], strip.Color(LEDred[LEDcolor][cLed-1] * brightness / 100, LEDgreen[LEDcolor][cLed-1] * brightness / 100, LEDblue[LEDcolor][cLed-1] * brightness / 100));
    }
  }

  strip.show();
  strip2.show();
}