#include "include/format.hpp"

#include <iostream>

namespace Liquid {
    FmtString::FmtString(const std::string& fmt) : fmt(fmt) {}

    FmtString::operator std::string() const {
        return fmt;
    }

    auto operator"" _fmt(const char* fmt, size_t) -> FmtString {
        return FmtString(fmt);
    }
}
