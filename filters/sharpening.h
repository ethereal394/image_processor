#pragma once

#include "base_filters.h"

class Sharpening : public virtual BaseFilterWithCrossProduct {
public:
    Sharpening();

    void Apply(Image&) const noexcept override;

protected:
    void ApplySharpening(Image&) const noexcept;
};
