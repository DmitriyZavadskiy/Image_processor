#include "crop.h"
#include <algorithm>

void CropFilter::Apply(Image &image) {
    int new_w = std::min(width_, image.Width());
    int new_h = std::min(height_, image.Height());

    Image temp(new_w, new_h);
    for (int y = 0; y < new_h; ++y) {
        for (int x = 0; x < new_w; ++x) {
            temp.GetPixel(x, y) = image.GetPixel(x, y);
        }
    }
    image = std::move(temp);
}
