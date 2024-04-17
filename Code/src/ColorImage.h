#pragma once
#include "Color.h"
#include "image_ppm.h"
#include <string>

class ColorImage {
    OCTET* image;
    int width, height;

public:
    ColorImage(const std::string& filename);
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
