#include <Servo.h>                    
Servo myservo;
void setup()
{

    myservo.attach(4);
}

void loop(){

    delay(1000);
    rotate(0);
    // delay(1000);
    // rotate(0);
    while(1);
}

void rotate(int angle){
    int anglex = myservo.read();
    if (angle > anglex){
        for (int i = anglex;i < angle;i++){
            myservo.write(i);
            delay(15);
        }
    }
    else if (angle < anglex){
        for (int i = anglex;i > angle;i--){
            myservo.write(i);
            delay(15);
        }
    }
}
