#ifndef LIQUID_APP_HPP
#define LIQUID_APP_HPP

#include "component.hpp"

#include <string>

namespace Liquid {
    Element Route(const std::string &path, const Component<> &component);
    int render(const Element &element);

    void navigate(const std::string &path);
    void exitApp();
    void playBeep();

    namespace Internal {
        void markDirty();
    }
}

#endif
