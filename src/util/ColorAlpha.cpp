#include "ColorAlpha.h"

ColorAlpha::ColorAlpha() : Color() {
    a = 0;
}

ColorAlpha::ColorAlpha(vec4 color) {
    r = color.x;
    g = color.y;
    b = color.z;
    a = color.w;
}

ColorAlpha::ColorAlpha(float r, float g, float b, float a) : Color(r, g, b) {
    this->a = a;
}
