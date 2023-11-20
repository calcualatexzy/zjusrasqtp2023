#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include"smallcar.h"

SMALLCAR::SMALLCAR(PIDCAR* car, SMALLCARARM* arm, SIDEHAND* hand, CK008** sw_list)
{
    CAR = car;
    ARM = arm;
    HAND = hand;
    SW_1 = sw_list[0];
    SW_2 = sw_list[1];
    SW_3 = sw_list[2];
    SW_4 = sw_list[3];
}

void SMALLCAR::init()
{
    CAR->init();
    ARM->init();
    HAND->init();
}

void SMALLCAR::first_step()
{
    CAR->gostraight(1, 0.5, true);
    ARM->marching();
    HAND->hand_front();
}

void SMALLCAR::first_step_to_gainring()
{
    CAR->gostraight(1, 0.5, true);
    ARM->grab_gainRing1();
}

void SMALLCAR::gostraight(int length, double speed_level, bool arm_forbid)
{
    if(!arm_forbid)
        ARM->marching();
    CAR->gostraight(length, speed_level);
}

void SMALLCAR::goback(int length, double speed_level, bool arm_forbid, bool adjust)
{
    if(!arm_forbid)
        ARM->marching();
    CAR->goback(length, speed_level, adjust);
}

void SMALLCAR::turnleft(int next_dir)
{
    CAR->turnleft(next_dir);
}

void SMALLCAR::turnright(int next_dir)
{
    CAR->turnright(next_dir);
}

void SMALLCAR::grab_gain_ring()
{
    CAR->move_back(550, 0.7);
    delay(300);
    ARM->grab_gainRing1();
    ARM->grab_gainRing2();
    CAR->gostraight(1);
}

void SMALLCAR::grab_nrom_ring()
{
    ARM->grab_ring();
    CAR->move_forward(300, 0.7);
    ARM->close_claw();
    CAR->gostraight(1);
}

void SMALLCAR::place_lower_front()
{
    CAR->move_forward(200, 0.5);
    ARM->placing_lower_front();
    CAR->goback(1);
}

void SMALLCAR::place_higher_front()
{
    CAR->move_forward(500, 0.7);
    ARM->placing_higher_front();
    CAR->goback(1);
}

void SMALLCAR::place_higher_back()
{
    CAR->move_back(550, 0.7);
    ARM->placing_higher_back();
    ARM->marching();
    CAR->gostraight(1);
}

void SMALLCAR::place_lower_back()
{
    CAR->move_back(200, 0.5);
    ARM->placing_lower_back();
    ARM->marching();
    CAR->gostraight(1);
}

void SMALLCAR::remove_lower()
{
    CAR->move_back(200, 0.7);
    ARM->remove_lower();
    ARM->marching();
    CAR->gostraight(1);
}

void SMALLCAR::remove_higher()
{
    CAR->move_back(500, 0.7);
    ARM->remove_higher();
    delay(500);
    ARM->marching();
    delay(200);
    CAR->gostraight(1);
}

void SMALLCAR::hands_up()
{
    HAND->hand_up();
}

void SMALLCAR::hands_front()
{
    HAND->hand_front();
}

void SMALLCAR::hands_back()
{
    HAND->hand_back();
}

bool SMALLCAR::switch_detect(int num)
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

void SMALLCAR::_stop()
{
    CAR->_stop();
}