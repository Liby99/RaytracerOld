#ifndef COLOR_H
#define COLOR_H

class Color {
    public:
        float r;
        float g;
        float b;
        Color();
        Color(vec3 color);
        Color(float r, float g, float b);    
};

#endif
