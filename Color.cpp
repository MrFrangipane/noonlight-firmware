#include "Color.h"


// borrowed from https://github.com/adafruit/Adafruit_NeoPixel/blob/master/Adafruit_NeoPixel.cpp
color_int Color::fromRGBW(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
    return ((color_int)w << 24) | ((color_int)r << 16) | ((color_int)g << 8) | b;
}


color_int Color::fromRGB(uint8_t r, uint8_t g, uint8_t b) {
    float r_ = static_cast<float>(r);
    float g_ = static_cast<float>(g);
    float b_ = static_cast<float>(b);

    float M = max(r_, max(g_, b_));
    float m = min(r_, min(g_, b_));

    if( M == 0) {
        return 0;
    }

    float W_;
    if( m / M < 0.5) {
        W_ = (m * M) / (M - m);
    } else {
        W_ = M;
    }

    float K = (W_ + M) / M;

    return Color::fromRGBW(
            static_cast<uint8_t>(floor(( K * r_ ) - W_)),
            static_cast<uint8_t>(floor(( K * g_ ) - W_)),
            static_cast<uint8_t>(floor(( K * b_ ) - W_)),
            static_cast<uint8_t>(W_)
    );
}


// borrowed from https://github.com/adafruit/Adafruit_NeoPixel/blob/master/Adafruit_NeoPixel.cpp
color_int Color::fromHSV(uint16_t h, uint16_t s, uint16_t v) {
    uint8_t r, g, b;

    h = (h * 1530L + 32768) / 65536;

    if (h < 510) { // Red to Green-1
        b = 0;
        if (h < 255) { //   Red to Yellow-1
            r = 255;
            g = h;       //     g = 0 to 254
        } else {         //   Yellow to Green-1
            r = 510 - h; //     r = 255 to 1
            g = 255;
        }
    } else if (h < 1020) { // Green to Blue-1
        r = 0;
        if (h < 765) { //   Green to Cyan-1
            g = 255;
            b = h - 510;  //     b = 0 to 254
        } else {          //   Cyan to Blue-1
            g = 1020 - h; //     g = 255 to 1
            b = 255;
        }
    } else if (h < 1530) { // Blue to Red-1
        g = 0;
        if (h < 1275) { //   Blue to Magenta-1
            r = h - 1020; //     r = 0 to 254
            b = 255;
        } else { //   Magenta to Red-1
            r = 255;
            b = 1530 - h; //     b = 255 to 1
        }
    } else { // Last 0.5 Red (quicker than % operator)
        r = 255;
        g = b = 0;
    }

    // Apply saturation and value to R,G,B, pack into 32-bit result:
    uint32_t v1 = 1 + v;  // 1 to 256; allows >>8 instead of /255
    uint16_t s1 = 1 + s;  // 1 to 256; same reason
    uint8_t s2 = 255 - s; // 255 to 0
    return ((((((r * s1) >> 8) + s2) * v1) & 0xff00) << 8) |
           (((((g * s1) >> 8) + s2) * v1) & 0xff00) |
           (((((b * s1) >> 8) + s2) * v1) >> 8);
}
