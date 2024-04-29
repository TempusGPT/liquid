#ifndef LIBS_ROUTER_HPP
#define LIBS_ROUTER_HPP

#include "liquid.hpp"

#include <string>
#include <tuple>

using namespace liquid;

namespace router {
    auto location = State("/");
}

auto location() -> std::string {
    return router::location();
};

auto navigate(const std::string& newLocation) -> void {
    router::location.set(newLocation);
};

auto Router(
    const std::initializer_list<std::pair<std::string, std::function<Element()>>>& routes
) -> Element {
    return EACH(routes, route, _) {
        WHEN(route.first == location()) {
            route.second(),
        } END_WHEN,
    } END_EACH;
}

#endif
