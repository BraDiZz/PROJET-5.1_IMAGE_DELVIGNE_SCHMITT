#include "ColorSelector.h"
#include <cmath>
#include <gtkmm/cssprovider.h>

ColorSelector::ColorSelector(double hue, double saturation) : saturationScale(Gtk::ORIENTATION_VERTICAL) {
    UpdateFrameColor();
    colorFrame.set_size_request(frameWidth, frameHeight);
    Glib::RefPtr<Gtk::CssProvider> cssProvider = Gtk::CssProvider::create();
    cssProvider->load_from_data("* { border-radius: 10px;}");
    colorFrame.get_style_context()->add_provider(cssProvider, GTK_STYLE_PROVIDER_PRIORITY_USER);

    hueScale.set_range(0, 360);
    hueScale.set_size_request(frameWidth, 20);
    hueScale.set_draw_value(false);
    SetHue(hue);

    saturationScale.set_range(0, 100);
    saturationScale.set_size_request(20, frameHeight);
    saturationScale.set_draw_value(false);
    saturationScale.set_inverted(true);
    saturationScale.set_value(100);
    SetSaturation(saturation);

    UpdateScaleColor();

    UpdateHueLabel();
    colorFrame.add(hueLabel);

    attach(saturationScale, 0, 0, 1, 1);
    attach(colorFrame, 1, 0, 1, 1);
    attach(hueScale, 1, 1, 1, 1);

    show_all();
}

void ColorSelector::SetHue(double hue) {
    double newHue = fmod(hue, 360);
    if (newHue < 0) {
        newHue += 360;
    }
    if (newHue != this->hue) {
        this->hue = newHue;
        UpdateHueScale();
        UpdateFrameColor();
        UpdateHueLabel();
        UpdateScaleColor();
    }
}

void ColorSelector::SetSaturation(double saturation) {
    double newSaturation = std::clamp(saturation, 0.0, 1.0);

    if (this->saturation != newSaturation) {
        this->saturation = newSaturation;
        saturationScale.set_value(saturation * 100);
        UpdateFrameColor();
        UpdateScaleColor();
    }
}

void ColorSelector::SetHueScaleMode(HueScaleMode hueScaleMode, int numberOfColors) {
    this->hueScaleMode = hueScaleMode;
    hueScale.set_visible(hueScaleMode != Disabled);
    UpdateHueScale();
    UpdateHueScaleColor();
    if (hueScaleMode == HueDistance) {
        hueScale.set_range(1, 360 / numberOfColors);
    } else {
        hueScale.set_range(0, 360);
    }
}

void ColorSelector::SetCallbacks(const ColorChangedCallback& colorChangedCallback, const HueDistanceChangedCallback& hueDistanceChangedCallback) {
    this->colorChangedCallback = colorChangedCallback;
    this->hueDistanceChangedCallback = hueDistanceChangedCallback;

    hueScale.signal_value_changed()
        .connect(sigc::mem_fun(*this, &ColorSelector::OnHueScaleValueChanged));
    saturationScale.signal_value_changed()
        .connect(sigc::mem_fun(*this, &ColorSelector::OnSaturationScaleValueChanged));
}

void ColorSelector::OnHueScaleValueChanged() {
    if (hueScaleMode == AbsoluteHue) {
        hue = hueScale.get_value();
        UpdateFrameColor();
        UpdateHueLabel();
        UpdateScaleColor();
        if (!colorChangedCallback) {
            std::cout << "colorChangedCallback is null in OnHueScaleValueChanged" << std::endl;
            return;
        }
        colorChangedCallback();
    } else if (hueScaleMode == HueDistance) {
        hueDistance = hueScale.get_value();
        if (!hueDistanceChangedCallback) {
            std::cout << "hueDistanceChangedCallback is null in OnHueScaleValueChanged" << std::endl;
            return;
        }
        hueDistanceChangedCallback();
    }
}

