#ifndef MOTORRUN_H
#define MOTORRUN_H

#include <Arduino.h>

class MotorRun {
  public:
    MotorRun(int enA, int in1, int in2, int enB, int in3, int in4) :
      enA(enA), in1(in1), in2(in2), enB(enB), in3(in3), in4(in4) {}	 	//类种定义了6个参数，要将传入的参数值分别赋值给相应的类中定义的变量。 

    void init() {		//初始化引脚 
      pinMode(enA, OUTPUT);
      pinMode(in1, OUTPUT);
      pinMode(in2, OUTPUT);
      pinMode(enB, OUTPUT);
      pinMode(in3, OUTPUT);
      pinMode(in4, OUTPUT);
    }

    void motorLeft(int pwm) {
      if (pwm > 0) {
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        analogWrite(enA, pwm);
      } else if (pwm < 0) {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        analogWrite(enA, -pwm);
      } else {
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        analogWrite(enA, 0);
      }
    }

    void motorRight(int pwm) {
      if (pwm > 0) {
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        analogWrite(enB, pwm);
      } else if (pwm < 0) {
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
        analogWrite(enB, -pwm);
      } else {
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
        analogWrite(enB, 0);
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
    int enA, in1, in2, enB, in3, in4;	 	// 定义电机引脚和PWM引脚 
};

#endif