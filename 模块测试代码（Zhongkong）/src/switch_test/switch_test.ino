#include<RGB.h>
#include<CK008.h>

RGB rgbLight(A10, A11, A12);
CK008 switch1(25);
CK008 switch2(27);
CK008 switch3(29);
CK008 switch4(31);

void setup()
{

}

void loop()
{
    if(switch1.detect() == NOT_TOUCHED && switch2.detect() == NOT_TOUCHED && switch3.detect() == NOT_TOUCHED && switch4.detect() == NOT_TOUCHED)
    {
        rgbLight.white();
    }
    else
    {
        if(switch1.detect() == TOUCHED)
            rgbLight.blue();
        else if(switch2.detect() == TOUCHED)
            rgbLight.green();
        else if(switch3.detect() == TOUCHED)
            rgbLight.red();
        else if(switch4.detect() == TOUCHED)
            rgbLight.yellow();
        delay(1000);
    }
}