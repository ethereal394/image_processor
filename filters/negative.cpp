#include "negative.h"

#include <vector>

void Negative::ApplyNegative(Image& image) const noexcept {
    for (int64_t i = 0; i < static_cast<int64_t>(image.GetHeight()); ++i) {
        for (int64_t j = 0; j < static_cast<int64_t>(image.GetWidth()); ++j) {
            RGB x = image.GetPixel(i, j);
            image.SetPixel(i, j, 1 - x.R, 1 - x.G, 1 - x.B);
        }
    }
}

void Negative::Apply(Image& image) const noexcept {
    ApplyNegative(image);
}
