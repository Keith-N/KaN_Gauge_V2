//==============================================
/*
  'display.h'

  Display setup and and printing functions.

*/
//==============================================
#pragma once

#include <TFT_eWidget.h>
#include <TFT_eSPI.h> 
#include <PNGdec.h>

#include <SPI.h>
#include "bootlogos/bmm.h"
#include "bootlogos/fome.h"
#include "bootlogos/mazda.h"
#include "bootlogos/kan.h"
#include "bootlogos/customBoot.h"

#include "wifi.h"
#include "pinMap.h"
#include "DataFunctions.h"
#include "SensorData.h"
#include "config.h"
#include "led.h"
#include "nvs.h"
#include "icons/alert.h"

#define TFT_BL 6 // LED back-light
#define PWM1_Ch 0
#define PWM1_Res 8
#define PWM1_Freq 1000
#define PWM_MAX 255

const int buildTime_ms = 1000;

int dispBrightness = 50;
int ledBrightness = 50;

int brightnessThresholdLow = 1000;
int brightnessThresholdHigh = 1500;

// Meter color schemes
#define RED2RED 0
#define GREEN2GREEN 1
#define BLUE2BLUE 2
#define BLUE2RED 3
#define GREEN2RED 4
#define RED2GREEN 5
#define TFT_GREY 0x2104 // Dark grey 16 bit color

#define boot3

#define BUFF_SIZE 64        // To speed up rendering we use a 64 pixel buffer
PNG png;                    // PNG decoder inatance
#define MAX_IMAGE_WDITH 240 // Adjust for your images

int16_t xpos = 0;
int16_t ypos = 0;

TFT_eSPI tft = TFT_eSPI(); // Invoke custom library with default width and height
MeterWidget AnMeter = MeterWidget(&tft);

bool range_error = 0;
int gaugeposition_x = -10; // these two variables govern the position
int gaugeposition_y = -12; // of the square + gauge on the display
int gaugeCenterPosXY[] = {-10 - 12};

void getBrightness()
{

  int input = analogRead(USER_INPUT_A1);

  if (input < brightnessThresholdHigh)
  {
    ledBrightness = brightness[2];
    dispBrightness = brightness[0];
  }

  else
  {
    ledBrightness = brightness[3];
    dispBrightness = brightness[1];
  }
}

void setDisplayBrightness(int duty)
{
  if (duty > 100)
  {
    duty = 100;
  }
  if (duty < 0)
  {
    duty = 0;
  }
  ledcWrite(PWM1_Ch, duty * PWM_MAX / 100);
}

void displayInit()
{

  getBrightness();
  ledcAttachPin(TFT_BL, PWM1_Ch);
  ledcSetup(PWM1_Ch, PWM1_Freq, PWM1_Res);
  setDisplayBrightness(dispBrightness);

  tft.begin();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  tft.setTextFont(2);
}

// #########################################################################
//  Analog Meter
// #########################################################################

void setupAnalogMeter(int pX, int pY, const char *name, const char *unit, float minVal, float maxVal)
{

  // setupAnalogMeter(x, y,  units,  min,  max);
  // Ameter.updateNeedle(current value, timer);

  // Colour zones are set as a start and end percentage of full scale (0-100)
  // If start and end of a colour zone are the same then that colour is not used
  //            --Red--  -Org-   -blue-  -Grn-
  AnMeter.setZones(90, 100, 0, 0, 0, 10, 0, 0); // Example here red starts at 75% and ends at 100% of full scale
  // Meter is 239 pixels wide and 126 pixels high

  float tempVal = (maxVal - minVal);

  char indicator0[4];
  dtostrf(minVal, 1, 1, indicator0);
  char indicator1[4];
  dtostrf(tempVal / 4 + minVal, 1, 1, indicator1);
  char indicator2[4];
  dtostrf(tempVal * 2 / 4 + minVal, 1, 1, indicator2);
  char indicator3[4];
  dtostrf(tempVal * 3 / 4 + minVal, 1, 1, indicator3);
  char indicator4[4];
  dtostrf(tempVal + minVal, 1, 1, indicator4);

  AnMeter.analogMeter(pX, pY, minVal, maxVal, unit, indicator0, indicator1, indicator2, indicator3, indicator4, selectedColor[4], TFT_WHITE, TFT_WHITE, TFT_RED, TFT_YELLOW, TFT_BLUE, TFT_GREEN); // Draw analogue meter at 0, 0
  // AnMeter.analogMeter(pX, pY, maxVal, unit, indicator0, indicator1, indicator2, indicator3, indicator4);
}

// #########################################################################
//  Draw the meter on the screen, returns x coord of righthand side
// #########################################################################

