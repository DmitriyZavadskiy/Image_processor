#include "matrix_filter.h"
#include "../image/image.h"
#include <algorithm>
#include <cmath>

static int ClampCoord(int v, int minv, int maxv) {
    return std::max(minv, std::min(v, maxv));
}

static inline double Clamp01(double x) {
    return std::max(0.0, std::min(x, 1.0));
}

MatrixFilter::MatrixFilter(const std::vector<double> &kernel, int kernel_size, bool clamp)
    : kernel_(kernel), kernel_size_(kernel_size), clamp_values_(clamp) {
}

void MatrixFilter::Apply(Image &image) {
    PreProcess(image);

    Image copy = image;
    int half = kernel_size_ / 2;

    for (int y = 0; y < image.Height(); ++y) {
        for (int x = 0; x < image.Width(); ++x) {
            double sum_r = 0;
            double sum_g = 0;
            double sum_b = 0;
            for (int ky = 0; ky < kernel_size_; ky++) {
                for (int kx = 0; kx < kernel_size_; kx++) {
                    int xx = ClampCoord(x + (kx - half), 0, image.Width() - 1);
                    int yy = ClampCoord(y + (ky - half), 0, image.Height() - 1);
                    double w = kernel_[ky * kernel_size_ + kx];
                    auto pix = copy.GetPixel(xx, yy);
                    sum_r += pix.r * w;
                    sum_g += pix.g * w;
                    sum_b += pix.b * w;
                }
            }
            if (clamp_values_) {
                sum_r = Clamp01(sum_r);
                sum_g = Clamp01(sum_g);
                sum_b = Clamp01(sum_b);
            }
            auto &out = image.GetPixel(x, y);
            out.r = sum_r;
            out.g = sum_g;
            out.b = sum_b;
        }
    }

    PostProcess(image);
}
