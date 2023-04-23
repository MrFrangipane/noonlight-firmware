#ifndef V02_RELEASE_DMX_CONSTANTS_H
#define V02_RELEASE_DMX_CONSTANTS_H


enum DmxProgram { SEGMENT, GRADIENT, STROBE };

struct DmxStatus {
    int startChannel;
    double h;
    double s;
    double v;
    DmxProgram program;
    double paramA;
    double paramB;
    double paramC;
    double paramD;
    double paramE;
    double paramF;
};

const byte dmxRxGPIO   = 11;
const byte dmxChH      = 1;
const byte dmxChS      = 2;
const byte dmxChV      = 3;
const byte dmxChProg   = 4;
const byte dmxChParamA = 5;
const byte dmxChParamB = 6;
const byte dmxChParamC = 7;
const byte dmxChParamD = 8;
const byte dmxChParamE = 9;
const byte dmxChParamF = 10;

#endif //V02_RELEASE_DMX_CONSTANTS_H
