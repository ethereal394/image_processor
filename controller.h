#pragma once

#include <string>
#include <unordered_map>

#include "factories/base_factory.h"
#include "factories/compress_factory.h"
#include "factories/crop_factory.h"
#include "factories/edge_detection_factory.h"
#include "factories/gaussian_blur_factory.h"
#include "factories/grayscale_factory.h"
#include "factories/negative_factory.h"
#include "factories/sharpening_factory.h"
#include "parser.h"

const std::unordered_map<std::string, std::unique_ptr<BaseFactory> > FACTORIES = []() {
    std::unordered_map<std::string, std::unique_ptr<BaseFactory> > temp;
    temp.emplace("crop", std::make_unique<CropFactory>());
    temp.emplace("gs", std::make_unique<GrayscaleFactory>());
    temp.emplace("neg", std::make_unique<NegativeFactory>());
    temp.emplace("sharp", std::make_unique<SharpeningFactory>());
    temp.emplace("edge", std::make_unique<EdgeDetectionFactory>());
    temp.emplace("compress", std::make_unique<CompressFactory>());
    temp.emplace("blur", std::make_unique<GaussianBlurFactory>());
    return temp;
}();

void ApplyFilters(const ParserResults &, Image &);
