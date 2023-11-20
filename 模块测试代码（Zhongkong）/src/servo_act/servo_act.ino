#include <Servo.h>
#include <Robotarm.h>   
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

void setup(){
    arm->init();

    delay(2000);
    arm->first_marching();
    delay(1000);
        
    arm->grab_gainRing();
    arm->marching();
    delay(1000);

    arm->placing_higher();
    arm->marching();
    delay(1000);

    arm->grab_ring();
    delay(300);
    arm->close_claw();
    delay(100);
    arm->marching();
    delay(1000);

    arm->placing_lower();

    // claw.attach(CLAW);
    // upper.attach(UPPER);
    // mid.attach(MID);
    // lower.attach(LOWER);
    // initialize();   //初始化
    
    // delay(1000);
    // first_marching(); //初始化姿态转行进姿态
    // delay(1000);
    
    // grab_gainRing();  //抓增益环
    // marching();       
    // delay(1000);
    
    // placing_higher(); //放三分区
    // marching();
    // delay(1000);
    
    // grab_ring();    //抓地上的环
    // delay(300);     //这里机械臂贴地后前进一小段卡位，再抓取
    // close_claw();
    // delay(100);
    // marching();
    // delay(1000);

    // placing_lower();  //放两分区
}

void loop(){

}