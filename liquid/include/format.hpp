#ifndef LIQUID_UTILITY_HPP
#define LIQUID_UTILITY_HPP

#include <sstream>
#include <string>

namespace liquid {
    class FmtString {
    public:
        FmtString(const std::string& fmt);
        operator std::string() const;

        template <typename T>
        auto operator%(T&& value) -> FmtString& {
            auto oldValue = '%' + std::to_string(index) + '%';
            auto newValue = (std::ostringstream() << value).str();
            auto pos = 0;

            while (std::string::npos != (pos = fmt.find(oldValue, pos))) {
                fmt.replace(pos, oldValue.length(), newValue);
                pos += newValue.length();
            }

            index += 1;
            return *this;
        }

    private:
        int index = 0;
        std::string fmt;
    };

    auto operator""_fmt(const char* fmt, size_t) -> FmtString;
}

#endif
