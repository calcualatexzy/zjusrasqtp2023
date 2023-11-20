#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif
#include "CK008.h"

CK008::CK008(int sig) {
    pinMode(sig, INPUT);
    pin = sig;
}

int CK008::detect() {
    return digitalRead(pin);
}
