#pragma once

#include "base_filters.h"

class Compress1 : public virtual BaseFilter {
public:
    Compress1(size_t, size_t);

    void Apply(Image&) const noexcept override;

protected:
    void ApplyCompress(Image&) const noexcept;

    size_t height_;
    size_t width_;
};

class Compress2 : public virtual BaseFilter {
public:
    explicit Compress2(double);

    void Apply(Image&) const noexcept override;

protected:
    void ApplyCompress(Image&) const noexcept;

    double coefficient_;
};
