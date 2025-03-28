#pragma once
#include <string>
#include <vector>

struct FilterCommand {
    std::string name;
    std::vector<std::string> params;
};

struct Args {
    std::string input_file;
    std::string output_file;
    std::vector<FilterCommand> filters;
};

Args ParseArgs(int argc, char** argv);
