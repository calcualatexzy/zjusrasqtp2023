#include<TB6612.h>

#define MotorAIN1 2
#define MotorAIN2 4
#define MotorBIN1 8
#define MotorBIN2 7
#define MotorPWMA 6
#define MotorPWMB 5
#define MotorSTBY 12

TB6612* motor = new TB6612(MotorAIN1, MotorAIN2, MotorPWMA, MotorBIN1, MotorBIN2, MotorPWMB, MotorSTBY);

void setup()
{

}

void loop()
{
    motor->runleft(90);
    motor->runright(90);
}