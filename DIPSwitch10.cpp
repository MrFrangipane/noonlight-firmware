#include <Arduino.h>

#include "Color.h"
#include "DIPSwitch10.h"


void DIPSwitch10::initPins(int startPin_, int endPin_) {
    startPin = startPin_;
    endPin = endPin_;

    for (int pin = startPin; pin <= endPin; pin++) {
        pinMode(pin, INPUT_PULLUP);
    }
}


void DIPSwitch10::read() {
    int switch_index = 0;
    for (int pin = startPin; pin <= endPin; pin++) {
        switches[switch_index] = !digitalRead(pin);
        switch_index ++;
    }
}


uint16_t DIPSwitch10::value() {
    uint16_t value = 0;

    if (switches[0] == true) {
        value = 1;
    }

    for (int i = 1; i < 10; i++) {
        value += switches[i] * (2 << (i - 1));
    }

    return min(value, 512);
}


bool DIPSwitch10::isDemoMode() {
    if ( switches[9] == 0) {
        return false;
    }

    for (int i = 0; i < 9; i++) {
        if (switches[i] == 1) {
            return true;
        }
    }

    return false;
}


color_int DIPSwitch10::demoCurrentColor() {
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
    uint8_t w = 0;

    if (switches[0] == 1) {
        r = 127;
    }
    if (switches[1] == 1) {
        r += 128;
    }

    if (switches[2] == 1) {
        g = 127;
    }
    if (switches[3] == 1) {
        g += 128;
    }

    if (switches[4] == 1) {
        b = 127;
    }
    if (switches[5] == 1) {
        b += 128;
    }

    if (switches[6] == 1) {
        w = 127;
    }
    if (switches[7] == 1) {
        w += 128;
    }

    return Color::fromRGBW(r, g, b, w);
}
