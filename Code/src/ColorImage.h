#pragma once
#include "image_ppm.h"

struct Color{
    unsigned char r, g, b;
};

class ColorImage{
    OCTET* image;
    int width, height;

public:
    ColorImage(char* filename);
    ColorImage(int width, int height);
    ~ColorImage();

    void Write(char* filename);
    void SetPixel(int x, int y, Color color);
    Color GetPixel(int x, int y);
    bool IsInside(int x, int y);

    int GetWidth();
    int GetHeight();
};

