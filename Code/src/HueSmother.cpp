#include "HueSmother.h"
#include <iostream>

void HueSmother::SmoothHue(ColorImage &image, int radius){
    ColorImage tempImage(image.GetWidth(), image.GetHeight());
    for(int x = 0; x < image.GetWidth(); x++){
        for(int y = 0; y < image.GetHeight(); y++){
            auto pixel = image.GetPixel(x, y).GetHSL();
            double newHue = GetAverageHue(image, x, y, radius);
            Color average = Color::FromHSL(newHue, pixel[1], pixel[2]);
            tempImage.SetPixel(x, y, average);
        }
    }
    image.Set(tempImage);
}

double HueSmother::GetAverageHue(const ColorImage &image, int x, int y, int radius){
    // Calculate the circular average of the hue of the pixels in the given radius around the given pixel
    double sumX = 0;
    double sumY = 0;
    for(int i = -radius; i <= radius; i++){
        for(int j = -radius; j <= radius; j++){
            int newX = x + i;
            int newY = y + j;
            if(image.IsInside(newX, newY)){
                auto pixel = image.GetPixel(newX, newY).GetHSL();
                double hueInRadians = pixel[0] * M_PI / 180.0;
                sumX += cos(hueInRadians);
                sumY += sin(hueInRadians);
            }
        }
    }
    double averageHueInRadians = atan2(sumY, sumX);
    double averageHueInDegrees = averageHueInRadians * 180.0 / M_PI;
    return averageHueInDegrees;
}