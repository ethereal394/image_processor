#include "controller.h"

#include "exceptions.h"
#include "image.h"

void ApplyFilters(const ParserResults& parser_results, Image& image) {
    for (const auto& filter : parser_results.filters) {
        auto factory = FACTORIES.find(filter.name);
        if (factory == FACTORIES.end()) {
            throw ParserException("no filter found with the name " + filter.name);
        }
        factory->second->Create(filter.arguments)->Apply(image);
    }
}
