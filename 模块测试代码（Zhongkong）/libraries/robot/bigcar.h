#ifndef __BIGCAR_H__
#define __BIGCAR_H__
#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include"PIDRouting.h"
#include"CK008.h"
#include"Robotarm.h"

class BIGCAR
{
    public:
        BIGCAR(TWOWHEELPIDCAR* car, BIGCARARM* arm, CK008** sw_list);
        void init();

        void gostraight(int length, double speed_level = 1.0);
        void turnleft();
        void turnright();
        void _stop();

        void grab(bool pre_place = false);
        void place_lower();
        void place_higher();
        void block();
        void place_hat();

        bool switch_detect(int num);
    private:
        TWOWHEELPIDCAR* CAR;
        BIGCARARM* ARM;
        CK008* SW_1;
        CK008* SW_2;
        CK008* SW_3;
        CK008* SW_4;
};

#endif