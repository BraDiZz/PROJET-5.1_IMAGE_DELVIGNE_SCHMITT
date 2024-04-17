#pragma once
#include <functional>
#include <gtkmm/eventbox.h>
#include <gtkmm/grid.h>
#include <gtkmm/scale.h>
#include <gtkmm/spinbutton.h>
#include <iostream>

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

    Gtk::EventBox colorFrame;
    Gtk::Scale hueScale;
    Gtk::Scale saturationScale;
    Gtk::Label hueLabel;

    HueScaleMode hueScaleMode = AbsoluteHue;

    ColorChangedCallback colorChangedCallback = nullptr;
    HueDistanceChangedCallback hueDistanceChangedCallback = nullptr;

public:
    ColorSelector(double hue, double saturation);

    void SetHue(double hue);
    double GetHue() const { return hue; }
    double GetHueDistance() const { return hueDistance; }
    void SetSaturation(double saturation);
    double GetSaturation() const { return saturation; }

    void SetHueScaleMode(HueScaleMode mode, int numberOfColorsinScheme = 0);

    void SetCallbacks(const ColorChangedCallback& colorChangedCallback, const HueDistanceChangedCallback& hueDistanceChangedCallback);

private:
    void OnHueScaleValueChanged();
    void OnSaturationScaleValueChanged();

    void UpdateFrameColor();
    void UpdateHueScale();
    void UpdateHueLabel();
    std::string GetLabelColor();

    void UpdateScaleColor();
    void UpdateHueScaleColor();
    void UpdateSaturationScaleColor();

    std::ostringstream GetCssColorStream(double colorHue, double colorSaturation, double colorValue);
};