#include "ColorScheme.h"
#include "ColorImage.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <memory>



class ColorMapper {
protected:
    ColorScheme* colorScheme;

    ColorMapper(ColorScheme* colorScheme) : colorScheme(colorScheme) {}
public:
    ~ColorMapper() { delete colorScheme;}
    
    void ConvertToColorScheme(ColorImage &image);

protected:
    virtual Color MapColor(Color color) = 0;
};

class ClosestMapper : public ColorMapper {
public:
    ClosestMapper(ColorScheme* colorScheme) : ColorMapper(colorScheme) {}

    Color MapColor(Color color) override;

protected:
    double GetClosestHue(double hue) const;
};

class ClosestMapperWithOffset : public ClosestMapper {
    double offset;

public:
    ClosestMapperWithOffset(ColorScheme* colorScheme, double offset) : ClosestMapper(colorScheme), offset(offset) {}

    Color MapColor(Color color) override;
};

struct ColorInterval {
        // Map the hues from start to end to hue
        double start;
        double end;
        double hue;

        bool Contains(double hue) const {
            if(start < end)
                return start <= hue && hue <= end;
            else // If the interval wraps around the 360 degree mark, we need to check two intervals
                return start <= hue || hue <= end;
        }
    };

class HistogramMapper : public ColorMapper {
    std::vector<ColorInterval> intervals{};

public:
    HistogramMapper(ColorScheme* colorScheme, const ColorImage& image);

    Color MapColor(Color color) override;

private:
    std::vector<int> GetHueHistogram(const ColorImage& image) const;
    void InitIntervals(const std::vector<int>& hueHistogram); // Create intervals based on the histogram by using k-means clustering
    std::vector<int> GetInitialCentroids(int k) const;
    std::vector<int> GetNewCentroids(const std::vector<int>& hueHistogram, const std::vector<int>& centroids) const;
    int GetLeftClusterBorder(const std::vector<int> &centroids, int centroidIndex) const;
    int GetRightClusterBorder(const std::vector<int> &centroids, int centroidIndex) const;
};