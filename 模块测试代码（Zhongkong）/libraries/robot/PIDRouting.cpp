#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include"PIDRouting.h"

PIDCAR::PIDCAR(int s_num, GREYSCALESENSOR** s_list, int* bias_val, int s_num_b, GREYSCALESENSOR** s_list_b, int* bias_val_b, TB6612* motor_front, TB6612* motor_back, GREYSCALESENSOR* L_sensor, GREYSCALESENSOR* R_sensor, RGB* rgb_light,  
int base_speed, int base_speed_b, double Kp_f, double Ki_f, double Kd_f, double Kp_b, double Ki_b, double Kd_b)
{
    SENSOR_NUM = s_num;
    SENSOR_LIST = s_list;
    BIAS_VAL = bias_val;

    SENSOR_NUM_BACK = s_num_b;
    SENSOR_LIST_BACK = s_list_b;
    BIAS_VAL_BACK = bias_val_b;

    L_EDGE_SENSOR = L_sensor;
    R_EDGE_SENSOR = R_sensor;

    MOTOR_FRONT = motor_front;
    MOTOR_BACK = motor_back;

    BASE_SPEED = base_speed;
    BASE_SPEED_BACK = base_speed_b;

    KP_FRONT = Kp_f;
    KI_FRONT = Ki_f;
    KD_FRONT = Kd_f;
    KP_BACK = Kp_b;
    KI_BACK = Ki_b;
    KD_BACK = Kd_b;

    RGB_LIGHT = rgb_light;

    init();
    return;
}

void PIDCAR::init()
{
    RGB_LIGHT->white();

    __I = 0;
    __I_BACK = 0;
    bias_last = 0;
    bias_last_back = 0;
    return;
}

void PIDCAR::cruise(double speed_level)
{
    double bias_now = 0;
    for(int i = 0; i < SENSOR_NUM; i++)
    {
        bias_now += SENSOR_LIST[i]->is_line() * BIAS_VAL[i];
    }
    __I = __I + bias_now;
    double PID_Front = KP_FRONT * bias_now + KI_FRONT * __I + KD_FRONT * (bias_now - bias_last);
    double PID_Back = KP_BACK * bias_now + KI_BACK * __I + KD_BACK * (bias_now - bias_last);
    bias_last = bias_now;
    MOTOR_FRONT->runleft(speed_level * (BASE_SPEED + (int)PID_Front));
    MOTOR_FRONT->runright(speed_level * (BASE_SPEED - (int)PID_Front));
    MOTOR_BACK->runleft(speed_level * (BASE_SPEED + (int)PID_Back));
    MOTOR_BACK->runright(speed_level * (BASE_SPEED - (int)PID_Back));
    return;
}

void PIDCAR::cruise_back(double speed_level)
{
    double bias_now = 0;
    for(int i = 0; i < SENSOR_NUM_BACK; i++)
    {
        bias_now += SENSOR_LIST_BACK[i]->is_line() * BIAS_VAL_BACK[i];
    }
    __I_BACK += bias_now;
    double PID_Front = KP_BACK * bias_now + KI_BACK * __I_BACK + KD_BACK * (bias_now - bias_last_back);
    double PID_Back = KP_FRONT * bias_now + KI_FRONT * __I_BACK + KD_FRONT * (bias_now - bias_last_back);
    bias_last_back = bias_now;
    MOTOR_FRONT->runleft(speed_level * (-BASE_SPEED + (int)PID_Back));
    MOTOR_FRONT->runright(speed_level * (-BASE_SPEED - (int)PID_Back));
    MOTOR_BACK->runleft(speed_level * (-BASE_SPEED + (int)PID_Front));
    MOTOR_BACK->runright(speed_level * (-BASE_SPEED - (int)PID_Front));
}

