#include <catch.hpp>
#include "../src/filters/blur.h"
#include "../src/image/image.h"

namespace {
constexpr double ZeroFive = 0.5;
}

TEST_CASE("BlurFilter: uniform image remains unchanged", "[blur]") {

    Image img(3, 3);
    for (int y = 0; y < img.Height(); ++y) {
        for (int x = 0; x < img.Width(); ++x) {
            img.GetPixel(x, y) = {ZeroFive, ZeroFive, ZeroFive};
        }
    }

    BlurFilter filter(1.0);
    filter.Apply(img);

    for (int y = 0; y < img.Height(); ++y) {
        for (int x = 0; x < img.Width(); ++x) {
            auto &p = img.GetPixel(x, y);
            REQUIRE(p.r == Approx(ZeroFive));
            REQUIRE(p.g == Approx(ZeroFive));
            REQUIRE(p.b == Approx(ZeroFive));
        }
    }
}

TEST_CASE("BlurFilter: non-uniform image becomes smoother", "[blur]") {

    Image img(3, 3);
    for (int y = 0; y < img.Height(); ++y) {
        img.GetPixel(0, y) = {0.0, 0.0, 0.0};
        img.GetPixel(1, y) = {ZeroFive, ZeroFive, ZeroFive};
        img.GetPixel(2, y) = {1.0, 1.0, 1.0};
    }

    BlurFilter filter(1.0);
    filter.Apply(img);

    for (int y = 0; y < img.Height(); ++y) {
        auto &p0 = img.GetPixel(0, y);
        auto &p1 = img.GetPixel(1, y);
        auto &p2 = img.GetPixel(2, y);
        REQUIRE(p0.r > 0.0);
        REQUIRE(p2.r < 1.0);
        REQUIRE(p1.r > p0.r);
        REQUIRE(p1.r < p2.r);
    }
}