void drawIcon(const unsigned short *icon, int16_t x, int16_t y, int8_t width, int8_t height)
{

  uint16_t pix_buffer[BUFF_SIZE]; // Pixel buffer (16 bits per pixel)

  tft.startWrite();

  // Set up a window the right size to stream pixels into
  tft.setAddrWindow(x, y, width, height);

  // Work out the number whole buffers to send
  uint16_t nb = ((uint16_t)height * width) / BUFF_SIZE;

  // Fill and send "nb" buffers to TFT
  for (int i = 0; i < nb; i++)
  {
    for (int j = 0; j < BUFF_SIZE; j++)
    {
      pix_buffer[j] = pgm_read_word(&icon[i * BUFF_SIZE + j]);
    }
    tft.pushColors(pix_buffer, BUFF_SIZE);
  }

  // Work out number of pixels not yet sent
  uint16_t np = ((uint16_t)height * width) % BUFF_SIZE;

  // Send any partial buffer left over
  if (np)
  {
    for (int i = 0; i < np; i++)
      pix_buffer[i] = pgm_read_word(&icon[nb * BUFF_SIZE + i]);
    tft.pushColors(pix_buffer, np);
  }

  tft.endWrite();
}

void drawAlert(int x, int y, int side, bool draw)
{
  if (draw && !range_error)
  {
    drawIcon(alert, x - alertWidth / 2, y - alertHeight / 2, alertWidth, alertHeight);
    range_error = 1;
  }
  else if (!draw)
  {
    tft.fillRect(x - alertWidth / 2, y - alertHeight / 2, alertWidth, alertHeight, TFT_BLACK);
    range_error = 0;
  }
}

// #########################################################################
// Return a 16 bit rainbow color
// #########################################################################
unsigned int rainbow(byte value)
{
  // Value is expected to be in range 0-127
  // The value is converted to a spectrum color from 0 = blue through to 127 = red

  byte red = 0;   // Red is the top 5 bits of a 16 bit color value
  byte green = 0; // Green is the middle 6 bits
  byte blue = 0;  // Blue is the bottom 5 bits

  byte quadrant = value / 32;

  if (quadrant == 0)
  {
    blue = 31;
    green = 2 * (value % 32);
    red = 0;
  }
  if (quadrant == 1)
  {
    blue = 31 - (value % 32);
    green = 63;
    red = 0;
  }
  if (quadrant == 2)
  {
    blue = 0;
    green = 63;
    red = value % 32;
  }
  if (quadrant == 3)
  {
    blue = 0;
    green = 63 - 2 * (value % 32);
    red = 31;
  }
  return (red << 11) + (green << 5) + blue;
}

//=========================================v==========================================
//                                      pngDraw
//====================================================================================
// This next function will be called during decoding of the png file to
// render each image line to the TFT. If you use a different TFT library
// you will need to adapt this function to suit.
// Callback function to draw pixels to the display
void pngDraw(PNGDRAW *pDraw)
{
  uint16_t lineBuffer[MAX_IMAGE_WDITH];
  png.getLineAsRGB565(pDraw, lineBuffer, PNG_RGB565_BIG_ENDIAN, 0xffffffff);
  tft.pushImage(xpos, ypos + pDraw->y, pDraw->iWidth, 1, lineBuffer);
}

void printBootLogo(int bootLogoSel)
{

  int16_t rcBMM, rcFOME, rcMazda, rcKan, rcCustomBoot;

  switch (bootLogoSel)
  {
  case 0:
    rcKan = png.openFLASH((uint8_t *)kan, sizeof(kan), pngDraw);
    if (rcKan == PNG_SUCCESS)
    {
      tft.startWrite();
      rcKan = png.decode(NULL, 0);
      tft.endWrite();
    }

    break;

  case 1:
    rcBMM = png.openFLASH((uint8_t *)bmm, sizeof(bmm), pngDraw);
    if (rcBMM == PNG_SUCCESS)
    {
      tft.startWrite();
      rcBMM = png.decode(NULL, 0);
      tft.endWrite();
    }

    break;

  case 2:

    rcFOME = png.openFLASH((uint8_t *)fome, sizeof(fome), pngDraw);
    if (rcFOME == PNG_SUCCESS)
    {
      tft.startWrite();
      rcFOME = png.decode(NULL, 0);
      tft.endWrite();
    }
    break;

  case 3:
    rcMazda = png.openFLASH((uint8_t *)mazda, sizeof(mazda), pngDraw);
    if (rcMazda == PNG_SUCCESS)
    {
      tft.startWrite();
      rcMazda = png.decode(NULL, 0);
      tft.endWrite();
    }
    break;

    case 4:
    rcCustomBoot = png.openFLASH((uint8_t *)customBoot, sizeof(customBoot), pngDraw);
    if (rcCustomBoot == PNG_SUCCESS)
    {
      tft.startWrite();
      rcCustomBoot = png.decode(NULL, 0);
      tft.endWrite();
    }
    break;

  default:
    break;
  }
}

