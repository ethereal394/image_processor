#include "io.h"

#include <cmath>
#include <limits>
#include <vector>

#include "exceptions.h"

const uint16_t SIGNATURE = 0x4D42;
const uint32_t OFFSET = 54;
const uint32_t HEADER_SIZE = 40;
const uint16_t PLANES = 1;
const uint16_t BITS_PER_PIXEL = 24;

BinaryReader::BinaryReader(const std::string& in_path) : in_(in_path) {
    if (!in_.is_open()) {
        throw InputException("can't open file");
    }
}

template <std::integral T>
void BinaryReader::Read(T& value) {
    in_.read(reinterpret_cast<char*>(&value), sizeof(value));
}

void BinaryReader::Seek(int64_t value, std::ios::seekdir seekdir) {
    in_.seekg(value, seekdir);
}

BinaryWriter::BinaryWriter(const std::string& out_path) : out_(out_path) {
    if (!out_.is_open()) {
        throw OutputException("can't open file");
    }
}

template <std::integral T>
void BinaryWriter::Write(T value) {
    out_.write(reinterpret_cast<char*>(&value), sizeof(value));
}

void BinaryWriter::Seek(int64_t value, std::ios::seekdir seekdir) {
    out_.seekp(value, seekdir);
}

Image ReadImage(const std::string& filename) {
    BinaryReader input(filename);
    uint16_t signature = 0;
    input.Read(signature);
    if (signature != SIGNATURE) {
        throw InputException("file isn't bmp file");
    }
    const int64_t skip1 = 8;
    input.Seek(skip1, std::ios_base::cur);
    uint32_t offset = 0;
    input.Read(offset);
    const int64_t skip2 = 4;
    input.Seek(skip2, std::ios_base::cur);
    int32_t width = 0;
    input.Read(width);
    int32_t height = 0;
    input.Read(height);
    const int64_t skip3 = 2;
    input.Seek(skip3, std::ios_base::cur);
    uint16_t bits_per_pixel = 0;
    input.Read(bits_per_pixel);
    if (bits_per_pixel != BITS_PER_PIXEL) {
        throw InputException("file isn't " + std::to_string(BITS_PER_PIXEL) + " bits per pixel format");
    }
    input.Seek(offset, std::ios::beg);
    uint32_t row_size = ((width * 3 + 3) >> 2) << 2;
    uint32_t padding = row_size - (width * 3);
    std::vector<std::vector<RGB>> image(height, std::vector<RGB>(width));
    for (int64_t i = 0; i < height; ++i) {
        for (int64_t j = 0; j < width; ++j) {
            uint8_t b = 0;
            input.Read(b);
            image[i][j].B = static_cast<double>(b) / std::numeric_limits<uint8_t>::max();
            uint8_t g = 0;
            input.Read(g);
            image[i][j].G = static_cast<double>(g) / std::numeric_limits<uint8_t>::max();
            uint8_t r = 0;
            input.Read(r);
            image[i][j].R = static_cast<double>(r) / std::numeric_limits<uint8_t>::max();
        }
        input.Seek(padding, std::ios::cur);
    }
    return Image(std::move(image));
}

void WriteImage(const Image& image, const std::string& filename) {
    BinaryWriter output(filename);
    uint32_t row_size = ((image.GetWidth() * 3 + 3) >> 2) << 2;
    uint32_t padding = row_size - (image.GetWidth() * 3);
    output.Write(SIGNATURE);
    uint32_t size = OFFSET + row_size * image.GetHeight();
    output.Write(size);
    output.Write(static_cast<uint16_t>(0));
    output.Write(static_cast<uint16_t>(0));
    output.Write(OFFSET);
    output.Write(HEADER_SIZE);
    output.Write(static_cast<int32_t>(image.GetWidth()));
    output.Write(static_cast<int32_t>(image.GetHeight()));
    output.Write(PLANES);
    output.Write(BITS_PER_PIXEL);
    output.Seek(OFFSET, std::ios_base::beg);
    for (int64_t i = 0; i < static_cast<int64_t>(image.GetHeight()); ++i) {
        for (int64_t j = 0; j < static_cast<int64_t>(image.GetWidth()); ++j) {
            RGB x = image.GetPixel(i, j);
            output.Write(static_cast<uint8_t>(round(x.B * std::numeric_limits<uint8_t>::max())));
            output.Write(static_cast<uint8_t>(round(x.G * std::numeric_limits<uint8_t>::max())));
            output.Write(static_cast<uint8_t>(round(x.R * std::numeric_limits<uint8_t>::max())));
        }
        for (size_t p = 0; p < padding; ++p) {
            output.Write(static_cast<uint8_t>(0));
        }
    }
}
