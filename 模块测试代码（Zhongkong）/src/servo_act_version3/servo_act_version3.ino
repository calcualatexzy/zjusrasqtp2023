#include <Servo.h>   
#define CLAW 2
#define UPPER 3
#define MID 4
#define LOWER 5       
#define CLAW_OPEN 90       
#define CLAW_CLOSE 113
Servo claw,upper,mid,lower;

void setup(){
    claw.attach(CLAW);
    upper.attach(UPPER);
    mid.attach(MID);
    lower.attach(LOWER);
    initialize();   //初始化
    
    delay(1000);
    first_marching(); //初始化姿态转行进姿态
    delay(1000);

    //grab_gainRing();  //抓增益环
    //delay(3000);
    
    //placing_lower_back(); //放二分区
    //marching();
    //delay(1000);
    //placing_higher_back();
    //grab_ring();    //抓地上的环
    //delay(300);     //这里机械臂贴地后前进一小段卡位，再抓取
    //close_claw();
    //delay(100);
    //marching();
    //delay(2000);

    //placing_higher_front();  //放三分区
    //remove_lower();
    //marching();
    //delay(1000);
    remove_lower();
    //marching();
}

void loop(){
  while(1);
}

void initialize()
{
    rotate_lower(88);
}

//所有舵机的delay参数均为10
void first_marching() //从初始化到行进姿态
{
    rotate_lower(65);
    rotate_mid(2);
    rotate_lower(29);
    rotate_upper(150);
}

void marching() //行进姿态
{
    rotate_lower(29);
    delay(100);
    rotate_mid(2);
    rotate_upper(150);
}

void grab_ring() //抓地上的环
{
    rotate_upper(173);
    rotate_lower(45);
    rotate_mid(25);
    rotate_lower(161);
}

void close_claw() //合上爪子
{
    rotate_claw(CLAW_CLOSE);
}

void grab_gainRing()  //倒退进入 抓增益环
{
    rotate_claw(CLAW_OPEN);
    rotate_upper(65);
    rotate_lower(63);
    rotate_mid(162);
    delay(500);
    rotate_claw(CLAW_CLOSE);
    delay(500);
    rotate_mid(2);
    rotate_lower(29);
    rotate_upper(150);
}

void placing_lower_back() //倒退进入二分区 放增益环
{
    rotate_lower(40);
    rotate_mid(52);
    rotate_upper(150);
    delay(200);
    rotate_claw(CLAW_OPEN);
}

void placing_higher_back()  //倒退进入三分区 放增益环
{
    rotate_lower(40);
    delay(200);
    rotate_mid(45);
    rotate_upper(135);
    delay(500);
    rotate_claw(CLAW_OPEN);
}

void placing_lower_front()  //正着进入二分区，放地上的环
{
    rotate_lower(48);
    rotate_mid(2);
    rotate_upper(68);
    delay(200);
    rotate_claw(CLAW_OPEN);
}

void placing_higher_front() //正着进入三分区，放地上的环
{
    rotate_lower(48);
    rotate_mid(2);
    rotate_upper(75);
    delay(200);
    rotate_claw(CLAW_OPEN);
}

void remove_lower()  //倒退进入对方二分区，捞走对方的环，扔到地上（一定概率会滚走）
{
    rotate_claw(CLAW_OPEN);
    rotate_lower(50);
    rotate_mid(95);
    rotate_upper(163);
    delay(200);
    rotate_claw(110);
    delay(200);
    rotate_mid(102);
    rotate_lower(90);
    delay(200);
    rotate_upper(50);

    rotate_claw(CLAW_OPEN);
     //可以抓上面两个，最下面抓不到


  // rotate_claw(CLAW_OPEN);
  // rotate_lower(48);
  // rotate_upper(80);
  // rotate_mid(135);
  // rotate_claw(113);
  // delay(200);
  // rotate_lower(90);
  // rotate_mid(102);
  // rotate_upper(50);
  // rotate_claw(CLAW_OPEN);
}

void remove_higher() //倒退进入对方三分区，捞走对方的环，扔到地上
{
  rotate_claw(CLAW_OPEN);
    rotate_lower(50);
    rotate_mid(100);
    delay(200);
    rotate_claw(CLAW_CLOSE);
    delay(200);
    rotate_lower(90);
    rotate_mid(50);
    rotate_upper(100);
    rotate_claw(CLAW_OPEN);
}

void rotate_claw(int angle){
    int anglex = claw.read();
    if (angle > anglex){
        for (int i = anglex;i < angle;i++){
            claw.write(i);
            delay(10);
        }
    }
    else if (angle < anglex){
        for (int i = anglex;i > angle;i--){
            claw.write(i);
            delay(10);
        }
    }
}

void rotate_upper(int angle){
    int anglex = upper.read();
    if (angle > anglex){
        for (int i = anglex;i < angle;i++){
            upper.write(i);
            delay(10);
        }
    }
    else if (angle < anglex){
        for (int i = anglex;i > angle;i--){
            upper.write(i);
            delay(10);
        }
    }
}

void rotate_mid(int angle){
    int anglex = mid.read();
    if (angle > anglex){
        for (int i = anglex;i < angle;i++){
            mid.write(i);
            delay(10);
        }
    }
    else if (angle < anglex){
        for (int i = anglex;i > angle;i--){
            mid.write(i);
            delay(10);
        }
    }
}

void rotate_lower(int angle){
    int anglex = lower.read();
    if (angle > anglex){
        for (int i = anglex;i < angle;i++){
            lower.write(i);
            delay(10);
        }
    }
    else if (angle < anglex){
        for (int i = anglex;i > angle;i--){
            lower.write(i);
            delay(10);
        }
    }
}