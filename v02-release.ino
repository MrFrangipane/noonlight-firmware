// NOON Light
// RP2040 (RPi Pico), DMX receiver, SK6812 (WS2812B) Fixture Controller
// for PCB v2 03/2023
// Libraries used: Adafruit NeoPXL8, PicoDMX
#include <Arduino.h>

#include <DmxInput.h>
#include <Adafruit_NeoPXL8.h>

#include "Color.h"
#include "DIPSwitch10.h"
#include "Renderer.h"
#include "dmx_constants.h"
#include "led_constants.h"

#define LOOP_DELAY 2

DIPSwitch10 dipSwitch10;

DmxInput dmx;
volatile uint8_t dmxBuffer[dmxChannelCount];
uint16_t dmxStartChannel;

Adafruit_NeoPXL8 leds(ledCount, ledPins, ledPixelType);

Renderer renderer(ledCount);

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    dipSwitch10.initPins(1, 10);

    leds.begin();
    leds.setBrightness(255);
    leds.clear();
    if( leds.canShow() ) {
        leds.show();
    }

    dmx.begin(dmxRxGPIO, 0, dmxChannelCount); // FIXME: read DIP channel
    dmx.read_async(dmxBuffer, dmxDataRecevied);
}


void loop() {
    dipSwitch10.read();

    // Demo -----------------------------------
    if (dipSwitch10.isDemoMode()) {
        leds.fill(dipSwitch10.demoCurrentColor(), 0, ledCount);

    // Dmx ------------------------------------
    } else {
        leds.clear();
        dmxStartChannel = dipSwitch10.value();
        if (dmxStartChannel == 0) {
          delay(LOOP_DELAY);
          return;
        }

        //
        // ACTUAL CODE HERE
        double a = (cos(static_cast<double>(millis()) / 2500) + 1) / 2;
        double b = (cos(static_cast<double>(millis()) / 50) + 1) / 2;

        renderer.clear();
        renderer.segment(120.0, 1.0, 1.0, a * 0.2, b * 0.6 + 0.2);

        for (int i = 0; i < ledCount; i++) {
            leds.setPixelColor(i, renderer.pixels[i]);
        }
    }

    if( leds.canShow() ) {
        leds.show();
    }

    delay(LOOP_DELAY);
}


void __isr dmxDataRecevied(DmxInput* instance) {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}
