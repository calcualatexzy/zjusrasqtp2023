#ifndef __SMALLCAR_H__
#define __SMALLCAR_H__
#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include"PIDRouting.h"
#include"Robotarm.h"
#include"CK008.h"

class SMALLCAR
{
    public:
        SMALLCAR(PIDCAR* car, SMALLCARARM* arm, SIDEHAND* hand, CK008** sw_list);
        void init();
        void first_step();
        void first_step_to_gainring();

        void gostraight(int length, double speed_level = 1.0, bool arm_forbid = true);
        void turnleft(int next_dir = DIR_FRONT);
        void turnright(int next_dir = DIR_FRONT);
        void goback(int length, double speed_level = 1.0, bool arm_forbid = true, bool adjust = 1);

        void grab_gain_ring();
        void grab_nrom_ring();
        void place_lower_back();
        void place_higher_back();
        void place_lower_front();
        void place_higher_front();

        void remove_lower();
        void remove_higher();

        void hands_up();
        void hands_front();
        void hands_back();

        void _stop();

        bool switch_detect(int num);
    private:
        PIDCAR* CAR;
        SMALLCARARM* ARM;
        SIDEHAND* HAND;
        CK008* SW_1;
        CK008* SW_2;
        CK008* SW_3;
        CK008* SW_4;
};

#endif