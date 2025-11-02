#include "base_filters.h"

BaseFilterWithCrossProduct::BaseFilterWithCrossProduct(double central_coefficient, double side_coefficient) noexcept
    : central_coefficient_(central_coefficient), side_coefficient_(side_coefficient) {
}

void BaseFilterWithCrossProduct::ApplyCrossProduct(Image& image) const noexcept {
    const int dx[4]{1, 0, -1, 0};
    const int dy[4]{0, 1, 0, -1};
    std::vector<std::vector<RGB>> result(image.GetHeight(), std::vector<RGB>(image.GetWidth()));
    for (int64_t i = 0; i < static_cast<int64_t>(result.size()); ++i) {
        for (int64_t j = 0; j < static_cast<int64_t>(result[0].size()); ++j) {
            auto p = static_cast<std::array<double*, 3>>(result[i][j]);
            auto x = static_cast<std::array<double, 3>>(image.GetPixel(i, j));
            for (size_t k = 0; k < p.size(); ++k) {
                *p[k] = x[k] * central_coefficient_;
            }
            for (size_t k = 0; k < 4; ++k) {
                x = static_cast<std::array<double, 3>>(image.GetPixel(i + dx[k], j + dy[k]));
                for (size_t t = 0; t < p.size(); ++t) {
                    *p[t] += x[t] * side_coefficient_;
                }
            }
            for (auto& k : p) {
                *k = std::clamp(*k, 0.0, 1.0);
            }
        }
    }
    image.SetPixels(std::move(result));
}

template <int N, int M>
BaseFilterWithMatrixProduct<N, M>::BaseFilterWithMatrixProduct(
    const std::array<std::array<int, N>, M>& coefficients) noexcept
    : coefficients_(coefficients) {
}

template <int N, int M>
void BaseFilterWithMatrixProduct<N, M>::ApplyMatrixProduct(Image& image) const noexcept {
    std::vector<std::vector<RGB>> result(image.GetHeight(), std::vector<RGB>(image.GetWidth()));
    for (int64_t i = 0; i < static_cast<int64_t>(result.size()); ++i) {
        for (int64_t j = 0; j < static_cast<int64_t>(result[0].size()); ++j) {
            auto p = static_cast<std::array<double*, 3>>(result[i][j]);
            for (int64_t k = 0; k < N; ++k) {
                for (int64_t t = 0; t < M; ++t) {
                    auto x = static_cast<std::array<double, 3>>(image.GetPixel(k, t));
                    for (size_t q = 0; q < p.size(); ++q) {
                        *p[q] += x[q] * coefficients_[i - N / 2 + k][j - M / 2 + t];
                    }
                }
            }
            for (auto& k : p) {
                *k = std::clamp(*k, 0.0, 1.0);
            }
        }
    }
    image.SetPixels(std::move(result));
}
