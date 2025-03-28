#include "sharpen.h"

namespace sharpen_constants {
constexpr int KernelSize = 3;
constexpr int CenterValue = 5;
constexpr int SurroundValue = -1;
constexpr int ZERO = 0;
}  // namespace sharpen_constants

SharpenFilter::SharpenFilter()
    : MatrixFilter({sharpen_constants::ZERO, sharpen_constants::SurroundValue, sharpen_constants::ZERO,
                    sharpen_constants::SurroundValue, sharpen_constants::CenterValue, sharpen_constants::SurroundValue,
                    sharpen_constants::ZERO, sharpen_constants::SurroundValue, sharpen_constants::ZERO},
                   sharpen_constants::KernelSize, true) {
}
