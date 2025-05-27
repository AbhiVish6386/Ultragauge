#include <Wire.h>
#include <U8g2lib.h>
#include "car_frames.h"
#include <Arduino.h>
#include "Button.h"
#include "u8g2_oledPrint.h"

// Define pin constants
#define Trig_Pin 5
#define Echo_pin 18
#define Buzz 4
#define BUTTON_PIN 19
Button myButton(BUTTON_PIN); // Button object created

// Create  object for SH1106 128x64 OLED
U8G2_SH1106_128X64_NONAME_F_HW_I2C display(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

float avg_Distance()
{
  float sum = 0;
  int no_sample = 5;

  for (int i = 0; i < no_sample; i++)
  {
    digitalWrite(Trig_Pin, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig_Pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig_Pin, LOW);

    long duration = pulseIn(Echo_pin, HIGH, 20000);
    float distance = (duration * 0.0343) / 2;
    sum += distance;
    delay(25);
  }
  return sum / no_sample;
}

int scalemode = 0; // 0=cm, 1=inch, 2=feet, 3=meter
bool lastButtonState = LOW;

void carAnimation(unsigned long duration_ms)
{
  unsigned long start = millis();
  while (millis() - start < duration_ms)
  {
    for (int i = 0; i < 27; i++)
    {
      display.clearBuffer();
      display.drawXBMP(4, 4, 120, 56, frames[i]);
      display.sendBuffer();
      delay(50);
    }
  }
}

void showWelcomeScreens()
{
  display.clearBuffer();
  carAnimation(2000);
  display.clearBuffer();

  // Screen 1
  oledPrint(display, u8g2_font_ncenR14_tr, 22, 28, "Welcome");
  oledPrint(display, u8g2_font_6x10_tr, 105, 56, "To:");
  display.sendBuffer();
  delay(2000);
  display.clearBuffer();

  // Screen 2
  oledPrint(display, u8g_font_ncenR14r, 8, 28, "Ultragauge");
  oledPrint(display, u8g2_font_6x10_tr, 0, 56, "Get Distance Digitaly");
  display.sendBuffer();
  delay(2000);
  display.clearBuffer();

  // Screen 3
  oledPrint(display, u8g_font_ncenR14r, 4, 28, "Powered By");
  oledPrint(display, u8g2_font_6x10_tr, 72, 56, "Abhishek");
  display.sendBuffer();
  delay(2000);
  display.clearBuffer();
}

void setup()
{
  Wire.begin();
  display.begin();
  Serial.begin(115200);
  myButton.begin();

  pinMode(Trig_Pin, OUTPUT);
  pinMode(Echo_pin, INPUT);
  pinMode(Buzz, OUTPUT);

  showWelcomeScreens();
}

void loop()
{
  float distance = avg_Distance();

  // Button Debounce Fix
  if (myButton.isPressed())
  {
    scalemode = (scalemode + 1) % 3;
  }

  String unit;
  switch (scalemode)
  {
  case 0:
    unit = "cm";
    break;
  case 1:
    distance /= 2.54;
    unit = "inch";
    break;
  case 2:
    distance /= 30.48;
    unit = "feet";
    break;
  case 3:
    distance /= 100.0;
    unit = "Mtr.";
    break;
  }

  Serial.print("\rDistance: ");
  Serial.print(distance);
  Serial.print(" ");
  Serial.print(unit);

  float collapse = 4;
  if (scalemode == 1)
    collapse = 1.57;
  if (scalemode == 2)
    collapse = 0.13;
  if (scalemode == 3)
    collapse = 0.04;

  display.clearBuffer();
  oledPrint(display, u8g2_font_6x10_tr, 10, 10, "Distance Measured");

  if (distance <= collapse)
  {
    oledPrint(display, u8g_font_ncenB14r, 8, 35, "Too Close!");
    digitalWrite(Buzz, HIGH);
  }
  else
  {
    digitalWrite(Buzz, LOW);
    oledPrint(display, u8g2_font_ncenB14_tr, 40, 45, distance, 1);
  }
  oledPrint(display, u8g2_font_6x10_tr, 100, 56, unit.c_str());
  display.sendBuffer();

  delay(250);
}
