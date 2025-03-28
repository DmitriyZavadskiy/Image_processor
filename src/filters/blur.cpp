#include "blur.h"
#include <cmath>
#include <vector>

namespace blur_constants {
constexpr double SigmaMultiplier = 3.0;
constexpr double GausDenominatorFactor = 2.0;
constexpr int KernelSizeFactor = 2;
constexpr int KernelSizeOffset = 1;
}  // namespace blur_constants

BlurFilter::BlurFilter(double sigma) : MatrixFilter({}, 0, false) {
    int radius = static_cast<int>(std::ceil(blur_constants::SigmaMultiplier * sigma));
    int size = blur_constants::KernelSizeFactor * radius + blur_constants::KernelSizeOffset;
    kernel_size_ = size;
    kernel_.resize(size * size);

    double sum = 0;
    for (int j = 0; j < size; ++j) {
        for (int i = 0; i < size; ++i) {
            int dx = i - radius;
            int dy = j - radius;
            double exponent = -(dx * dx + dy * dy) / (blur_constants::GausDenominatorFactor * sigma * sigma);
            double val = std::exp(exponent);
            kernel_[j * size + i] = val;
            sum += val;
        }
    }
    for (double &v : kernel_) {
        v /= sum;
    }

    clamp_values_ = true;
}
