#include "edge_detection_factory.h"

#include "../exceptions.h"
#include "../filters/edge_detection.h"

std::unique_ptr<BaseFilter> EdgeDetectionFactory::Create(const std::vector<std::string>& input_params) {
    if (input_params.size() != 1) {
        throw FilterException("number of arguments of edge detection filter must be 1");
    }
    auto res = ConvertStringToDouble(input_params[0]);
    if (!res.has_value()) {
        throw FilterException("first argument of edge detection filter must be a positive number");
    }
    return std::make_unique<EdgeDetection>(res.value());
}
