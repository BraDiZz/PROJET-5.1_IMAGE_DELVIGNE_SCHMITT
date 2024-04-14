#include "PaletteSelection.h"

PaletteSelection::PaletteSelection(ColorSchemeChangedCallback callback) : plusAndMinusButtons([this](PlusAndMinusButtonsType type) { OnPlusOrMinusClicked(type); }), callback(callback) {
    set_orientation(Gtk::ORIENTATION_VERTICAL);
    colorBox.set_margin_top(10); // Set margin on the start side
    colorBox.set_valign(Gtk::ALIGN_CENTER);
    pack_start(buttonBox, Gtk::PACK_SHRINK, 0);
    pack_start(colorBox, Gtk::PACK_SHRINK, 0);

    set_margin_start(10);  // Set margin on the start side
    set_margin_end(10);    // Set margin on the end side
    set_margin_top(10);    // Set margin on the top side
    set_margin_bottom(10); // Set margin on the bottom side

    InitializeButtons();
    colorSelectors.emplace_back([this] { OnColorChanged(0); }, [this] { OnHueDistanceChanged(); });
    SetColorSchemeMode(ColorSchemeType::Monochrome);
}

void PaletteSelection::InitializeButtons() {
    InitializeButton(monochromeButton, "Monochrome", ColorSchemeType::Monochrome);
    InitializeButton(complementaryButton, "Complementary", ColorSchemeType::Complementary);
    InitializeButton(triadicButton, "Triadic", ColorSchemeType::Triadic);
    InitializeButton(analogousButton, "Analogous", ColorSchemeType::Analogous);
    InitializeButton(manualButton, "Manual", ColorSchemeType::Manual);
}

void PaletteSelection::InitializeButton(Gtk::Button& button, const std::string& label, ColorSchemeType mode) {
    button.set_label(label);
    button.set_margin_start(5);
    button.set_margin_end(5);
    button.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &PaletteSelection::SetColorSchemeMode), mode));
    buttonBox.pack_start(button, Gtk::PACK_SHRINK, 0);
}

void PaletteSelection::SetColorSchemeMode(ColorSchemeType mode) {
    colorSchemeType = mode;
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
        colorScheme = std::make_shared<AnalogousColorScheme>(colorSelectors[0].GetHue(), 20, numberOfColorsAnalogous);
        break;
    case ColorSchemeType::Manual:
        std::vector<ColorSchemeColor> colors;
        for (int i = 0; i < numberOfColorsManual; i++) {
            colors.emplace_back(colorSelectors[0].GetHue() + i * 10, colorSelectors[0].GetSaturation());
        }
        colorScheme = std::make_shared<ColorScheme>(colors);
        break;
    }

    colorSelectors.clear();
    auto colorSchemeColors = colorScheme->GetColors();
    for (int i = 0; i < colorScheme->GetNumberOfColors(); i++) {
        colorSelectors.emplace_back([this, i] { OnColorChanged(i); }, [this] { OnHueDistanceChanged(); });
    }

    for (int i = 1; i < colorScheme->GetNumberOfColors(); i++) {
        if (mode != ColorSchemeType::Manual) {
            colorSelectors[i].SetHueScaleMode(HueScaleMode::Disabled);
        }

        colorSelectors.back().SetHue(colorSchemeColors[i].hue);
        colorSelectors.back().SetSaturation(colorSchemeColors[i].saturation);
    }

    if (mode == ColorSchemeType::Analogous) {
        colorSelectors[1].SetHueScaleMode(HueScaleMode::HueDistance);
    }

    DrawColorSelectors();
}

void PaletteSelection::DrawColorSelectors() {
    colorBox.remove(plusAndMinusButtons);
    for (auto& colorSelector : colorSelectors) {
        colorBox.pack_start(colorSelector, Gtk::PACK_SHRINK, 0);
    }
    if (colorSchemeType == ColorSchemeType::Analogous || colorSchemeType == ColorSchemeType::Manual) {
        colorBox.pack_start(plusAndMinusButtons, Gtk::PACK_SHRINK, 0);
        plusAndMinusButtons.set_valign(Gtk::ALIGN_CENTER); // Center the plus and minus buttons vertically
    }
}

void PaletteSelection::OnColorChanged(int colorSelectorIndex) {
    colorScheme->SetColor(colorSelectorIndex, colorSelectors[colorSelectorIndex].GetHue(), colorSelectors[colorSelectorIndex].GetSaturation());
    for (int i = 0; i < colorScheme->GetNumberOfColors(); i++) {
        if (colorSelectors[i].GetHue() != colorScheme->GetColors()[i].hue) {
            colorSelectors[i].SetHue(colorScheme->GetColors()[i].hue);
        }
        if (colorSelectors[i].GetSaturation() != colorScheme->GetColors()[i].saturation) {
            colorSelectors[i].SetSaturation(colorScheme->GetColors()[i].saturation);
        }
    }
    callback();
}

void PaletteSelection::OnHueDistanceChanged() {
    double hueDistance = colorSelectors[1].GetHueDistance();
    colorScheme = std::make_shared<AnalogousColorScheme>(colorSelectors[0].GetHue(), hueDistance, numberOfColorsAnalogous);
    auto colorSchemeColors = colorScheme->GetColors();
    for (int i = 1; i < colorScheme->GetNumberOfColors(); i++) {
        colorSelectors[i].SetHue(colorSchemeColors[i].hue);
        colorSelectors[i].SetSaturation(colorSchemeColors[i].saturation);
    }
}

void PaletteSelection::OnPlusOrMinusClicked(PlusAndMinusButtonsType type) {
    int addition = 0;

    if (type == PlusAndMinusButtonsType::Plus) {
        addition = 1;
    } else {
        addition = -1;
    }

    if (colorSchemeType == ColorSchemeType::Analogous) {
        numberOfColorsAnalogous += addition;
        numberOfColorsAnalogous = std::clamp(numberOfColorsAnalogous, 2, 7);
    }
    if (colorSchemeType == ColorSchemeType::Manual) {
        numberOfColorsManual += addition;
        numberOfColorsManual = std::clamp(numberOfColorsManual, 2, 7);
    }

    SetColorSchemeMode(colorSchemeType);
}