#ifndef V02_RELEASE_DMX_CONSTANTS_H
#define V02_RELEASE_DMX_CONSTANTS_H


enum DmxProgram { SEGMENT, GRADIENT, STROBE };

struct DmxStatus {
    int startChannel;
    double h;
    double s;
    double v;
    DmxProgram program;
    double paramPhase;
    double paramSpeed;
    double paramOrigin;
    double paramWidth;
};

const byte dmxRxGPIO   = 11;

// enum ?
const byte dmxChH      = 1;
const byte dmxChS      = 2;
const byte dmxChV      = 3;
const byte dmxChProg   = 4;  // [0:85] GRADIENT - [86:170] SEGMENT - [171:255] STROBE
const byte dmxChParamPhase = 5;
const byte dmxChParamSpeed = 6;
const byte dmxChParamOrigin = 7;
const byte dmxChParamWidth = 8;


#endif //V02_RELEASE_DMX_CONSTANTS_H