void defaultsDisplay(){
    tft.fillScreen(TFT_BLACK);
    tft.drawCentreString("Button held on start!", 120, 100, 2);
    tft.drawCentreString("Hold for 10sec to reset to defaults", 120, 120, 2);
}

void releaseDefaultDisplay(){

    tft.fillScreen(TFT_BLACK);
    tft.drawCentreString("Release button to reset defaults!", 120, 120, 2);

}

void showBootLogos(int start)
{

  // First logo held for logoTime_ms
  int timeBuf;
  if (start == 0)
  {
    tft.fillScreen(TFT_BLACK);
    printBootLogo(bootLogo1);

    timeBuf = millis();
    while (millis() < (timeBuf + logoTime_ms))
    {
    };
  }

  
  if (start == 0 || start == 1)
  {
    tft.fillScreen(TFT_BLACK);
    printBootLogo(bootLogo2);
    timeBuf = millis();
    while (millis() < (timeBuf + logoTime_ms))
    {
    };
  }

  
  if (start == 0 || start == 1 || start == 2)
  {

    tft.fillScreen(TFT_BLACK);
    printBootLogo(bootLogo3);

    tft.setTextColor(TFT_WHITE);
    tft.drawCentreString(build, 120, 160, 2);

    if (nvsReset == true)
    {
      tft.drawCentreString("Config Reset", 100, 180, 2);
    }

    timeBuf = millis();
    while (millis() < (timeBuf + logoTime_ms))
    {
    };
  }
}

//====================================================================================
// This is the function to draw the icon stored as an array in program memory (FLASH)
//====================================================================================

// Draw array "icon" of defined width and height at coordinate x,y
// Maximum icon size is 255x255 pixels to avoid integer overflow

int ringMeter(float value, float vmin, float vmax, int x, int y, int r, const char *units, byte scheme, int digit, int decimals)
{

  // Minimum value of r is about 52 before value text intrudes on ring
  // drawing the text first is an option

  x += r;
  y += r; // Calculate coords of centre of ring

  int w = r / 8; // Width of outer ring is 1/4 of radius

  int angle = 150; // Half the sweep angle of meter (300 degrees)

  int v = map((value * 100), (vmin * 100), (vmax * 100), -angle, angle); // Map the value to an angle v

  byte seg = 3; // Segments are 3 degrees wide = 100 segments for 300 degrees
  byte inc = 6; // Draw segments every 3 degrees, increase to 6 for segmented ring

  // Variable to save "value" text color from scheme and set default
  int color = TFT_BLUE;

  // Draw color blocks every inc degrees
  for (int i = -angle + inc / 2; i < angle - inc / 2; i += inc)
  {
    // Calculate pair of coordinates for segment start
    float sx = cos((i - 90) * 0.0174532925);
    float sy = sin((i - 90) * 0.0174532925);
    uint16_t x0 = sx * (r - w) + x;
    uint16_t y0 = sy * (r - w) + y;
    uint16_t x1 = sx * r + x;
    uint16_t y1 = sy * r + y;

    // Calculate pair of coordinates for segment end
    float sx2 = cos((i + seg - 90) * 0.0174532925);
    float sy2 = sin((i + seg - 90) * 0.0174532925);
    int x2 = sx2 * (r - w) + x;
    int y2 = sy2 * (r - w) + y;
    int x3 = sx2 * r + x;
    int y3 = sy2 * r + y;

    if (i < v)
    { // Fill in coloured segments with 2 triangles
      switch (scheme)
      {
      case 0:
        color = TFT_RED;
        break; // Fixed color
      case 1:
        color = TFT_GREEN;
        break; // Fixed color
      case 2:
        color = TFT_BLUE;
        break; // Fixed color
      case 3:
        color = rainbow(map(i, -angle, angle, 0, 127));
        break; // Full spectrum blue to red
      case 4:
        color = rainbow(map(i, -angle, angle, 70, 127));
        break; // Green to red (high temperature etc)
      case 5:
        color = rainbow(map(i, -angle, angle, 127, 63));
        break; // Red to green (low battery etc)
      case 6:
        color = TFT_BLACK;
        break;
      default:
        color = TFT_BLUE;
        break; // Fixed color
      }
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, color);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, color);
      // text_colour = color; // Save the last color drawn
    }
    else // Fill in blank segments
    {
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_GREY);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_GREY);
    }
  }
  // Convert value to a string
  char buf[10];
  byte len = 5;
  dtostrf(value, len, 2, buf);
  buf[len] = ' ';
  buf[len + 1] = 0; // Add blanking space and terminator, helps to centre text too!

  // Set the text color to default
  tft.setTextSize(1);

  // if (value < vmin || value > vmax) {
  //   drawAlert(x, y + 90, 50, 1);
  // } else {
  //   drawAlert(x, y + 90, 50, 0);
  // }

  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  // Uncomment next line to set the text color to the last segment value!
  tft.setTextColor(color, TFT_BLACK);
  tft.setTextDatum(MC_DATUM);
  // Print value, if the meter is large then use big font 8, othewise use 4
  if (r > 84)
  {
    tft.setTextPadding(55 * 3);   // Allow for 3 digits each 55 pixels wide
    tft.drawString(buf, x, y, 4); // Value in middle
  }
  else
  {
    tft.setTextPadding(3 * 14);   // Allow for 3 digits each 14 pixels wide
    tft.drawString(buf, x, y, 4); // Value in middle
  }
  tft.setTextSize(1);
  tft.setTextPadding(0);
  // Print units, if the meter is large then use big font 4, othewise use 2
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  if (r > 84)
    tft.drawString(units, x, y + 60, 4); // Units display
  else
    tft.drawString(units, x, y + 15, 2); // Units display

  // Calculate and return right hand side x coordinate
  return x + r;
}

