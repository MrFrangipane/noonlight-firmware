#ifndef V02_RELEASE_COLOR_H
#define V02_RELEASE_COLOR_H

#include <Arduino.h>


typedef uint32_t color_int;  // FIXME: define 8b and 16b too

class Color {
public:
    static color_int fromRGBW(uint8_t r, uint8_t g, uint8_t b, uint8_t w);
    static color_int fromRGB(uint8_t r, uint8_t g, uint8_t b);
    static color_int fromHSV(uint16_t h, uint16_t s, uint16_t v);
};


#endif //V02_RELEASE_COLOR_H
