#pragma once

#include "base_filters.h"

class GaussianBlur : public virtual BaseFilter {
public:
    explicit GaussianBlur(double);

    void Apply(Image&) const noexcept override;

protected:
    void ApplyGaussianBlur(Image&) const noexcept;

    double sigma_;
};
