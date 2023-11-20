#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "RGB.h"

RGB::RGB(int red, int green, int blue){
    red_pin = red;
    green_pin = green;
    blue_pin = blue;
    pinMode(red_pin, OUTPUT);
    pinMode(green_pin, OUTPUT);
    pinMode(blue_pin, OUTPUT);
}

void RGB::set_rgb(int red, int green, int blue){
    analogWrite(red_pin, 255 - red);
    analogWrite(green_pin, 255 - green);
    analogWrite(blue_pin, 255 - blue);
}

void RGB::white(){
    set_rgb(255, 255, 255);
}

void RGB::red(){
    set_rgb(255, 0, 0);
}

void RGB::blue(){
    set_rgb(0, 0, 255);
}

void RGB::green(){
    set_rgb(0, 255, 0);
}

void RGB::magenta(){
    set_rgb(255, 0, 255);
}

void RGB::cyan(){
    set_rgb(0, 255, 255);
}

void RGB::turnoff(){
    set_rgb(0, 0, 0);
}

void RGB::yellow(){
    set_rgb(255, 255, 0);
}
