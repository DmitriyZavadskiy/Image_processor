#include "dumper.h"
#include "../image/format.h"
#include <fstream>
#include <stdexcept>
#include <vector>
#include <algorithm>

namespace bmp_const {
constexpr uint16_t SIGNATURE = 0x4D42;
constexpr int BitsPerPixel = 24;
constexpr int PixelComponents = 3;
constexpr int ALIGNMENT = 4;
constexpr double MaxColorValue = 255.0;
}  // namespace bmp_const

void SaveBMP(const Image &image, const std::string &filename) {
    std::ofstream out(filename, std::ios::binary);
    if (!out) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    int32_t width = image.Width();
    int32_t height = image.Height();

    int row_size =
        ((width * bmp_const::PixelComponents + bmp_const::ALIGNMENT - 1) / bmp_const::ALIGNMENT) * bmp_const::ALIGNMENT;
    int data_size = row_size * height;

    BMPFileHeader file_header{};
    BMPInfoHeader info_header{};

    file_header.bfType = bmp_const::SIGNATURE;
    file_header.bfSize = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + data_size;
    file_header.bfOffBits = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);

    info_header.biSize = sizeof(BMPInfoHeader);
    info_header.biWidth = width;
    info_header.biHeight = height;
    info_header.biPlanes = 1;
    info_header.biBitCount = bmp_const::BitsPerPixel;
    info_header.biCompression = 0;
    info_header.biSizeImage = data_size;

    out.write(reinterpret_cast<const char *>(&file_header), sizeof(file_header));
    out.write(reinterpret_cast<const char *>(&info_header), sizeof(info_header));

    std::vector<uint8_t> row_buffer(row_size);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            auto pix = image.GetPixel(x, height - 1 - y);
            uint8_t r = static_cast<uint8_t>(std::clamp(pix.r, 0.0, 1.0) * bmp_const::MaxColorValue);
            uint8_t g = static_cast<uint8_t>(std::clamp(pix.g, 0.0, 1.0) * bmp_const::MaxColorValue);
            uint8_t b = static_cast<uint8_t>(std::clamp(pix.b, 0.0, 1.0) * bmp_const::MaxColorValue);

            row_buffer[x * bmp_const::PixelComponents + 0] = b;
            row_buffer[x * bmp_const::PixelComponents + 1] = g;
            row_buffer[x * bmp_const::PixelComponents + 2] = r;
        }

        for (int i = width * bmp_const::PixelComponents; i < row_size; ++i) {
            row_buffer[i] = 0;
        }

        out.write(reinterpret_cast<const char *>(row_buffer.data()), static_cast<std::streamsize>(row_buffer.size()));
    }
}