int ringMeterNoText(float value, float vmin, float vmax, int x, int y, int r, const char *units, byte scheme, int digit, int decimals)
{
  // int xpos = 20, ypos = 50, gap = 100, radius = 116;
  // Minimum value of r is about 52 before value text intrudes on ring
  // drawing the text first is an option

  x += r;
  y += r; // Calculate coords of centre of ring

  int w = r / 8; // Width of outer ring is 1/4 of radius

  int angle = 150; // Half the sweep angle of meter (300 degrees)

  int v = map((value * 100), (vmin * 100), (vmax * 100), -angle, angle); // Map the value to an angle v

  byte seg = 3; // Segments are 3 degrees wide = 100 segments for 300 degrees
  byte inc = 6; // Draw segments every 3 degrees, increase to 6 for segmented ring

  // Variable to save "value" text color from scheme and set default
  int color = TFT_BLUE;

  // Draw color blocks every inc degrees
  for (int i = -angle + inc / 2; i < angle - inc / 2; i += inc)
  {
    // Calculate pair of coordinates for segment start
    float sx = cos((i - 90) * 0.0174532925);
    float sy = sin((i - 90) * 0.0174532925);
    uint16_t x0 = sx * (r - w) + x;
    uint16_t y0 = sy * (r - w) + y;
    uint16_t x1 = sx * r + x;
    uint16_t y1 = sy * r + y;

    // Calculate pair of coordinates for segment end
    float sx2 = cos((i + seg - 90) * 0.0174532925);
    float sy2 = sin((i + seg - 90) * 0.0174532925);
    int x2 = sx2 * (r - w) + x;
    int y2 = sy2 * (r - w) + y;
    int x3 = sx2 * r + x;
    int y3 = sy2 * r + y;

    if (i < v)
    { // Fill in coloured segments with 2 triangles
      switch (scheme)
      {
      case 0:
        color = TFT_RED;
        break; // Fixed color
      case 1:
        color = TFT_GREEN;
        break; // Fixed color
      case 2:
        color = TFT_BLUE;
        break; // Fixed color
      case 3:
        color = rainbow(map(i, -angle, angle, 0, 127));
        break; // Full spectrum blue to red
      case 4:
        color = rainbow(map(i, -angle, angle, 70, 127));
        break; // Green to red (high temperature etc)
      case 5:
        color = rainbow(map(i, -angle, angle, 127, 63));
        break; // Red to green (low battery etc)
      default:
        color = TFT_BLUE;
        break; // Fixed color
      }
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, color);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, color);
      // text_colour = color; // Save the last color drawn
    }
    else // Fill in blank segments
    {
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_GREY);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_GREY);
    }
  }
  // Convert value to a string
  char buf[10];
  byte len = 5;
  dtostrf(value, len, 2, buf);
  buf[len] = ' ';
  buf[len + 1] = 0; // Add blanking space and terminator, helps to centre text too!

  // Set the text color to default
  tft.setTextSize(1);

  // if (value < vmin || value > vmax) {
  //   drawAlert(x, y + 90, 50, 1);
  // } else {
  //   drawAlert(x, y + 90, 50, 0);
  // }

  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  // // Uncomment next line to set the text color to the last segment value!
  // tft.setTextColor(color, TFT_BLACK);
  // tft.setTextDatum(MC_DATUM);
  // // Print value, if the meter is large then use big font 8, othewise use 4
  // if (r > 84) {
  //   tft.setTextPadding(55 * 3);    // Allow for 3 digits each 55 pixels wide
  //   tft.drawString(buf, x, y, 4);  // Value in middle
  // } else {
  //   tft.setTextPadding(3 * 14);    // Allow for 3 digits each 14 pixels wide
  //   tft.drawString(buf, x, y, 4);  // Value in middle
  // }
  // tft.setTextSize(1);
  // tft.setTextPadding(0);
  // // Print units, if the meter is large then use big font 4, othewise use 2
  // tft.setTextColor(TFT_WHITE, TFT_BLACK);
  // if (r > 84) tft.drawString(units, x, y + 60, 4);  // Units display
  // else tft.drawString(units, x, y + 15, 2);         // Units display

  // Calculate and return right hand side x coordinate
  return x + r;
}

