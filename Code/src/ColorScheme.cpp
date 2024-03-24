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