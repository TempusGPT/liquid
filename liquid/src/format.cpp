#include "include/format.hpp"

#include <iostream>

namespace liquid {
    FmtString::FmtString(const std::string& fmt) : fmt(fmt) {}

    FmtString::operator std::string() const {
        return fmt;
    }

    auto operator""_f(const char* fmt, size_t) -> FmtString {
        return FmtString(fmt);
    }
}
