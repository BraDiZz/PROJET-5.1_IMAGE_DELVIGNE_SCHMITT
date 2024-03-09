#include "ColorImage.h"
#include "ColorScheme.h"
#include "ColorSchemeConverter.h"

int main(int argc, char* argv[]){
    char inputFileName[250], outputFileName[250];
    double hue;
      
    if (argc != 4){
        printf("Usage: ImageIn.ppm ImageOut.pgm hue\n"); 
        exit (1) ;
    }
      
    sscanf (argv[1],"%s",inputFileName) ;
    sscanf (argv[2],"%s",outputFileName);
    sscanf (argv[3],"%lf",&hue);

    ColorImage img(inputFileName);
    ColorScheme scheme({hue});

    ColorSchemeConverter::ConvertToColorScheme(img, scheme);
    img.Write(outputFileName);
}