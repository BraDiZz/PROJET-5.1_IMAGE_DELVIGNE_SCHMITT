#include "PaletteSelection.h"

PaletteSelection::PaletteSelection() {
    set_orientation(Gtk::ORIENTATION_HORIZONTAL);

    set_margin_start(10);  // Set margin on the start side
    set_margin_end(10);    // Set margin on the end side
    set_margin_top(10);    // Set margin on the top side
    set_margin_bottom(10); // Set margin on the bottom side

    separator.set_size_request(10, -1);

    colorSelector1.SetHue(100);

    pack_start(colorSelector1, Gtk::PACK_SHRINK, 0);
    pack_start(separator, Gtk::PACK_SHRINK, 0);
    pack_start(colorSelector2, Gtk::PACK_SHRINK, 0);
}