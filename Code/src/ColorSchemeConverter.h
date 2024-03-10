#pragma once
#include "ColorScheme.h"
#include "ColorImage.h"

class ColorSchemeConverter{
public:
    static void ConvertToColorScheme(ColorImage& image, const ColorScheme& scheme);
};