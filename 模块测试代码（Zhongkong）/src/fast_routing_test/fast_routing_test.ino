#include <cruisingmodule.h>
#include <greyscalesensor.h>
#include <TB6612.h>
#include <stdio.h>
#include <CK008.h>
#include<FastRouting.h>

#define LGrey A5
#define RGrey A4
#define LCruise A1
#define MCruise A2
#define RCruise A3
#define LCruiseBack A6
#define MCruiseBack A7
#define RCruiseBack A8

#define MotorAIN1 4
#define MotorAIN2 3
#define MotorBIN1 6
#define MotorBIN2 7
#define MotorPWMA 2
#define MotorPWMB 8
#define MotorSTBY 5

#define CK008Pin 13

GREYSCALESENSOR* L_GreySensor = new GREYSCALESENSOR(LGrey, WHITE, 300);
GREYSCALESENSOR* R_GreySensor = new GREYSCALESENSOR(RGrey, WHITE, 300);
CRUISINGMODULE* Cru_Modele_Front = new CRUISINGMODULE(LCruise, MCruise, RCruise, WHITE, 400);
CRUISINGMODULE* Cru_Modele_Back = new CRUISINGMODULE(LCruiseBack, MCruiseBack, RCruiseBack, WHITE, 400);
TB6612* motor = new TB6612(MotorAIN1, MotorAIN2, MotorPWMA, MotorBIN1, MotorBIN2, MotorPWMB, MotorSTBY);
CK008* ck008 = new CK008(CK008Pin);
FASTCAR* mycar = new FASTCAR(L_GreySensor, R_GreySensor, motor, Cru_Modele_Front);

void setup()
{
    while(ck008->detect() == NOT_TOUCHED)
    {
        delay(50);
    }
}

void loop()
{

    mycar->gostraight(1);
    mycar->turnright();
    mycar->gostraight(4);
    mycar->turnleft();
    mycar->gostraight(3);
    mycar->turnright();
    mycar->gostraight(2);
    mycar->turnright();
    mycar->gostraight(3);

    mycar->goback(1);
    mycar->turnright();
    mycar->gostraight(4);
    mycar->turnright();
    mycar->gostraight(1);
    mycar->turnright();
    mycar->gostraight(4);
    mycar->turnright();
    mycar->gostraight(2);

    mycar->goback(1);
    mycar->turnright();
    mycar->gostraight(4);
    mycar->turnright();
    mycar->gostraight(2);
    mycar->turnright();
    mycar->gostraight(4);
    mycar->turnright();
    mycar->gostraight(3);

    mycar->goback(1);
    mycar->turnright();
    mycar->gostraight(6);
    mycar->turnleft();
    mycar->gostraight(1);
    mycar->turnleft();
    mycar->gostraight(6);

    mycar->goback(1);

    motor->brake();
    while(1);
}