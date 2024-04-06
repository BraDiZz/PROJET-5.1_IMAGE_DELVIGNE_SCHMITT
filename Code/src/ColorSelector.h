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
    Gtk::Label hueLabel;

public:
    ColorSelector();
    void SetHue(double hue);

private:
    void OnHueScaleValueChanged();

    void UpdateFrameColor();
    void UpdateHueScale();
    void UpdateHueLabel();
};