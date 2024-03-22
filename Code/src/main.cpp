#include "ColorImage.h"
#include "ColorScheme.h"
#include "ColorSchemeConverter.h"
#include "HueSmother.h"
#include <iostream>


#include <gtkmm.h>
#include <gdkmm/pixbuf.h>

bool is_path_valid(const std::string& filename) {
    size_t pos = filename.find_last_of(".");
    if (pos != std::string::npos) {
        std::string extension = filename.substr(pos + 1);
        printf("extension = %s \n",extension);
        return extension == "png" || extension == "jpg" || extension == "jpeg";

    }
    printf("baka\n");
    return false;
}


void find_image(Gtk::Window& parent_window,std::string& image_path,Gtk::Image& ImageIn,Gtk::Entry &entry,char* &file_path) {
    Gtk::FileChooserDialog dialog("Veuillez choisir un fichier", Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog.set_transient_for(parent_window); // Définir la fenêtre parente
    
    // Ajouter un bouton pour confirmer la sélection
    dialog.add_button("_Ouvrir", Gtk::RESPONSE_OK);
    dialog.add_button("_Annuler", Gtk::RESPONSE_CANCEL);

    // Filtrer uniquement les fichiers d'image
    auto filter = Gtk::FileFilter::create();
    filter->set_name("Images");
    filter->add_mime_type("image/png");
    filter->add_mime_type("image/jpeg");
    filter->add_mime_type("image/gif");
    filter->add_mime_type("image/bmp");
    dialog.add_filter(filter);

    int result = dialog.run();

    // Vérifier si l'utilisateur a sélectionné un fichier
    if (result == Gtk::RESPONSE_OK) {
        std::cout << "Fichier sélectionné : " << dialog.get_filename() << std::endl;
        image_path = dialog.get_filename();
        printf("image path = %s\n",image_path.c_str());
        file_path = new char[image_path.length() + 1];
        

        if (is_path_valid(image_path)) {
            std::string command = "./src/resize_image.sh " + image_path;
            strcpy(file_path, image_path.c_str());
            printf("file_path= %s\n",file_path);

            entry.set_text(image_path);
            //printf("commande = %s\n",command.c_str());
            system(command.c_str());
            std::cout << image_path << " est un fichier valide" << std::endl;
            Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_file(image_path);
            ImageIn.set(pixbuf);
        } else {
            std::cout << image_path << " n'est pas un fichier valide" << std::endl;
        }
    }
}

void click_mono(Gtk::Window& parent_window,Gtk::Image& ImageIn,Gtk::Image& ImageOut,char*& file_path) {
    //printf("file path = %s\n",file_path);
    //ColorImage img(file_path);
    //ComplementaryColorScheme scheme(60);
    //ColorSchemeConverter::ConvertToColorScheme(img, scheme);
    //Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_data(img.getImage(), Gdk::COLORSPACE_RGB, false, 8, img.GetWidth(), img.GetHeight(), 3);
    //printf("width = %d height = %d\n",img.GetWidth(),img.GetHeight());
    // ImageOut.set(pixbuf);
    
    // Glib::RefPtr<Gdk::Pixbuf> pixbuf = ImageIn.get_pixbuf();
    // if (pixbuf) {
    //     // Affecter le pixbuf à ImageOut
    //     ImageOut.set(pixbuf);
    // }
}

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

    // AnalogousColorScheme scheme(hue1, hue2, 5);
    
    //HueSmother::SmoothHue(img, 10);
    //img.Write(outputFileName);


    // graphic application*
    char* file_path = "d";


    Gtk::Main kit(argc, argv);
    Gtk::Window window;
	window.set_title("a");
	window.set_default_size(800,800);

	// Création d'une boîte horizontale pour contenir le bouton
    Gtk::Grid grid;
    window.add(grid);


    // Créer un bouton pour ouvrir le dialogue de sélection de fichier
    Gtk::Button buttonImgIn("Ouvrir une image");
    Gtk::Button buttonTransformation("Appliquer les modifications");
    

    Gtk::Entry entry;
    std::string image_path=" ";
    Gtk::Image ImageIn;
    Gtk::Image ImageOut;
    buttonImgIn.signal_clicked().connect([&window,&image_path,&ImageIn,&entry,&file_path]() { find_image(window,image_path,ImageIn,entry,file_path); });
    
    //printf("width = %d height = %d\n",img.GetWidth(),img.GetHeight());





    Gtk::Button buttonMono("Monochrome");
    buttonMono.signal_clicked().connect([&window,&ImageIn,&ImageOut,&file_path]() { click_mono(window,ImageIn,ImageOut,file_path); });

    Gtk::Button buttonComp("Complémentaire");
    Gtk::Button buttonTria("Triadic");
    Gtk::Button buttonAna("Analogue");

     // Création d'un Gtk::SpinButton
    Gtk::SpinButton buttonHue1(Gtk::Adjustment::create(0.0, 0.0, 100.0, 1.0, 10.0, 0.0), 0.0, 0);
    Gtk::SpinButton buttonHue2(Gtk::Adjustment::create(0.0, 0.0, 100.0, 1.0, 10.0, 0.0), 0.0, 0);
    Gtk::SpinButton buttonHue3(Gtk::Adjustment::create(0.0, 0.0, 100.0, 1.0, 10.0, 0.0), 0.0, 0);
    buttonHue1.set_numeric(true); // Affiche uniquement des valeurs numériques
    buttonHue1.set_range(0, 359); // Définit la plage de valeurs possibles
    buttonHue2.set_numeric(true); // Affiche uniquement des valeurs numériques
    buttonHue2.set_range(0, 359); // Définit la plage de valeurs possibles
    buttonHue3.set_numeric(true); // Affiche uniquement des valeurs numériques
    buttonHue3.set_range(0, 359); // Définit la plage de valeurs possibles
    

    // Charger une image depuis un fichier dans un Gdk::Pixbuf

    // if(is_path_valid(image_path)){
    //     // Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_file(image_path);
    //     // Gtk::Image ImageIn(pixbuf);
    //     // grid.attach(ImageIn);
    //     printf("beurk\n"); 
    // }



    
    grid.set_column_spacing(10);
    grid.set_row_spacing(10);
    // grid.set_column_homogeneous(true);
    // //grid.attach(ImageIn);
    // Gtk::Label filler;
    // filler.set_size_request(100, -1); // Définir la largeur de la colonne sur 200 pixels
    // grid.attach(filler, 10, 0, 1, 1);

    grid.attach(buttonImgIn,0,0,1,1);
    grid.attach(entry,1,0,1,1);
    grid.attach(buttonMono,0,2,1,1); // Ajoute le bouton à gauche de la boîte
    grid.attach(buttonComp,1,2,1,1); // Ajoute le bouton à gauche de la boîte
    grid.attach(buttonTria,2,2,1,1); // Ajoute le bouton à gauche de la boîte
    grid.attach(buttonAna,3,2,1,1); // Ajoute le bouton à gauche de la boîte
    grid.attach(buttonHue1,0,3,1,1);
    grid.attach(buttonHue2,1,3,1,1);
    grid.attach(buttonHue3,2,3,1,1);
    grid.attach(ImageIn,4,4,1,1);
    grid.attach(ImageOut,4,5,1,1);
    
    // Ajout de la boîte à la fenêtre



	 // Affichage de la fenêtre
    window.show_all();


    kit.run(window);
    return 0;
}