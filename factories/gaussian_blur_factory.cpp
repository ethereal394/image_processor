#include "gaussian_blur_factory.h"

#include "../exceptions.h"
#include "../filters/gaussian_blur.h"

std::unique_ptr<BaseFilter> GaussianBlurFactory::Create(const std::vector<std::string>& input_params) {
    if (input_params.size() != 1) {
        throw FilterException("number of arguments of gaussian blur filter must be 1");
    }
    auto res = ConvertStringToDouble(input_params[0]);
    if (!res.has_value()) {
        throw FilterException("first argument of gaussian blur filter must be a positive number");
    }
    return std::make_unique<GaussianBlur>(res.value());
}
