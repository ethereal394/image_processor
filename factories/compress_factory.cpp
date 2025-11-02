#include "compress_factory.h"

#include "../exceptions.h"
#include "../filters/compress.h"

std::unique_ptr<BaseFilter> CompressFactory::Create(const std::vector<std::string>& input_params) {
    if (input_params.size() == 2) {
        auto res = ConvertStringToSizeT(input_params[0]);
        if (!res.has_value()) {
            throw FilterException(
                "if compress filter have 2 arguments first argument of compress filter must be positive integer");
        }
        size_t width = res.value();
        res = ConvertStringToSizeT(input_params[1]);
        if (!res.has_value()) {
            throw FilterException(
                "if compress filter have 2 arguments second argument of compress filter must be positive integer");
        }
        size_t height = res.value();
        return std::make_unique<Compress1>(height, width);
    }
    if (input_params.size() == 1) {
        auto res = ConvertStringToDouble(input_params[0]);
        if (!res.has_value()) {
            throw FilterException(
                "if compress filter have 1 arguments first argument of compress filter must be positive number");
        }
        return std::make_unique<Compress2>(res.value());
    }
    throw FilterException("number of arguments of compress filter must be 1 or 2");
}
