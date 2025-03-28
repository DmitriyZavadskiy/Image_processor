#include "neg.h"

void NegativeFilter::Apply(Image &image) {
    for (int y = 0; y < image.Height(); ++y) {
        for (int x = 0; x < image.Width(); ++x) {
            auto &p = image.GetPixel(x, y);
            p.r = 1.0 - p.r;
            p.g = 1.0 - p.g;
            p.b = 1.0 - p.b;
        }
    }
}
