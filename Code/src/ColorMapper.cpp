#include "ColorMapper.h"
#include <cmath>
#include <iostream>
#include <stdlib.h>

// ############################################################################################################
// #                                                                                                          #
// #                                                ColorMapper                                               #
// #                                                                                                          #
// ############################################################################################################

void ColorMapper::ConvertToColorScheme(ColorImage& image) {
    for (int x = 0; x < image.GetWidth(); x++) {
        for (int y = 0; y < image.GetHeight(); y++) {
            Color pixel = image.GetPixel(x, y);
            Color newColor = MapColor(pixel);
            image.SetPixel(x, y, newColor);
        }
    }
}

// ############################################################################################################
// #                                                                                                          #
// #                                                ClosestMapper                                              #
// #                                                                                                          #
// ############################################################################################################

Color ClosestMapper::MapColor(Color color) {
    auto originalHSLColor = color.GetHSL();
    auto closest = GetClosestColor(originalHSLColor[0]);

    Color closestColor;
    closestColor.SetHSL(closest.hue, originalHSLColor[1], originalHSLColor[2]);
    return closestColor;
}

ColorSchemeColor ClosestMapper::GetClosestColor(double hue) const {
    hue = fmod(hue, 360);

    double minDistance = 360;
    ColorSchemeColor closestColor;
    for (const auto& color : colorScheme->GetColors()) {
        double distance = std::min(std::abs(color.hue - hue), 360 - std::abs(color.hue - hue));
        if (distance < minDistance) {
            minDistance = distance;
            closestColor = color;
        }
    }
    return closestColor;
}

// ############################################################################################################
// #                                                                                                          #
// #                                        ClosestMapperWithOffset                                           #
// #                                                                                                          #
// ############################################################################################################

Color ClosestMapperWithOffset::MapColor(Color color) {
    auto originalHSLColor = color.GetHSL();
    double closestHue = GetClosestColor(originalHSLColor[0] + offset).hue;

    Color closestColor;
    closestColor.SetHSL(closestHue, originalHSLColor[1], originalHSLColor[2]);
    return closestColor;
}

// ############################################################################################################
// #                                                                                                          #
// #                                              HistogramMapper                                             #
// #                                                                                                          #
// ############################################################################################################

void HistogramMapper::SetImage(const ColorImage& image) {
    std::vector<int> hueHistogram = GetHueHistogram(image);
    InitIntervals(hueHistogram);
    for (ColorInterval interval : intervals) {
        printf("Interval: %f - %f -> %f\n", interval.start, interval.end, interval.hue);
    }
}

Color HistogramMapper::MapColor(Color color) {
    auto originalHSLColor = color.GetHSL();
    for (ColorInterval interval : intervals) {
        if (interval.Contains(originalHSLColor[0])) {
            Color newColor;
            newColor.SetHSL(interval.hue, originalHSLColor[1], originalHSLColor[2]);
            return newColor;
        }
    }
    return color;
}

std::vector<int> HistogramMapper::GetHueHistogram(const ColorImage& image) const {
    std::vector<int> hueHistogram(360, 0);
    for (int x = 0; x < image.GetWidth(); x++) {
        for (int y = 0; y < image.GetHeight(); y++) {
            Color pixel = image.GetPixel(x, y);
            int hue = pixel.GetHSL()[0];
            hue = hue < 0 ? 0 : (hue > 359 ? 359 : hue);
            hueHistogram[hue]++;
        }
    }
    return hueHistogram;
}

void HistogramMapper::InitIntervals(const std::vector<int>& hueHistogram) {
    intervals.clear();

    std::vector<int> centroids = GetInitialCentroids(colorScheme->GetNumberOfColors());
    std::vector<int> newCentroids(centroids.size(), 0);

    int iterations = 0;
    while (centroids != newCentroids && iterations < 100) {
        std::cout << "Iteration " << iterations << std::endl;
        iterations++;
        centroids = newCentroids;
        newCentroids = GetNewCentroids(hueHistogram, centroids);
        for (size_t i = 0; i < centroids.size(); i++) {
            std::cout << centroids[i] << " ";
        }
    }
    std::cout << "Converged after " << iterations << " iterations" << std::endl;
    for (size_t i = 0; i < centroids.size(); i++) {
        ColorInterval interval;
        interval.start = GetLeftClusterBorder(centroids, i);
        interval.end = GetRightClusterBorder(centroids, i);
        interval.hue = colorScheme->GetColors()[i].hue;
        intervals.push_back(interval);
    }
}

std::vector<int> HistogramMapper::GetInitialCentroids(int k) const {
    std::cout << k << std::endl;
    std::vector<int> centroids(k, 0);
    for (int i = 0; i < k; i++) {
        centroids[i] = i * 360 / k;
    }

    return centroids;
}

std::vector<int> HistogramMapper::GetNewCentroids(const std::vector<int>& hueHistogram, const std::vector<int>& centroids) const {
    std::vector<int> newCentroids(centroids.size(), 0);
    for (size_t i = 0; i < centroids.size(); i++) {
        int leftBorderOfCluster = GetLeftClusterBorder(centroids, i);
        int rightBorderOfCluster = GetRightClusterBorder(centroids, i);
        int sum = 0;
        int count = 0;
        for (int j = leftBorderOfCluster; j != rightBorderOfCluster; j = (j + 1) % 360) {
            sum += hueHistogram[j] * j;
            count += hueHistogram[j];
        }
        sum += hueHistogram[rightBorderOfCluster] * rightBorderOfCluster;
        count += hueHistogram[rightBorderOfCluster];
        if (count != 0) {
            newCentroids[i] = sum / count;
        } else {
            newCentroids[i] = std::rand() % 255; // If the cluster is empty, assign a random value
        }
    }
    return newCentroids;
}

int HistogramMapper::GetLeftClusterBorder(const std::vector<int>& centroids, size_t centroidIndex) const {
    if (centroidIndex != 0) {
        return std::ceil((centroids[centroidIndex - 1] + centroids[centroidIndex]) / 2);
    } else {
        return fmod(std::ceil((centroids[centroids.size() - 1] + centroids[centroidIndex] + 360) / 2), 360); // The + 360 is to handle the case where the cluster wraps around the 0/360 degree boundary
    }
}

int HistogramMapper::GetRightClusterBorder(const std::vector<int>& centroids, size_t centroidIndex) const {
    if (centroidIndex != centroids.size() - 1) {
        return std::floor((centroids[centroidIndex] + centroids[centroidIndex + 1]) / 2);
    } else {
        return fmod(std::floor((centroids[centroidIndex] + centroids[0] + 360) / 2), 360); // The + 360 is to handle the case where the cluster wraps around the 0/360 degree boundary
    }
}