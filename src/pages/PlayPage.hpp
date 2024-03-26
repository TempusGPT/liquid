#ifndef PAGES_PLAYPAGE_HPP
#define PAGES_PLAYPAGE_HPP

#include "components/Snake.hpp"
#include "liquid.hpp"

using namespace Liquid;

auto PlayPage() -> Element {
    return Group({
        Snake(4, { 20, 20 }),
    });
}

#endif
