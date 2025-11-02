#pragma once

#include "base_filters.h"

class Grayscale : public virtual BaseFilter {
public:
    Grayscale() = default;

    void Apply(Image&) const noexcept override;

protected:
    void ApplyGrayscale(Image&) const noexcept;
};
