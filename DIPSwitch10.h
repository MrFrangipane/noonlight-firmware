#ifndef V02_RELEASE_DIPSWITCH10_H
#define V02_RELEASE_DIPSWITCH10_H

#include "Color.h"

class DIPSwitch10 {
private:
    int startPin;
    int endPin;
    int switches[10];

public:
    void initPins(int startPin_, int endPin_);
    void read();
    uint16_t value();
    bool isDemoMode();
    color_int demoCurrentColor();
};

#endif //V02_RELEASE_DIPSWITCH10_H
