#pragma once
#include <functional>
#include <gtkmm/frame.h>
#include <gtkmm/grid.h>
#include <gtkmm/scale.h>
#include <gtkmm/spinbutton.h>

using ColorChangedCallback = std::function<void()>;
using HueDistanceChangedCallback = std::function<void()>;

enum HueScaleMode {
    AbsoluteHue, // Selecting a hue value for this color directly
    HueDistance, // Selecting a hue value relative to the previous color
    Disabled     // Hue scale is disabled
};

class ColorSelector : public Gtk::Grid {
    int frameWidth = 100;
    int frameHeight = 100;

    double hue = 0;
    double hueDistance = 10;
    double saturation = 1;

    Gtk::Frame colorFrame;
    Gtk::Scale hueScale;
    Gtk::Scale saturationScale;
    Gtk::Label hueLabel;

    HueScaleMode hueScaleMode = AbsoluteHue;

    ColorChangedCallback colorChangedCallback;
    HueDistanceChangedCallback hueDistanceChangedCallback;

public:
    ColorSelector(ColorChangedCallback colorChangedCallback, HueDistanceChangedCallback hueDistanceChangedCallback);
    void SetHue(double hue);
    double GetHue() const { return hue; }
    double GetHueDistance() const { return hueDistance; }
    void SetSaturation(double saturation);
    double GetSaturation() const { return saturation; }

    void SetHueScaleMode(HueScaleMode mode, int numberOfColorsinScheme = 0);

private:
    void OnHueScaleValueChanged();
    void OnSaturationScaleValueChanged();

    void UpdateFrameColor();
    void UpdateHueScale();
    void UpdateHueLabel();
    std::string GetLabelColor();
};