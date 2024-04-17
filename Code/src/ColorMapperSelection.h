#pragma once
#include "ColorMapper.h"

#include <memory>

#include <gtkmm/comboboxtext.h>
#include <gtkmm/frame.h>
#include <gtkmm/grid.h>
#include <gtkmm/scale.h>
#include <gtkmm/checkbutton.h>

using ColorMapperChangedCallback = std::function<void()>;

class ColorMapperSelection : public Gtk::Frame {
    Gtk::Grid grid;

    std::shared_ptr<ColorMapper> mapper;
    ColorMapperType mapperType = ColorMapperType::Closest;

    Gtk::ComboBoxText dropDownText;
    Gtk::CheckButton useSaturationButton;
    Gtk::Scale offsetScale;

    ColorMapperChangedCallback callback;

public:
    ColorMapperSelection(ColorMapperChangedCallback callback);

    std::shared_ptr<ColorMapper> GetColorMapper() const {
        return mapper;
    }

private:
    void OnDropdownChanged();
    void OnScaleChanged();

    void UpdateColorMapper();
    void UpdateOptions();
};