#include "gaussian_blur.h"

#include <cmath>
#include <numbers>
#include <vector>

GaussianBlur::GaussianBlur(double sigma) : sigma_(sigma) {
    if (sigma <= 0) {
        throw FilterException("gaussian blur argument must be positive number");
    }
}

double Square(double x) {
    return x * x;
}

int64_t Square(int64_t x) {
    return x * x;
}

void GaussianBlur::ApplyGaussianBlur(Image& image) const noexcept {
    int64_t border = floor(3 * sigma_);
    std::vector<std::vector<RGB>> vert_sum(image.GetHeight(), std::vector<RGB>(2 * border + image.GetWidth()));
    for (int64_t i = 0; i < static_cast<int64_t>(vert_sum.size()); ++i) {
        for (int64_t j = 0; j < static_cast<int64_t>(vert_sum[0].size()); ++j) {
            for (int64_t k = -border; k <= border; ++k) {
                double coefficient = 1.0 / (2 * std::numbers::pi * Square(sigma_)) *
                                     exp(static_cast<double>(-Square(k)) / (2 * Square(sigma_)));
                vert_sum[i][j] += image.GetPixel(i + k, j - border) * coefficient;
            }
        }
    }
    for (int64_t i = 0; i < static_cast<int64_t>(image.GetHeight()); ++i) {
        for (int64_t j = 0; j < static_cast<int64_t>(image.GetWidth()); ++j) {
            RGB pixel;
            for (int64_t p = -border; p <= border; ++p) {
                double coefficient = exp(static_cast<double>(-Square(p)) / (2 * Square(sigma_)));
                pixel += vert_sum[i][j + border - p] * coefficient;
            }
            image.SetPixel(i, j, pixel);
        }
    }
}

void GaussianBlur::Apply(Image& image) const noexcept {
    ApplyGaussianBlur(image);
}
