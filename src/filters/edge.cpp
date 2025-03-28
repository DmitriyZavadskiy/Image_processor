#include "edge.h"
#include "../filters/grayscale.h"

EdgeFilter::EdgeFilter(double threshold)
    : MatrixFilter({0, -1, 0, -1, 4, -1, 0, -1, 0}, 3, true), threshold_(threshold) {
}

void EdgeFilter::PreProcess(Image &image) {
    GrayScaleFilter gs;
    gs.Apply(image);
}

void EdgeFilter::PostProcess(Image &image) {
    for (int y = 0; y < image.Height(); ++y) {
        for (int x = 0; x < image.Width(); ++x) {
            auto &p = image.GetPixel(x, y);
            double v = (p.r > threshold_) ? 1.0 : 0.0;
            p.r = p.g = p.b = v;
        }
    }
}
