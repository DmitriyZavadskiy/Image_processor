#include <iostream>
#include <stdexcept>
#include "src/args/args.h"
#include "src/bmp/loader.h"
#include "src/bmp/dumper.h"
#include "src/filters/registry.h"
#include "src/image/image.h"

int main(int argc, char **argv) {
    try {
        if (argc < 3) {
            std::cerr << "Usage: cd cmake-build-debug/ <-- там бинарник || ./image_processor.exe "
                         "../test_script/data/input.bmp ../tmp/output.bmp  filters"
                      << std::endl;
            return 1;
        }
        std::string input_file = argv[1];
        std::string output_file = argv[2];

        Args parsed_args = ParseArgs(argc, argv);
        Image image = LoadBMP(parsed_args.input_file);
        RegisterAllFilters();

        for (auto &flt_cmd : parsed_args.filters) {
            auto filter = FilterRegistry::Instance().CreateFilter(flt_cmd.name, flt_cmd.params);
            if (!filter) {
                throw std::runtime_error("Unknown filter: " + flt_cmd.name);
            }
            filter->Apply(image);
        }

        SaveBMP(image, parsed_args.output_file);

        return 0;
    } catch (const std::exception &ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }
}
