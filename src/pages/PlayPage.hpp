#ifndef PAGES_PLAYPAGE_HPP
#define PAGES_PLAYPAGE_HPP

#include "components/Snake.hpp"
#include "liquid.hpp"

using namespace Liquid;

Element PlayPage() {
    return Group({
        Snake(20, 20),
    });
}

#endif
