#include "negative_factory.h"

#include "../exceptions.h"
#include "../filters/negative.h"

std::unique_ptr<BaseFilter> NegativeFactory::Create(const std::vector<std::string>& input_params) {
    if (!input_params.empty()) {
        throw FilterException("number of arguments of negative filter must be 0");
    }
    return std::make_unique<Negative>();
}
