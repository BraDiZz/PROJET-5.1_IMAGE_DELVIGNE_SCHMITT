#include "ColorImage.h"
#include <stdexcept>

ColorImage::ColorImage(char *filename){
    lire_nb_lignes_colonnes_image_ppm(filename, &height, &width);
    int size = width * height * 3;
    allocation_tableau(image, OCTET, size);
    lire_image_ppm(filename, image, width * height);
}

ColorImage::ColorImage(int width, int height) : width(width), height(height){
    int size = width * height * 3;
    allocation_tableau(image, OCTET, size);
}

ColorImage::~ColorImage(){
    free(image);
}

void ColorImage::Write(char *filename){
    ecrire_image_ppm(filename, image, height, width);
}

void ColorImage::SetPixel(int x, int y, Color color){
    if(!IsInside(x, y)){
        std::string message = "Can not set pixel. Pixel does not lie inside the image. x = " + std::to_string(x) + ", y = " + std::to_string(y);
        throw std::runtime_error(message);
    }
    int i = GetIndexInArray(x, y);
    image[i] = color.r;
    image[i + 1] = color.g;
    image[i + 2] = color.b;
}

Color ColorImage::GetPixel(int x, int y) const{
    if(!IsInside(x, y)){
        std::string message = "Can not get pixel. Pixel does not lie inside the image. x = " + std::to_string(x) + ", y = " + std::to_string(y);
        throw std::runtime_error(message);
    }
    int i = GetIndexInArray(x, y);
    return {image[i], image[i + 1], image[i + 2]};
}

int ColorImage::GetIndexInArray(int x, int y) const{
    return y * width * 3 + x * 3;
}

bool ColorImage::IsInside(int x, int y) const{
    return x >= 0 && x < width && y >= 0 && y < height;
}

void ColorImage::Set(const ColorImage &other){
    if(width != other.width || height != other.height){
        std::string message = "Can not set image. Image dimensions do not match. This image: " + std::to_string(width) + "x" + std::to_string(height) + ", other image: " + std::to_string(other.width) + "x" + std::to_string(other.height);
        throw std::runtime_error(message);
    }
    for(int i = 0; i < width * height * 3; i++){
        image[i] = other.image[i];
    }
}

int ColorImage::GetWidth(){
    return width;
}

int ColorImage::GetHeight(){
    return height;
}
