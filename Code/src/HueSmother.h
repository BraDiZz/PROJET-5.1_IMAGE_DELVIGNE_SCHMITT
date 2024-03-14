#pragma once
#include "ColorImage.h"

class HueSmother {
public:
    static void SmoothHue(ColorImage &image, int radius);
    static double GetAverageHue(const ColorImage &image, int x, int y, int radius);
};