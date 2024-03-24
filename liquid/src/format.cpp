#include "include/format.hpp"

#include <iostream>

namespace Liquid {
    StringFormatter::StringFormatter(const std::string &fmt) : fmt(fmt) {}

    StringFormatter::operator std::string() const {
        return fmt;
    }

    StringFormatter operator"" _f(const char *fmt, size_t) {
        return StringFormatter(fmt);
    }
}