void PIDCAR::gostraight(int length, double speed_level, bool first, bool adjust)
{
    RGB_LIGHT->red();

    int corner_count = 1;
    int side_sensor_forbid = 40;
    if(first)
        side_sensor_forbid = 0;
    while(1)
    {
        if((SENSOR_LIST[0]->is_line() && SENSOR_LIST[1]->is_line() && SENSOR_LIST[2]->is_line()) && side_sensor_forbid < 0)
        {
            if(corner_count % length == 0)
            {
                init();
                _stop();
                int adjust_dir = DIR_FRONT;
                for(int i = 1; i <= 30; i++)
                {
                    if(L_EDGE_SENSOR->is_line() && R_EDGE_SENSOR->is_line())
                    {
                        adjust_dir = DIR_BACK;
                    }
                    delay(10);
                }
                if(adjust)
                {                    
                    adjust_cross(adjust_dir);
                    delay(400);
                }
                else
                {
                    delay(200);
                }
                return;
            }
            else
            {
                corner_count ++;
                side_sensor_forbid = 40;
            }
        }
        else
        {
            if((corner_count == 1 && side_sensor_forbid > 0) || (corner_count == length && side_sensor_forbid < -30))
                cruise(0.5);
            else
                cruise(speed_level);
        }
        delay(10);
        side_sensor_forbid --;
    }
}

void PIDCAR::_stop()
{
    MOTOR_BACK->brake();
    MOTOR_FRONT->brake();
    return;
}

void PIDCAR::goback(int length, double speed_level, bool adjust)
{
    RGB_LIGHT->yellow();

    int corner_count = 1;
    int side_sensor_forbid = 40;
    while(1)
    {
        if((SENSOR_LIST_BACK[0]->is_line() && SENSOR_LIST_BACK[1]->is_line() && SENSOR_LIST_BACK[2]->is_line()) && side_sensor_forbid < 0)
        {
            if(corner_count % length == 0)
            {
                init();
                _stop();
                int adjust_dir = DIR_BACK;
                for(int i = 1; i <= 30; i++)
                {
                    if(L_EDGE_SENSOR->is_line() && R_EDGE_SENSOR->is_line())
                    {
                        adjust_dir = DIR_FRONT;
                    }
                    delay(10);
                }
                if(adjust)
                {                    
                    adjust_cross(adjust_dir);
                    delay(400);
                }
                else
                {
                    delay(200);
                }
                return;
            }
            else
            {
                corner_count ++;
                side_sensor_forbid = 40;
            }
        }
        else
        {
            if((corner_count == 1 && side_sensor_forbid > 0) || (corner_count == length && side_sensor_forbid < -30))
                cruise_back(0.5);
            else
                cruise_back(speed_level);
        }
        delay(10);
        side_sensor_forbid --;
    }
    
}

void PIDCAR::move_forward(int time, double speed_level)
{
    for(int i = 1; i <= time / 10; i++)
    {
        cruise(speed_level);
        delay(10);
    }
    _stop();
}

void PIDCAR::move_back(int time, double speed_level)
{
    for(int i = 1; i <= time / 10; i++)
    {
        cruise_back(speed_level);
        delay(10);
    }
    _stop();
}

void PIDCAR::adjust_cross(int init_dir)
{
    RGB_LIGHT->blue();

    int direction = init_dir;
    int maxn = 150;
    while(!(L_EDGE_SENSOR->is_line() && R_EDGE_SENSOR->is_line()))
    {
        int count = 0;
        while(count <= maxn)
        {
            if(L_EDGE_SENSOR->is_line() && R_EDGE_SENSOR->is_line())
            {
                break;
            }
            else if(direction == DIR_FRONT)
            {
                cruise(0.3);
            }
            else
            {
                cruise_back(0.3);
            }
            count ++;
            delay(10);
        }
        if(count == maxn + 1)
        {
            maxn += 10;
            RGB_LIGHT->white();
        }
        direction = - direction;
    }
    _stop();
    return;
}

void PIDCAR::adjust_line(int init_dir)
{
    RGB_LIGHT->blue();

    int direction = init_dir;
    while(!((SENSOR_LIST[1]->is_line() && SENSOR_LIST[2]->is_line()) && (SENSOR_LIST_BACK[1]->is_line() && SENSOR_LIST_BACK[2]->is_line())))
    {
        if(direction == DIR_BACK)
        {
            while(!(SENSOR_LIST[1]->is_line() && SENSOR_LIST[2]->is_line()))
            {
                for(int i = 0; i < 15; i ++)
                {
                    cruise_back(0.3);
                    delay(20);
                }
            }
        }
        else
        {
            while(!(SENSOR_LIST_BACK[1]->is_line() && SENSOR_LIST_BACK[2]->is_line()))      
            {
                for(int i = 0; i < 5; i ++)
                {
                    cruise(0.3);
                    delay(10);
                }
            }
        }
        direction = - direction;
    }
    _stop();
    return;
}

