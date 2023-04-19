#ifndef V02_RELEASE_LED_CONSTANTS_H
#define V02_RELEASE_LED_CONSTANTS_H

#include <Arduino.h>
#include <Adafruit_NeoPXL8.h>

#define LED_GPIO 12 // (pin 16)

int8_t ledPins[8] = {
    LED_GPIO + 0,
    LED_GPIO + 1,
    LED_GPIO + 2,
    LED_GPIO + 3,
    LED_GPIO + 4,
    LED_GPIO + 5,
    LED_GPIO + 6,
    LED_GPIO + 7
};

const int ledCount = 144;
const int ledPixelType = NEO_GRBW;

#endif //V02_RELEASE_LED_CONSTANTS_H
