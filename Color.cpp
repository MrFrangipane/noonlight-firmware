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
color_int Color::fromHSV(double h, double s, double v) {
    double r = 0, g = 0, b = 0;

    if (v > gammaTreshold) {
        v = max(0.004, pow(v, gamma));
    }

    if (s == 0)
    {
        r = v;
        g = v;
        b = v;
    }
    else
    {
        int i;
        double f, p, q, t;

        if (h == 360)
            h = 0;
        else
            h = h / 60;

        i = (int)trunc(h);
        f = h - i;

        p = v * (1.0 - s);
        q = v * (1.0 - (s * f));
        t = v * (1.0 - (s * (1.0 - f)));

        switch (i)
        {
            case 0:
                r = v;
                g = t;
                b = p;
                break;

            case 1:
                r = q;
                g = v;
                b = p;
                break;

            case 2:
                r = p;
                g = v;
                b = t;
                break;

            case 3:
                r = p;
                g = q;
                b = v;
                break;

            case 4:
                r = t;
                g = p;
                b = v;
                break;

            default:
                r = v;
                g = p;
                b = q;
                break;
        }

    }

    return Color::fromRGB(r * 255, g * 255, b * 255);
}
