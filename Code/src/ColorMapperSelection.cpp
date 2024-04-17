#include "ColorMapperSelection.h"
#include <gtkmm/cssprovider.h>
#include <gtkmm/liststore.h>
#include <gtkmm/stylecontext.h>

ColorMapperSelection::ColorMapperSelection(ColorMapperChangedCallback callback) : callback(callback) {
    dropDownText.append("Closest");
    dropDownText.append("Closest with offset");
    dropDownText.append("Histogram");
    dropDownText.set_active(0);
    dropDownText.set_margin_start(10);
    dropDownText.set_margin_end(10);
    dropDownText.signal_changed().connect(sigc::mem_fun(*this, &ColorMapperSelection::OnDropdownChanged));

    grid.attach(dropDownText, 0, 0, 1, 1);

    useSaturationButton.set_label("Use Saturation");
    useSaturationButton.signal_toggled().connect(sigc::mem_fun(*this, &ColorMapperSelection::UpdateColorMapper));
    grid.attach(useSaturationButton, 1, 0, 1, 1);

    offsetScale.set_size_request(200, 20);
    offsetScale.set_range(0, 360);
    offsetScale.set_value(90);
    offsetScale.signal_value_changed().connect(sigc::mem_fun(*this, &ColorMapperSelection::OnScaleChanged));

    set_label("Color Mapper");
    set_margin_start(10);  // Set margin on the start side
    set_margin_end(10);    // Set margin on the end side
    set_margin_bottom(10); // Set margin on the bottom side
    Glib::RefPtr<Gtk::CssProvider> cssProvider = Gtk::CssProvider::create();
    cssProvider->load_from_data("* { border-radius: 10px;}");
    get_style_context()->add_provider(cssProvider, GTK_STYLE_PROVIDER_PRIORITY_USER);

    grid.set_margin_top(5);
    grid.set_margin_bottom(5);

    UpdateColorMapper();

    add(grid);
    show_all();
}

void ColorMapperSelection::OnDropdownChanged() {
    mapperType = dropDownText.get_active_row_number() == 0   ? ColorMapperType::Closest
                 : dropDownText.get_active_row_number() == 1 ? ColorMapperType::ClosestWithOffset
                                                             : ColorMapperType::Histogram;
    UpdateOptions();
    UpdateColorMapper();
}

void ColorMapperSelection::OnScaleChanged() {
    UpdateColorMapper();
}

void ColorMapperSelection::UpdateColorMapper() {
    switch (mapperType) {
    case ColorMapperType::Closest:
        mapper = std::make_shared<ClosestMapper>(useSaturationButton.get_active());
        break;
    case ColorMapperType::ClosestWithOffset:
        mapper = std::make_shared<ClosestMapper>(useSaturationButton.get_active(), offsetScale.get_value());
        break;
    case ColorMapperType::Histogram:
        mapper = std::make_shared<HistogramMapper>(useSaturationButton.get_active());
        break;
    }
    callback();
}

void ColorMapperSelection::UpdateOptions() {
    if (mapperType == ColorMapperType::ClosestWithOffset) {
        grid.attach(offsetScale, 1, 1, 1, 1);
        offsetScale.show();
    } else {
        grid.remove(offsetScale);
        offsetScale.hide();
    }
}
