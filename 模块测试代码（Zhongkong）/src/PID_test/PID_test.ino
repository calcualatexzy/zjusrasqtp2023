#include<PIDRouting.h>
#include<TB6612.h>
#include<greyscalesensor.h>
#include<CK008.h>
#include<RGB.h>
#include<Servo.h>
#include<Robotarm.h>

#define L_SENSOR_PIN A0
#define R_SENSOR_PIN A1

#define Cruise_PIN1 A2
#define Cruise_PIN2 A4
#define Cruise_PIN3 A6
#define Cruise_PIN4 A8
#define Cruise_Back_PIN1 A3
#define Cruise_Back_PIN2 A5
#define Cruise_Back_PIN3 A7
#define Cruise_Back_PIN4 A9

#define MOTOR_FRONT_PWMA 8 
#define MOTOR_FRONT_AIN2 12
#define MOTOR_FRONT_AIN1 14
#define MOTOR_FRONT_STBY 16
#define MOTOR_FRONT_BIN1 18
#define MOTOR_FRONT_BIN2 20
#define MOTOR_FRONT_PWMB 10

#define MOTOR_BACK_PWMA 9
#define MOTOR_BACK_AIN2 13
#define MOTOR_BACK_AIN1 15
#define MOTOR_BACK_STBY 17
#define MOTOR_BACK_BIN1 19
#define MOTOR_BACK_BIN2 21
#define MOTOR_BACK_PWMB 11

#define RED_PIN A10
#define GREEN_PIN A11
#define BLUE_PIN A12

#define SWITCH_Pin 31
#define CLAW_PIN 2
#define UPPER_PIN 3
#define MID_PIN 4
#define LOWER_PIN 5       
#define CLAW_OPEN 90       
#define CLAW_CLOSE 111
int servo_pin_list[] = {CLAW_PIN, UPPER_PIN, MID_PIN, LOWER_PIN};
Servo* claw = new Servo();
Servo* upper = new Servo();
Servo* mid = new Servo();
Servo* lower = new Servo();
Servo* servo_list[] = {claw, upper, mid, lower};
SMALLCARARM* arm = new SMALLCARARM(servo_list, servo_pin_list);

GREYSCALESENSOR* L_sensor = new GREYSCALESENSOR(L_SENSOR_PIN, WHITE, 500);
GREYSCALESENSOR* R_sensor = new GREYSCALESENSOR(R_SENSOR_PIN, WHITE, 500);

GREYSCALESENSOR* Cruise_sensor1 = new GREYSCALESENSOR(Cruise_PIN1, LINE_VALUE_LOW, 300);
GREYSCALESENSOR* Cruise_sensor2 = new GREYSCALESENSOR(Cruise_PIN2, LINE_VALUE_LOW, 300);
GREYSCALESENSOR* Cruise_sensor3 = new GREYSCALESENSOR(Cruise_PIN3, LINE_VALUE_LOW, 300);
GREYSCALESENSOR* Cruise_sensor4 = new GREYSCALESENSOR(Cruise_PIN4, LINE_VALUE_LOW, 300);
GREYSCALESENSOR* Cruise_sensor_list[] = {Cruise_sensor1, Cruise_sensor2, Cruise_sensor3, Cruise_sensor4};

GREYSCALESENSOR* Cruise_sensor1_b = new GREYSCALESENSOR(Cruise_Back_PIN1, LINE_VALUE_LOW, 300);
GREYSCALESENSOR* Cruise_sensor2_b = new GREYSCALESENSOR(Cruise_Back_PIN2, LINE_VALUE_LOW, 300);
GREYSCALESENSOR* Cruise_sensor3_b = new GREYSCALESENSOR(Cruise_Back_PIN3, LINE_VALUE_LOW, 300);
GREYSCALESENSOR* Cruise_sensor4_b = new GREYSCALESENSOR(Cruise_Back_PIN4, LINE_VALUE_LOW, 300);
GREYSCALESENSOR* Cruise_sensor_list_b[] = {Cruise_sensor1_b, Cruise_sensor2_b, Cruise_sensor3_b, Cruise_sensor4_b};

TB6612* Motor_Front = new TB6612(MOTOR_FRONT_AIN1, MOTOR_FRONT_AIN2, MOTOR_FRONT_PWMA, MOTOR_FRONT_BIN1, MOTOR_FRONT_BIN2, MOTOR_FRONT_PWMB, MOTOR_FRONT_STBY);
TB6612* Motor_Back = new TB6612(MOTOR_BACK_AIN1, MOTOR_BACK_AIN2, MOTOR_BACK_PWMA, MOTOR_BACK_BIN1, MOTOR_BACK_BIN2, MOTOR_BACK_PWMB, MOTOR_BACK_STBY);

int bias_val[] = {-5, -2, 2, 5}; 
int bias_val_b[] = {-5, -2, 2, 5};

RGB* rgb_light = new RGB(RED_PIN, GREEN_PIN, BLUE_PIN);

PIDCAR* mycar = new PIDCAR(4, Cruise_sensor_list, bias_val, 4, Cruise_sensor_list_b, bias_val_b, Motor_Front, Motor_Back, L_sensor, R_sensor, rgb_light, 110, 110);

CK008* Switch = new CK008(SWITCH_Pin);

void setup()
{
    arm->init();

    while(Switch->detect() == NOT_TOUCHED)
    {
        delay(50);
    }
    // Serial.begin(9600);
}

void loop()
{
    // Serial.println(Cruise_sensor1->read_value());

    // mycar->gostraight(8);
    arm->first_marching();
    mycar->gostraight(3);
    mycar->turnright();
    mycar->gostraight(3);
    mycar->turnright();
    mycar->gostraight(3);
    mycar->turnright();
    mycar->gostraight(3);
    delay(200);

    mycar->goback(3);
    mycar->turnleft();
    mycar->goback(3);
    mycar->turnleft();
    mycar->goback(3);
    mycar->turnleft();
    mycar->goback(3);
    delay(200);

    mycar->gostraight(3);
    mycar->turnleft();
    mycar->gostraight(3);
    mycar->turnleft();
    mycar->gostraight(3);
    mycar->turnleft();
    mycar->gostraight(3);
    delay(200);

    mycar->goback(3);
    mycar->turnright();
    mycar->goback(3);
    mycar->turnright();
    mycar->goback(3);
    mycar->turnright();
    mycar->goback(3);

    while(1);
}