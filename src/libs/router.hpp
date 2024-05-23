#ifndef LIBS_COMPONENTS_ROUTER_HPP
#define LIBS_COMPONENTS_ROUTER_HPP

#include "liquid.hpp"

#include <functional>
#include <string>
#include <unordered_map>

auto location() -> std::string;
auto navigate(const std::string& location) -> void;

auto Router(
    const std::unordered_map<std::string, std::function<liquid::Element()>>& routes
) -> liquid::Element;

#endif
