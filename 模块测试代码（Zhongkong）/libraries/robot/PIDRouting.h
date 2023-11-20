#ifndef __PIDROUTING_H__
#define __PIDROUTING_H__
#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include"greyscalesensor.h"
#include"TB6612.h"
#include"RGB.h"

#define DIR_FRONT 1
#define DIR_BACK -1

class PIDCAR
{
public:
    PIDCAR(int s_num, GREYSCALESENSOR** s_list, int* bias_val, 
    int s_num_b, GREYSCALESENSOR** s_list_b, int* bias_val_b, 
    TB6612* motor_front, TB6612* motor_back, 
    GREYSCALESENSOR* L_sensor, GREYSCALESENSOR* R_sensor, 
    RGB* rgb_light, 
    int base_speed = 90, int base_speed_b = 90, double Kp_f = 4.134, double Ki_f = 0.021, double Kd_f = 2.0, double Kp_b = 4.134, double Ki_b = 0.021, double Kd_b = 2.0);
    void cruise(double speed_level = 1.0);
    void cruise_back(double speed_level = 1.0);
    void init();
    void gostraight(int length, double speed_level = 1.0, bool first = false, bool adjust = true);
    void goback(int length, double speed_level = 1.0, bool adjust = true);
    void move_forward(int time, double speed_level = 1.0);
    void move_back(int time, double speed_level = 1.0);
    void _stop();
    void adjust_cross(int init_dir);
    void adjust_line(int init_dir);
    void turnleft(int next_dir = DIR_FRONT);
    void turnright(int next_dir = DIR_FRONT);

private:
    int SENSOR_NUM;
    GREYSCALESENSOR** SENSOR_LIST;
    int* BIAS_VAL;
    int BASE_SPEED;
    
    int SENSOR_NUM_BACK;
    GREYSCALESENSOR** SENSOR_LIST_BACK;
    int* BIAS_VAL_BACK;
    int BASE_SPEED_BACK;

    GREYSCALESENSOR* L_EDGE_SENSOR;
    GREYSCALESENSOR* R_EDGE_SENSOR;

    TB6612* MOTOR_FRONT;
    TB6612* MOTOR_BACK;
    double KP_FRONT;
    double KI_FRONT;
    double KD_FRONT;
    double KP_BACK;
    double KI_BACK;
    double KD_BACK;
    double bias_last;
    double bias_last_back;
    int __I;
    int __I_BACK;

    RGB* RGB_LIGHT;
};

class TWOWHEELPIDCAR
{
public:
    TWOWHEELPIDCAR(int s_num, GREYSCALESENSOR** s_list, int* bias_val, GREYSCALESENSOR* L_sensor, GREYSCALESENSOR* R_sensor, TB6612* motor, RGB* rgb_light, int base_speed = 90, double Kp = 4.134, double Ki = 0.02, double Kd = 2.0);
    void cruise(double speed_level = 1.0);
    void init();
    void gostraight(int length, double speed_level = 1.0);
    void goback(int length, double speed_level = 1.0);
    void move_forward(int time, double speed_level = 1.0);
    void move_back(int time, double speed_level = 1.0);
    void _stop();
    void turnleft();
    void turnright();
private:
    int SENSOR_NUM;
    GREYSCALESENSOR** SENSOR_LIST;
    GREYSCALESENSOR* L_EDGE_SENSOR;
    GREYSCALESENSOR* R_EDGE_SENSOR;
    int* BIAS_VAL;
    int BASE_SPEED;

    TB6612* MOTOR;

    double KP;
    double KI;
    double KD;
    double bias_last;

    double fix_val_left;
    double fix_val_right;

    int __I;
    RGB* RGB_LIGHT;
};

#endif