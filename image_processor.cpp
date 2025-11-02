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
                         "  -edge [threshold]             = highlights edge that more than threshold\n";

int main(int argc, char** argv) {
    if (argc <= 2) {
        std::cout << HELP << std::endl;
        return 0;
    }
    try {
        ParserResults parser_info = Parse(argc, argv);
        Image image(ReadImage(parser_info.input_file));
        ApplyFilters(parser_info, image);
        WriteImage(image, parser_info.output_file);
    } catch (ImageProcessorException& exc) {
        std::cout << exc.what() << std::endl;
    } catch (std::exception& exc) {
        std::cout << "unexpected exception: " << exc.what() << std::endl;
    }
}
