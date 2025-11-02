#pragma once

#include "base_factory.h"

class EdgeDetectionFactory : public BaseFactory {
public:
    std::unique_ptr<BaseFilter> Create(const std::vector<std::string>&) override;
};