void ColorSelector::OnSaturationScaleValueChanged() {
    saturation = saturationScale.get_value() / 100.0;
    UpdateFrameColor();
    UpdateHueLabel();
    UpdateScaleColor();
    if (!colorChangedCallback) {
        std::cout << "colorChangedCallback is null in OnSaturationScaleValueChanged" << std::endl;
        return;
    }
    colorChangedCallback();
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
    hueLabel.set_markup("<span font='25' weight='bold' foreground='" + labelColor + "'>" + std::to_string(static_cast<int>(hue)) + "</span>");
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

void ColorSelector::UpdateScaleColor() {
    UpdateHueScaleColor();
    UpdateSaturationScaleColor();
}

void ColorSelector::UpdateHueScaleColor() {
    if (hueScaleMode == Disabled) {
        return;
    }
    std::ostringstream fullCssColorStream = GetCssColorStream(hue, 1, 1);
    std::ostringstream darkerCssColorStream = GetCssColorStream(hue, saturation, 0.8);
    std::ostringstream darkCssColorStream = GetCssColorStream(hue, saturation, 0.5);

    std::string cssStyle;

    if (hueScaleMode == AbsoluteHue) {
        // Create a CSS style string that changes the color of the slider (knob), the highlight, and the outline
        cssStyle = "scale slider { background: " + fullCssColorStream.str() + "; }" +
                   "scale trough { background: linear-gradient(to right, #ff0000 0%, #ffff00 16.67%, #00ff00 33.33%, #00ffff 50%, #0000ff 66.67%, #ff00ff 83.33%, #ff0000 100%); border-color: #343434; min-height: 5px;}" +
                   "scale highlight { background: transparent; border-color: #343434;}";

    } else {
        cssStyle = "scale slider { background: " + fullCssColorStream.str() + "; }" +
                   "scale trough { background: " + darkerCssColorStream.str() + "; border-color: #343434; min-height: 5px;}" +
                   "scale highlight { background: transparent; border-color: #343434;}";
    }
    // Create a CSS provider
    Glib::RefPtr<Gtk::CssProvider> cssProvider = Gtk::CssProvider::create();

    // Load the CSS style string into the CSS provider
    cssProvider->load_from_data(cssStyle);

    // Apply the CSS provider to the scales only
    hueScale.get_style_context()->add_provider(cssProvider, GTK_STYLE_PROVIDER_PRIORITY_USER);
}

void ColorSelector::UpdateSaturationScaleColor() {
    std::ostringstream fullCssColorStream = GetCssColorStream(hue, saturation, 1);
    std::ostringstream darkerCssColorStream = GetCssColorStream(hue, saturation, 0.8);
    std::ostringstream darkCssColorStream = GetCssColorStream(hue, saturation, 0.5);

    // Create a CSS style string that changes the color of the slider (knob), the highlight, and the outline
    std::string cssStyle = "scale slider { background: " + fullCssColorStream.str() + "; border-color: " + darkCssColorStream.str() + "; }" +
                           "scale highlight { background: linear-gradient(to top, white, " + darkerCssColorStream.str() + "); border-color: #343434; min-width: 5px; }" +
                           "scale trough { border-color: #343434;}";

    // Create a CSS provider
    Glib::RefPtr<Gtk::CssProvider> cssProvider = Gtk::CssProvider::create();

    // Load the CSS style string into the CSS provider
    cssProvider->load_from_data(cssStyle);

    // Apply the CSS provider to the scales only
    saturationScale.get_style_context()->add_provider(cssProvider, GTK_STYLE_PROVIDER_PRIORITY_USER);
}

std::ostringstream ColorSelector::GetCssColorStream(double colorHue, double colorSaturation, double colorValue) {
    Gdk::RGBA color;
    color.set_hsv(colorHue, colorSaturation, colorValue);
    std::ostringstream cssColorStream;
    cssColorStream << "rgba(" << color.get_red() * 255 << ", " << color.get_green() * 255 << ", " << color.get_blue() * 255 << ", " << color.get_alpha() << ")";
    return cssColorStream;
}