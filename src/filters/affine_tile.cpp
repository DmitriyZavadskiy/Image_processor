#include "affine_tile.h"
#include "../image/image.h"
#include <cmath>

namespace affine_tile_constants {
constexpr double DetThreshold = 1e-12;
constexpr double RoundingOffset = 0.5;
}  // namespace affine_tile_constants

static int WrapCoord(int x, int max_size) {
    int r = x % max_size;
    if (r < 0) {
        r += max_size;
    }
    return r;
}

AffineTileFilter::AffineTileFilter(double a, double b, double c, double d, double tx, double ty)
    : a_(a), b_(b), c_(c), d_(d), tx_(tx), ty_(ty) {
}

void AffineTileFilter::Apply(Image &image) {
    double det = a_ * d_ - b_ * c_;
    if (std::fabs(det) < affine_tile_constants::DetThreshold) {
        return;
    }
    double inv_det = 1.0 / det;

    double a = d_ * inv_det;
    double b = -b_ * inv_det;
    double c = -c_ * inv_det;
    double d = a_ * inv_det;
    double tx = (b_ * ty_ - d_ * tx_) * inv_det;
    double ty = (c_ * tx_ - a_ * ty_) * inv_det;

    int w = image.Width();
    int h = image.Height();

    Image copy = image;

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            double u = a * x + b * y + tx;
            double v = c * x + d * y + ty;

            int uu = static_cast<int>(std::floor(u + affine_tile_constants::RoundingOffset));
            int vv = static_cast<int>(std::floor(v + affine_tile_constants::RoundingOffset));

            uu = WrapCoord(uu, w);
            vv = WrapCoord(vv, h);

            image.GetPixel(x, y) = copy.GetPixel(uu, vv);
        }
    }
}
