#include <catch.hpp>
#include "../src/filters/grayscale.h"
#include "../src/image/image.h"

namespace {
constexpr int ImageWidth = 2;
constexpr int ImageHeight = 2;
constexpr double TestRed = 0.2;
constexpr double TestGreen = 0.4;
constexpr double TestBlue = 0.6;
// Ожидаемое значение яркости по формуле: Gray = 0.299 * R + 0.587 * G + 0.114 * B
constexpr double ExpectedGray = 0.299 * TestRed + 0.587 * TestGreen + 0.114 * TestBlue;
constexpr float OnePercentError = 1e-6;
}  // namespace

// Вспомогательная функция для сравнения пикселей
static void RequirePixelApprox(const Color &p, double expected_r, double expected_g, double expected_b,
                               double epsilon = OnePercentError) {
    REQUIRE(p.r == Approx(expected_r).epsilon(epsilon));
    REQUIRE(p.g == Approx(expected_g).epsilon(epsilon));
    REQUIRE(p.b == Approx(expected_b).epsilon(epsilon));
}

TEST_CASE("GrayscaleFilter Test", "[grayscale]") {
    Image img(ImageWidth, ImageHeight);
    for (int y = 0; y < ImageHeight; ++y) {
        for (int x = 0; x < ImageWidth; ++x) {
            img.GetPixel(x, y) = {TestRed, TestGreen, TestBlue};
        }
    }

    GrayScaleFilter filter;
    filter.Apply(img);

    for (int y = 0; y < ImageHeight; ++y) {
        for (int x = 0; x < ImageWidth; ++x) {
            auto &p = img.GetPixel(x, y);
            RequirePixelApprox(p, ExpectedGray, ExpectedGray, ExpectedGray);
        }
    }
}
