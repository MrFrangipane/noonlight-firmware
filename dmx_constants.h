#ifndef V02_RELEASE_DMX_CONSTANTS_H
#define V02_RELEASE_DMX_CONSTANTS_H


enum DmxProgram { SEGMENT, GRADIENT, STROBE };

struct DmxStatus {
    int startChannel;
    double h;
    double s;
    double v;
    DmxProgram program;
    double phase;
    double speed;
    double origin;
    double width;
    double fixedWidth;
};

const byte dmxRxGPIO   = 11;

// enum ?
const byte dmxChH      = 1;
const byte dmxChS      = 2;
const byte dmxChV      = 3;
const byte dmxChProg   = 4;  // [0:85] GRADIENT - [86:170] SEGMENT - [171:255] STROBE
const byte dmxChPhase = 5;
const byte dmxChSpeed = 6;
const byte dmxChOrigin = 7;
const byte dmxChWidth = 8;
const byte dmxChFixedWidth = 9;


#endif //V02_RELEASE_DMX_CONSTANTS_H
