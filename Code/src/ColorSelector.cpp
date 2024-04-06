#include "ColorSelector.h"

ColorSelector::ColorSelector() {
    UpdateFrameColor();
    colorFrame.set_size_request(frameWidth, frameHeight);

    hueScale.set_range(0, 360);
    hueScale.set_size_request(frameWidth, 20);
    hueScale.signal_value_changed().connect(sigc::mem_fun(*this, &ColorSelector::OnHueScaleValueChanged));

    attach(colorFrame, 0, 0, 1, 1);
    attach(hueScale, 0, 1, 1, 1);
}

void ColorSelector::OnHueScaleValueChanged() {
    hue = hueScale.get_value();
    UpdateFrameColor();
}

void ColorSelector::UpdateFrameColor() {
    Gdk::RGBA color;
    color.set_hsv(hue, 1, 1);
    colorFrame.override_background_color(color);
}

void ColorSelector::UpdateHueScale() {
    hueScale.set_value(hue);
}