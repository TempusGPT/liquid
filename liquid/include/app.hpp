#ifndef LIQUID_APP_HPP
#define LIQUID_APP_HPP

#include "element.hpp"

#include <string>

namespace Liquid {
    int render(const Element &element);

    std::string pathname();
    void navigate(const std::string &path);
    void exitApp();
    void playBeep();

    namespace Internal {
        void markDirty();
    }
}

#endif
