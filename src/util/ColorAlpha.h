#ifndef COLOR_ALPHA_H
#define COLOR_ALPHA_H

#include "Color.h"

class ColorAlpha : public Color {
    private:
        float a;
    public:
        ColorAlpha();
        ColorAlpha(vec4 color);
        ColorAlpha(float r, float g, float b, float a);
};

#endif
