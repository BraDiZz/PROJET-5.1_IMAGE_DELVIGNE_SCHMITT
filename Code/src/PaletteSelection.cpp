#include "PaletteSelection.h"

PaletteSelection::PaletteSelection() {
    set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    label.set_text("This is a subsection");
    button.set_label("Click me!");

    pack_start(label, Gtk::PACK_SHRINK, 0);
    pack_start(button, Gtk::PACK_SHRINK, 0);
}