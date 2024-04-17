#pragma once
#include "ColorMapper.h"

#include <memory>

#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <gtkmm/scale.h>

class ColorMapperSelection : public Gtk::Grid {
    std::shared_ptr<ColorMapper> mapper = std::make_shared<ClosestMapper>();

    Gtk::Button closestButton;
    Gtk::Button closestOffsetButton;
    Gtk::Button histogramButton;

    Gtk::Scale offsetScale;

public:
    ColorMapperSelection();

    std::shared_ptr<ColorMapper> GetColorMapper() const {
        return mapper;
    }

private:
    void InitializeButton(Gtk::Button& button, const std::string& label, ColorMapperType mode);
    void OnButtonClicked(ColorMapperType mode);
};