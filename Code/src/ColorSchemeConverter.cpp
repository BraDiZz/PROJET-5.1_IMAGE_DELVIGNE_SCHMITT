#include "ColorSchemeConverter.h"

void ColorSchemeConverter::ConvertToColorScheme(ColorImage &image, const ColorScheme &scheme){
    for(int x = 0; x < image.GetWidth(); x++){
        for(int y = 0; y < image.GetHeight(); y++){
            Color pixel = image.GetPixel(x, y);
            Color closestColor = scheme.GetClostesColorInScheme(pixel);
            image.SetPixel(x, y, closestColor);
        }
    }
}