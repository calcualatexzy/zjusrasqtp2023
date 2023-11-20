#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include"bigcar.h"

BIGCAR::BIGCAR(TWOWHEELPIDCAR* car, BIGCARARM* arm, CK008** sw_list)
{
    CAR = car;
    ARM = arm;
    SW_1 = sw_list[0];
    SW_2 = sw_list[1];
    SW_3 = sw_list[2];
    SW_4 = sw_list[3];
}

void BIGCAR::init()
{
    CAR->init();
    ARM->init();
}

void BIGCAR::gostraight(int length, double speed_level)
{
    CAR->gostraight(length, speed_level);
}

void BIGCAR::turnleft()
{
    CAR->turnleft();
}

void BIGCAR::turnright()
{
    CAR->turnright();
}

void BIGCAR::_stop()
{
    CAR->_stop();
}

bool BIGCAR::switch_detect(int num)
{
    switch (num)
    {
    case 1:
        if(SW_1->detect() == TOUCHED)
            return 1;
        else
            return 0;
        break;
    case 2:
        if(SW_2->detect() == TOUCHED)
            return 1;
        else
            return 0;
        break;
    case 3:
        if(SW_3->detect() == TOUCHED)
            return 1;
        else
            return 0;
        break;
    case 4:
        if(SW_4->detect() == TOUCHED)
            return 1;
        else
            return 0;
        break;
    
    default:
        break;
    }
}

void BIGCAR::grab(bool pre_place)
{
    ARM->grab(pre_place);
}

void BIGCAR::place_lower()
{
    CAR->move_forward(200, 0.7);
    ARM->placing_lower();
    CAR->goback(2);
}

void BIGCAR::place_higher()
{
    CAR->move_forward(1000, 0.8);
    delay(400);
    ARM->placing_higher();
}

void BIGCAR::block()
{
    ARM->block();
}

void BIGCAR::place_hat()
{
    CAR->move_forward(1000, 0.8);
    ARM->rotate_turntable(150);
    ARM->claw_open();
    CAR->goback(1);
}