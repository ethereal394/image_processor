#pragma once

#include "base_filters.h"

class Crop : public virtual BaseFilter {
public:
    Crop(size_t, size_t);

    void Apply(Image&) const noexcept override;

protected:
    void ApplyCrop(Image&) const noexcept;

    size_t height_;
    size_t width_;
};
