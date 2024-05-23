#ifndef LIBS_COMPONENTS_ROUTER_HPP
#define LIBS_COMPONENTS_ROUTER_HPP

#include "liquid.hpp"

#include <functional>
#include <string>
#include <unordered_map>

using namespace liquid;
using namespace std::string_literals;

namespace router {
    auto location = State("/"s);
}

auto location() -> std::string {
    return *router::location;
};

auto navigate(const std::string& location) -> void {
    router::location = location;
};

auto Router(const std::unordered_map<std::string, std::function<Element()>>& routes) -> Element {
    return WHEN(routes.find(location()) != routes.end()) {
        routes.at(location())(),
    } END_WHEN;
}

#endif
