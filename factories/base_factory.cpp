#include "base_factory.h"

std::optional<size_t> ConvertStringToSizeT(const std::string& value) noexcept {
    const int radix = 10;
    size_t res = 0;
    for (char i : value) {
        if (!isdigit(i)) {
            return std::nullopt;
        }
        res = res * radix + (i - '0');
    }
    return res;
}

std::optional<double> ConvertStringToDouble(const std::string& value) noexcept {
    const int radix = 10;
    int d10 = 1;
    double res = 0;
    for (char i : value) {
        if (!isdigit(i)) {
            if (i != '.' || d10 != 1) {
                return std::nullopt;
            }
            d10 *= radix;
        } else {
            if (d10 == 1) {
                res = res * radix + (i - '0');
            } else {
                res = res + static_cast<double>(i - '0') / d10;
                d10 *= radix;
            }
        }
    }
    return res;
}
