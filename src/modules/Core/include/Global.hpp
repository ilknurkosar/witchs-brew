#pragma once

#include "Resource.hpp"
#include <memory>
#include <vector>
namespace Global {
    extern std::vector<std::unique_ptr<Resource>> resources;
    extern bool showStats;
}