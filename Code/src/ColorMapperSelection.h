#pragma once
#include "ColorMapper.h"

#include <memory>

#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <gtkmm/scale.h>

using ColorMapperChangedCallback = std::function<void()>;

class ColorMapperSelection : public Gtk::Grid {
    std::shared_ptr<ColorMapper> mapper;
    ColorMapperType mapperType = ColorMapperType::Closest;

    Gtk::Button closestButton;
    Gtk::Button closestOffsetButton;
    Gtk::Button histogramButton;

    Gtk::Scale offsetScale;

    ColorMapperChangedCallback callback;

public:
    ColorMapperSelection(ColorMapperChangedCallback callback);

    std::shared_ptr<ColorMapper> GetColorMapper() const {
        return mapper;
    }

private:
    void InitializeButton(Gtk::Button& button, const std::string& label, ColorMapperType mode);
    void OnButtonClicked(ColorMapperType mode);
    void OnScaleChanged();

    void UpdateColorMapper();
};