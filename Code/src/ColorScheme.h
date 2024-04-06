#pragma once
#include "Color.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

enum struct ColorSchemeType {
    Monochrome,
    Complementary,
    Triadic,
    Analogous,
    Manual
};

struct ColorSchemeColor {
    double hue;
    double saturation = 1;

    ColorSchemeColor(double hueIn, double saturationIn = 1) : hue(fmod(hueIn, 360)), saturation(std::clamp(saturationIn, 0.0, 1.0)) {}
};

struct ColorScheme {
protected:
    std::vector<ColorSchemeColor> colors;

public:
    ColorScheme(std::vector<ColorSchemeColor> colors) : colors(colors){};
    const std::vector<ColorSchemeColor> &GetColors() const { return colors; }
    int GetNumberOfColors() const { return colors.size(); }
};

struct MonochromeColorScheme : public ColorScheme {
public:
    MonochromeColorScheme(double hue) : ColorScheme({hue}) {}
};

struct ComplementaryColorScheme : public ColorScheme {
public:
    ComplementaryColorScheme(double hue) : ColorScheme({hue, hue + 180}) {}
};

struct AnalogousColorScheme : public ColorScheme {
public:
    AnalogousColorScheme(double hue, double colorDistance, unsigned int numberOfHues) : ColorScheme({hue}) {
        for (unsigned int i = 1; i < (numberOfHues - 1) / 2; i++) {
            this->colors.emplace_back(hue + i * colorDistance);
            this->colors.emplace_back(hue - i * colorDistance);
        }
    }
};

struct TriadicColorScheme : public ColorScheme {
public:
    TriadicColorScheme(double hue) : ColorScheme({hue, hue + 120, hue + 240}) {}
};