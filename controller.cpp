#include "controller.h"

#include "exceptions.h"
#include "image.h"

std::vector<std::unique_ptr<BaseFilter>> CreateFilters(const ParserResults& parser_results) {
    std::vector<std::unique_ptr<BaseFilter>> filters;
    for (const auto& filter : parser_results.filters) {
        auto factory = FACTORIES.find(filter.name);
        if (factory == FACTORIES.end()) {
            throw ParserException("no filter found with the name " + filter.name);
        }
        filters.push_back(factory->second->Create(filter.arguments));
    }
    return filters;
}


void ApplyFilters(Image& image, const std::vector<std::unique_ptr<BaseFilter>>& filters) {
    for (const auto& filter : filters) {
        filter->Apply(image);
    }
}