#include "args.h"

Args ParseArgs(int argc, char** argv) {
    Args result;
    result.input_file = argv[1];
    result.output_file = argv[2];

    int i = 3;
    while (i < argc) {

        std::string filter_name = argv[i++];
        if (!filter_name.empty() && filter_name[0] == '-') {
            filter_name = filter_name.substr(1);
        }

        FilterCommand cmd;
        cmd.name = filter_name;

        while (i < argc && argv[i][0] != '-') {
            cmd.params.push_back(argv[i]);
            i++;
        }

        result.filters.push_back(cmd);
    }

    return result;
}
