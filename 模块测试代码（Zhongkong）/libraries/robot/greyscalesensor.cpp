#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include"greyscalesensor.h"

GREYSCALESENSOR::GREYSCALESENSOR(int pin, int line_color, int compare) : PIN(pin), LINE(line_color), CMP(compare)
{
    pinMode(pin, INPUT);
}

int GREYSCALESENSOR::read_value()
{
    return analogRead(PIN);
}

bool GREYSCALESENSOR::is_line()
{
    if(read_value() * LINE > CMP * LINE)
        return true;
    else
        return false;
}