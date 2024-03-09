#include "include/utility.hpp"

#include <iostream>

namespace Liquid {
    void replaceAll(std::string &str, const std::string &oldValue, const std::string &newValue) {
        auto pos = 0;
        while (std::string::npos != (pos = str.find(oldValue, pos))) {
            str.replace(pos, oldValue.length(), newValue);
            pos += newValue.length();
        }
    }

    void formatString(std::string &fmt, int index) {}
}