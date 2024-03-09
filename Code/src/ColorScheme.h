#pragma once
#include "Color.h"
#include <vector>

class ColorScheme{
    std::vector<double> hues;

public:
    ColorScheme(std::vector<double> hues);
    Color GetClostesColorInScheme(const Color& color);

private:
    double GetClosestHue(double hue);
};