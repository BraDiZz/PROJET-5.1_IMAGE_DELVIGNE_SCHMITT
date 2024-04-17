#pragma once
#include <gtkmm.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/image.h>
#include <gtkmm/window.h>

#include "ColorMapperSelection.h"
#include "PaletteSelection.h"

class MainPalette : public Gtk::Window {
    Gtk::Box mainBox;
    Gtk::Box fileSelectionBox;
    PaletteSelection paletteSelection;
    ColorMapperSelection colorMapperSelection;
    Gtk::Box imageBox;
    Gtk::Box saveBox;

    // Créer un bouton pour ouvrir le dialogue de sélection de fichier
    Gtk::Image iconImage;
    Gtk::Button buttonImgIn;
    Gtk::Entry entry;
    std::string image_path;

    Gtk::Image ImageIn;
    Gtk::Image ImageOut;

    Gtk::Button buttonSave;
    Gtk::Entry Entry_Image_Out;

public:
    MainPalette();

private:
    bool PathIsValid(const std::string& filename);
    void LoadImage();

    void SaveImage();

    void UpdateColorScheme();
};