int ringMeter1(float value, float vmin, float vmax, int x, int y, int r, const char *units, byte scheme, byte seg, byte inc)
{
  // int xpos = 20, ypos = 50, gap = 100, radius = 116;
  //  Minimum value of r is about 52 before value text intrudes on ring
  //  drawing the text first is an option

  x += r;
  y += r; // Calculate coords of centre of ring

  int w = r / 8; // Width of outer ring is 1/4 of radius

  int angle = 150; // Half the sweep angle of meter (300 degrees)

  int v = map((value * 100), (vmin * 100), (vmax * 100), -angle, angle); // Map the value to an angle v

  // byte seg = 3;  // Segments are 3 degrees wide = 100 segments for 300 degrees
  // byte inc = 6;  // Draw segments every 3 degrees, increase to 6 for segmented ring

  // Variable to save "value" text color from scheme and set default
  int color = TFT_BLUE;

  // Draw color blocks every inc degrees
  for (int i = -angle + inc / 2; i < angle - inc / 2; i += inc)
  {
    // Calculate pair of coordinates for segment start
    float sx = cos((i - 90) * 0.0174532925);
    float sy = sin((i - 90) * 0.0174532925);
    uint16_t x0 = sx * (r - w) + x;
    uint16_t y0 = sy * (r - w) + y;
    uint16_t x1 = sx * r + x;
    uint16_t y1 = sy * r + y;

    // Calculate pair of coordinates for segment end
    float sx2 = cos((i + seg - 90) * 0.0174532925);
    float sy2 = sin((i + seg - 90) * 0.0174532925);
    int x2 = sx2 * (r - w) + x;
    int y2 = sy2 * (r - w) + y;
    int x3 = sx2 * r + x;
    int y3 = sy2 * r + y;

    if (i < v)
    { // Fill in coloured segments with 2 triangles
      switch (scheme)
      {
      case 0:
        color = TFT_RED;
        break; // Fixed color
      case 1:
        color = TFT_GREEN;
        break; // Fixed color
      case 2:
        color = TFT_BLUE;
        break; // Fixed color
      case 3:
        color = rainbow(map(i, -angle, angle, 0, 127));
        break; // Full spectrum blue to red
      case 4:
        color = rainbow(map(i, -angle, angle, 70, 127));
        break; // Green to red (high temperature etc)
      case 5:
        color = rainbow(map(i, -angle, angle, 127, 63));
        break; // Red to green (low battery etc)
      default:
        color = TFT_BLUE;
        break; // Fixed color
      }
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, color);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, color);
      // text_colour = color; // Save the last color drawn
    }
    else // Fill in blank segments
    {
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_GREY);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_GREY);
    }
  }
  // Convert value to a string
  char buf[10];
  byte len = 5;
  dtostrf(value, len, 2, buf);
  buf[len] = ' ';
  buf[len + 1] = 0; // Add blanking space and terminator, helps to centre text too!

  // Set the text color to default
  tft.setTextSize(1);

  // if (value < vmin || value > vmax) {
  //   drawAlert(x, y + 90, 50, 1);
  // } else {
  //   drawAlert(x, y + 90, 50, 0);
  // }

  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  // Uncomment next line to set the text color to the last segment value!
  tft.setTextColor(color, TFT_BLACK);
  tft.setTextDatum(MC_DATUM);

  // Print value, if the meter is large then use big font 8, othewise use 4
  if (r > 84)
  {
    tft.setTextPadding(55 * 3);        // Allow for 3 digits each 55 pixels wide
    tft.drawString(buf, x, y - 20, 4); // Value in middle
  }
  else
  {
    tft.setTextPadding(3 * 14);   // Allow for 3 digits each 14 pixels wide
    tft.drawString(buf, x, y, 4); // Value in middle
  }

  tft.setTextSize(1);
  tft.setTextPadding(0);
  // Print units, if the meter is large then use big font 4, othewise use 2

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  if (r > 84)
    tft.drawString(units, x, y + 60, 4); // Units display
  else
    tft.drawString(units, x, y + 15, 2); // Units display

  // Calculate and return right hand side x coordinate
  return x + r;
}

