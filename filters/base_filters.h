#pragma once

#include <array>
#include <algorithm>

#include "../image.h"
#include "../exceptions.h"

class BaseFilter {
public:
    virtual void Apply(Image&) const noexcept = 0;

    virtual ~BaseFilter() = default;
};

class BaseFilterWithCrossProduct : public virtual BaseFilter {
public:
    BaseFilterWithCrossProduct(double, double) noexcept;

protected:
    void ApplyCrossProduct(Image&) const noexcept;

    double central_coefficient_;
    double side_coefficient_;
};

template <int N, int M>
class BaseFilterWithMatrixProduct : public virtual BaseFilter {
public:
    explicit BaseFilterWithMatrixProduct(const std::array<std::array<int, N>, M>&) noexcept;

protected:
    void ApplyMatrixProduct(Image&) const noexcept;

    std::array<std::array<int, N>, M> coefficients_;
};