void PIDCAR::turnleft(int next_dir)
{
    RGB_LIGHT->green();

    MOTOR_FRONT->runleft(-90);
    MOTOR_BACK->runleft(-90);
    MOTOR_FRONT->runright(90);
    MOTOR_BACK->runright(90);
    delay(500);
    MOTOR_FRONT->runleft(-60);
    MOTOR_BACK->runleft(-60);
    MOTOR_FRONT->runright(60);
    MOTOR_BACK->runright(60);

    if(next_dir == DIR_FRONT)
    {    
        while(!(SENSOR_LIST[SENSOR_NUM / 2 - 1]->is_line() && SENSOR_LIST[SENSOR_NUM / 2]->is_line()))
        {
            delay(5);
        }
    }
    else
    {
        while(!(SENSOR_LIST_BACK[SENSOR_NUM / 2 - 1]->is_line() && SENSOR_LIST_BACK[SENSOR_NUM / 2]->is_line()))
        {
            delay(5);
        }
    }
    // if((SENSOR_LIST[1]->is_line() && SENSOR_LIST[2]->is_line()))
    // {
    //     adjust_line(DIR_FRONT);
    // }
    // else
    // {
    //     adjust_line(DIR_BACK);
    // }
    _stop();
    return;
}

void PIDCAR::turnright(int next_dir)
{
    RGB_LIGHT->green();

    MOTOR_FRONT->runleft(90);
    MOTOR_BACK->runleft(90);
    MOTOR_FRONT->runright(-90);
    MOTOR_BACK->runright(-90);
    delay(600);
    MOTOR_FRONT->runleft(60);
    MOTOR_BACK->runleft(60);
    MOTOR_FRONT->runright(-60);
    MOTOR_BACK->runright(-60);
    if(next_dir == DIR_FRONT)
    {    
        while(!(SENSOR_LIST[SENSOR_NUM / 2 - 1]->is_line() && SENSOR_LIST[SENSOR_NUM / 2]->is_line()))
        {
            delay(10);
        }
    }
    else
    {
        while(!(SENSOR_LIST_BACK[SENSOR_NUM / 2 - 1]->is_line() && SENSOR_LIST_BACK[SENSOR_NUM / 2]->is_line()))
        {
            delay(10);
        }
    }
    // if((SENSOR_LIST[1]->is_line() && SENSOR_LIST[2]->is_line()))
    // {
    //     adjust_line(DIR_FRONT);
    // }
    // else
    // {
    //     adjust_line(DIR_BACK);
    // }
    _stop();
    return;
}

TWOWHEELPIDCAR::TWOWHEELPIDCAR(int s_num, GREYSCALESENSOR** s_list, int* bias_val, GREYSCALESENSOR* L_sensor, GREYSCALESENSOR* R_sensor, TB6612* motor, RGB* rgb_light, int base_speed, double Kp, double Ki, double Kd)
{
    SENSOR_NUM = s_num;
    SENSOR_LIST = s_list;
    BIAS_VAL = bias_val;
    MOTOR = motor;
    RGB_LIGHT = rgb_light;
    BASE_SPEED = base_speed;
    L_EDGE_SENSOR = L_sensor;
    R_EDGE_SENSOR = R_sensor;
    KP = Kp;
    KD = Kd;
    KI = Ki;

    fix_val_left = 1.0;
    fix_val_right = 1.0;

    init();
}

void TWOWHEELPIDCAR::init()
{
    __I = 0;
    bias_last = 0;
    RGB_LIGHT->white();
}

