#ifndef MOTORRUN_H
#define MOTORRUN_H

#include <Arduino.h>

class MotorRun {
  public:
    MotorRun(int LPWM, int in1, int in2, int RPWM, int in3, int in4) :
      LPWM(LPWM), in1(in1), in2(in2), RPWM(RPWM), in3(in3), in4(in4) {}	 	//类种定义了6个参数，要将传入的参数值分别赋值给相应的类中定义的变量。 

    void init() {		//初始化引脚 
      pinMode(LPWM, OUTPUT);
      pinMode(in1, OUTPUT);
      pinMode(in2, OUTPUT);
      pinMode(RPWM, OUTPUT);
      pinMode(in3, OUTPUT);
      pinMode(in4, OUTPUT);
    }

    void motorLeft(int pwm) {
      if (pwm > 0) {
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        analogWrite(LPWM, pwm);
      } else if (pwm < 0) {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        analogWrite(LPWM, -pwm);
      } else {
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        analogWrite(LPWM, 0);
      }
    }

    void motorRight(int pwm) {
      if (pwm > 0) {
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        analogWrite(RPWM, pwm);
      } else if (pwm < 0) {
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
        analogWrite(RPWM, -pwm);
      } else {
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
        analogWrite(RPWM, 0);
      }
    }

    void brake(int time) { 		//刹车函数，传入反转持续时间，需要根据自己的小车调整 
      motorLeft(-255);
      motorRight(-255);
      delay(time);
      stop();
    }

    void stop() {
      motorLeft(0);
      motorRight(0);
    }

  private:
    int LPWM, in1, in2, RPWM, in3, in4;	 	// 定义电机引脚和PWM引脚 
};

#endif