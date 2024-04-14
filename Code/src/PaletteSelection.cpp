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
    colorSelectors.emplace_back(0, 1);
    SetColorSchemeMode(ColorSchemeType::Monochrome);

    plusAndMinusButtons.set_valign(Gtk::ALIGN_CENTER); // Center the plus and minus buttons vertically
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
        colorScheme = std::make_shared<AnalogousColorScheme>(colorSelectors[0].GetHue(), 10, numberOfColorsAnalogous);
        break;
    case ColorSchemeType::Manual:
        std::vector<ColorSchemeColor> colors;
        for (int i = 0; i < numberOfColorsManual; i++) {
            double randomHue = rand() % 360;
            colors.emplace_back(randomHue, 1);
        }
        colorScheme = std::make_shared<ColorScheme>(colors);
        break;
    }

    RedrawColorSelectors();
}

void PaletteSelection::RedrawColorSelectors() {
    DestroyColorSelectors();

    // Create new ColorSelectors
    colorSelectors.reserve(colorScheme->GetNumberOfColors());
    auto colorSchemeColors = colorScheme->GetColors();
    for (int i = 0; i < colorScheme->GetNumberOfColors(); i++) {
        colorSelectors.emplace_back(colorSchemeColors[i].hue, colorSchemeColors[i].saturation);
        colorBox.pack_start(colorSelectors.back(), Gtk::PACK_SHRINK, 0);
    }

    SetHueScaleModes();

    if (colorSchemeType == ColorSchemeType::Analogous || colorSchemeType == ColorSchemeType::Manual) {
        colorBox.pack_start(plusAndMinusButtons, Gtk::PACK_SHRINK, 0);
    }

    for (int i = 0; i < colorScheme->GetNumberOfColors(); i++) {
        colorSelectors[i].SetCallbacks([this, i] { OnColorChanged(i); }, [this] { OnHueDistanceChanged(); });
    }
}

void PaletteSelection::DestroyColorSelectors() {
    for (auto& colorSelector : colorSelectors) {
        colorBox.remove(colorSelector);
    }
    colorSelectors.clear();
    colorBox.remove(plusAndMinusButtons);
}

void PaletteSelection::SetHueScaleModes() {
    if (colorSchemeType != ColorSchemeType::Manual) {
        for (int i = 1; i < colorScheme->GetNumberOfColors(); i++) {
            colorSelectors[i].SetHueScaleMode(HueScaleMode::Disabled);
        }
    }

    if (colorSchemeType == ColorSchemeType::Analogous) {
        colorSelectors[1].SetHueScaleMode(HueScaleMode::HueDistance, numberOfColorsAnalogous);
    }
}

void PaletteSelection::UpdateColorSelectors() {
    for (size_t i = 0; i < colorSelectors.size(); i++) {
        colorSelectors[i].SetHue(colorScheme->GetColors()[i].hue);
        colorSelectors[i].SetSaturation(colorScheme->GetColors()[i].saturation);
    }
}

void PaletteSelection::OnColorChanged(int colorSelectorIndex) {
    colorScheme->SetColor(colorSelectorIndex, colorSelectors[colorSelectorIndex].GetHue(), colorSelectors[colorSelectorIndex].GetSaturation());
    UpdateColorSelectors();
    callback();
}

void PaletteSelection::OnHueDistanceChanged() {
    double hueDistance = colorSelectors[1].GetHueDistance();
    colorScheme = std::make_shared<AnalogousColorScheme>(colorSelectors[0].GetHue(), hueDistance, numberOfColorsAnalogous);
    UpdateColorSelectors();
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