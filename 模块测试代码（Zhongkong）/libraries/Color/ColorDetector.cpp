#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "ColorDetector.h"

#define judge_red(r,g,b) ((g) - (r) > 100 && (b) - (r) > 100)
#define judge_blue(r,g,b) ((g) - (b) > 100 && (r) - (b) > 100)
#define judge_green(r,g,b) ((r) - (g) > 10 && (b) - (g) > 10)

/**
 * @param S0
 * @param S1
 * @param S2
 * @param S3
 * @param OUT
 */
ColorDetector::ColorDetector(int S0, int S1, int S2, int S3, int OUT)
{
    pinS0 = S0;
    pinS1 = S1;
    pinS2 = S2;
    pinS3 = S3;
    pinOUT = OUT;
    pinMode(pinS0, OUTPUT);
    pinMode(pinS1, OUTPUT);
    pinMode(pinS2, OUTPUT);
    pinMode(pinS3, OUTPUT);
    pinMode(pinOUT, INPUT);
    digitalWrite(pinS0, HIGH);
    digitalWrite(pinS1, LOW);
}

String ColorDetector::color()
{   
    int r = process_red_value();
    delay(10);
    int g = process_green_value();
    delay(10);
    int b = process_blue_value();
    delay(10);
    if (300 < r+b+g && r+b+g < 2000)
    {
        if (judge_red(r,g,b)) return "red";
        else if (judge_blue(r,g,b)) return "blue";
        else if (judge_green(r,g,b)) return "green";
    }
    return "unknown";
}
int ColorDetector::red()
{
    return process_red_value();
}

int ColorDetector::green()
{
    return process_green_value();
}

int ColorDetector::blue()
{
    return process_blue_value();
}

int ColorDetector::process_red_value()
{
  digitalWrite(pinS2, LOW);
  digitalWrite(pinS3, LOW);
  return pulseIn(pinOUT, LOW);
}
int ColorDetector::process_green_value()
{
  digitalWrite(pinS2, HIGH);
  digitalWrite(pinS3, HIGH);
  return pulseIn(pinOUT, LOW);
}
int ColorDetector::process_blue_value()
{
  digitalWrite(pinS2, LOW);
  digitalWrite(pinS3, HIGH);
  return pulseIn(pinOUT, LOW);
}