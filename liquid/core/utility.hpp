#ifndef LIQUID_UTILITY_HPP
#define LIQUID_UTILITY_HPP

#include <iostream>
#include <sstream>
#include <string>

namespace std {
    std::string to_string(const std::string &value) {
        return value;
    }
}

namespace Liquid {
    void replaceAll(std::string &str, const std::string &oldValue, const std::string &newValue) {
        if (oldValue.empty()) {
            return;
        }

        auto pos = str.find(oldValue, 0);
        while (pos != std::string::npos) {
            str.replace(pos, oldValue.length(), newValue);
            pos += newValue.length();
            pos = str.find(oldValue, pos);
        }
    }

    void formatString(std::string &str, int index) {}

    template <typename T, typename... TArgs>
    void formatString(std::string &str, int index, const T &value, const TArgs &...args) {
        auto oldValue = "{" + std::to_string(index) + "}";
        auto newValue = (std::ostringstream() << value).str();
        replaceAll(str, oldValue, newValue);
        formatString(str, index + 1, args...);
    }
}

template <typename... TArgs>
std::string f(const std::string &fmt, const TArgs &...args) {
    auto result = fmt;
    Liquid::formatString(result, 0, args...);
    return result;
}

#endif