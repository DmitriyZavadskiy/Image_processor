#pragma once
#include "filters/filter.h"

class AffineTileFilter : public Filter {
public:
    AffineTileFilter(double a, double b, double c, double d, double tx, double ty);

    void Apply(Image &image) override;

private:
    double a_;
    double b_;
    double c_;
    double d_;
    double tx_;
    double ty_;
};
