#include "negative.h"

void Negative::ApplyNegative(Image& image) const noexcept {
    for (int64_t i = 0; i < static_cast<int64_t>(image.GetHeight()); ++i) {
        for (int64_t j = 0; j < static_cast<int64_t>(image.GetWidth()); ++j) {
            RGB pixel = image.GetPixel(i, j);
            image.SetPixel(i, j, 1 - pixel.R, 1 - pixel.G, 1 - pixel.B);
        }
    }
}

void Negative::Apply(Image& image) const noexcept {
    ApplyNegative(image);
}