void TWOWHEELPIDCAR::cruise(double speed_level)
{
    double bias_now = 0;
    for(int i = 0; i < SENSOR_NUM; i++)
    {
        bias_now += SENSOR_LIST[i]->is_line() * BIAS_VAL[i];
    }
    if(!SENSOR_LIST[1]->is_line())
    {
        bias_now *= 2.0;
    }
    __I = __I + bias_now;
    double PID = KP * bias_now + KI * __I + KD * (bias_now - bias_last);
    bias_last = bias_now;
    MOTOR->runleft(fix_val_left * speed_level * (BASE_SPEED + (int)PID));
    MOTOR->runright(fix_val_right * speed_level * (BASE_SPEED - (int)PID));

    // bool L_S = SENSOR_LIST[0]->is_line();
    // bool M_S = SENSOR_LIST[1]->is_line();
    // bool R_S = SENSOR_LIST[2]->is_line();

    // if(M_S && !L_S && !R_S)
    // {
    //     MOTOR->runleft(speed_level * 90);
    //     MOTOR->runright(speed_level * 90);
    // }
    // else if(M_S && L_S && !R_S)
    // {
    //     MOTOR->runleft(speed_level * 60);
    //     MOTOR->runright(speed_level * 90);
    // }
    // else if(M_S && !L_S && R_S)
    // {
    //     MOTOR->runleft(speed_level * 90);
    //     MOTOR->runright(speed_level * 60);
    // }
    // else if(!M_S && L_S && !R_S)
    // {
    //     MOTOR->runleft(speed_level * 20);
    //     MOTOR->runright(speed_level * 90);
    // }
    // else if(!M_S && !L_S && R_S)
    // {
    //     MOTOR->runleft(speed_level * 90);
    //     MOTOR->runright(speed_level * 20);
    // }
    // else
    // {
    //     MOTOR->runleft(speed_level * 90);
    //     MOTOR->runright(speed_level * 90);
    // }
    return;
}

void TWOWHEELPIDCAR::gostraight(int length, double speed_level)
{
    RGB_LIGHT->red();

    int corner_count = 1;
    int side_sensor_forbid = 80;
    while(1)
    {
        if((L_EDGE_SENSOR->is_line() || R_EDGE_SENSOR->is_line()) && side_sensor_forbid < 0)
        {
            if(corner_count % length == 0)
            {
                init();
                _stop();
                delay(200);
                MOTOR->runright(40);
                MOTOR->runleft(40);
                delay(250);
                _stop();
                return;
            }
            else
            {
                corner_count ++;
                side_sensor_forbid = 80;
            }
        }
        else
        {
            cruise(speed_level);
        }
        delay(5);
        side_sensor_forbid --;
    }
}

void TWOWHEELPIDCAR::goback(int length, double speed_level)
{
    RGB_LIGHT->yellow();

    int corner_count = 1;
    int side_sensor_forbid = 30;
    while(1)
    {
        if((L_EDGE_SENSOR->is_line() || R_EDGE_SENSOR->is_line()) && side_sensor_forbid < 0)
        {
            if(corner_count % length == 0)
            {
                init();
                _stop();
                delay(200);
                MOTOR->runleft(50);
                MOTOR->runright(50);
                delay(425);
                return;
            }
            else
            {
                corner_count ++;
                side_sensor_forbid = 40;
            }
        }
        else
        {
            MOTOR->runleft(fix_val_left *  speed_level * (-BASE_SPEED));
            MOTOR->runright(fix_val_right * speed_level * (-BASE_SPEED - 8));
        }
        delay(10);
        side_sensor_forbid --;
    }
}

void TWOWHEELPIDCAR::move_forward(int time, double speed_level)
{
    for(int i = 1; i <= time / 10; i++)
    {
        cruise(speed_level);
        delay(10);
    }
}

void TWOWHEELPIDCAR::move_back(int time, double speed_level)
{
    for(int i = 1; i <= time / 10; i++)
    {
        MOTOR->runleft(fix_val_left * speed_level * (-BASE_SPEED));
        MOTOR->runright(fix_val_right * speed_level * (-BASE_SPEED - 10));
        delay(10);
    }
}

void TWOWHEELPIDCAR::_stop()
{
    MOTOR->brake();
}

void TWOWHEELPIDCAR::turnleft()
{
    RGB_LIGHT->green();

    MOTOR->brake();
    delay(100);

    MOTOR->runleft(-60);
    MOTOR->runright(60);
    delay(600);
    MOTOR->runleft(-60);
    MOTOR->runright(60);

    while(!(SENSOR_LIST[1]->is_line() && !SENSOR_LIST[0]->is_line()))
    {
        delay(5);
    }

}
void TWOWHEELPIDCAR::turnright()
{
    RGB_LIGHT->green();

    MOTOR->brake();
    delay(100);

    MOTOR->runleft(60);
    MOTOR->runright(-60);
    delay(600);
  
    while(!(SENSOR_LIST[1]->is_line() && !SENSOR_LIST[2]->is_line()))
    {
        delay(5);
    }
}