#include "include/format.hpp"

#include <iostream>

namespace Liquid {
    StringFormatter::StringFormatter(const std::string& fmt) : fmt(fmt) {}

    StringFormatter::operator std::string() const {
        return fmt;
    }

    auto operator"" _f(const char* fmt, size_t) -> StringFormatter {
        return StringFormatter(fmt);
    }
}
