#include "ColorImage.h"
#include "ColorScheme.h"
#include "ColorSchemeConverter.h"

int main(int argc, char* argv[]){
    char inputFileName[250], outputFileName[250];
    double hue1, hue2;
      
    if (argc != 5){
        printf("Usage: ImageIn.ppm ImageOut.pgm hue1 hue2\n"); 
        exit (1) ;
    }
      
    sscanf (argv[1],"%s",inputFileName) ;
    sscanf (argv[2],"%s",outputFileName);
    sscanf (argv[3],"%lf",&hue1);
    sscanf (argv[4],"%lf",&hue2);

    ColorImage img(inputFileName);
    ColorScheme scheme({hue1, hue2});

    ColorSchemeConverter::ConvertToColorScheme(img, scheme);
    img.Write(outputFileName);
}