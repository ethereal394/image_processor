#include "crop.h"

#include <vector>

Crop::Crop(size_t height, size_t width) : height_(height), width_(width) {
    if (height_ == 0) {
        throw FilterException("first crop filter argument must be positive number");
    }
    if (width_ == 0) {
        throw FilterException("second crop filter argument must be positive number");
    }
}

void Crop::ApplyCrop(Image& image) const noexcept {
    std::vector<std::vector<RGB>> result(std::min(height_, image.GetHeight()),
                                         std::vector<RGB>(std::min(width_, image.GetWidth())));
    for (int64_t i = 0; i < static_cast<int64_t>(result.size()); ++i) {
        for (int64_t j = 0; j < static_cast<int64_t>(result[0].size()); ++j) {
            result[i][j] =
                image.GetPixel(i + static_cast<int64_t>(image.GetHeight()) - static_cast<int64_t>(result.size()), j);
        }
    }
    image.SetPixels(std::move(result));
}

void Crop::Apply(Image& image) const noexcept {
    ApplyCrop(image);
}
