#include "exceptions.h"

const char* ImageProcessorException::what() const noexcept {
    return message_.c_str();
}

FilterException::FilterException(const std::string& message) {
    message_ = message;
}

ParserException::ParserException(const std::string& message) {
    message_ = message;
}

InputException::InputException(const std::string& message) {
    message_ = "error with input file: " + message;
}

OutputException::OutputException(const std::string& message) {
    message_ = "error with output file: " + message;
}
