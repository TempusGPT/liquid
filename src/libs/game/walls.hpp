#ifndef LIBS_GAME_FRAME_HPP
#define LIBS_GAME_FRAME_HPP

#include "libs/range.hpp"
#include "libs/vector.hpp"
#include "liquid.hpp"

using namespace liquid;

auto Walls(
    const Prop<std::string>& ch,
    const Prop<Vector>& size,
    const Prop<Color>& foreground = Color::White,
    const Prop<Color>& background = Color::Black
) -> Element {
    return Group({
        EACH(Range(0, size->x), x, _) {
            Cursor(x * 2, 0),
            Text(ch, foreground, background),
            Cursor(x * 2, GET(size->y - 1)),
            Text(ch, foreground, background),
        } END_EACH,

        EACH(Range(0, size->y), y, _) {
            Cursor(0, y),
            Text(ch, foreground, background),
            Cursor(GET((size->x - 1) * 2), y),
            Text(ch, foreground, background),
        } END_EACH,
    });
}

#endif
