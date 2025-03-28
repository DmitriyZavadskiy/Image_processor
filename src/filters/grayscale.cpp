#include "grayscale.h"

namespace gray_scale_constants {
constexpr double LuminanceR = 0.299;
constexpr double LuminanceG = 0.587;
constexpr double LuminanceB = 0.114;
}  // namespace gray_scale_constants

void GrayScaleFilter::Apply(Image &image) {
    for (int y = 0; y < image.Height(); ++y) {
        for (int x = 0; x < image.Width(); ++x) {
            auto &pix = image.GetPixel(x, y);
            double gray = gray_scale_constants::LuminanceR * pix.r + gray_scale_constants::LuminanceG * pix.g +
                          gray_scale_constants::LuminanceB * pix.b;
            pix.r = pix.g = pix.b = gray;
        }
    }
}
