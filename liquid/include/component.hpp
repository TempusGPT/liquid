#ifndef LIQUID_COMPONENT_HPP
#define LIQUID_COMPONENT_HPP

#include "element.hpp"
#include "prop.hpp"

namespace Liquid {
    auto Goto(const Prop<int>& x, const Prop<int>& y) -> Element;
    auto Group(const Prop<std::vector<Element>>& elements) -> Element;

    auto Route(
        const Prop<std::string>& path,
        const Prop<std::function<Element()>>& component
    ) -> Element;

    auto Text(
        const Prop<std::string>& value,
        const Prop<Color>& foreground = Color::White,
        const Prop<Color>& background = Color::Black
    ) -> Element;
}

#endif
