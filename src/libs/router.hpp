#ifndef LIBS_ROUTER_HPP
#define LIBS_ROUTER_HPP

#include "liquid.hpp"

#include <string>
#include <tuple>

using namespace Liquid;

class Router {
public:
    auto path() const -> std::string {
        return currentPath();
    };

    auto navigate(const std::string& newPath) -> void {
        currentPath.set(newPath);
    };

private:
    static inline auto currentPath = createSignal("/");
};

auto useRouter() -> Router {
    return Router();
}

auto Route(
    const Prop<std::string>& path,
    const Prop<std::function<Element()>>& component
) -> Element {
    auto router = useRouter();

    return WHEN(path() == router.path()) {
        component()(),
    } END_WHEN;
}

#endif
