#pragma once
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <functional>
#include "filter.h"

using FilterCreator = std::function<std::unique_ptr<Filter>(const std::vector<std::string> &)>;

class FilterRegistry {
public:
    static FilterRegistry &Instance();

    void Register(const std::string &name, FilterCreator creator);

    std::unique_ptr<Filter> CreateFilter(const std::string &name, const std::vector<std::string> &params);

private:
    FilterRegistry() = default;
    std::map<std::string, FilterCreator> creators_;
};

void RegisterAllFilters();
