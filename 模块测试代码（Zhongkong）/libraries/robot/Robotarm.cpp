#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include"Robotarm.h"
#include<Servo.h>

ROBOTARM::ROBOTARM(int servo_num, Servo** servo_list, int* servo_pin)
{
    SERVO_NUM = servo_num;
    SERVO_LIST = servo_list;
    SERVO_PIN = servo_pin;
    return;
}

void ROBOTARM::rotate(int num, int angle)
{
    int anglex = SERVO_LIST[num - 1]->read();
    if (angle > anglex){
        for (int i = anglex;i < angle;i++){
            SERVO_LIST[num - 1]->write(i);
            delay(8);
        }
    }
    else if (angle < anglex){
        for (int i = anglex;i > angle;i--){
            SERVO_LIST[num - 1]->write(i);
            delay(8);
        }
    }
}

void ROBOTARM::init()
{
    for(int i = 0; i < SERVO_NUM; i++)
    {
        SERVO_LIST[i]->attach(SERVO_PIN[i]);
    }
}

SMALLCARARM::SMALLCARARM(Servo** servo_list, int* servo_pin) : ARM(4, servo_list, servo_pin)
{}

void SMALLCARARM::init()
{
    ARM.init();
    rotate_lower(65);
    rotate_mid(2);
    rotate_lower(29);
    rotate_upper(105);
}

void SMALLCARARM::rotate_claw(int angle)
{
    ARM.rotate(1, angle);
}

void SMALLCARARM::rotate_upper(int angle)
{
    ARM.rotate(2, angle);
}

void SMALLCARARM::rotate_mid(int angle)
{
    ARM.rotate(3, angle);
}

void SMALLCARARM::rotate_lower(int angle)
{
    ARM.rotate(4, angle);
}

void SMALLCARARM::first_marching()
{
    rotate_lower(65);
    rotate_mid(2);
    rotate_lower(29);
    rotate_upper(150);
}

void SMALLCARARM::marching()
{
    rotate_lower(29);
    delay(100);
    rotate_mid(2);
    rotate_upper(150);
}

void SMALLCARARM::grab_ring()
{
    open_claw();
    rotate_upper(173);
    rotate_lower(45);
    rotate_mid(25);
    rotate_lower(161);
}

void SMALLCARARM::close_claw()
{
    rotate_claw(113);
}

void SMALLCARARM::open_claw()
{
    rotate_claw(90);
}

void SMALLCARARM::grab_gainRing1()
{
    open_claw();
    rotate_upper(65);
    rotate_lower(63);
    rotate_mid(162);
    delay(500);
}

void SMALLCARARM::grab_gainRing2()
{
    close_claw();
    delay(500);
    rotate_mid(2);
    rotate_lower(29);
    rotate_upper(140);
}

void SMALLCARARM::placing_lower_back()
{
    rotate_lower(40);
    rotate_mid(52);
    rotate_upper(150);
    delay(200);
    close_claw();
}

void SMALLCARARM::placing_higher_back()
{
    rotate_lower(40);
    delay(200);
    rotate_mid(40);
    rotate_upper(155);
    delay(500);
    open_claw();
}

void SMALLCARARM::placing_lower_front()
{
    rotate_lower(48);
    rotate_mid(2);
    rotate_upper(68);
    delay(200);
    open_claw();
}

void SMALLCARARM::placing_higher_front()
{
    rotate_lower(48);
    rotate_mid(2);
    rotate_upper(75);
    delay(200);
    open_claw();
}

void SMALLCARARM::remove_lower()
{
    open_claw();
    rotate_lower(50);
    rotate_mid(95);
    rotate_upper(163);
    delay(200);
    rotate_claw(110);
    delay(200);
    rotate_mid(102);
    rotate_lower(90);
    delay(200);
    rotate_upper(50);

    close_claw();
}

void SMALLCARARM::remove_higher()
{
    open_claw();
    rotate_lower(50);
    rotate_mid(100);
    delay(200);
    close_claw();
    delay(200);
    rotate_lower(90);
    rotate_mid(50);
    rotate_upper(100);
    open_claw(); 
}

SIDEHAND::SIDEHAND(Servo** servo_list, int* servo_pin) : HAND(2, servo_list, servo_pin)
{}

void SIDEHAND::init()
{
    HAND.init();
    hand_up();
}

void SIDEHAND::hand_up()
{
    HAND.rotate(1, 90);
    HAND.rotate(2, 90);
}

void SIDEHAND::hand_front()
{
    HAND.rotate(1, 45);
    HAND.rotate(2, 135);
}

void SIDEHAND::hand_back()
{
    HAND.rotate(1, 180);
    HAND.rotate(2, 0);
}

BIGCARARM::BIGCARARM(Servo** servo_list, int* servo_pin) : ARM(3, servo_list, servo_pin)
{}

void BIGCARARM::init()
{
    ARM.init();
    rotate_turntable(175);
    rotate_wrist(0);
    claw_open();
    delay(1000);
    claw_close();
}

void BIGCARARM::rotate_claw(int angle)
{
    ARM.rotate(1, angle);
}

void BIGCARARM::rotate_wrist(int angle)
{
    ARM.rotate(2, angle);
}

void BIGCARARM::rotate_turntable(int angle)
{
    ARM.rotate(3, angle);
}

void BIGCARARM::claw_close()
{
    rotate_claw(53);
}

void BIGCARARM::claw_open()
{
    rotate_claw(130);
}

void BIGCARARM::placing_lower()
{
    rotate_wrist(130);
    rotate_turntable(90);
    delay(200);
    claw_open();
    rotate_turntable(130);
    rotate_wrist(0);
}

void BIGCARARM::placing_higher()
{
    rotate_wrist(130);
    rotate_turntable(160);
    delay(200);
    claw_open();
    rotate_wrist(150);
    rotate_turntable(170);  
}

void BIGCARARM::grab(bool pre_place)
{
    rotate_wrist(0);
    rotate_turntable(28);
    claw_open();
    delay(200);
    rotate_turntable(0);
    delay(200);
    claw_close();
    if(pre_place)
        rotate_turntable(170);
    else
        rotate_turntable(60);
    return;
}

void BIGCARARM::block()
{
    rotate_wrist(130);
    rotate_turntable(140);
}
