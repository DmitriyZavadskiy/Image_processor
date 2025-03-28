#include <catch.hpp>
#include "../src/filters/neg.h"
#include "../src/image/image.h"

namespace {
constexpr int ImageWidth = 2;
constexpr int ImageHeight = 2;
constexpr double NegativeInput = 0.3;
constexpr double ExpectedNegative = 1.0 - NegativeInput;
constexpr float OnePercentError = 1e-6;
}  // namespace

static void RequirePixelApprox(const Color &p, double expected_r, double expected_g, double expected_b,
                               double epsilon = OnePercentError) {
    REQUIRE(p.r == Approx(expected_r).epsilon(epsilon));
    REQUIRE(p.g == Approx(expected_g).epsilon(epsilon));
    REQUIRE(p.b == Approx(expected_b).epsilon(epsilon));
}

TEST_CASE("NegativeFilter Test", "[negative]") {
    Image img(ImageWidth, ImageHeight);
    for (int y = 0; y < ImageHeight; ++y) {
        for (int x = 0; x < ImageWidth; ++x) {
            img.GetPixel(x, y) = {NegativeInput, NegativeInput, NegativeInput};
        }
    }

    NegativeFilter filter;
    filter.Apply(img);

    for (int y = 0; y < ImageHeight; ++y) {
        for (int x = 0; x < ImageWidth; ++x) {
            auto &p = img.GetPixel(x, y);
            RequirePixelApprox(p, ExpectedNegative, ExpectedNegative, ExpectedNegative);
        }
    }
}
