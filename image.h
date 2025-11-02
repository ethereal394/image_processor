#pragma once

#include <array>
#include <cstdint>
#include <vector>

class RGB {
public:
    double R = 0;
    double G = 0;
    double B = 0;

    void Normalize();

    explicit operator std::array<double, 3>() const;

    explicit operator std::array<double*, 3>();

    RGB& operator+=(RGB);

    RGB& operator*=(double);

    RGB& operator/=(double);
};

RGB operator+(RGB, RGB);

RGB operator*(RGB, double);

RGB operator/(RGB, double);

class Image {
public:
    Image() = default;

    explicit Image(const std::vector<std::vector<RGB>>&);

    explicit Image(std::vector<std::vector<RGB>>&&);

    size_t GetWidth() const;

    size_t GetHeight() const;

    RGB GetPixel(int64_t, int64_t) const;

    void SetPixels(const std::vector<std::vector<RGB>>&);

    void SetPixels(std::vector<std::vector<RGB>>&&);

    void SetPixel(int64_t, int64_t, double, double, double);

    void SetPixel(int64_t, int64_t, RGB);

private:
    std::vector<std::vector<RGB>> image_;
};
