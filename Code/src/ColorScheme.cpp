#include "ColorScheme.h"
#include <stdlib.h>
#include <cmath>

ColorScheme::ColorScheme(std::vector<double> huesIn) : hues(huesIn) {
    for(double& hue : this->hues){
        hue = fmod(hue, 360);
        if(hue < 0){
            hue += 360;
        }
    }
}

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
