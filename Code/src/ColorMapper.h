#pragma once
#include "ColorImage.h"
#include "ColorScheme.h"
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

enum struct ColorMapperType {
    Closest,
    ClosestWithOffset,
    Histogram
};

class ColorMapper {
protected:
    std::shared_ptr<ColorScheme> colorScheme;
    bool useSaturation;

    ColorMapper(bool useSaturation) : useSaturation(useSaturation) {}

public:
    void ConvertToColorScheme(ColorImage& image);
    void SetColorScheme(std::shared_ptr<ColorScheme> colorScheme) { this->colorScheme = colorScheme; }
    virtual void SetImage(const ColorImage& image) {}

protected:
    virtual Color MapColor(Color color) = 0;
};

class ClosestMapper : public ColorMapper {
    double offset;

public:
    ClosestMapper(bool useSaturation, double offset = 0) : ColorMapper(useSaturation), offset(offset) {}

    Color MapColor(Color color) override;

protected:
    ColorSchemeColor GetClosestColor(double hue) const;
};

struct ColorInterval {
    // Map the hues from start to end to hue
    double start;
    double end;
    ColorSchemeColor color;

    bool Contains(double hue) const {
        if (start < end)
            return start <= hue && hue <= end;
        else // If the interval wraps around the 360 degree mark, we need to check two intervals
            return start <= hue || hue <= end;
    }
};

class HistogramMapper : public ColorMapper {
    std::vector<ColorInterval> intervals{};

public:
    HistogramMapper(bool useSaturation) : ColorMapper(useSaturation) {}

    void SetImage(const ColorImage& image) override;

    Color MapColor(Color color) override;

private:
    std::vector<int> GetHueHistogram(const ColorImage& image) const;
    void InitIntervals(const std::vector<int>& hueHistogram); // Create intervals based on the histogram by using k-means clustering
    std::vector<int> GetInitialCentroids(int k) const;
    std::vector<int> GetNewCentroids(const std::vector<int>& hueHistogram, const std::vector<int>& centroids) const;
    int GetLeftClusterBorder(const std::vector<int>& centroids, size_t centroidIndex) const;
    int GetRightClusterBorder(const std::vector<int>& centroids, size_t centroidIndex) const;
};