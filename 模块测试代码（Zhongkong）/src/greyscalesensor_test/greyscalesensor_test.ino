#include <cruisingmodule.h>
#include <greyscalesensor.h>
#include <TB6612.h>
#include <stdio.h>
#include <CK008.h>
#include <Routing.h>

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

#define CK008Pin 13

GREYSCALESENSOR L_GreySensor(LGrey, WHITE, 800);
GREYSCALESENSOR R_GreySensor(RGrey, WHITE, 800);
CRUISINGMODULE Cru_Modele(LCruise, MCruise, RCruise, WHITE, 500);
TB6612 motor(MotorAIN1, MotorAIN2, MotorPWMA, MotorBIN1, MotorBIN2, MotorPWMB, MotorSTBY);
CK008 ck008(CK008Pin);
int cornerCount;
int forbid;

void setup()
{
  Serial.begin(9600);
  cornerCount = 1;
  while (ck008.detect() == NOT_TOUCHED)
  {
    delay(10);
  }
  
}

void loop()
{
    if(R_GreySensor.is_line() && forbid < 0)
    {
        if(cornerCount % 3 == 0)
            turnright();
        cornerCount ++;
        forbid = 10;
    }
    else
    {
        cruise();
    }
    delay(10);    
    forbid -= 1;
    // Serial.println(R_GreySensor.read_value());
    // delay(10);
}

void turnright(){
    motor.runright(50);
    motor.runleft(50);
    delay(50);
    motor.brake();
    delay(500);
    motor.runright(-50);
    motor.runleft(50); //40
    bool flag1 = false, flag2 = false;
    while (true){
        if (! Cru_Modele.on_line()){
            flag1 = true;
            delay(50);
        }

        if (Cru_Modele.on_line() && flag1){
            flag1 = false; //to avoid get into this block again and again
            flag2 = true;
            delay(50);
        }

        if (flag2 && Cru_Modele.on_line()) break;
    }
    motor.brake();
    delay(500);
}

void turnleft(){
    motor.brake();
    delay(200);
    motor.runright(60);
    motor.runleft(-55); //-50
    bool flag = false;
    while (true){
        if (! Cru_Modele.on_line()){
            flag = true;
            delay(100);
        }
        if (flag && Cru_Modele.on_line()) break;
    }
    motor.brake();
    delay(100);
}

void cruise(){
    int LineError;
    LineError = Cru_Modele.get_pose();
    if (LineError == STRAIGHT){
        motor.runright(90);
        motor.runleft(90);
    }
    else if (LineError == RIGHT){
        motor.runright(30);
        motor.runleft(90);
    }
    else if (LineError == EXTRARIGHT){
        motor.runright(0);
        motor.runleft(90);
    }
    else if (LineError == LEFT){
        motor.runright(90);
        motor.runleft(30);
    }
    else if (LineError == EXTRALEFT){
        motor.runright(90);
        motor.runleft(0);
    }
}
