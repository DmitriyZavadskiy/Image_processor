#include <catch.hpp>
#include "../src/args/args.h"
#include <memory>
#include <cstring>
#include <vector>

constexpr const char* ProgramName = "./image_processor";
constexpr const char* InputFile = "input.bmp";
constexpr const char* OutputFile = "/tmp/output.bmp";

constexpr const char* FilterCrop = "-crop";
constexpr const char* CropWidth = "800";
constexpr const char* CropHeight = "600";

constexpr const char* FilterGrayscale = "-gs";

constexpr const char* FilterBlur = "-blur";
constexpr const char* BlurSigma = "0.5";

constexpr int ExpectedArgc = 9;
constexpr int ExpectedFilterCount = 3;

TEST_CASE("ParseArgs Basic Test", "[args]") {
    std::vector<std::string> argv_array = {ProgramName, InputFile,       OutputFile, FilterCrop, CropWidth,
                                           CropHeight,  FilterGrayscale, FilterBlur, BlurSigma};

    const int argc = static_cast<int>(argv_array.size());

    REQUIRE(argc == ExpectedArgc);

    std::vector<std::unique_ptr<char[]>> storage(argc);
    std::vector<char*> argv(argc);
    for (int i = 0; i < argc; ++i) {
        const std::string& s = argv_array[i];
        storage[i] = std::make_unique<char[]>(s.size() + 1);
        std::memcpy(storage[i].get(), s.c_str(), s.size() + 1);
        argv[i] = storage[i].get();
    }

    auto result = ParseArgs(argc, argv.data());

    REQUIRE(result.input_file == InputFile);
    REQUIRE(result.output_file == OutputFile);

    REQUIRE(result.filters.size() == ExpectedFilterCount);

    REQUIRE(result.filters[0].name == "crop");
    REQUIRE(result.filters[0].params.size() == 2);
    REQUIRE(result.filters[0].params[0] == CropWidth);
    REQUIRE(result.filters[0].params[1] == CropHeight);

    REQUIRE(result.filters[1].name == "gs");
    REQUIRE(result.filters[1].params.empty());

    REQUIRE(result.filters[2].name == "blur");
    REQUIRE(result.filters[2].params.size() == 1);
    REQUIRE(result.filters[2].params[0] == BlurSigma);
}
