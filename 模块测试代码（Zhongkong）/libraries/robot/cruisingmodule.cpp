#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include"cruisingmodule.h"

CRUISINGMODULE::CRUISINGMODULE(int Lpin, int Mpin, int Rpin, int line_color, int compare) : L_sensor(Lpin, -line_color, compare), M_sensor(Mpin, -line_color, compare), R_sensor(Rpin, -line_color, compare)
{}

int CRUISINGMODULE::get_pose()
{
    bool LD = L_sensor.is_line();
    bool RD = R_sensor.is_line();
    bool MD = M_sensor.is_line();

    if (MD && !LD && !RD)
        return STRAIGHT;
    else if (MD && LD && !RD)
        return LEFT;
    else if (!MD && LD && !RD)
        return EXTRALEFT;
    else if (MD && !LD && RD)
        return RIGHT;
    else if (!MD && !LD && RD)
        return EXTRARIGHT;
    else
        return STRAIGHT;
}

bool CRUISINGMODULE::on_line()
{
    return M_sensor.is_line();
}

bool CRUISINGMODULE :: M_on_line()
{
    return M_sensor.is_line();
}

bool CRUISINGMODULE :: R_on_line()
{
    return R_sensor.is_line();
}

bool CRUISINGMODULE :: L_on_line()
{
    return L_sensor.is_line();
}