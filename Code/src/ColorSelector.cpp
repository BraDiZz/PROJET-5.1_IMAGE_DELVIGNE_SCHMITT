#include "ColorSelector.h"

ColorSelector::ColorSelector() {
    UpdateFrameColor();
    colorFrame.set_size_request(frameWidth, frameHeight);

    hueScale.set_range(0, 360);
    hueScale.set_size_request(frameWidth, 20);
    hueScale.set_draw_value(false);
    hueScale.signal_value_changed()
        .connect(sigc::mem_fun(*this, &ColorSelector::OnHueScaleValueChanged));

    UpdateHueLabel();
    colorFrame.add(hueLabel);

    attach(colorFrame, 0, 0, 1, 1);
    attach(hueScale, 0, 1, 1, 1);
}

void ColorSelector::SetHue(double hue) {
    this->hue = hue;
    UpdateHueScale();
    UpdateFrameColor();
    UpdateHueLabel();
}

void ColorSelector::OnHueScaleValueChanged() {
    hue = hueScale.get_value();
    UpdateFrameColor();
    UpdateHueLabel();
}

void ColorSelector::UpdateFrameColor() {
    Gdk::RGBA color;
    color.set_hsv(hue, 1, 1);
    colorFrame.override_background_color(color);
}

void ColorSelector::UpdateHueScale() {
    hueScale.set_value(hue);
}

void ColorSelector::UpdateHueLabel() {
    hueLabel.set_markup("<span font='20' weight='bold'>" + std::to_string(static_cast<int>(hue)) + "</span>");
}