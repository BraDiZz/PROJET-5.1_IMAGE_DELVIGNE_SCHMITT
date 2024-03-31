#include "ColorImage.h"
#include "ColorMapper.h"
#include "ColorScheme.h"
#include "HueSmother.h"
#include <cstring>
#include <iostream>

#include <gdkmm/pixbuf.h>
#include <gtkmm.h>
#include <memory>

bool is_path_valid(const std::string &filename) {
    size_t pos = filename.find_last_of(".");
    if (pos != std::string::npos) {
        std::string extension = filename.substr(pos + 1);
        return extension == "png" || extension == "jpg" || extension == "jpeg";
    }
    return false;
}

void find_image(Gtk::Window &parent_window, char image_path[250], Gtk::Image &ImageIn, Gtk::Entry &entry) {
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

void click_scheme(Gtk::Window &parent_window, Gtk::Image &ImageOut, char image_path[250], Gtk::SpinButton &buttonHue1, Gtk::SpinButton &buttonDistance, Gtk::SpinButton &buttonNumberHues, ColorSchemeType schemeType, ColorMapperType mapperType) {
    if (buttonHue1.get_value() == -1)
        buttonHue1.set_value(360);
    if (buttonHue1.get_value() == 361)
        buttonHue1.set_value(0);
    ColorImage img(image_path);
    std::unique_ptr<ColorMapper> mapper;
    std::shared_ptr<ColorScheme> colorScheme;

    switch (schemeType) {
    case ColorSchemeType::Monochrome:
        colorScheme = std::make_shared<MonochromeColorScheme>(buttonHue1.get_value());
        break;
    case ColorSchemeType::Complementary:
        colorScheme = std::make_shared<ComplementaryColorScheme>(buttonHue1.get_value());
        break;
    case ColorSchemeType::Triadic:
        colorScheme = std::make_shared<TriadicColorScheme>(buttonHue1.get_value());
        break;
    case ColorSchemeType::Analogous:
        colorScheme = std::make_shared<AnalogousColorScheme>(buttonHue1.get_value(), buttonDistance.get_value(), buttonNumberHues.get_value());
        break;
    default:
        throw std::runtime_error("Invalid color scheme type");
    }

    switch (mapperType) {
    case ColorMapperType::Closest:
        mapper = std::make_unique<ClosestMapper>(colorScheme);
        break;
    case ColorMapperType::ClosestWithOffset:
        mapper = std::make_unique<ClosestMapperWithOffset>(colorScheme, buttonDistance.get_value());
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

void click_mono(Gtk::Window &parent_window, ColorSchemeType &Scheme_mode, Gtk::Grid &grid, Gtk::SpinButton &buttonHue1) {
    Scheme_mode = ColorSchemeType::Monochrome;
    Gtk::Widget *widget_to_keep = grid.get_child_at(0, 3);
    if (!widget_to_keep) {
        grid.attach(buttonHue1, 0, 3, 1, 1);
    }
    Gtk::Widget *widget_to_remove = grid.get_child_at(2, 3);
    Gtk::Widget *widget_to_remove2 = grid.get_child_at(4, 3);
    if (widget_to_remove) {
        grid.remove(*widget_to_remove);
        grid.remove(*widget_to_remove2);
    }
    parent_window.show_all();
}

void click_comp(Gtk::Window &parent_window, ColorSchemeType &Scheme_mode, Gtk::Grid &grid, Gtk::SpinButton &buttonHue1) {
    Scheme_mode = ColorSchemeType::Complementary;
    Gtk::Widget *widget_to_keep = grid.get_child_at(0, 3);
    if (!widget_to_keep) {
        grid.attach(buttonHue1, 0, 3, 1, 1);
    }
    Gtk::Widget *widget_to_remove = grid.get_child_at(2, 3);
    Gtk::Widget *widget_to_remove2 = grid.get_child_at(4, 3);
    if (widget_to_remove) {
        grid.remove(*widget_to_remove);
        grid.remove(*widget_to_remove2);
    }
    parent_window.show_all();
}

void click_triadic(Gtk::Window &parent_window, ColorSchemeType &Scheme_mode, Gtk::Grid &grid, Gtk::SpinButton &buttonHue1) {
    Scheme_mode = ColorSchemeType::Triadic;
    Gtk::Widget *widget_to_keep = grid.get_child_at(0, 3);
    if (!widget_to_keep) {
        grid.attach(buttonHue1, 0, 3, 1, 1);
    }
    Gtk::Widget *widget_to_remove = grid.get_child_at(2, 3);
    Gtk::Widget *widget_to_remove2 = grid.get_child_at(4, 3);
    if (widget_to_remove) {
        grid.remove(*widget_to_remove);
        grid.remove(*widget_to_remove2);
    }
    parent_window.show_all();
}
void click_Analogus(Gtk::Window &parent_window, ColorSchemeType &Scheme_mode, Gtk::Grid &grid, Gtk::SpinButton &buttonHue1, Gtk::SpinButton &buttonDistance, Gtk::SpinButton &buttonNumberHues) {
    Scheme_mode = ColorSchemeType::Analogous;
    Gtk::Widget *widget_to_keep = grid.get_child_at(0, 3);
    Gtk::Widget *widget_to_keep2 = grid.get_child_at(2, 3);
    Gtk::Widget *widget_to_keep3 = grid.get_child_at(4, 3);
    if (!widget_to_keep) {
        grid.attach(buttonHue1, 0, 3, 1, 1);
    }
    if (!widget_to_keep2) {
        grid.attach(buttonDistance, 2, 3, 1, 1);
    }
    if (!widget_to_keep3) {
        grid.attach(buttonNumberHues, 4, 3, 1, 1);
    }
    parent_window.show_all();
}

void click_save(Gtk::Window &parent_window, char image_path[250], Gtk::Entry &Entry_Image_Out) {
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

int main(int argc, char *argv[]) {
    ColorSchemeType schemeMode;

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
    char image_path[250];
    Gtk::Image ImageIn;
    Gtk::Image ImageOut;

    Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_file("Images/white.png");
    ImageIn.set(pixbuf);

    Glib::RefPtr<Gdk::Pixbuf> pixbuf2 = Gdk::Pixbuf::create_from_file("Images/white.png");
    ImageOut.set(pixbuf2);

    buttonImgIn.signal_clicked().connect([&window, &ImageOut, &image_path, &ImageIn, &entry]() { find_image(window, image_path, ImageIn, entry); });

    Gtk::SpinButton buttonHue1(Gtk::Adjustment::create(0.0, 0.0, 100.0, 1.0, 10.0, 0.0), 0.0, 0);
    Gtk::SpinButton buttonDistance(Gtk::Adjustment::create(0.0, 0.0, 100.0, 1.0, 10.0, 0.0), 0.0, 0);
    Gtk::SpinButton buttonNumberHues(Gtk::Adjustment::create(0.0, 0.0, 100.0, 1.0, 10.0, 0.0), 0.0, 0);
    buttonHue1.set_numeric(true);
    buttonHue1.set_range(-1, 361);
    buttonHue1.set_value(0);
    buttonDistance.set_numeric(true);
    buttonDistance.set_range(1, 15);
    buttonNumberHues.set_numeric(true);
    buttonNumberHues.set_range(1, 15);

    buttonHue1.signal_value_changed().connect([&window, &ImageOut, &image_path, &buttonHue1, &buttonDistance, &buttonNumberHues, &schemeMode]() {
        click_scheme(window, ImageOut, image_path, buttonHue1, buttonDistance, buttonNumberHues, schemeMode, ColorMapperType::Closest);
    });
    buttonDistance.signal_value_changed().connect([&window, &ImageOut, &image_path, &buttonHue1, &buttonDistance, &buttonNumberHues, &schemeMode]() {
        click_scheme(window, ImageOut, image_path, buttonHue1, buttonDistance, buttonNumberHues, schemeMode, ColorMapperType::Closest);
    });
    buttonNumberHues.signal_value_changed().connect([&window, &ImageOut, &image_path, &buttonHue1, &buttonDistance, &buttonNumberHues, &schemeMode]() {
        click_scheme(window, ImageOut, image_path, buttonHue1, buttonDistance, buttonNumberHues, schemeMode, ColorMapperType::Closest);
    });

    Gtk::Button buttonMono("Monochrome");
    buttonMono.signal_clicked().connect([&window, &schemeMode, &grid, &buttonHue1]() { click_mono(window, schemeMode, grid, buttonHue1); });
    buttonMono.signal_clicked().connect([&window, &ImageOut, &image_path, &buttonHue1, &buttonDistance, &buttonNumberHues, &schemeMode]() { click_scheme(window, ImageOut, image_path, buttonHue1, buttonDistance, buttonNumberHues, schemeMode, ColorMapperType::Closest); });

    Gtk::Button buttonComp("Complémentaire");
    buttonComp.signal_clicked().connect([&window, &schemeMode, &grid, &buttonHue1]() { click_comp(window, schemeMode, grid, buttonHue1); });
    buttonComp.signal_clicked().connect([&window, &ImageOut, &image_path, &buttonHue1, &buttonDistance, &buttonNumberHues, &schemeMode]() { click_scheme(window, ImageOut, image_path, buttonHue1, buttonDistance, buttonNumberHues, schemeMode, ColorMapperType::Closest); });

    Gtk::Button buttonTria("Triadic");
    buttonTria.signal_clicked().connect([&window, &schemeMode, &grid, &buttonHue1]() { click_triadic(window, schemeMode, grid, buttonHue1); });
    buttonTria.signal_clicked().connect([&window, &ImageOut, &image_path, &buttonHue1, &buttonDistance, &buttonNumberHues, &schemeMode]() { click_scheme(window, ImageOut, image_path, buttonHue1, buttonDistance, buttonNumberHues, schemeMode, ColorMapperType::Closest); });

    Gtk::Button buttonAna("Analogue");
    buttonAna.signal_clicked().connect([&window, &schemeMode, &grid, &buttonHue1, &buttonDistance, &buttonNumberHues]() { click_Analogus(window, schemeMode, grid, buttonHue1, buttonDistance, buttonNumberHues); });
    buttonAna.signal_clicked().connect([&window, &ImageOut, &image_path, &buttonHue1, &buttonDistance, &buttonNumberHues, &schemeMode]() { click_scheme(window, ImageOut, image_path, buttonHue1, buttonDistance, buttonNumberHues, schemeMode, ColorMapperType::Closest); });

    Gtk::Button buttonSave("Sauvegarder l'image");
    buttonSave.signal_clicked().connect([&window, &image_path, &Entry_Image_Out]() { click_save(window, image_path, Entry_Image_Out); });

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
    grid.attach(buttonMono, 0, 2, 1, 1);
    grid.attach(buttonComp, 1, 2, 2, 1);
    grid.attach(buttonTria, 3, 2, 2, 1);
    grid.attach(buttonAna, 5, 2, 2, 1);
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