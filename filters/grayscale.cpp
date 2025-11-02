#include "grayscale.h"

#include <vector>

const double R_COEFFICIENT = 0.299;
const double G_COEFFICIENT = 0.587;
const double B_COEFFICIENT = 0.114;

void Grayscale::ApplyGrayscale(Image& image) const noexcept {
    for (int64_t i = 0; i < static_cast<int64_t>(image.GetHeight()); ++i) {
        for (int64_t j = 0; j < static_cast<int64_t>(image.GetWidth()); ++j) {
            RGB pixel = image.GetPixel(i, j);
            double gray_value = R_COEFFICIENT * pixel.R + G_COEFFICIENT * pixel.G + B_COEFFICIENT * pixel.B;
            image.SetPixel(i, j, gray_value, gray_value, gray_value);
        }
    }
}

void Grayscale::Apply(Image& image) const noexcept {
    ApplyGrayscale(image);
}
