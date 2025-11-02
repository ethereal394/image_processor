#include "parser.h"

#include "exceptions.h"

ParserResults::ParserResults(const char*&& input, const char*&& output) : input_file(input), output_file(output) {
}

ParserResults Parse(int argc, char**& argv) {
    if (argc >= 4 && argv[3][0] != '-') {
        throw ParserException("first argument after files is not filter name");
    }
    ParserResults result(std::move(argv[1]), std::move(argv[2]));
    size_t filters_count = 0;
    for (int64_t i = 3; i < argc; ++i) {
        if (argv[i][0] == '-') {
            ++filters_count;
        }
    }
    result.filters.reserve(filters_count);
    for (int64_t i = 3; i < argc;) {
        auto& filter = result.filters.emplace_back();
        filter.name = std::move((argv[i] + 1));
        int64_t j = i + 1;
        while (j < argc && argv[j][0] != '-') {
            ++j;
        }
        filter.arguments.reserve(j - i - 1);
        for (int64_t k = i + 1; k < j; ++k) {
            filter.arguments.emplace_back(std::move(argv[k]));
        }
        i = j;
    }
    return result;
}
