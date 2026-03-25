#pragma once

#include "base_filters.h"

class Rotate : public virtual BaseFilter {
public:
    Rotate() = default;

    void Apply(Image&) const noexcept override;

protected:
    void ApplyRotate(Image&) const noexcept;
};
