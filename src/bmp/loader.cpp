#include "loader.h"
#include "../image/format.h"
#include <fstream>
#include <stdexcept>
#include <vector>

namespace bmp_constants {
constexpr uint16_t SIGNATURE = 0x4D42;
constexpr int BItsPerPixel = 24;
constexpr int PixelComponents = 3;
constexpr int ALIGNMENT = 4;
constexpr double MaxColorValue = 255.0;
}  // namespace bmp_constants

Image LoadBMP(const std::string &filename) {
    std::ifstream in(filename, std::ios::binary);
    if (!in) {
        throw std::runtime_error("Cannot open input file: " + filename);
    }

    BMPFileHeader file_header;
    BMPInfoHeader info_header;

    in.read(reinterpret_cast<char *>(&file_header), sizeof(file_header));
    in.read(reinterpret_cast<char *>(&info_header), sizeof(info_header));

    if (file_header.bfType != bmp_constants::SIGNATURE) {
        throw std::runtime_error("Not a BMP file.");
    }
    if (info_header.biBitCount != bmp_constants::BItsPerPixel || info_header.biCompression != 0) {
        throw std::runtime_error("Unsupported BMP format (must be 24-bit).");
    }

    in.seekg(file_header.bfOffBits, std::ios::beg);

    int32_t width = info_header.biWidth;
    int32_t height = info_header.biHeight;

    Image image(width, height);

    int row_size =
        ((width * bmp_constants::PixelComponents + bmp_constants::ALIGNMENT - 1) / bmp_constants::ALIGNMENT) *
        bmp_constants::ALIGNMENT;

    std::vector<uint8_t> row_buffer(row_size);

    for (int y = 0; y < height; ++y) {
        in.read(reinterpret_cast<char *>(row_buffer.data()), static_cast<std::streamsize>(row_buffer.size()));
        for (int x = 0; x < width; ++x) {
            uint8_t b = row_buffer[x * bmp_constants::PixelComponents + 0];
            uint8_t g = row_buffer[x * bmp_constants::PixelComponents + 1];
            uint8_t r = row_buffer[x * bmp_constants::PixelComponents + 2];

            image.GetPixel(x, height - 1 - y) = {static_cast<double>(r) / bmp_constants::MaxColorValue,
                                                 static_cast<double>(g) / bmp_constants::MaxColorValue,
                                                 static_cast<double>(b) / bmp_constants::MaxColorValue};
        }
    }

    return image;
}
