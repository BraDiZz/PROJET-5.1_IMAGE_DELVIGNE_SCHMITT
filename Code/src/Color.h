#pragma once
#include <array>

struct Color{
    unsigned char r, g, b;

    std::array<double, 3> GetHSL() const;
    void SetHSL(double hue, double saturation, double lightness);

    static Color FromHSL(double hue, double saturation, double lightness);
};