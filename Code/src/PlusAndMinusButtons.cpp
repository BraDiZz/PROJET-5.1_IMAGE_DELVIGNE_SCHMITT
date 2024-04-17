#include "PlusAndMinusButtons.h"

PlusAndMinusButtons::PlusAndMinusButtons(ButtonsClickedCallback callback) : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5), callback(callback) {
    plusButton.set_label("+");
    plusButton.signal_clicked().connect([this] { this->callback(PlusAndMinusButtonsType::Plus); });
    pack_start(plusButton, Gtk::PACK_SHRINK, 0);

    minusButton.set_label("-");
    minusButton.signal_clicked().connect([this] { this->callback(PlusAndMinusButtonsType::Minus); });
    pack_start(minusButton, Gtk::PACK_SHRINK, 0);
    show_all();

    set_margin_start(10);
    set_margin_bottom(30);
}