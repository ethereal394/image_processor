#include "rotate.h"

void Rotate::ApplyRotate(Image& image) const noexcept {
    std::vector<std::vector<RGB>> result(image.GetWidth(), std::vector<RGB>(image.GetHeight()));
    for (int64_t i = 0; i < static_cast<int64_t>(result.size()); i++) {
        for (int64_t j = 0; j < static_cast<int64_t>(result[0].size()); j++) {
            result[static_cast<int64_t>(result.size()) - 1 - i][j] = image.GetPixel(j, i);
        }
    }
    image.SetPixels(std::move(result));
}

void Rotate::Apply(Image& image) const noexcept {
    ApplyRotate(image);
}
