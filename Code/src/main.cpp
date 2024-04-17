#include "MainPalette.h"

#include "ColorImage.h"
#include "ColorMapper.h"
#include "ColorMapperSelection.h"
#include "ColorScheme.h"
#include "HueSmother.h"
#include "PaletteSelection.h"
#include <cstring>
#include <iostream>

#include <gdkmm/pixbuf.h>
#include <gtkmm.h>
#include <memory>

int main(int argc, char* argv[]) {
    Gtk::Main kit(argc, argv);
    MainPalette palette;
    kit.run(palette);
    return 0;
}