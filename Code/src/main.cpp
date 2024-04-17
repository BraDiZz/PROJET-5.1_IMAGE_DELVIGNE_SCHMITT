#include "MainPalette.h"
#include <gtkmm/main.h>

int main(int argc, char* argv[]) {
    Gtk::Main kit(argc, argv);
    MainPalette palette;
    kit.run(palette);
    return 0;
}