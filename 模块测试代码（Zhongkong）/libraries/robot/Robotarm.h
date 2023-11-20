#ifndef __ROBOTARM_H__
#define __ROBOTARM_H__

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include<Servo.h>

class ROBOTARM
{
    public:
        ROBOTARM(int servo_num, Servo** servo_list, int* servo_pin);
        void init();
        void rotate(int num, int angle);
    private:
        Servo** SERVO_LIST;
        int SERVO_NUM;
        int* SERVO_PIN;
};

class SMALLCARARM
{
    public:
        SMALLCARARM(Servo** servo_list, int* servo_pin);
        void init();

        void rotate_claw(int angle);
        void rotate_upper(int angle);
        void rotate_mid(int angle);
        void rotate_lower(int angle);

        void first_marching();
        void marching();
        void grab_ring();
        void close_claw();
        void open_claw();
        void grab_gainRing1();
        void grab_gainRing2();
        void placing_lower_back();
        void placing_higher_back();
        void placing_lower_front();
        void placing_higher_front();
        void remove_higher();
        void remove_lower();
    private:
        ROBOTARM ARM;
};

class SIDEHAND
{
    public:
        SIDEHAND(Servo** servo_list, int* servo_pin);
        void init();

        void hand_up();
        void hand_front();
        void hand_back();
    private:
        ROBOTARM HAND;
};

class BIGCARARM
{
    public:
        BIGCARARM(Servo** servo_list, int* servo_pin);
        void init();

        void rotate_claw(int angle);
        void rotate_wrist(int angle);
        void rotate_turntable(int angle);

        void claw_open();
        void claw_close();

        void grab(bool pre_place = false);
        void placing_lower();
        void placing_higher();
        void block();

        void place_hat();
    private:
        ROBOTARM ARM;
};

#endif