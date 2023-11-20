#include<PIDRouting.h>
#include<TB6612.h>
#include<greyscalesensor.h>
#include<CK008.h>
#include<RGB.h>
#include<Servo.h>
#include<Robotarm.h>
#include<smallcar.h>

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

#define CLAW_PIN 2
#define UPPER_PIN 3
#define MID_PIN 4
#define LOWER_PIN 5

#define L_HAND_PIN 6 
#define R_HAND_PIN 7

#define SW1_PIN 25
#define SW2_PIN 27
#define SW3_PIN 29
#define SW4_PIN 31

#define ECHO_MODE 1
#define HAT_MODE 2
#define TEST_MODE 3
#define MOVE_HAT_MODE 4

GREYSCALESENSOR* L_sensor = new GREYSCALESENSOR(L_SENSOR_PIN, LINE_VALUE_LOW, 300);
GREYSCALESENSOR* R_sensor = new GREYSCALESENSOR(R_SENSOR_PIN, LINE_VALUE_LOW, 300);

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

PIDCAR* car = new PIDCAR(4, Cruise_sensor_list, bias_val, 4, Cruise_sensor_list_b, bias_val_b, Motor_Front, Motor_Back, L_sensor, R_sensor, rgb_light, 110, 110);
//define a PIDCAR

int servo_pin_list[] = {CLAW_PIN, UPPER_PIN, MID_PIN, LOWER_PIN};
Servo* claw = new Servo();
Servo* upper = new Servo();
Servo* mid = new Servo();
Servo* lower = new Servo();
Servo* servo_list[] = {claw, upper, mid, lower};
SMALLCARARM* arm = new SMALLCARARM(servo_list, servo_pin_list);
//define a SMALLCAR's ARM

int hand_pin_list[] = {L_HAND_PIN, R_HAND_PIN};
Servo* left_hand = new Servo();
Servo* right_hand = new Servo();
Servo* hand_list[] = {left_hand, right_hand};
SIDEHAND* side_hand = new SIDEHAND(hand_list, hand_pin_list);
//define SMALLCAR's side hands

CK008* SW_1 = new CK008(SW1_PIN);
CK008* SW_2 = new CK008(SW2_PIN);
CK008* SW_3 = new CK008(SW3_PIN);
CK008* SW_4 = new CK008(SW4_PIN);
CK008* Sw_list[] = {SW_1, SW_2, SW_3, SW_4};
//define 4 switch

SMALLCAR* mycar = new SMALLCAR(car, arm, side_hand, Sw_list);
//define the complete car

int run_mode = 1;

void setup()
{
    
    // Serial.begin(9600);
    while(!mycar->switch_detect(1))
    {
        delay(50);
    }
    mycar->init();
    delay(1000);
    while(1)
    {
        if(mycar->switch_detect(1))
        {
            run_mode = ECHO_MODE;
            break;
        }
        else if(mycar->switch_detect(2))
        {
            run_mode = HAT_MODE;
            break;
        }
        else if(mycar->switch_detect(3))
        {
            run_mode = TEST_MODE;
            break;
        }
        else if(mycar->switch_detect(4))
        {
            run_mode = MOVE_HAT_MODE;
            break;
        }
        delay(50);
    }
}

void loop()
{
    switch ((run_mode))
    {
    case ECHO_MODE:
        energy_echo();
        break;
    
    case HAT_MODE:
        place_hat();
        break;

    case TEST_MODE:
        remove_3();
        break;

    case MOVE_HAT_MODE:
        remove_hat();
        break;

    default:
        break;
    }
}

void remove_3()
{
    mycar->first_step();
    mycar->turnleft(DIR_BACK);
    mycar->goback(1);
    mycar->turnleft(DIR_BACK);
    mycar->goback(1);
    car->move_back(550,0.7);
    mycar->remove_higher();
    while(1);
}

