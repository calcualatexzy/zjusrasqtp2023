#include <cruisingmodule.h>
#include <greyscalesensor.h>
#include <TB6612.h>
#include <stdio.h>
#include <CK008.h>
#include <Routing.h>
#include <Servo.h>
#include<Robotarm.h>

#define LGrey A5
#define RGrey A4
#define LCruise A1
#define MCruise A2
#define RCruise A3

#define MotorAIN1 2
#define MotorAIN2 4
#define MotorBIN1 8
#define MotorBIN2 7
#define MotorPWMA 6
#define MotorPWMB 5
#define MotorSTBY 12

#define CLAWPIN 9
#define WRISTPIN 10
#define TURNTABLEPIN 11

#define CK008Pin 13

GREYSCALESENSOR* L_GreySensor = new GREYSCALESENSOR(LGrey, WHITE, 400);
GREYSCALESENSOR* R_GreySensor = new GREYSCALESENSOR(RGrey, WHITE, 400);
CRUISINGMODULE* Cru_Modele = new CRUISINGMODULE(LCruise, MCruise, RCruise, WHITE, 500);
TB6612* motor = new TB6612(MotorAIN1, MotorAIN2, MotorPWMA, MotorBIN1, MotorBIN2, MotorPWMB, MotorSTBY);
CK008* ck008 = new CK008(CK008Pin);
MYCAR* mycar = new MYCAR(L_GreySensor, R_GreySensor, motor, Cru_Modele);
ROBOTARM* robotarm = new ROBOTARM(CLAWPIN, WRISTPIN, TURNTABLEPIN);

void setup()
{
    while(ck008->detect() == NOT_TOUCHED)
    {
        delay(50);
    }

    mycar->sample();
    
    while(ck008->detect() == NOT_TOUCHED)
    {
        delay(50);
    }
}

void loop()
{
    mycar->gostraight(2);
    motor->brake();
    robotarm->grab_first();

    mycar->turnright();
    mycar->gostraight(2);
    motor->brake();
    robotarm->grab_second();

    mycar->gostraight(4);
    motor->brake();
    robotarm->place_lower();

    motor->brake();
    while(1);
}
