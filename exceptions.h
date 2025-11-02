#pragma once

#include <exception>
#include <string>

class ImageProcessorException : std::exception {
public:
    const char* what() const noexcept override;

protected:
    std::string message_;
};

class FilterException final : public ImageProcessorException {
public:
    explicit FilterException(const std::string&);

    FilterException() = delete;
};

class ParserException final : public ImageProcessorException {
public:
    explicit ParserException(const std::string&);

    ParserException() = delete;
};

class InputException final : public ImageProcessorException {
public:
    explicit InputException(const std::string&);

    InputException() = delete;
};

class OutputException final : public ImageProcessorException {
public:
    explicit OutputException(const std::string&);

    OutputException() = delete;
};
