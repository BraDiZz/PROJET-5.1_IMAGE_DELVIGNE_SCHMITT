#include "ColorSelector.h"
#include <cmath>
#include <iostream>

ColorSelector::ColorSelector(ColorChangedCallback callback, HueDistanceChangedCallback hueDistanceChangedCallback) : saturationScale(Gtk::ORIENTATION_VERTICAL), colorChangedCallback(callback), hueDistanceChangedCallback(hueDistanceChangedCallback) {
    UpdateFrameColor();
    colorFrame.set_size_request(frameWidth, frameHeight);

    hueScale.set_range(0, 360);
    hueScale.set_size_request(frameWidth, 20);
    hueScale.set_draw_value(false);
    hueScale.signal_value_changed()
        .connect(sigc::mem_fun(*this, &ColorSelector::OnHueScaleValueChanged));

    saturationScale.set_range(0, 100);
    saturationScale.set_size_request(20, frameHeight);
    saturationScale.set_draw_value(false);
    saturationScale.set_inverted(true);
    saturationScale.set_value(100);
    saturationScale.signal_value_changed()
        .connect(sigc::mem_fun(*this, &ColorSelector::OnSaturationScaleValueChanged));

    UpdateHueLabel();
    colorFrame.add(hueLabel);

    attach(saturationScale, 0, 0, 1, 1);
    attach(colorFrame, 1, 0, 1, 1);
    attach(hueScale, 1, 1, 1, 1);

    show_all();
}

void ColorSelector::SetHue(double hue) {
    this->hue = fmod(hue, 360);
    if (this->hue < 0) {
        this->hue += 360;
    }
    UpdateHueScale();
    UpdateFrameColor();
    UpdateHueLabel();
}

void ColorSelector::SetSaturation(double saturation) {
    this->saturation = std::clamp(saturation, 0.0, 1.0);
    saturationScale.set_value(saturation * 100);
    UpdateFrameColor();
}

void ColorSelector::SetHueScaleMode(HueScaleMode hueScaleMode) {
    this->hueScaleMode = hueScaleMode;
    hueScale.set_visible(hueScaleMode != Disabled);
}

void ColorSelector::OnHueScaleValueChanged() {
    if (hueScaleMode == AbsoluteHue) {
        hue = hueScale.get_value();
        UpdateFrameColor();
        UpdateHueLabel();
        colorChangedCallback();
    } else if (hueScaleMode == HueDistance) {
        hueDistance = hueScale.get_value();
        hueDistanceChangedCallback();
    }
}

void ColorSelector::OnSaturationScaleValueChanged() {
    saturation = saturationScale.get_value() / 100.0;
    UpdateFrameColor();
    UpdateHueLabel();
    if (colorChangedCallback) {
        colorChangedCallback();
    }
}

void ColorSelector::UpdateFrameColor() {
    Gdk::RGBA color;
    color.set_hsv(hue, saturation, 1);
    colorFrame.override_background_color(color);
}

void ColorSelector::UpdateHueScale() {
    if (hueScaleMode == AbsoluteHue) {
        hueScale.set_value(hue);
    } else if (hueScaleMode == HueDistance) {
        hueScale.set_value(hueDistance);
    }
}

void ColorSelector::UpdateHueLabel() {
    std::string labelColor = GetLabelColor();
    hueLabel.set_markup("<span font='20' weight='bold' foreground='" + labelColor + "'>" + std::to_string(static_cast<int>(hue)) + "</span>");
}

std::string ColorSelector::GetLabelColor() {
    Gdk::RGBA color;
    color.set_hsl(hue, saturation, 0.2);

    int r = static_cast<int>(color.get_red_u() / 257);
    int g = static_cast<int>(color.get_green_u() / 257);
    int b = static_cast<int>(color.get_blue_u() / 257);

    char hex_color[9];
    sprintf(hex_color, "#%02X%02X%02X", r, g, b);

    return std::string(hex_color);
}