#include "anime.h"

void Anime::ApplyAnime(Image& image) const noexcept {
    for (int64_t i = 0; i < static_cast<int64_t>(image.GetHeight()); i += 2) {
        for (int64_t j = 0; j < static_cast<int64_t>(image.GetWidth()); ++j) {
            image.SetPixel(i, j, 0, 0, 0);
        }
    }
}

void Anime::Apply(Image& image) const noexcept {
    ApplyAnime(image);
}
