#include "grayscale_factory.h"

#include "../exceptions.h"
#include "../filters/grayscale.h"

std::unique_ptr<BaseFilter> GrayscaleFactory::Create(const std::vector<std::string>& input_params) {
    if (!input_params.empty()) {
        throw FilterException("number of arguments of grayscale filter must be 0");
    }
    return std::make_unique<Grayscale>();
}
