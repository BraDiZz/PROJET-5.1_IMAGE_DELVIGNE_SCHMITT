#include <gtkmm.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>

class PaletteSelection : public Gtk::Box {
    Gtk::Label label;
    Gtk::Button button;

public:
    PaletteSelection();
};