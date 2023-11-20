#include <cruisingmodule.h>
#include <greyscalesensor.h>
#include <TB6612.h>
#include <stdio.h>
#include <CK008.h>
#include <Routing.h>
#include <Servo.h>

#define LGrey A7
#define RGrey A2
#define Cruise1 A5
#define Cruise2 A3
#define Cruise3 A1
#define Cruise4 A6
#define Cruise5 A4
#define Cruise6 A0

#define MotorAIN1 3
#define MotorAIN2 5
#define MotorBIN1 6
#define MotorBIN2 4
#define MotorPWMA 7
#define MotorPWMB 2
#define MotorSTBY 8

#define CLAW 9
#define WRIST 10
#define TURNTABLE 11

#define CK008Pin 13
#define RESETPin A0

#define RESET_MODE 1
#define NORM_MODE 2
#define DK_MODE 3

GREYSCALESENSOR* L_GreySensor = new GREYSCALESENSOR(LGrey, WHITE, 300);
GREYSCALESENSOR* R_GreySensor = new GREYSCALESENSOR(RGrey, WHITE, 300);
CRUISINGMODULE* Cru_Modele = new CRUISINGMODULE(LCruise, MCruise, RCruise, WHITE, 500);
TB6612* motor = new TB6612(MotorAIN1, MotorAIN2, MotorPWMA, MotorBIN1, MotorBIN2, MotorPWMB, MotorSTBY);
CK008* ck008 = new CK008(CK008Pin);
CK008* reset_button = new CK008(RESETPin);
MYCAR* mycar = new MYCAR(L_GreySensor, R_GreySensor, motor, Cru_Modele);
Servo claw,wrist,turntable;

int run_mode = 0;

void setup()
{
     claw.attach(CLAW);
     wrist.attach(WRIST);
     turntable.attach(TURNTABLE);
     rotate_wrist(0);

     while(1)
    {
        if(reset_button->detect() == TOUCHED)
        {
            run_mode = RESET_MODE;
            delay(2000);
            return;
        }
        if(ck008->detect() == TOUCHED)
        {
            break;
        }
        delay(50);
    }

    delay(1000);

     while(1)
    {
        if(reset_button->detect() == TOUCHED)
        {
            run_mode = DK_MODE;
            break;
        }
        if(ck008->detect() == TOUCHED)
        {
            run_mode = NORM_MODE;
            break;
        }
        delay(50);
    }
    delay(2000);
}

void loop()
{
    switch(run_mode)
    {
        case NORM_MODE:
            energy_echo();
            break;
        case DK_MODE:
            duikang();
            break;
        case RESET_MODE:
            reset_run();
            break;
    }
}

void energy_echo()
{
    // mycar->gostraight(2);
    // motor->brake();
    // grab_first();

    // mycar->turnright();
    // mycar->gostraight(2);
    // motor->brake();
    // grab_second();

    // mycar->gostraight(4);
    // motor->brake();
    // mycar->move(125);
    // placing_lower();
    // mycar->goback(2);
    // delay(200);
    // mycar->turnleft();
    // mycar->gostraight(2);


//3score1
    mycar->gostraight(1);
    mycar->turnright();
    mycar->gostraight(4);
    mycar->turnleft();

    mycar->gostraight(2);

    motor->brake();
    grab_first();

    mycar->gostraight(2);
    motor->brake();
    grab_second();
    mycar->gostraight(1);
    mycar->turnright();
    
    rotate_turntable(180);    
    mycar->move(650);
    placing_higher();

    motor->brake();
    while(1);

//3score2

}

void duikang()
{
    mycar->gostraight(4);
    mycar->turnright();
    mycar->gostraight(2);
    motor->brake();    
    grab_first();
    
    mycar->turnright();
    mycar->gostraight(2);
    motor->brake();
    grab_second();
    mycar->turnleft();

    mycar->gostraight(4);
    motor->brake();
    mycar->move(125);
    placing_lower();
    mycar->goback(2);
    motor->runleft(-60);
    motor->runright(60);
    delay(200);
    mycar->turnleft();

    mycar->gostraight(1);
    mycar->turnleft();
    mycar->gostraight(3);
    rotate_turntable(177);
    mycar->move(675);

    motor->brake();
    while(1);
}

void reset_run()
{
    mycar->gostraight(3);
    mycar->turnright();
    rotate_turntable(177);
    mycar->move(750);
    motor->brake();
    while(1);
}

void placing_lower()
{
  rotate_wrist(130);
  rotate_turntable(110);
  rotate_claw(120);
  rotate_turntable(177);
  rotate_wrist(0);
}

void placing_higher()
{
  rotate_wrist(130);
  rotate_claw(120);
  rotate_wrist(150);
  rotate_turntable(177);  
}

void grab_second()
{
  rotate_turntable(28);
  delay(100);
  rotate_claw(115);
  delay(200);
  rotate_turntable(0);
  delay(20);
  rotate_claw(78);
  rotate_turntable(177);
}

void grab_first()
{
  rotate_claw(122);
  delay(100);
  rotate_turntable(0);
  rotate_claw(80);
  rotate_turntable(60);
}

void rotate_claw(int angle){
    int anglex = claw.read();
    if (angle > anglex){
        for (int i = anglex;i < angle;i++){
            claw.write(i);
            delay(15);
        }
    }
    else if (angle < anglex){
        for (int i = anglex;i > angle;i--){
            claw.write(i);
            delay(15);
        }
    }
}

void rotate_wrist(int angle){
    int anglex = wrist.read();
    if (angle > anglex){
        for (int i = anglex;i < angle;i++){
            wrist.write(i);
            delay(15);
        }
    }
    else if (angle < anglex){
        for (int i = anglex;i > angle;i--){
            wrist.write(i);
            delay(15);
        }
    }
}

void rotate_turntable(int angle){
    int anglex = turntable.read();
    if (angle > anglex){
        for (int i = anglex;i < angle;i++){
            turntable.write(i);
            delay(15);
        }
    }
    else if (angle < anglex){
        for (int i = anglex;i > angle;i--){
            turntable.write(i);
            delay(15);
        }
    }
}