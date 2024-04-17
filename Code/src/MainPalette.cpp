#include "MainPalette.h"

#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <string>

MainPalette::MainPalette() : mainBox(Gtk::ORIENTATION_VERTICAL), paletteSelection([&]() { UpdateColorScheme(); }), colorMapperSelection(), imageBox(Gtk::ORIENTATION_HORIZONTAL), saveBox(Gtk::ORIENTATION_HORIZONTAL) {
    set_title("Application Graphique Armonie de Couleur");
    set_default_size(1000, 680);

    mainBox.pack_start(fileSelectionBox, Gtk::PACK_SHRINK, 0);
    mainBox.pack_start(paletteSelection, Gtk::PACK_SHRINK, 0);
    mainBox.pack_start(colorMapperSelection, Gtk::PACK_SHRINK, 0);
    mainBox.pack_start(imageBox, Gtk::PACK_SHRINK, 0);
    mainBox.pack_start(saveBox, Gtk::PACK_SHRINK, 0);
    add(mainBox);

    Entry_Image_Out.set_text("Nom_de_l'image");

    std::cout << "MainPalette" << std::endl;

    Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_file("Images/white.png");
    Glib::RefPtr<Gdk::Pixbuf> pixbuf2 = Gdk::Pixbuf::create_from_file("Images/white.png");
    std::cout << "MainPalette2" << std::endl;
    ImageIn.set(pixbuf);
    ImageIn.set_margin_start(10);
    ImageIn.set_margin_end(5);

    ImageOut.set(pixbuf2);
    ImageOut.set_margin_start(5);
    ImageOut.set_margin_end(10);

    fileSelectionBox.pack_start(buttonImgIn, Gtk::PACK_SHRINK, 0);
    buttonImgIn.set_label("Open Image");
    fileSelectionBox.pack_start(entry, Gtk::PACK_SHRINK, 0);

    imageBox.pack_start(ImageIn, Gtk::PACK_SHRINK, 0);
    imageBox.pack_start(ImageOut, Gtk::PACK_SHRINK, 0);

    saveBox.pack_start(Entry_Image_Out, Gtk::PACK_SHRINK, 0);
    saveBox.pack_start(buttonSave, Gtk::PACK_SHRINK, 0);
    buttonSave.set_label("Save Image");

    buttonImgIn.signal_clicked().connect([&]() { LoadImage(); });
    buttonSave.signal_clicked().connect([&]() { SaveImage(); });

    show_all();
}

bool MainPalette::PathIsValid(const std::string& filename) {
    size_t pos = filename.find_last_of(".");
    if (pos != std::string::npos) {
        std::string extension = filename.substr(pos + 1);
        return extension == "png" || extension == "jpg" || extension == "jpeg";
    }
    return false;
}

void MainPalette::LoadImage() {
    std::cout << "LoadImage" << std::endl;
    Gtk::FileChooserDialog dialog("Veuillez choisir un fichier", Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog.set_transient_for(*this); // Définir la fenêtre parente

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
        if (PathIsValid(filename)) {
            std::string resize_command = "./src/resize_image.sh " + filename;
            system(resize_command.c_str());

            // Définir le chemin de l'image ppm convertie
            std::string ppm_filename = filename.substr(0, filename.find_last_of('/') + 1) + "tmp.ppm";
            image_path = ppm_filename;

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

void MainPalette::SaveImage() {
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

void MainPalette::UpdateColorScheme() {
    std::cout << "Image Path: " << image_path << std::endl;
    if (!image_path.empty()) {
        ColorImage img(image_path);
        std::shared_ptr<ColorMapper> mapper = colorMapperSelection.GetColorMapper();
        std::shared_ptr<ColorScheme> colorScheme = paletteSelection.GetColorScheme();

        mapper->SetColorScheme(colorScheme);
        mapper->SetImage(img);

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