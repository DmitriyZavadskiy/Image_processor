#include "registry.h"
#include <cstddef>
#include <stdexcept>

#include "crop.h"
#include "filters/affine_tile.h"
#include "grayscale.h"
#include "neg.h"
#include "sharpen.h"
#include "edge.h"
#include "blur.h"

namespace {
constexpr size_t CropMinParams = 2;
constexpr size_t AffinetileMinParams = 6;
constexpr size_t FifthParam = 5;
}  // namespace

FilterRegistry &FilterRegistry::Instance() {
    static FilterRegistry instance;
    return instance;
}

void FilterRegistry::Register(const std::string &name, FilterCreator creator) {
    creators_[name] = creator;
}

std::unique_ptr<Filter> FilterRegistry::CreateFilter(const std::string &name, const std::vector<std::string> &params) {
    auto it = creators_.find(name);
    if (it == creators_.end()) {
        return nullptr;
    }
    return it->second(params);
}

void RegisterAllFilters() {

    FilterRegistry::Instance().Register("crop", [](const std::vector<std::string> &p) -> std::unique_ptr<Filter> {
        if (p.size() < CropMinParams) {
            throw std::runtime_error("Not enough params for crop");
        }
        int w = std::stoi(p[0]);
        int h = std::stoi(p[1]);
        return std::make_unique<CropFilter>(w, h);
    });

    FilterRegistry::Instance().Register("gs", [](const std::vector<std::string> &p) -> std::unique_ptr<Filter> {
        return std::make_unique<GrayScaleFilter>();
    });

    FilterRegistry::Instance().Register("neg", [](const std::vector<std::string> &p) -> std::unique_ptr<Filter> {
        return std::make_unique<NegativeFilter>();
    });

    FilterRegistry::Instance().Register("sharp", [](const std::vector<std::string> &p) -> std::unique_ptr<Filter> {
        return std::make_unique<SharpenFilter>();
    });

    FilterRegistry::Instance().Register("edge", [](const std::vector<std::string> &p) -> std::unique_ptr<Filter> {
        if (p.empty()) {
            throw std::runtime_error("Not enough params for edge");
        }
        double th = std::stod(p[0]);
        return std::make_unique<EdgeFilter>(th);
    });

    FilterRegistry::Instance().Register("blur", [](const std::vector<std::string> &p) -> std::unique_ptr<Filter> {
        if (p.empty()) {
            throw std::runtime_error("Not enough params for blur");
        }
        double sigma = std::stod(p[0]);
        return std::make_unique<BlurFilter>(sigma);
    });

    FilterRegistry::Instance().Register("affinetile", [](const std::vector<std::string> &p) -> std::unique_ptr<Filter> {
        // пример для вызова:
        // ./image_processor.exe ../test_script/data/lenna.bmp ../tmp/out.bmp  -affinetile 0.2 0 0 0.2 0 0
        if (p.size() < AffinetileMinParams) {
            throw std::runtime_error("Not enough params for affinetile");
        }
        double a = std::stod(p[0]);
        double b = std::stod(p[1]);
        double c = std::stod(p[2]);
        double d = std::stod(p[3]);
        double tx = std::stod(p[4]);
        double ty = std::stod(p[FifthParam]);
        return std::make_unique<AffineTileFilter>(a, b, c, d, tx, ty);
    });
}