int ringMeter2(float value, float vmin, float vmax, int x, int y, int r, const char *units, byte scheme, byte seg, byte inc, int digit, int decimals)
{
  // int xpos = 20, ypos = 50, gap = 100, radius = 116;
  //  Minimum value of r is about 52 before value text intrudes on ring
  //  drawing the text first is an option

  x += r;
  y += r; // Calculate coords of centre of ring

  int w = r / 8; // Width of outer ring is 1/4 of radius

  int angle = 150; // Half the sweep angle of meter (300 degrees)

  int v = map((value * 100), (vmin * 100), (vmax * 100), -angle, angle); // Map the value to an angle v

  // byte seg = 3;  // Segments are 3 degrees wide = 100 segments for 300 degrees
  // byte inc = 6;  // Draw segments every 3 degrees, increase to 6 for segmented ring

  // Variable to save "value" text color from scheme and set default
  int color = TFT_BLUE;

  // Draw color blocks every inc degrees
  for (int i = -angle + inc / 2; i < angle - inc / 2; i += inc)
  {
    // Calculate pair of coordinates for segment start
    float sx = cos((i - 90) * 0.0174532925);
    float sy = sin((i - 90) * 0.0174532925);
    uint16_t x0 = sx * (r - w) + x;
    uint16_t y0 = sy * (r - w) + y;
    uint16_t x1 = sx * r + x;
    uint16_t y1 = sy * r + y;

    // Calculate pair of coordinates for segment end
    float sx2 = cos((i + seg - 90) * 0.0174532925);
    float sy2 = sin((i + seg - 90) * 0.0174532925);
    int x2 = sx2 * (r - w) + x;
    int y2 = sy2 * (r - w) + y;
    int x3 = sx2 * r + x;
    int y3 = sy2 * r + y;

    if (i < v)
    { // Fill in coloured segments with 2 triangles
      switch (scheme)
      {
      case 0:
        color = TFT_RED;
        break; // Fixed color
      case 1:
        color = TFT_GREEN;
        break; // Fixed color
      case 2:
        color = TFT_BLUE;
        break; // Fixed color
      case 3:
        color = rainbow(map(i, -angle, angle, 0, 127));
        break; // Full spectrum blue to red
      case 4:
        color = rainbow(map(i, -angle, angle, 70, 127));
        break; // Green to red (high temperature etc)
      case 5:
        color = rainbow(map(i, -angle, angle, 127, 63));
        break; // Red to green (low battery etc)
      default:
        color = TFT_BLUE;
        break; // Fixed color
      }
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, color);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, color);
      // text_colour = color; // Save the last color drawn
    }
    else // Fill in blank segments
    {
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_GREY);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_GREY);
    }
  }
  // Convert value to a string
  char buf[10];
  byte len = 5;
  dtostrf(value, len, 2, buf);
  buf[len] = ' ';
  buf[len + 1] = 0; // Add blanking space and terminator, helps to centre text too!

  // Set the text color to default
  tft.setTextSize(1);

  // if (value < vmin || value > vmax) {
  //   drawAlert(x, y + 90, 50, 1);
  // } else {
  //   drawAlert(x, y + 90, 50, 0);
  // }

  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  // Uncomment next line to set the text color to the last segment value!
  tft.setTextColor(color, TFT_BLACK);
  tft.setTextDatum(MC_DATUM);

  // Print value, if the meter is large then use big font 8, othewise use 4

  // tft.setTextPadding(55 * 3);    // Allow for 3 digits each 55 pixels wide
  tft.drawString(buf, x, y + 80, 4); // Value in middle

  tft.setTextSize(1);
  tft.setTextPadding(0);
  // Print units, if the meter is large then use big font 4, othewise use 2

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawString(units, x, y + 110, 4); // Units display

  // Calculate and return right hand side x coordinate
  return x + r;
}

