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
    int startLed;
    int endLed;
    int steps;

    if (start < end) {
        startLed = (int)(start * pixelCount);
        endLed = (int)(end * pixelCount);
    } else {
        startLed = (int)(end * pixelCount);
        endLed = (int)(start * pixelCount);
    }

    steps = endLed - startLed;
    if (steps == 0) {
        steps = 1;
        startLed --;
    }

    for (int i = 0; i < steps + 1; i++) {
        pixels[startLed + i] = Color::fromHSV(h, s, v);
    }
}


void Renderer::gradient(double h, double s, double v, double start, double end) {
    int startLed;
    int endLed;
    int steps;

    double vStart;
    double vEnd;

    if (start < end) {
        vStart = v;
        vEnd = 0.0;

        startLed = (int)(start * pixelCount);
        endLed = (int)(end * pixelCount);
    } else {
        vStart = 0.0;
        vEnd = v;

        startLed = (int)(end * pixelCount);
        endLed = (int)(start * pixelCount);
    }

    steps = endLed - startLed;
    if (steps == 0) {
        steps = 1;
        startLed --;
    }


    for (int i = 0; i < steps + 1; i++) {
        pixels[startLed + i] = Color::fromHSV(h, s, (vStart + (vEnd - vStart) * (double)i / (double)steps));
    }
}