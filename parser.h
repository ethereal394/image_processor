#pragma once

#include <string>
#include <vector>

class Filter {
public:
    std::string name;
    std::vector<std::string> arguments;
};

class ParserResults {
public:
    std::string input_file;
    std::string output_file;
    std::vector<Filter> filters;

    ParserResults(const char*&&, const char*&&);

    ParserResults() = default;
};

ParserResults Parse(int, char**&);
