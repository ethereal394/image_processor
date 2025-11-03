#include "sharpening.h"

const int CENTRAL_COEFFICIENT = 5;
const int SIDE_COEFFICIENT = -1;

Sharpening::Sharpening() : BaseFilterWithCrossProduct(CENTRAL_COEFFICIENT, SIDE_COEFFICIENT) {
}

void Sharpening::ApplySharpening(Image& image) const noexcept {
    ApplyCrossProduct(image);
}

void Sharpening::Apply(Image& image) const noexcept {
    ApplySharpening(image);
}
