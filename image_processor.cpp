#include <iostream>

#include "controller.h"
#include "exceptions.h"
#include "image.h"
#include "io.h"
#include "parser.h"

const std::string HELP = "usage: \n"
                         "\n"
                         "  image_processor <path to input file> <path to output file> [filters]\n"
                         "  image_processor [options]\n"
                         "\n"
                         "options:\n"
                         "\n"
                         "  -h, --help                    = gives help\n"
                         "\n"
                         "filters:\n"
                         "\n"
                         "  -crop [width][height]         = crops image to size width by height\n"
                         "  -compress [width][height]     = compress image to size width by height\n"
                         "  -compress [coefficient]       = compress image with coefficient\n"
                         "  -gs                           = makes image gray\n"
                         "  -neg                          = makes image negative\n"
                         "  -sharp                        = applies sharpness on image\n"
                         "  -blur [sigma]                 = applies gaussian blur with coefficient sigma\n"
                         "  -edge [threshold]             = highlights edge that more than threshold\n"
                         "  -rotate                       = rotates the image to the right by 90 degrees\n";

int main(int argc, char** argv) {
    if (argc <= 2) {
        std::cout << HELP << std::endl;
        return 0;
    }
    ParserResults parser_info;
    Image image;
    std::vector<std::unique_ptr<BaseFilter>> filters;
    try {
        parser_info = Parse(argc, argv);
        filters = CreateFilters(parser_info);
        image = Image(ReadImage(parser_info.input_file));
    } catch (ImageProcessorException& exc) {
        std::cout << exc.what() << std::endl;
    } catch (std::exception& exc) {
        std::cout << "unexpected exception: " << exc.what() << std::endl;
    }
    ApplyFilters(image, filters);
    try {
        WriteImage(image, parser_info.output_file);
    } catch (ImageProcessorException& exc) {
        std::cout << exc.what() << std::endl;
    } catch (std::exception& exc) {
        std::cout << "unexpected exception: " << exc.what() << std::endl;
    }
}
