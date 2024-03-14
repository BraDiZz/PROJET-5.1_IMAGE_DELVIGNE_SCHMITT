#include "Color.h"
#include <stdlib.h>
#include <cmath>

std::array<double, 3> Color::GetHSL() const{
    double r = this->r / 255.0;
    double g = this->g / 255.0;
    double b = this->b / 255.0;

    double max = std::max(r, std::max(g, b));
    double min = std::min(r, std::min(g, b));
    double delta = max - min;

    double lightness = (max + min) / 2.0;
    double saturation = 0;
    double hue = 0;

    if(delta != 0){
        saturation = delta / (1 - std::abs(2 * lightness - 1));
        if(max == r){
            hue = 60 * fmod((g - b) / delta, 6);
        }else if(max == g){
            hue = 60 * ((b - r) / delta + 2);
        }else{
            hue = 60 * ((r - g) / delta + 4);
        }
    }

    return {hue, saturation, lightness};
}

void Color::SetHSL(double hue, double saturation, double lightness){
    double c = (1 - std::abs(2 * lightness - 1)) * saturation;
    double x = c * (1 - std::abs(fmod(hue / 60, 2) - 1));
    double m = lightness - c / 2;

    double r, g, b;
    if(hue < 60){
        r = c;
        g = x;
        b = 0;
    }else if(hue < 120){
        r = x;
        g = c;
        b = 0;
    }else if(hue < 180){
        r = 0;
        g = c;
        b = x;
    }else if(hue < 240){
        r = 0;
        g = x;
        b = c;
    }else if(hue < 300){
        r = x;
        g = 0;
        b = c;
    }else{
        r = c;
        g = 0;
        b = x;
    }

    this->r = (r + m) * 255;
    this->g = (g + m) * 255;
    this->b = (b + m) * 255;
}