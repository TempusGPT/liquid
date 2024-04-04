#ifndef LIQUID_COMPONENT_HPP
#define LIQUID_COMPONENT_HPP

#include "element.hpp"
#include "prop.hpp"

namespace liquid {
    auto Goto(const Prop<int>& x, const Prop<int>& y) -> Element;
    auto Group(const Prop<std::vector<Element>>& elements) -> Element;

    auto Text(
        const Prop<std::string>& value,
        const Prop<Color>& foreground = Color::White,
        const Prop<Color>& background = Color::Black
    ) -> Element;
}

#endif
