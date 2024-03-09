#pragma once
#include <array>

struct Color{
    unsigned char r, g, b;

    std::array<double, 3> GetHSL() const;
    void SetHSV(double hue, double saturation, double lightness);
};