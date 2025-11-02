#include "compress.h"

#include <cmath>
#include <vector>

void Compress(std::vector<std::vector<RGB>>& result, double height_coefficient, double width_coefficient,
              Image& image) noexcept {
    for (int64_t i = 0; i < static_cast<int64_t>(result.size()); ++i) {
        for (int64_t j = 0; j < static_cast<int64_t>(result[0].size()); ++j) {
            auto& x = result[i][j];
            int64_t count = 0;
            for (int64_t k = ceil(static_cast<double>(i) * height_coefficient);
                 k < static_cast<int64_t>(ceil(static_cast<double>(i + 1) * height_coefficient)); ++k) {
                for (int64_t p = ceil(static_cast<double>(j) * width_coefficient);
                     p < static_cast<int64_t>(ceil(static_cast<double>(j + 1) * width_coefficient)); ++p) {
                    x += image.GetPixel(k, p);
                    ++count;
                }
            }
            x /= static_cast<double>(count);
        }
    }
    image.SetPixels(std::move(result));
}

Compress1::Compress1(size_t height, size_t width) : height_(height), width_(width) {
    if (height_ == 0) {
        throw FilterException("first compress filter argument must be positive number");
    }
    if (width_ == 0) {
        throw FilterException("second compress filter argument must be positive number");
    }
}

void Compress1::ApplyCompress(Image& image) const noexcept {
    std::vector<std::vector<RGB>> result(std::min(height_, image.GetHeight()),
                                         std::vector<RGB>(std::min(width_, image.GetWidth())));
    double height_coefficient = std::max(static_cast<double>(image.GetHeight()) / static_cast<double>(height_), 1.0);
    double width_coefficient = std::max(static_cast<double>(image.GetWidth()) / static_cast<double>(width_), 1.0);
    Compress(result, height_coefficient, width_coefficient, image);
}

void Compress1::Apply(Image& image) const noexcept {
    ApplyCompress(image);
}

Compress2::Compress2(double coefficient) : coefficient_(coefficient) {
    if (coefficient_ < 1.0) {
        throw FilterException("compress filter argument must be more or equal than 1");
    }
}

void Compress2::ApplyCompress(Image& image) const noexcept {
    std::vector<std::vector<RGB>> result(
        static_cast<size_t>(static_cast<double>(image.GetHeight()) / coefficient_),
        std::vector<RGB>(static_cast<size_t>(static_cast<double>(image.GetWidth()) / coefficient_)));
    Compress(result, coefficient_, coefficient_, image);
}

void Compress2::Apply(Image& image) const noexcept {
    ApplyCompress(image);
}
