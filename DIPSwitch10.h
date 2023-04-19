#ifndef V02_RELEASE_DIPSWITCH10_H
#define V02_RELEASE_DIPSWITCH10_H

#include <Arduino.h>


enum demoColor {
    red,
    green,
    blue,
    white
};


class DIPSwitch10 {
private:
    int startPin;
    int endPin;
    int switches[10];

public:
    void initPins(int startPin_, int endPin_);
    void read();
    bool isDemoMode();
    demoColor demoCurrentColor();
};

#endif //V02_RELEASE_DIPSWITCH10_H
