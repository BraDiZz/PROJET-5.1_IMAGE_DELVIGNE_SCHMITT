#include "ColorImage.h"
#include "ColorMapper.h"
#include "ColorScheme.h"
#include "HueSmother.h"
#include "PaletteSelection.h"
#include <cstring>
#include <iostream>

#include <gdkmm/pixbuf.h>
#include <gtkmm.h>
#include <memory>

bool is_path_valid(const std::string& filename) {
    size_t pos = filename.find_last_of(".");
    if (pos != std::string::npos) {
        std::string extension = filename.substr(pos + 1);
        return extension == "png" || extension == "jpg" || extension == "jpeg";
    }
    return false;
}

void find_image(Gtk::Window& parent_window, char image_path[250], Gtk::Image& ImageIn, Gtk::Entry& entry) {
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
    filter->add_mime_type("image/jpg");
    dialog.add_filter(filter);

    int result = dialog.run();

    // Vérifier si l'utilisateur a sélectionné un fichier
    if (result == Gtk::RESPONSE_OK) {
        std::string filename = dialog.get_filename();
        if (is_path_valid(filename)) {
            std::string resize_command = "./src/resize_image.sh " + filename;
            system(resize_command.c_str());

            // Définir le chemin de l'image ppm convertie
            std::string ppm_filename = filename.substr(0, filename.find_last_of('/') + 1) + "tmp.ppm";
            strcpy(image_path, ppm_filename.c_str());

            // Appeler le script "toppm.sh" pour convertir l'image en ppm
            std::string ppm_command = "./src/toppm.sh " + filename + " " + image_path;
            system(ppm_command.c_str());

            entry.set_text(ppm_filename);
            Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_file(ppm_filename);
            ImageIn.set(pixbuf);
        } else {
            std::cout << filename << " n'est pas un fichier valide" << std::endl;
        }
    }
}

void OnColorSchemeChanged(Gtk::Window& parent_window, Gtk::Image& ImageOut, char image_path[250], ColorMapperType mapperType, const PaletteSelection& paletteSelection) {
    if (strcmp(image_path, "") != 0) {
        ColorImage img(image_path);
        std::unique_ptr<ColorMapper> mapper;
        std::shared_ptr<ColorScheme> colorScheme = paletteSelection.GetColorScheme();

        switch (mapperType) {
        case ColorMapperType::Closest:
            mapper = std::make_unique<ClosestMapper>(colorScheme);
            break;
        case ColorMapperType::ClosestWithOffset:
            mapper = std::make_unique<ClosestMapperWithOffset>(colorScheme, 90);
            break;
        case ColorMapperType::Histogram:
            mapper = std::make_unique<HistogramMapper>(colorScheme, img);
            break;
        default:
            throw std::runtime_error("Invalid mapper type");
        }

        mapper->ConvertToColorScheme(img);

        std::string str_image_path = std::string(image_path);
        size_t last_slash = str_image_path.find_last_of("/");
        std::string path_prefix = str_image_path.substr(0, last_slash);
        last_slash = path_prefix.find_last_of("/");
        std::string final_path_prefix = path_prefix.substr(0, last_slash + 1);
        final_path_prefix += "ImagesOut/tmp.ppm";
        char newPath[250];

        std::strcpy(newPath, final_path_prefix.c_str());
        img.Write(newPath);
        Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_file(newPath);
        ImageOut.set(pixbuf);
    }
}

void click_save(Gtk::Window& parent_window, char image_path[250], Gtk::Entry& Entry_Image_Out) {
    if (Entry_Image_Out.get_text() != "") {
        // écrit l'image tmp.ppm dans image, qui est l'image temporaire modifié
        char newPath[250];
        std::string str_image_path = std::string(image_path);
        size_t last_slash = str_image_path.find_last_of("/");
        std::string path_prefix = str_image_path.substr(0, last_slash);
        last_slash = path_prefix.find_last_of("/");
        std::string final_path_prefix = path_prefix.substr(0, last_slash + 1);
        final_path_prefix += "ImagesOut/tmp.ppm";
        std::strcpy(newPath, final_path_prefix.c_str());
        ColorImage img(newPath);

        // ecrit l'image modifié avec le nom choisi pour la sauvegarder
        str_image_path = std::string(image_path);
        last_slash = str_image_path.find_last_of("/");
        path_prefix = str_image_path.substr(0, last_slash);
        last_slash = path_prefix.find_last_of("/");
        final_path_prefix = path_prefix.substr(0, last_slash + 1);
        final_path_prefix += "ImagesOut/" + Entry_Image_Out.get_text() + ".ppm";
        std::strcpy(newPath, final_path_prefix.c_str());
        img.Write(newPath);
    }
}

int main(int argc, char* argv[]) {
    Gtk::Main kit(argc, argv);
    Gtk::Window window;
    window.set_title("Application Graphique Armonie de Couleur");
    window.set_default_size(1000, 680);

    // Création d'une boîte horizontale pour contenir le bouton
    Gtk::Grid grid;
    window.add(grid);

    // Créer un bouton pour ouvrir le dialogue de sélection de fichier
    Gtk::Button buttonImgIn("Ouvrir une image");
    Gtk::Button buttonTransformation("Appliquer les modifications");

    Gtk::Entry entry;
    Gtk::Entry Entry_Image_Out;
    Entry_Image_Out.set_text("Nom_de_l'image");
    char image_path[250] = "";
    Gtk::Image ImageIn;
    Gtk::Image ImageOut;

    Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_file("Images/white.png");
    ImageIn.set(pixbuf);

    Glib::RefPtr<Gdk::Pixbuf> pixbuf2 = Gdk::Pixbuf::create_from_file("Images/white.png");
    ImageOut.set(pixbuf2);

    buttonImgIn.signal_clicked().connect([&window, &ImageOut, &image_path, &ImageIn, &entry]() { find_image(window, image_path, ImageIn, entry); });

    Gtk::Button buttonSave("Sauvegarder l'image");
    buttonSave.signal_clicked().connect([&window, &image_path, &Entry_Image_Out]() { click_save(window, image_path, Entry_Image_Out); });
    PaletteSelection paletteSelection([&]() {
        OnColorSchemeChanged(window, ImageOut, image_path, ColorMapperType::Closest, paletteSelection);
    });

    // Gtk::Button buttonScheme("Appliquer schéma");
    // buttonScheme.signal_clicked().connect([&window,& ImageOut,&image_path,& buttonHue1,&Scheme_mode]() { click_scheme(window,ImageOut,image_path,buttonHue1,Scheme_mode); });

    grid.set_column_spacing(10);
    grid.set_row_spacing(10);
    // grid.set_column_homogeneous(true);
    // //grid.attach(ImageIn);
    // Gtk::Label filler;
    // filler.set_size_request(100, -1); // Définir la largeur de la colonne sur 200 pixels
    // grid.attach(filler, 10, 0, 1, 1);

    grid.attach(buttonImgIn, 0, 0, 1, 1);
    grid.attach(entry, 1, 0, 9, 1);
    grid.attach(paletteSelection, 0, 2, 10, 1);
    grid.attach(Entry_Image_Out, 1, 5, 2, 1);
    // grid.attach(buttonScheme,0,5,1,1);
    grid.attach(buttonSave, 0, 5, 1, 1);

    grid.attach(ImageIn, 0, 4, 5, 1);
    grid.attach(ImageOut, 5, 4, 5, 1);

    // Ajout de la boîte à la fenêtre

    // Affichage de la fenêtre
    window.show_all();

    kit.run(window);
    return 0;
}