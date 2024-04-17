#include "ColorMapperSelection.h"

ColorMapperSelection::ColorMapperSelection() {
    InitializeButton(closestButton, "Closest", ColorMapperType::Closest);
    InitializeButton(closestOffsetButton, "Closest with offset", ColorMapperType::ClosestWithOffset);
    InitializeButton(histogramButton, "Histogram", ColorMapperType::Histogram);

    attach(closestButton, 0, 0, 1, 1);
    attach(closestOffsetButton, 1, 0, 1, 1);
    attach(histogramButton, 2, 0, 1, 1);

    offsetScale.set_range(0, 360);
    attach(offsetScale, 1, 1, 1, 1);

    set_margin_start(10);  // Set margin on the start side
    set_margin_end(10);    // Set margin on the end side
    set_margin_top(5);     // Set margin on the top side
    set_margin_bottom(10); // Set margin on the bottom side

    show_all();
}

void ColorMapperSelection::InitializeButton(Gtk::Button& button, const std::string& label, ColorMapperType mode) {
    button.set_label(label);
    button.set_margin_start(5);
    button.set_margin_end(5);
    button.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &ColorMapperSelection::OnButtonClicked), mode));
}

void ColorMapperSelection::OnButtonClicked(ColorMapperType mode) {
    switch (mode) {
    case ColorMapperType::Closest:
        mapper = std::make_shared<ClosestMapper>();
        break;
    case ColorMapperType::ClosestWithOffset:
        mapper = std::make_shared<ClosestMapperWithOffset>(offsetScale.get_value());
        break;
    case ColorMapperType::Histogram:
        mapper = std::make_shared<HistogramMapper>();
        break;
    }
}