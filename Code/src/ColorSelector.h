#pragma once
#include <functional>
#include <gtkmm/frame.h>
#include <gtkmm/grid.h>
#include <gtkmm/scale.h>
#include <gtkmm/spinbutton.h>

using ColorChangedCallback = std::function<void()>;

class ColorSelector : public Gtk::Grid {
    int frameWidth = 100;
    int frameHeight = 100;

    double hue = 0;
    double saturation = 1;

    Gtk::Frame colorFrame;
    Gtk::Scale hueScale;
    Gtk::Scale saturationScale;
    Gtk::Label hueLabel;

    bool showHueScale = true;

    ColorChangedCallback colorChangedCallback;

public:
    ColorSelector(ColorChangedCallback colorChangedCallback = nullptr);
    void SetHue(double hue);
    double GetHue() const { return hue; }
    void SetSaturation(double saturation);
    double GetSaturation() const { return saturation; }

    void SetShowHueScale(bool showHueScale);

private:
    void OnHueScaleValueChanged();
    void OnSaturationScaleValueChanged();

    void UpdateFrameColor();
    void UpdateHueScale();
    void UpdateHueLabel();
    std::string GetLabelColor();
};