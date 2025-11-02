#pragma once

#include "grayscale.h"

class EdgeDetection : public virtual Grayscale, public virtual BaseFilterWithCrossProduct {
public:
    explicit EdgeDetection(double);

    void Apply(Image&) const noexcept override;

protected:
    void ApplyEdgeDetection(Image&) const noexcept;

    double threshold_;
};
