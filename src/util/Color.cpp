#include "Color.h"

Color::Color() {
    r = 0;
    g = 0;
    b = 0;
}

Color::Color(vec3 color) {
    r = color.x;
    g = color.y;
    b = color.z;
}

Color::Color(float r, float, g, float b) {
    this->r = r;
    this->g = g;
    this->b = b;
}
