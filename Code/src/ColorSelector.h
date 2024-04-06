#pragma once
#include <gtkmm/frame.h>
#include <gtkmm/grid.h>
#include <gtkmm/scale.h>
#include <gtkmm/spinbutton.h>

class ColorSelector : public Gtk::Grid {
    int frameWidth = 100;
    int frameHeight = 100;

    double hue = 0;

    Gtk::Frame colorFrame;
    Gtk::Scale hueScale;

public:
    ColorSelector();

private:
    void OnHueScaleValueChanged();

    void UpdateFrameColor();
    void UpdateHueScale();
};