void gaugeArc(float value, float min, float max, int x, int y, int r, int arcWidth, int totalAngle, byte scheme, byte numSegments, byte numIncrements, int digits, int decimals)
{

  int color = TFT_BLUE;

  // Get center of arc
  x += r;
  y += r;

  // Ring width
  int w = r / arcWidth;

  // half of arc total angle (300 deg)
  int angle = totalAngle / 2;

  // Get the angle based on the current value, limited to max/min angle based on max/min value
  int v = map((value * 100), (min * 100), (max * 100), -1 * angle, angle);

  // Draw color blocks for given number of increments
  for (int i = -angle + numIncrements / 2; i < angle - numIncrements / 2; i += numIncrements)
  {

    // Calculate pair of coordinates for segment start
    float sx = cos((i - 90) * 0.0174532925);
    float sy = sin((i - 90) * 0.0174532925);
    uint16_t x0 = sx * (r - w) + x;
    uint16_t y0 = sy * (r - w) + y;
    uint16_t x1 = sx * r + x;
    uint16_t y1 = sy * r + y;

    // Calculate pair of coordinates for segment end
    float sx2 = cos((i + numSegments - 90) * 0.0174532925);
    float sy2 = sin((i + numSegments - 90) * 0.0174532925);
    int x2 = sx2 * (r - w) + x;
    int y2 = sy2 * (r - w) + y;
    int x3 = sx2 * r + x;
    int y3 = sy2 * r + y;

    if (i < v)
    { // Fill in coloured segments with 2 triangles
      switch (scheme)
      {
      case 0:
        color = TFT_RED;
        break; // Fixed color
      case 1:
        color = TFT_GREEN;
        break; // Fixed color
      case 2:
        color = TFT_BLUE;
        break; // Fixed color
      case 3:
        color = rainbow(map(i, -angle, angle, 0, 127));
        break; // Full spectrum blue to red
      case 4:
        color = rainbow(map(i, -angle, angle, 70, 127));
        break; // Green to red (high temperature etc)
      case 5:
        color = rainbow(map(i, -angle, angle, 127, 63));
        break; // Red to green (low battery etc)
      case 6:
        color = TFT_WHITE;
        break;
      case 7:
        color = TFT_BLACK;
        break;
      case 8:
        color = customArcColor[0];
        break;
      case 9:
        color = customArcColor[1];
        break;

      default:
        color = TFT_BLUE;
        break; // Fixed color
      }

      tft.fillTriangle(x0, y0, x1, y1, x2, y2, color);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, color);
    }

    else // Fill in blank segments
    {
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_GREY);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_GREY);
    }
  }
}

void gaugeArcInvert(float value, float min, float max, int x, int y, int r, int arcWidth, int totalAngle, byte scheme, byte numSegments, byte numIncrements, int digits, int decimals)
{

  int color = TFT_BLUE;

  // Get center of arc
  x += r;
  y += r;

  // Ring width
  int w = r / arcWidth;

  // half of arc total angle (300 deg)
  int angle = totalAngle / 2;

  // Get the angle based on the current value, limited to max/min angle based on max/min value
  int v = map((value * 100), (min * 100), (max * 100), -1 * angle, angle);

  // Draw color blocks for given number of increments
  for (int i = -angle + numIncrements / 2; i < angle - numIncrements / 2; i += numIncrements)
  {

    // Calculate pair of coordinates for segment start
    float sx = cos((i - 90) * 0.0174532925);
    float sy = -sin((i - 90) * 0.0174532925);
    uint16_t x0 = sx * (r - w) + x;
    uint16_t y0 = sy * (r - w) + y;
    uint16_t x1 = sx * r + x;
    uint16_t y1 = sy * r + y;

    // Calculate pair of coordinates for segment end
    float sx2 = cos((i + numSegments - 90) * 0.0174532925);
    float sy2 = -sin((i + numSegments - 90) * 0.0174532925);
    int x2 = sx2 * (r - w) + x;
    int y2 = sy2 * (r - w) + y;
    int x3 = sx2 * r + x;
    int y3 = sy2 * r + y;

    if (i < v)
    { // Fill in coloured segments with 2 triangles
      switch (scheme)
      {
      case 0:
        color = TFT_RED;
        break; // Fixed color
      case 1:
        color = TFT_GREEN;
        break; // Fixed color
      case 2:
        color = TFT_BLUE;
        break; // Fixed color
      case 3:
        color = rainbow(map(i, -angle, angle, 0, 127));
        break; // Full spectrum blue to red
      case 4:
        color = rainbow(map(i, -angle, angle, 70, 127));
        break; // Green to red (high temperature etc)
      case 5:
        color = rainbow(map(i, -angle, angle, 127, 63));
        break; // Red to green (low battery etc)
      case 6:
        color = TFT_WHITE;
        break;
      case 7:
        color = TFT_BLACK;
        break;
      case 8:
        color = customArcColor[0];
        break;
      case 9:
        color = customArcColor[1];
        break;

      default:
        color = TFT_BLUE;
        break; // Fixed color
      }

      tft.fillTriangle(x0, y0, x1, y1, x2, y2, color);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, color);
    }

    else // Fill in blank segments
    {
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_GREY);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_GREY);
    }
  }
}

