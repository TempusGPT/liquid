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

template <typename... TArgs>
std::string f(const std::string &fmt, const TArgs &...args) {
    auto result = fmt;
    auto index = 0;

    for (const auto &value : {args...}) {
        auto placeholder = "{" + std::to_string(index) + "}";
        replaceAll(result, placeholder, std::to_string(value));
        index += 1;
    }

    return result;
}

#endif