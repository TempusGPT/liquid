#include "router.hpp"

using namespace liquid;
using namespace std::string_literals;

static auto locationValue = State("/"s);

auto location() -> std::string {
    return *locationValue;
};

auto navigate(const std::string& location) -> void {
    locationValue = location;
};

auto Router(const std::unordered_map<std::string, std::function<Element()>>& routes) -> Element {
    return WHEN(routes.find(location()) != routes.end()) {
        routes.at(location())(),
    } END_WHEN;
}
