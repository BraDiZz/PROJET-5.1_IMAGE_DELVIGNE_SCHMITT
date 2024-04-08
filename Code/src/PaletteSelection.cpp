#include "PaletteSelection.h"

PaletteSelection::PaletteSelection() {
    set_orientation(Gtk::ORIENTATION_VERTICAL);
    separator.set_size_request(-1, 10);
    pack_start(buttonBox, Gtk::PACK_SHRINK, 0);
    pack_start(separator, Gtk::PACK_SHRINK, 0);
    pack_start(colorBox, Gtk::PACK_SHRINK, 0);

    set_margin_start(10);  // Set margin on the start side
    set_margin_end(10);    // Set margin on the end side
    set_margin_top(10);    // Set margin on the top side
    set_margin_bottom(10); // Set margin on the bottom side

    InitializeButtons();
    colorSelectors.emplace_back();
    SetColorSchemeMode(ColorSchemeType::Monochrome);
}

void PaletteSelection::InitializeButtons() {
    InitializeButton(monochromeButton, "Monochrome", ColorSchemeType::Monochrome);
    InitializeButton(complementaryButton, "Complementary", ColorSchemeType::Complementary);
    InitializeButton(triadicButton, "Triadic", ColorSchemeType::Triadic);
    InitializeButton(analogousButton, "Analogous", ColorSchemeType::Analogous);
    InitializeButton(manualButton, "Manual", ColorSchemeType::Manual);
}

void PaletteSelection::InitializeButton(Gtk::Button &button, const std::string &label, ColorSchemeType mode) {
    button.set_label(label);
    button.set_margin_start(5);
    button.set_margin_end(5);
    button.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &PaletteSelection::SetColorSchemeMode), mode));
    buttonBox.pack_start(button, Gtk::PACK_SHRINK, 0);
}

void PaletteSelection::SetColorSchemeMode(ColorSchemeType mode) {
    switch (mode) {
    case ColorSchemeType::Monochrome:
        colorScheme = std::make_shared<MonochromeColorScheme>(colorSelectors[0].GetHue());
        break;
    case ColorSchemeType::Complementary:
        colorScheme = std::make_shared<ComplementaryColorScheme>(colorSelectors[0].GetHue());
        break;
    case ColorSchemeType::Triadic:
        colorScheme = std::make_shared<TriadicColorScheme>(colorSelectors[0].GetHue());
        break;
    case ColorSchemeType::Analogous:
        colorScheme = std::make_shared<AnalogousColorScheme>(colorSelectors[0].GetHue(), 30, 5);
        break;
    case ColorSchemeType::Manual:
        colorScheme = std::make_shared<ColorScheme>(std::vector<ColorSchemeColor>{colorSelectors[0].GetHue(), colorSelectors[0].GetHue() + 10, colorSelectors[0].GetHue() + 20, colorSelectors[0].GetHue() + 30, colorSelectors[0].GetHue() + 40});
        break;
    }

    colorSelectors.clear();
    for (const auto &color : colorScheme->GetColors()) {
        colorSelectors.emplace_back();
        colorSelectors.back().SetHue(color.hue);
        colorSelectors.back().SetSaturation(color.saturation);
    }
    if (mode != ColorSchemeType::Manual) {
        for (int i = 1; i < colorScheme->GetNumberOfColors(); i++) {
            colorSelectors[i].SetShowHueScale(false);
        }
    }
    DrawColorSelectors();
}

void PaletteSelection::DrawColorSelectors() {
    for (auto &colorSelector : colorSelectors) {
        colorBox.pack_start(colorSelector, Gtk::PACK_SHRINK, 0);
    }
}
