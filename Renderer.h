#ifndef V02_RELEASE_RENDERER_H
#define V02_RELEASE_RENDERER_H

#include "Color.h"


class Renderer {
private:
    uint16_t pixelCount;
public:
    color_int *pixels;
    Renderer(uint16_t pixelCount_);
    void clear();
    void fill(color_int color);
    void segment(double h, double s, double v, double start, double end);
    void gradient(double h, double s, double v, double start, double end);
};


#endif //V02_RELEASE_RENDERER_H
