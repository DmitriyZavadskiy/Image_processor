#include <catch.hpp>
#include "../src/bmp/dumper.h"
#include "../src/bmp/loader.h"
#include "../src/image/image.h"
#include <filesystem>

namespace {
constexpr int TestWidth = 3;
constexpr int TestHeight = 3;
constexpr double Tolerance = 0.02;
}  // namespace

TEST_CASE("SaveBMP and LoadBMP Test", "[bmp]") {

    Image img(TestWidth, TestHeight);
    for (int y = 0; y < TestHeight; ++y) {
        for (int x = 0; x < TestWidth; ++x) {

            double r = (TestWidth > 1) ? static_cast<double>(x) / (TestWidth - 1) : 0.0;
            double g = (TestHeight > 1) ? static_cast<double>(y) / (TestHeight - 1) : 0.0;
            double b = ((TestWidth + TestHeight) > 2) ? static_cast<double>(x + y) / (TestWidth + TestHeight - 2) : 0.0;
            img.GetPixel(x, y) = {r, g, b};
        }
    }

    std::string tmp_file = "test_output.bmp";
    SaveBMP(img, tmp_file);

    Image loaded = LoadBMP(tmp_file);

    for (int y = 0; y < TestHeight; ++y) {
        for (int x = 0; x < TestWidth; ++x) {
            auto orig = img.GetPixel(x, y);
            auto copy = loaded.GetPixel(x, y);

            REQUIRE(copy.r == Approx(orig.r).epsilon(Tolerance));
            REQUIRE(copy.g == Approx(orig.g).epsilon(Tolerance));
            REQUIRE(copy.b == Approx(orig.b).epsilon(Tolerance));
        }
    }

    std::filesystem::remove(tmp_file);
}
