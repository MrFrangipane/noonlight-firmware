#include "Oscillator.h"

#include <Arduino.h>
#include "helpers.h"


Oscillator::Oscillator() {
    lastTimestamp = 0;
}


void Oscillator::setSpeed(double s) {
    speed = s;
    stepDelta = pow(speed, 2.2) / 15;
}


void Oscillator::setPhase(double p) {
    phase = p;
}


void Oscillator::step() {
    unsigned long elapsed = millis() - lastTimestamp;
    lastTimestamp = millis();

    if (speed != 0.0) {
        currentPhase += stepDelta * (double)elapsed;
        value = cos(currentPhase + phase) * 0.5 + 0.5;

    } else {
        currentPhase = 0.0;
        value = cos(currentPhase + phase) * 0.5 + 0.5;
        printDouble(phase, 100);
    }
}


double Oscillator::getValue() {
    return value;
}
