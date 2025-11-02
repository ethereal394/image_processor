#pragma once

#include <memory>
#include <optional>
#include <string>

#include "../filters/base_filters.h"

class BaseFactory {
public:
    virtual std::unique_ptr<BaseFilter> Create(const std::vector<std::string>&) = 0;

    virtual ~BaseFactory() = default;
};

std::optional<size_t> ConvertStringToSizeT(const std::string&) noexcept;

std::optional<double> ConvertStringToDouble(const std::string&) noexcept;
