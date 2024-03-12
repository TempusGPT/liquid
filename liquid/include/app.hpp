#ifndef LIQUID_APP_HPP
#define LIQUID_APP_HPP

#include "component.hpp"

#include <string>

Element Route(const std::string &path, const Component<> &component);

void navigate(const std::string &path);
void exitApp();
void playBeep();
int render(const Element &element);

namespace Liquid {
    void markDirty();
}

#endif
