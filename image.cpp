#include "image.h"

void RGB::Normalize() {
    R = std::min(1.0, std::max(0.0, R));
    G = std::min(1.0, std::max(0.0, G));
    B = std::min(1.0, std::max(0.0, B));
}

RGB::operator std::array<double, 3>() const {
    return {R, G, B};
}

RGB::operator std::array<double*, 3>() {
    return {&R, &G, &B};
}

RGB& RGB::operator+=(RGB x) {
    R += x.R;
    G += x.G;
    B += x.B;
    return *this;
}

RGB& RGB::operator*=(double k) {
    R *= k;
    G *= k;
    B *= k;
    return *this;
}

RGB& RGB::operator/=(double k) {
    R /= k;
    G /= k;
    B /= k;
    return *this;
}

RGB operator+(RGB x, RGB y) {
    return {x.R + y.R, x.G + y.G, x.B + y.B};
}

RGB operator*(RGB x, double k) {
    return {x.R * k, x.G * k, x.B * k};
}

RGB operator/(RGB x, double k) {
    return {x.R / k, x.G / k, x.B / k};
}

Image::Image(const std::vector<std::vector<RGB>>& image) : image_(image) {
}

Image::Image(std::vector<std::vector<RGB>>&& image) : image_(std::move(image)) {
}

size_t Image::GetWidth() const {
    return image_[0].size();
}

size_t Image::GetHeight() const {
    return image_.size();
}

RGB Image::GetPixel(int64_t x, int64_t y) const {
    if (x < 0 && y < 0) {
        return image_[0][0];
    }
    if (x < 0 && y >= static_cast<int64_t>(GetWidth())) {
        return image_[0].back();
    }
    if (x >= static_cast<int64_t>(GetHeight()) && y < 0) {
        return image_.back()[0];
    }
    if (x >= static_cast<int64_t>(GetHeight()) && y >= static_cast<int64_t>(GetWidth())) {
        return image_.back().back();
    }
    if (x < 0) {
        return image_[0][y];
    }
    if (x >= static_cast<int64_t>(GetHeight())) {
        return image_.back()[y];
    }
    if (y < 0) {
        return image_[x][0];
    }
    if (y >= static_cast<int64_t>(GetWidth())) {
        return image_[x].back();
    }
    return image_[x][y];
}

void Image::SetPixels(const std::vector<std::vector<RGB>>& image) {
    image_ = image;
}

void Image::SetPixels(std::vector<std::vector<RGB>>&& image) {
    image_ = std::move(image);
}

void Image::SetPixel(int64_t i, int64_t j, double r, double g, double b) {
    image_[i][j].R = r;
    image_[i][j].G = g;
    image_[i][j].B = b;
}

void Image::SetPixel(int64_t i, int64_t j, RGB x) {
    image_[i][j] = x;
}
