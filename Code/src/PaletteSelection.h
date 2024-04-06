#include "ColorSelector.h"
#include <gtkmm.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>

class PaletteSelection : public Gtk::Box {
    ColorSelector colorSelector1;
    Gtk::Separator separator;
    ColorSelector colorSelector2;

public:
    PaletteSelection();
};