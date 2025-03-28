#include <catch.hpp>
#include "../src/filters/affine_tile.h"
#include "../src/image/image.h"
#include "image/color.h"

namespace {
constexpr double ZeroFive = 0.5;
constexpr float OnePercentError = 1e-6;
}  // namespace

static void RequirePixelApprox(const Color &p, double r, double g, double b, double eps = OnePercentError) {
    REQUIRE(p.r == Approx(r).epsilon(eps));
    REQUIRE(p.g == Approx(g).epsilon(eps));
    REQUIRE(p.b == Approx(b).epsilon(eps));
}

TEST_CASE("AffineTileFilter swap test") {

    Image img(2, 2);
    img.GetPixel(0, 0) = {1.0, 0.0, 0.0};
    img.GetPixel(1, 0) = {0.0, 1.0, 0.0};
    img.GetPixel(0, 1) = {0.0, 0.0, 1.0};
    img.GetPixel(1, 1) = {ZeroFive, ZeroFive, ZeroFive};

    AffineTileFilter filter(0.0, 1.0, 1.0, 0.0, 0.0, 0.0);
    filter.Apply(img);

    REQUIRE(img.Width() == 2);
    REQUIRE(img.Height() == 2);

    // Проверяем содержимое пикселей:
    RequirePixelApprox(img.GetPixel(0, 0), 1.0, 0.0, 0.0);
    RequirePixelApprox(img.GetPixel(1, 0), 0.0, 0.0, 1.0);
    RequirePixelApprox(img.GetPixel(0, 1), 0.0, 1.0, 0.0);
    RequirePixelApprox(img.GetPixel(1, 1), ZeroFive, ZeroFive, ZeroFive);
}
