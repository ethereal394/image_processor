#pragma once

#include "base_filters.h"

class Negative : public virtual BaseFilter {
public:
    Negative() = default;

    void Apply(Image&) const noexcept override;

protected:
    void ApplyNegative(Image&) const noexcept;
};
