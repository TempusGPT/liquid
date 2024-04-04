#ifndef LIBS_ROUTER_HPP
#define LIBS_ROUTER_HPP

#include "liquid.hpp"

#include <string>
#include <tuple>

using namespace liquid;

namespace router {
    auto currentPath = Signal("/");
}

auto path() -> std::string {
    return router::currentPath();
};

auto navigate(const std::string& newPath) -> void {
    router::currentPath.set(newPath);
};

auto Route(
    const Prop<std::string>& path,
    const Prop<std::function<Element()>>& component
) -> Element {
    return WHEN(path() == ::path()) {
        component()(),
    } END_WHEN;
}

#endif
