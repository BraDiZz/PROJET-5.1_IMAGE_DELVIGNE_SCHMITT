#include "ColorScheme.h"
#include "ColorSelector.h"
#include "PlusAndMinusButtons.h"
#include <gtkmm.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <memory>

using ColorSchemeChangedCallback = std::function<void()>;

class PaletteSelection : public Gtk::Box {
    Gtk::Box buttonBox;
    Gtk::Box colorBox;

    Gtk::Button monochromeButton;
    Gtk::Button complementaryButton;
    Gtk::Button triadicButton;
    Gtk::Button analogousButton;
    Gtk::Button manualButton;

    std::vector<ColorSelector> colorSelectors;

    PlusAndMinusButtons plusAndMinusButtons;

    ColorSchemeType colorSchemeType;
    int numberOfColorsAnalogous = 5;
    int numberOfColorsManual = 5;
    std::shared_ptr<ColorScheme> colorScheme;

    ColorSchemeChangedCallback callback;

public:
    PaletteSelection(ColorSchemeChangedCallback callback);

    std::shared_ptr<ColorScheme> GetColorScheme() const { return colorScheme; }

private:
    void InitializeButtons();
    void InitializeButton(Gtk::Button &button, const std::string &label, ColorSchemeType mode);

    void SetColorSchemeMode(ColorSchemeType mode);

    void DrawColorSelectors();

    void OnColorChanged(int colorSelectorIndex);

    void OnPlusOrMinusClicked(PlusAndMinusButtonsType type);
};