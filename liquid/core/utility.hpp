#ifndef LIQUID_UTILITY_HPP
#define LIQUID_UTILITY_HPP

#include <iostream>
#include <sstream>
#include <string>

namespace Liquid {
    void replaceAll(std::string &str, const std::string &oldValue, const std::string &newValue) {
        auto pos = 0;
        while (std::string::npos != (pos = str.find(oldValue, pos))) {
            str.replace(pos, oldValue.length(), newValue);
            pos += newValue.length();
        }
    }

    void formatString(std::string &fmt, int index) {}

    template <typename T, typename... TArgs>
    void formatString(std::string &fmt, int index, const T &value, const TArgs &...args) {
        auto oldValue = "{" + std::to_string(index) + "}";
        auto newValue = (std::ostringstream() << value).str();
        replaceAll(fmt, oldValue, newValue);
        formatString(fmt, index + 1, args...);
    }
}

template <typename... TArgs>
std::string f(const std::string &fmt, const TArgs &...args) {
    auto mutableFmt = fmt;
    Liquid::formatString(mutableFmt, 0, args...);
    return mutableFmt;
}

#endif
