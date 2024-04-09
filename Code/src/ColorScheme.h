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
    double hue = 0;
    double saturation = 1;

    ColorSchemeColor() = default;
    ColorSchemeColor(double hueIn, double saturationIn = 1) : hue(fmod(hueIn, 360)), saturation(std::clamp(saturationIn, 0.0, 1.0)) {}
};

struct ColorScheme {
protected:
    std::vector<ColorSchemeColor> colors;

public:
    ColorScheme(std::vector<ColorSchemeColor> colors) : colors(colors){};
    const std::vector<ColorSchemeColor> &GetColors() const { return colors; }
    int GetNumberOfColors() const { return colors.size(); }

    virtual void SetColor(int index, double hue, double saturation) {
        colors[index].hue = fmod(hue, 360);
        colors[index].saturation = std::clamp(saturation, 0.0, 1.0);
    }
};

struct MonochromeColorScheme : public ColorScheme {
public:
    MonochromeColorScheme(double hue) : ColorScheme({hue}) {}
};

struct ComplementaryColorScheme : public ColorScheme {
public:
    ComplementaryColorScheme(double hue) : ColorScheme({hue, hue + 180}) {}

    void SetColor(int index, double hue, double saturation) override {
        if (index == 0) {
            colors[1].hue = fmod(hue + 180, 360);
        }
        ColorScheme::SetColor(index, hue, saturation);
    }
};

struct AnalogousColorScheme : public ColorScheme {
    double colorDistance;

public:
    AnalogousColorScheme(double hue, double colorDistance, unsigned int numberOfHues) : ColorScheme({hue}), colorDistance(colorDistance) {
        for (unsigned int i = 1; i < numberOfHues; i++) {
            colors.emplace_back(hue + i * colorDistance);
        }
    }

    void SetColor(int index, double hue, double saturation) override {
        if (index == 0) {
            for (unsigned int i = 1; i < colors.size(); i++) {
                colors[i].hue = fmod(hue + colorDistance * i, 360);
            }
        }
        ColorScheme::SetColor(index, hue, saturation);
    }
};

struct TriadicColorScheme : public ColorScheme {
public:
    TriadicColorScheme(double hue) : ColorScheme({hue, hue + 120, hue + 240}) {}

    void SetColor(int index, double hue, double saturation) override {
        if (index == 0) {
            colors[1].hue = fmod(hue + 120, 360);
            colors[2].hue = fmod(hue + 240, 360);
        }
        ColorScheme::SetColor(index, hue, saturation);
    }
};