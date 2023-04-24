// NOON Light
// RP2040 (RPi Pico), DMX receiver, SK6812 (WS2812B) Fixture Controller
// for PCB v2 03/2023
// Libraries used: Adafruit NeoPXL8, PicoDMX
// version 0.0.1
#include <DmxInput.h>
#include <Adafruit_NeoPXL8.h>

#include "Color.h"
#include "DIPSwitch10.h"
#include "Renderer.h"
#include "oscillator.h"
#include "dmx_constants.h"
#include "led_constants.h"

#define LOOP_DELAY 2
//#define SERIAL_DMX_DEBUG


DIPSwitch10 dipSwitch10;
DmxInput dmx;
DmxStatus dmxStatus;
volatile uint8_t dmxBuffer[512];
Oscillator oscillator;
Renderer renderer(ledCount);
Adafruit_NeoPXL8 leds(ledCount, ledPins, ledPixelType);
double Color::gamma = 2.5;
double Color::gammaTreshold = 0.01;  // compute gamma for this HSV Value and up


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
        // PARSE DMX
        dmxStatus.h = (double)dmxBuffer[dmxStatus.startChannel + dmxChH - 1] / 255.0 * 360;
        dmxStatus.s = (double)dmxBuffer[dmxStatus.startChannel + dmxChS - 1] / 255.0;
        dmxStatus.v = (double)dmxBuffer[dmxStatus.startChannel + dmxChV - 1] / 255.0;
        switch (dmxBuffer[dmxStatus.startChannel + dmxChProg - 1]) {
            case 0 ... 85:
                dmxStatus.program = DmxProgram::GRADIENT;
                break;

            case 86 ... 170:
                dmxStatus.program = DmxProgram::SEGMENT;
                break;

            case 171 ... 255:
                dmxStatus.program = DmxProgram::STROBE;
                break;
        }
        dmxStatus.paramPhase = (double)dmxBuffer[dmxStatus.startChannel + dmxChParamPhase - 1] / 255.0 * 2.0 * 3.1416;
        dmxStatus.paramSpeed = (double)dmxBuffer[dmxStatus.startChannel + dmxChParamSpeed - 1] / 255.0;
        dmxStatus.paramOrigin = (double)dmxBuffer[dmxStatus.startChannel + dmxChParamOrigin - 1] / 255.0;
        dmxStatus.paramWidth = (double)dmxBuffer[dmxStatus.startChannel + dmxChParamWidth - 1] / 255.0;

        //
        // COMPUTE
        oscillator.setSpeed(dmxStatus.paramSpeed);
        oscillator.setPhase(dmxStatus.paramPhase);
        oscillator.step();

        renderer.clear();

        #ifdef SERIAL_DMX_DEBUG
        for (int i=0; i < 8; i++) {
            Serial.print(dmxBuffer[i + dmxStatus.startChannel]); // QLC+ vs OLA ?
            Serial.print(" ");
        }
        #endif
        

        switch (dmxStatus.program) {
            case DmxProgram::SEGMENT:
                renderer.segment(
                    dmxStatus.h, dmxStatus.s, dmxStatus.v,
                    dmxStatus.paramOrigin,
                    dmxStatus.paramOrigin + oscillator.getValue() * dmxStatus.paramWidth
                );
                renderer.segment(
                    dmxStatus.h, dmxStatus.s, dmxStatus.v,
                    dmxStatus.paramOrigin,
                    dmxStatus.paramOrigin - oscillator.getValue() * dmxStatus.paramWidth
                );
                break;

            case DmxProgram::GRADIENT:
                renderer.gradient(
                        dmxStatus.h, dmxStatus.s, dmxStatus.v,
                        dmxStatus.paramOrigin,
                        dmxStatus.paramOrigin + oscillator.getValue() * dmxStatus.paramWidth
                );
                renderer.gradient(
                        dmxStatus.h, dmxStatus.s, dmxStatus.v,
                        dmxStatus.paramOrigin,
                        dmxStatus.paramOrigin - oscillator.getValue() * dmxStatus.paramWidth
                );
                break;

            case DmxProgram::STROBE:
                renderer.fill(0);
                if (oscillator.getValue() > 0.5) {
                    renderer.fill(Color::fromHSV(dmxStatus.h, dmxStatus.s, dmxStatus.v));
                } else {
                    renderer.fill(0);
                }
                break;
        }

        //
        // RENDER
        for (int i = 0; i < ledCount; i++) {
            leds.setPixelColor(i, renderer.pixels[i]);
        }

        #ifdef SERIAL_DMX_DEBUG
        Serial.println("");
        #endif
    }

    if( leds.canShow() ) {
        leds.show();
    }

    delay(LOOP_DELAY);
}


void __isr dmxDataRecevied(DmxInput* instance) {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}
