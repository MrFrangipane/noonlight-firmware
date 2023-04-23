#include "Oscillator.h"

#include <Arduino.h>

void Oscillator::setSpeed(double s) {
    speed = s;
    stepDelta = pow(speed, 2.2) / 8;
}


void Oscillator::step() {
    if (speed != 0.0) {
        phase += stepDelta;
        value = cos(phase) * 0.5 + 0.5;

    } else {
        phase = 0.0;
        value = 1.0;
    }
}


double Oscillator::getValue() {
    return value;
}
