#ifndef LIQUID_APP_HPP
#define LIQUID_APP_HPP

#include "element.hpp"

#include <string>

namespace Liquid {
    int render(const Element &element);

    std::string path();
    void navigate(const std::string &path);
    void exit();
    void beep();

    namespace Internal {
        void markDirty();
    }
}

#endif