void energy_echo()
{
    mycar->first_step();

    mycar->turnleft(DIR_BACK);
    mycar->goback(3);
    mycar->turnleft(DIR_BACK);
    mycar->goback(3);

    mycar->grab_gain_ring();
    
    mycar->turnleft(DIR_BACK);
    mycar->hands_back();
    mycar->goback(3);
    mycar->turnleft(DIR_BACK);
    mycar->goback(3);
    mycar->turnleft(DIR_BACK);
    mycar->goback(6, 1.0, true, false);

    mycar->hands_up();
    arm->open_claw();
    arm->marching();

    mycar->gostraight(4);
    mycar->turnleft();
    mycar->goback(7);
    mycar->turnleft(DIR_BACK);
    mycar->goback(2, 1.0, true, false);
    while(1)
    {
        mycar->turnleft(DIR_BACK);
        mycar->goback(1);
    }
    // delay(18000);
    // mycar->gostraight(2);
    // mycar->turnleft(DIR_BACK);
    // mycar->goback(6);
    // mycar->turnright(DIR_BACK);
    // mycar->place_higher_back();

    // mycar->gostraight(2);
    // mycar->turnright(DIR_BACK);
    // mycar->hands_back();
    // mycar->goback(6);
    // mycar->turnleft();
    // mycar->goback(4);

    mycar->_stop();
    while(1);
}

void remove_hat()
{
    mycar->first_step();
    mycar->turnleft(DIR_BACK);
    mycar->goback(4);
    mycar->turnleft(DIR_BACK);
    mycar->goback(1);
    mycar->turnright(DIR_BACK);
    mycar->goback(1);
    mycar->turnleft(DIR_BACK);
    mycar->gostraight(4);
    mycar->remove_higher();

    mycar->turnright(DIR_BACK);
    mycar->hands_back();
    mycar->goback(1);

    mycar->turnleft(DIR_BACK);
    mycar->goback(2);
    mycar->turnleft(DIR_BACK);
    mycar->goback(4);
    mycar->turnleft(DIR_BACK);
    mycar->goback(3);
    mycar->turnright(DIR_BACK);
    mycar->goback(2);
    mycar->turnleft(DIR_BACK);
    mycar->goback(3);
    mycar->turnleft(DIR_BACK);
    mycar->goback(6, 1.0, true, false);
    mycar->hands_up();

    mycar->gostraight(6);
    mycar->turnleft(DIR_BACK);
    mycar->goback(6);
    mycar->turnright(DIR_BACK);
    mycar->goback(1);
    mycar->turnleft(DIR_BACK);
    mycar->goback(2);
    mycar->remove_lower();
    mycar->turnleft(DIR_BACK);
    mycar->goback(1);
    mycar->remove_lower();



    mycar->_stop();
    while(1);

}

void place_hat()
{
    mycar->first_step();

    mycar->turnleft(DIR_BACK);
    mycar->goback(3);
    mycar->turnleft(DIR_BACK);
    mycar->goback(3);

    mycar->grab_gain_ring();

    mycar->turnright(DIR_BACK);
    mycar->goback(2);
    mycar->turnleft(DIR_BACK);
    mycar->goback(2);
    mycar->place_higher_back();
    
    mycar->turnright(DIR_BACK);
    mycar->hands_back();
    mycar->goback(1);

    mycar->turnleft(DIR_BACK);
    mycar->goback(2);
    mycar->turnleft(DIR_BACK);
    mycar->goback(4);
    mycar->turnleft(DIR_BACK);
    mycar->goback(3);
    mycar->turnright(DIR_BACK);
    mycar->goback(2);
    mycar->turnleft(DIR_BACK);
    mycar->goback(3);
    mycar->turnleft(DIR_BACK);
    mycar->goback(6, 1.0, true, false);
    mycar->hands_up();

    mycar->gostraight(6);
    mycar->turnleft(DIR_BACK);
    mycar->goback(6);
    mycar->turnright(DIR_BACK);
    mycar->goback(1);
    mycar->turnleft(DIR_BACK);
    mycar->goback(2);
    mycar->remove_lower();
    mycar->turnleft(DIR_BACK);
    mycar->goback(1);
    mycar->remove_lower();



    mycar->_stop();
    while(1);
}