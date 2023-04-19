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
