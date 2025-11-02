#pragma once

#include <concepts>
#include <fstream>
#include <string>

#include "image.h"

class BinaryReader {
public:
    explicit BinaryReader(const std::string&);

    template <std::integral T>
    void Read(T&);

    void Seek(int64_t, std::ios::seekdir);

private:
    std::ifstream in_;
};

class BinaryWriter {
public:
    explicit BinaryWriter(const std::string&);

    template <std::integral T>
    void Write(T);

    void Seek(int64_t, std::ios::seekdir);

private:
    std::ofstream out_;
};

Image ReadImage(const std::string&);

void WriteImage(const Image&, const std::string&);
