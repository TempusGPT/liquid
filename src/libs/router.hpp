#ifndef LIBS_ROUTER_HPP
#define LIBS_ROUTER_HPP

#include "liquid.hpp"

#include <functional>
#include <string>
#include <unordered_map>

using namespace liquid;

namespace router {
    auto location = State<std::string>("/");
}

auto location() -> std::string {
    return *router::location;
};

auto navigate(const std::string& newLocation) -> void {
    router::location = newLocation;
};

auto Router(const std::unordered_map<std::string, std::function<Element()>>& routes) -> Element {
    return WHEN(routes.find(location()) != routes.end()) {
        routes.at(location())(),
    } END_WHEN;
}

#endif
