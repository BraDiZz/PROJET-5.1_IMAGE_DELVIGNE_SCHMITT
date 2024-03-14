#pragma once
#include "Color.h"
#include <vector>

class ColorScheme{
protected:
    std::vector<double> hues;

public:
    ColorScheme(std::vector<double> hues);
    Color GetClostesColorInScheme(const Color& color) const;

private:
    double GetClosestHue(double hue) const;
};

class MonochromeColorScheme : public ColorScheme{
public:
    MonochromeColorScheme(double hue): ColorScheme({hue}){}
};

class ComplementaryColorScheme : public ColorScheme{
public:
    ComplementaryColorScheme(double hue): ColorScheme({hue, hue + 180}){}
};

class AnalogousColorScheme : public ColorScheme{
public:
    AnalogousColorScheme(double hue, double colorDistance, unsigned int numberOfHues): ColorScheme({hue}){
        for(unsigned int i = 1; i < (numberOfHues - 1) / 2; i++){
            this->hues.push_back(hue + i * colorDistance);
            this->hues.push_back(hue - i * colorDistance);
        }
    }
};

class TriadicColorScheme : public ColorScheme{
public:
    TriadicColorScheme(double hue): ColorScheme({hue, hue + 120, hue + 240}){}
};