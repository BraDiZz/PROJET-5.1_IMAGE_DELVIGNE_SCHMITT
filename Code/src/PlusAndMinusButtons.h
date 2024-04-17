#pragma once
#include <gtkmm/box.h>
#include <gtkmm/button.h>

enum class PlusAndMinusButtonsType {
    Plus,
    Minus
};

class PlusAndMinusButtons : public Gtk::Box {
    Gtk::Button plusButton;
    Gtk::Button minusButton;

    using ButtonsClickedCallback = std::function<void(PlusAndMinusButtonsType)>;
    ButtonsClickedCallback callback;

public:
    PlusAndMinusButtons(ButtonsClickedCallback callback);
};