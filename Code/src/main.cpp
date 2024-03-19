#include "ColorImage.h"
#include "ColorScheme.h"
#include "ColorSchemeConverter.h"
#include "HueSmother.h"
#include <gtkmm.h>

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
    // AnalogousColorScheme scheme(hue1, hue2, 5);
    ComplementaryColorScheme scheme(hue1);

    ColorSchemeConverter::ConvertToColorScheme(img, scheme);
    //HueSmother::SmoothHue(img, 10);
    img.Write(outputFileName);

    Gtk::Main kit(argc, argv);
    Gtk::Window window;
	window.set_title("a");
	window.set_default_size(1200,1200);

	// Création d'une boîte horizontale pour contenir le bouton
    Gtk::Box box(Gtk::ORIENTATION_HORIZONTAL, 10); // Espacement de 10 pixels entre les widgets
    box.set_margin_top(1000); // Espacement de 50 pixels à partir du haut de la fenêtre
	box.set_margin_right(1000); // Espacement de 50 pixels à partir du haut de la fenêtre

	

    // Création d'un bouton avec le label "Cliquez ici"
    Gtk::Button button("Cliquez ici");

    // Ajout du bouton à la boîte
    box.pack_start(button); // Ajoute le bouton à gauche de la boîte

    // Ajout de la boîte à la fenêtre
    window.add(box);


	 // Affichage de la fenêtre
    window.show_all();


    kit.run(window);
}