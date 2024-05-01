#ifndef COMPONENTS_FRAME_HPP
#define COMPONENTS_FRAME_HPP

#include "libs/range.hpp"
#include "libs/vector.hpp"
#include "liquid.hpp"

using namespace liquid;

auto Frame(
    const Prop<std::string>& ch,
    const Prop<Vector>& size,
    Color foreground = Color::White,
    Color background = Color::Black
) -> Element {
    return Group({
        EACH(Range(0, size->x), x, _) {
            Cursor(x * 2, 0),
            Text(GET(*ch), foreground, background),
            Cursor(x * 2, GET(size->y - 1)),
            Text(GET(*ch), foreground, background),
        } END_EACH,

        EACH(Range(0, size->y), y, _) {
            Cursor(0, y),
            Text(GET(*ch), foreground, background),
            Cursor(GET((size->x - 1) * 2), y),
            Text(GET(*ch), foreground, background),
        } END_EACH,
    });
}

#endif
