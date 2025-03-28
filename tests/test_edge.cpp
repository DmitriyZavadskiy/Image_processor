#include <catch.hpp>
#include "../src/filters/edge.h"
#include "../src/image/image.h"

namespace con {
constexpr float OnePercentError = 1e-6;
}
// Вспомогательная функция для сравнения пикселей с допуском
static void RequirePixelApprox(const Color &p, double expected_r, double expected_g, double expected_b,
                               double epsilon = con::OnePercentError) {
    REQUIRE(p.r == Approx(expected_r).epsilon(epsilon));
    REQUIRE(p.g == Approx(expected_g).epsilon(epsilon));
    REQUIRE(p.b == Approx(expected_b).epsilon(epsilon));
}

TEST_CASE("edge_filter_main test", "[edge]") {
    // Создаем изображение 3x3
    constexpr int ImageWidth = 3;
    constexpr int ImageHeight = 3;
    Image img(ImageWidth, ImageHeight);

    // Заполняем изображение черным
    for (int y = 0; y < ImageHeight; ++y) {
        for (int x = 0; x < ImageWidth; ++x) {
            img.GetPixel(x, y) = {0.0, 0.0, 0.0};
        }
    }

    // Устанавливаем центральный пиксель в белый
    img.GetPixel(1, 1) = {1.0, 1.0, 1.0};

    // Создаем фильтр с порогом 0.5
    constexpr double ThresholdValue = 0.5;
    EdgeFilter edge_filter_main(ThresholdValue);
    edge_filter_main.Apply(img);

    for (int y = 0; y < ImageHeight; ++y) {
        for (int x = 0; x < ImageWidth; ++x) {
            if (x == 1 && y == 1) {
                RequirePixelApprox(img.GetPixel(x, y), 1.0, 1.0, 1.0);
            } else {
                RequirePixelApprox(img.GetPixel(x, y), 0.0, 0.0, 0.0);
            }
        }
    }
}
