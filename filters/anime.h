#pragma once

#include "base_filters.h"

class Anime : public virtual BaseFilter {
public:
    Anime() = default;

    void Apply(Image&) const noexcept override;

protected:
    void ApplyAnime(Image&) const noexcept;
};
