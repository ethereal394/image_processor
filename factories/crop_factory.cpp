#include "crop_factory.h"

#include "../exceptions.h"
#include "../filters/crop.h"

std::unique_ptr<BaseFilter> CropFactory::Create(const std::vector<std::string>& input_params) {
    if (input_params.size() != 2) {
        throw FilterException("number of arguments of crop filter must be 2");
    }
    auto res = ConvertStringToSizeT(input_params[0]);
    if (!res.has_value()) {
        throw FilterException("first argument of crop filter must be positive integer");
    }
    size_t width = res.value();
    res = ConvertStringToSizeT(input_params[1]);
    if (!res.has_value()) {
        throw FilterException("second argument of crop filter must be positive integer");
    }
    size_t height = res.value();
    return std::make_unique<Crop>(height, width);
}
