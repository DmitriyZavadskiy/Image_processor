#include <catch.hpp>
#include "../src/filters/crop.h"
#include "../src/image/image.h"

namespace {
constexpr int OrigWidth = 4;
constexpr int OrigHeight = 4;
constexpr int CropWidth = 2;
constexpr int CropHeight = 3;
constexpr double RDivisor = 3.0;
constexpr double GDivisor = 3.0;
constexpr double BDivisor = 6.0;
constexpr float OnePercentError = 1e-6;
}  // namespace

static void RequirePixelApprox(const Color &p, double expected_r, double expected_g, double expected_b,
                               double eps = OnePercentError) {
    REQUIRE(p.r == Approx(expected_r).epsilon(eps));
    REQUIRE(p.g == Approx(expected_g).epsilon(eps));
    REQUIRE(p.b == Approx(expected_b).epsilon(eps));
}

TEST_CASE("CropFilter test", "[crop]") {

    Image img(OrigWidth, OrigHeight);
    for (int y = 0; y < OrigHeight; ++y) {
        for (int x = 0; x < OrigWidth; ++x) {
            double r = static_cast<double>(x) / RDivisor;
            double g = static_cast<double>(y) / GDivisor;
            double b = static_cast<double>(x + y) / BDivisor;
            img.GetPixel(x, y) = {r, g, b};
        }
    }

    CropFilter crop(CropWidth, CropHeight);
    crop.Apply(img);

    const int expected_width = std::min(CropWidth, OrigWidth);
    const int expected_height = std::min(CropHeight, OrigHeight);

    REQUIRE(img.Width() == expected_width);
    REQUIRE(img.Height() == expected_height);

    for (int y = 0; y < expected_height; ++y) {
        for (int x = 0; x < expected_width; ++x) {
            double expected_r = static_cast<double>(x) / RDivisor;
            double expected_g = static_cast<double>(y) / GDivisor;
            double expected_b = static_cast<double>(x + y) / BDivisor;
            RequirePixelApprox(img.GetPixel(x, y), expected_r, expected_g, expected_b);
        }
    }
}
