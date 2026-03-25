#include "rotate_factory.h"

#include "../exceptions.h"
#include "../filters/rotate.h"

std::unique_ptr<BaseFilter> RotateFactory::Create(const std::vector<std::string>& input_params) {
    if (!input_params.empty()) {
        throw FilterException("number of arguments of rotate filter must be 0");
    }
    return std::make_unique<Rotate>();
}
