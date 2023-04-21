#include "Renderer.h"

Renderer::Renderer(uint16_t pixelCount_) {
    pixelCount = pixelCount_;
    pixels = (color_int *)malloc(sizeof(color_int) * pixelCount_);
}


void Renderer::clear() {
    for (int i = 0; i < pixelCount; i++) {
        pixels[i] = 0;
    }
}


void Renderer::fill(color_int color) {
    for (int i = 0; i < pixelCount; i++) {
        pixels[i] = color;
    }
}


void Renderer::segment(double h, double s, double v, double start, double end) {
    color_int color = Color::fromHSV(h, s, v);

    double d_startLed = start * pixelCount;
    double d_endLed = end * pixelCount;

    int i_startLed = (int)trunc(d_startLed);
    int i_endLed = (int)trunc(d_endLed);

    if (i_startLed > 0) {
        pixels[i_startLed - 1] = Color::fromHSV(h, s, 1 - v * (d_startLed - i_startLed));
    }

    if (i_endLed < pixelCount) {
        pixels[i_endLed + 1] = Color::fromHSV(h, s, v * (d_endLed - i_endLed));
    }

    for (int i=i_startLed; i<=d_endLed; i++) {
        pixels[i] = color;
    }
}