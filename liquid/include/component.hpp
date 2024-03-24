#ifndef LIQUID_COMPONENT_HPP
#define LIQUID_COMPONENT_HPP

#include "element.hpp"
#include "prop.hpp"

namespace Liquid {
    Element Goto(const Prop<int> &x, const Prop<int> &y);
    Element Group(const Prop<std::vector<Element>> &elements);
    Element Route(const Prop<std::string> &path, const Prop<std::function<Element()>> &component);

    Element Text(
        const Prop<std::string> &value,
        const Prop<Color> &foreground = Color::White,
        const Prop<Color> &background = Color::Black
    );
}

#endif
