#include "ColorScheme.h"
#include <stdlib.h>

ColorScheme::ColorScheme(std::vector<double> hues) : hues(hues) {}

Color ColorScheme::GetClostesColorInScheme(const Color& color) const{
    auto originalHSLColor = color.GetHSL();
    double closestHue = GetClosestHue(originalHSLColor[0]);

    Color closestColor;
    closestColor.SetHSV(closestHue, originalHSLColor[1], originalHSLColor[2]);
    return closestColor;
}

double ColorScheme::GetClosestHue(double hue) const{
    double minDistance = 360;
    double closestHue;
    for(double h : this->hues){
        double distance = std::min(std::abs(h - hue), 360 - std::abs(h - hue));
        if(distance < minDistance){
            minDistance = distance;
            closestHue = h;
        }
    }
    return closestHue;
}
