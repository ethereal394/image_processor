#include "edge_detection.h"

#include <vector>

#include "../factories/grayscale_factory.h"

const int CENTRAL_COEFFICIENT = 4;
const int SIDE_COEFFICIENT = -1;

EdgeDetection::EdgeDetection(double threshold)
    : BaseFilterWithCrossProduct(CENTRAL_COEFFICIENT, SIDE_COEFFICIENT), threshold_(threshold) {
    if (threshold_ < 0) {
        throw FilterException("edge detection filter argument must be more or equal than 0");
    }
    if (threshold_ > 1) {
        throw FilterException("edge detection filter argument must be less or equal than 1");
    }
}

void EdgeDetection::ApplyEdgeDetection(Image& image) const noexcept {
    ApplyGrayscale(image);
    ApplyCrossProduct(image);
    for (int64_t i = 0; i < static_cast<int64_t>(image.GetHeight()); ++i) {
        for (int64_t j = 0; j < static_cast<int64_t>(image.GetWidth()); ++j) {
            int x = image.GetPixel(i, j).R > threshold_ ? 1 : 0;
            image.SetPixel(i, j, x, x, x);
        }
    }
}

void EdgeDetection::Apply(Image& image) const noexcept {
    ApplyEdgeDetection(image);
}
