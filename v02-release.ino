// NOON Light
// RP2040 (RPi Pico), DMX receiver, SK6812 (WS2812B) Fixture Controller
// for PCB v2 03/2023
// Libraries used: Adafruit NeoPXL8, PicoDMX
#include <DmxInput.h>
#include <Adafruit_NeoPXL8.h>

#include "Color.h"
#include "DIPSwitch10.h"
#include "Renderer.h"
#include "oscillator.h"
#include "dmx_constants.h"
#include "led_constants.h"

#define LOOP_DELAY 2

DIPSwitch10 dipSwitch10;
DmxInput dmx;
DmxStatus dmxStatus;
volatile uint8_t dmxBuffer[512];
Oscillator oscillator;
Renderer renderer(ledCount);
Adafruit_NeoPXL8 leds(ledCount, ledPins, ledPixelType);


void setup() {
    Serial.begin();

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    dipSwitch10.initPins(1, 10);

    leds.begin();
    leds.setBrightness(255);
    leds.clear();
    if( leds.canShow() ) {
        leds.show();
    }

    dmx.begin(dmxRxGPIO, 1, 512);
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
        dmxStatus.startChannel = dipSwitch10.value();
        if (dmxStatus.startChannel == 0) {
          delay(LOOP_DELAY);
          return;
        }

        //
        // ACTUAL CODE HERE
        dmxStatus.h = (double)dmxBuffer[dmxStatus.startChannel + dmxChH - 1] / 255.0 * 360;
        dmxStatus.s = (double)dmxBuffer[dmxStatus.startChannel + dmxChS - 1] / 255.0;
        dmxStatus.v = (double)dmxBuffer[dmxStatus.startChannel + dmxChV - 1] / 255.0;
        //dmxStatus.program = dmxBuffer[dmxStatus.startChannel + dmxChProg - 1] 

        oscillator.setSpeed((double)dmxBuffer[dmxStatus.startChannel + dmxChParamA - 1] / 255.0);
        oscillator.step();

        renderer.clear();

        renderer.segment(dmxStatus.h, dmxStatus.s, dmxStatus.v, 0.5, oscillator.getValue());
        renderer.segment(dmxStatus.h, dmxStatus.s, dmxStatus.v, 0.5, 1 - oscillator.getValue());

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