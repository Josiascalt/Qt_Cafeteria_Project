#ifndef TYPE_ALIASES_H
#define TYPE_ALIASES_H
#pragma once

#include <memory>
#include <chrono>

#include "domain.h"

namespace cafeteria_app {
    namespace type_aliases {
        using Size = size_t;
        using Index = size_t;
        using TimePoint = std::time_t;

        using UserPtr = std::unique_ptr<domain::users::User>;                           
    } // namespace type_aliases
} // namespace cafeteria_app

#endif //TYPE_ALIASES_H