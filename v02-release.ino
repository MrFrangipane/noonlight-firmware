// NOON Light
//
// RP2040 (RPi Pico), DMX receiver, SK6812 (WS2812B) Fixture Controller
//
// for PCB v2 03/2023
//
// Libraries used: Adafruit NeoPXL8, PicoDMX
#include <Arduino.h>

#include <DmxInput.h>
#include <Adafruit_NeoPXL8.h>

#include "DIPSwitch10.h"
#include "dmx_constants.h"


DIPSwitch10 dipSwitch10;
DmxInput dmx;
volatile uint8_t dmxBuffer[dmxChannelCount];
uint16_t dmxStartChannel;


void setup() {
    Serial.begin();

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    dipSwitch10.initPins(1, 10);

    dmx.begin(dmxRxGPIO, 0, dmxChannelCount);
    dmx.read_async(dmxBuffer, dmxDataRecevied);
}


void loop() {
    dipSwitch10.read();

    Serial.println(dipSwitch10.isDemoMode());

    delay(200);
}


void __isr dmxDataRecevied(DmxInput* instance) {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}
