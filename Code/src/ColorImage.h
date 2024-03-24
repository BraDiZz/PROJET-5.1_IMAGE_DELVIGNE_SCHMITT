#pragma once
#include "image_ppm.h"
#include "Color.h"

class ColorImage{
    OCTET* image;
    int width, height;

public:
    ColorImage(char* filename);
    ColorImage(int width, int height);
    ~ColorImage();

    void Write(char* filename);
    void SetPixel(int x, int y, Color color);
    Color GetPixel(int x, int y) const;
    bool IsInside(int x, int y) const;

    void Set(const ColorImage& other);

    int GetWidth() const;
    int GetHeight() const;

private:
    int GetIndexInArray(int x, int y) const;

};

