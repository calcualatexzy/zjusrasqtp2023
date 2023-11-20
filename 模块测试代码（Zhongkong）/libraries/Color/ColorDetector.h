#ifndef COLORDETECOR_H
#define COLORDETECOR_H
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <SoftwareSerial.h>

class ColorDetector{
    public:
        ColorDetector(int S0, int S1, int S2, int S3, int OUT);
        String color(); 
        int red();
        int green();
        int blue();
    private:
        int pinS0;
        int pinS1;
        int pinS2;
        int pinS3;
        int pinOUT; 
        int process_red_value();
        int process_green_value();
        int process_blue_value();
};

#endif