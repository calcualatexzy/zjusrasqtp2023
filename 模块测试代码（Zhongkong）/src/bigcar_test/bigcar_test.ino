#include<PIDRouting.h>
#include<TB6612.h>
#include<greyscalesensor.h>
#include<CK008.h>
#include<RGB.h>
#include<Servo.h>
#include<Robotarm.h>
#include<bigcar.h>

#define CLAW_PIN 2
#define WRIST_PIN 3
#define TURNTABLE_PIN 4

#define PWMA 8
#define PWMB 10
#define AIN2 12
#define AIN1 14
#define STBY 16
#define BIN1 18
#define BIN2 20

#define Sensor1_PIN A0
#define Sensor2_PIN A2
#define Sensor3_PIN A4

#define L_sensor_PIN A6
#define R_sensor_PIN A8
 
#define SW1_PIN 25
#define SW2_PIN 27
#define SW3_PIN 29
#define SW4_PIN 31

#define RED_PIN A8
#define GREEN_PIN A9
#define BLUE_PIN A10

#define CMP_VAL 500
#define speed_level 1.0

#define ECHO_MODE 1
#define HAT_MODE 2

GREYSCALESENSOR* Cruise_Sensor1 = new GREYSCALESENSOR(Sensor1_PIN, LINE_VALUE_LOW, CMP_VAL);
GREYSCALESENSOR* Cruise_Sensor2 = new GREYSCALESENSOR(Sensor2_PIN, LINE_VALUE_LOW, CMP_VAL);
GREYSCALESENSOR* Cruise_Sensor3 = new GREYSCALESENSOR(Sensor3_PIN, LINE_VALUE_LOW, CMP_VAL);
GREYSCALESENSOR* L_sensor = new GREYSCALESENSOR(L_sensor_PIN, WHITE, 400);
GREYSCALESENSOR* R_sensor = new GREYSCALESENSOR(R_sensor_PIN, WHITE, 400);

GREYSCALESENSOR* Sensor_list[] = {Cruise_Sensor1, Cruise_Sensor2, Cruise_Sensor3};
int bias_value[] = {-4, 0, 4};

TB6612* motor = new TB6612(AIN1, AIN2, PWMA, BIN1, BIN2, PWMB, STBY);

CK008* SW_1 = new CK008(SW1_PIN);
CK008* SW_2 = new CK008(SW2_PIN);
CK008* SW_3 = new CK008(SW3_PIN);
CK008* SW_4 = new CK008(SW4_PIN);

CK008* Switch_list[] = {SW_1, SW_2, SW_3, SW_4};

RGB* rgb_light = new RGB(RED_PIN, GREEN_PIN, BLUE_PIN);

TWOWHEELPIDCAR* car = new TWOWHEELPIDCAR(3, Sensor_list, bias_value, L_sensor, R_sensor, motor, rgb_light, 70, 4.8, 0, 0);
//define the TWOWHEELPIDCAR

Servo* claw = new Servo();
Servo* wrist = new Servo();
Servo* turntable = new Servo();

Servo* servo_list[] = {claw, wrist, turntable};
int servo_pin[] = {CLAW_PIN, WRIST_PIN, TURNTABLE_PIN};

BIGCARARM* arm = new BIGCARARM(servo_list, servo_pin);
//define the BIGCARARM

BIGCAR* mycar = new BIGCAR(car, arm, Switch_list);

int run_mode = 0;

void setup()
{
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
        delay(50);
    }
}

void loop()
{
    // mycar->grab();
    // delay(1000);
    // mycar->grab();
    // delay(1000);
    // mycar->grab(true);
    // while(!mycar->switch_detect(1))
    // {
    //     delay(50);
    // }
    // mycar->init();

    switch ((run_mode))
    {
    case ECHO_MODE:
        energy_echo();
        break;
    
    case HAT_MODE:
        place_hat();
        break;

    default:
        break;
    }

}

void energy_echo()
{
    delay(4500);

    mycar->gostraight(2, speed_level);
    mycar->grab();

    mycar->turnright();
    mycar->gostraight(2, speed_level);
    mycar->grab(true);
    mycar->gostraight(4, speed_level);
    mycar->place_lower();

    mycar->turnleft();
    
    mycar->gostraight(2, speed_level);
    mycar->turnleft();
    mycar->gostraight(1, speed_level);
    mycar->grab();
    mycar->turnright();
    mycar->gostraight(2, speed_level);
    mycar->grab(true);
    mycar->gostraight(1, speed_level);
    mycar->turnright();
    mycar->place_higher();
    car->goback(1);
    mycar->turnleft();
    mycar->gostraight(1);
    mycar->grab();
    mycar->turnright();
    mycar->gostraight(2);
    mycar->grab();
    mycar->turnright();
    mycar->gostraight(2);
    mycar->grab(true);
    mycar->turnright();
    mycar->gostraight(1);
    mycar->turnleft();
    mycar->gostraight(5);
    mycar->place_lower();

    mycar->_stop();
    while (1);
}

void place_hat()
{
    delay(4500);

    mycar->gostraight(1);
    mycar->turnright();
    mycar->gostraight(1);
    mycar->turnleft();
    mycar->gostraight(1);
    mycar->place_hat();
    mycar->turnright();
    mycar->gostraight(1);
    mycar->grab();
    mycar->gostraight(2);
    mycar->turnleft();
    mycar->gostraight(2);
    mycar->grab();
    mycar->gostraight(2);
    mycar->grab(true);
    mycar->gostraight(1);
    mycar->turnright();
    mycar->place_higher();
    mycar->block();
    mycar->_stop();
    while(1);
}