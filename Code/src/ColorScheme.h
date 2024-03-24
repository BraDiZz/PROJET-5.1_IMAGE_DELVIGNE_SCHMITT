#pragma once
#include "Color.h"
#include <vector>
#include <iostream>

struct ColorScheme{
protected:
    std::vector<double> hues;

public:
    ColorScheme(std::vector<double> hues);
    const std::vector<double>& GetHues() const { return hues; }
    int GetNumberOfHues() const { return hues.size(); }
};

struct MonochromeColorScheme : public ColorScheme{
public:
    MonochromeColorScheme(double hue): ColorScheme({hue}){}
};

struct ComplementaryColorScheme : public ColorScheme{
public:
    ComplementaryColorScheme(double hue): ColorScheme({hue, hue + 180}){}
};

struct AnalogousColorScheme : public ColorScheme{
public:
    AnalogousColorScheme(double hue, double colorDistance, unsigned int numberOfHues): ColorScheme({hue}){
        for(unsigned int i = 1; i < (numberOfHues - 1) / 2; i++){
            this->hues.push_back(hue + i * colorDistance);
            this->hues.push_back(hue - i * colorDistance);
        }
    }
};

struct TriadicColorScheme : public ColorScheme{
public:
    TriadicColorScheme(double hue): ColorScheme({hue, hue + 120, hue + 240}){}
};