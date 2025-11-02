#include "sharpening_factory.h"

#include "../exceptions.h"
#include "../filters/sharpening.h"

std::unique_ptr<BaseFilter> SharpeningFactory::Create(const std::vector<std::string>& input_params) {
    if (!input_params.empty()) {
        throw FilterException("number of arguments of sharpening filter must be 0");
    }
    return std::make_unique<Sharpening>();
}
