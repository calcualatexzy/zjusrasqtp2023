#ifndef __GREYSCALESENSOR_H__
#define __GREYSCALESENSOR_H__

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define WHITE 1
#define BLACK -1
#define LINE_VALUE_LOW -1
#define LINE_VALUE_HIGH 1

class GREYSCALESENSOR
{
    public:
        GREYSCALESENSOR(int pin, int line_color, int compare);
        int read_value();
        bool is_line();
        int CMP;
    private:
        int PIN;
        int LINE;
};

#endif