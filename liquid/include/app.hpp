#ifndef LIQUID_APP_HPP
#define LIQUID_APP_HPP

#include "component.hpp"

#include <string>

namespace Liquid {
    void markDirty();
}

Element Route(const Prop<std::string> &path, const Prop<Component<>> &component);

void navigate(const std::string &path);
void exitApp();
void playBeep();
int render(const Element &element);

#endif
