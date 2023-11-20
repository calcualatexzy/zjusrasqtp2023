#ifndef TOUCHSENSOR_H
#define TOUCHSENSOR_H

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#define TOUCHED 0
#define NOT_TOUCHED 1

class CK008 {
    public:
        /* Initialize the touch sensor. */
        CK008(int sig);

        /* Detect whether the button has been pressed. 
         * @return TOUCHED / NOT_TOUCHED
         * @author Kaixuan WANG
         */
        int detect();
    private:
        int pin;
};

#endif
