#ifndef __CRUISINGMODULE_H__
#define __CRUISINGMODULE_H__

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include"greyscalesensor.h"

#define STRAIGHT    1
#define LEFT        2
#define EXTRALEFT   3
#define RIGHT       4
#define EXTRARIGHT  5
#define CROSS       6

class CRUISINGMODULE
{
    public:
        CRUISINGMODULE(int Lpin, int Mpin, int Rpin, int line_color, int compare);
        int get_pose();
        bool on_line();
        bool M_on_line();
        bool L_on_line();
        bool R_on_line();
    private:
        GREYSCALESENSOR L_sensor, M_sensor, R_sensor;
};

#endif