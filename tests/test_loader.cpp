#include <catch.hpp>
#include "../src/bmp/loader.h"
#include "../src/bmp/dumper.h"
#include "../src/image/image.h"
#include <filesystem>

namespace {
constexpr int TestWidth = 3;
constexpr int TestHeight = 3;

constexpr double Tolerance = 0.02;
}  // namespace

TEST_CASE("LoadBMP Test", "[bmp][loader]") {

    Image original(TestWidth, TestHeight);
    for (int y = 0; y < TestHeight; ++y) {
        for (int x = 0; x < TestWidth; ++x) {

            double r = (TestWidth > 1) ? static_cast<double>(x) / (TestWidth - 1) : 0.0;
            double g = (TestHeight > 1) ? static_cast<double>(y) / (TestHeight - 1) : 0.0;
            double b = ((TestWidth + TestHeight) > 2) ? static_cast<double>(x + y) / (TestWidth + TestHeight - 2) : 0.0;
            original.GetPixel(x, y) = {r, g, b};
        }
    }

    const std::string tmp_filename = "temp_test.bmp";
    SaveBMP(original, tmp_filename);

    Image loaded = LoadBMP(tmp_filename);

    REQUIRE(loaded.Width() == original.Width());
    REQUIRE(loaded.Height() == original.Height());

    for (int y = 0; y < TestHeight; ++y) {
        for (int x = 0; x < TestWidth; ++x) {
            auto orig_pixel = original.GetPixel(x, y);
            auto loaded_pixel = loaded.GetPixel(x, y);
            REQUIRE(loaded_pixel.r == Approx(orig_pixel.r).epsilon(Tolerance));
            REQUIRE(loaded_pixel.g == Approx(orig_pixel.g).epsilon(Tolerance));
            REQUIRE(loaded_pixel.b == Approx(orig_pixel.b).epsilon(Tolerance));
        }
    }

    std::filesystem::remove(tmp_filename);
}