void gaugeText(float value, float min, float max, int x, int y, int fontSize, const char *units, const char *name, int color, int color2, bool printUnits, bool printname, int unitOffset, bool alert, int alertColor, int digit, int decimals)
{

  // if (name == "None") {return;}

  // Convert value to a string
  char buf[10];
  byte len = 5;

  if (value >= 10 && decimals > 1){
    decimals = 1;
  }

    if (value >= 100 && decimals > 0){
    decimals = 0;
  }

  dtostrf(value, digit, decimals, buf);

  buf[len] = ' ';

  // Add blanking space and terminator, helps to centre text too!
  buf[len + 1] = 0;

  tft.setTextSize(1);
  tft.setTextColor(color, TFT_BLACK);

  if (alert == true)
  {

    tft.setTextColor(alertColor, TFT_BLACK);
  }

  // Uncomment next line to set the text color to the last segment value!
  // tft.setTextColor(color, TFT_BLACK);
  tft.setTextDatum(MC_DATUM);

  switch (fontSize)
  {

  case 0:
    tft.setTextPadding(3 * 14);
    tft.drawString(buf, x, y, 2);
    break;

  case 1:
    tft.setTextPadding(8 * 3);
    tft.drawString(buf, x, y, 4);
    break;

  case 3:
    tft.setTextPadding(25 * 5);
    tft.drawString(buf, x - 5, y - 10, 6);
    break;

  case 4:
    tft.setTextPadding(25 * 5);
    tft.drawString(buf, x, y - 10, 6);
    break;

  case 5:
    tft.setTextPadding(500);
    tft.drawString(buf, x + 15, y - 20, 8);
    break;

  case 6:
    tft.setTextPadding(125);
    tft.drawString(buf, x + 15, y - 20, 6);
    break;

  default:
    tft.setTextPadding(8 * 3);
    tft.drawString(buf, x, y, 4);
    break;
  }

  tft.setTextSize(1);
  tft.setTextPadding(0);

  if (printUnits == true)
  {

    tft.setTextColor(color2, TFT_BLACK);

    switch (fontSize)
    {

    case 0:
      tft.drawString(units, x, y + unitOffset, 2);
      break;

    case 1:
      tft.drawString(units, x, y + unitOffset, 2);
      break;

    case 3:
      tft.drawString(units, x + 55, y + unitOffset + 15, 4);
      break;

    case 4:
      tft.drawString(units, x, y + unitOffset + 15, 4);
      break;

    case 5:
      tft.drawString(units, x + 180, y + unitOffset + 32, 4);
      break;

    case 6:
      tft.drawString(units, x + 40, y + 9, 2);
      break;


    default:
      tft.drawString(units, x, y + unitOffset, 2);
      break;
    }
  }

  if (printname == true)
  {

    switch (fontSize)
    {

      tft.setTextColor(color2, TFT_BLACK);
    case 0:
      tft.drawString(name, x, y - unitOffset - 5, 2);
      break;

    case 1:
      tft.drawString(name, x, y - unitOffset - 5, 2);
      break;

    case 3:
      tft.drawString(name, x - 65, y + unitOffset + 15, 4);
      break;

    case 4:
      tft.drawString(name, x, y - unitOffset - 40, 4);
      break;

    case 5:
      tft.drawString(name, x - 42, y + unitOffset + 32, 4);
      break;

    case 6:
      tft.drawString(name, x- 12, y + 9, 2);
      break;

    default:
      tft.drawString(name, x, y - unitOffset - 5, 2);
      break;
    }
  }
}

void gaugeText2(float value, float min, float max, int x, int y, int fontSize, const char *units, int color, int color2, bool printUnits, int unitOffset, bool alert, int alertColor, int digit, int decimals)
{

  // Convert value to a string
  char buf[10];
  byte len = 5;

  dtostrf(value, len, 2, buf);

  buf[len] = ' ';

  // Add blanking space and terminator, helps to centre text too!
  buf[len + 1] = 0;

  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  if (alert == true)
  {

    tft.setTextColor(TFT_RED, TFT_BLACK);
  }

  // Uncomment next line to set the text color to the last segment value!
  // tft.setTextColor(color, TFT_BLACK);
  tft.setTextDatum(MC_DATUM);

  // if (fontSize > 0)
  {
    tft.setTextPadding(8 * 3);    // Allow for 3 digits each 55 pixels wide
    tft.drawString(buf, x, y, 4); // Value in middle
  }
  // else
  // {
  //    tft.setTextPadding(3 * 14);       // Allow for 3 digits each 14 pixels wide
  //   tft.drawString(buf, x, y, 2); // Value in middle
  // }

  tft.setTextSize(1);
  // tft.setTextPadding(0);
  //  Print units, if the meter is large then use big font 4, othewise use 2

  if (printUnits == true)
  {
    tft.setTextColor(color2, TFT_BLACK);
    if (fontSize > 0)
      tft.drawString(units, x, y + unitOffset * 2, 4); // Units display
    else
      tft.drawString(units, x, y + unitOffset, 2); // Units display
  }
}
void otaShowUpdate(int updateStatus)
{
}