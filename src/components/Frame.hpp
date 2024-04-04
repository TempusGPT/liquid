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
        EACH(Range(0, size().x), x, _) {
            Goto(x * 2, 0),
            Text(RP(ch()), foreground, background),
            Goto(x * 2, RP(size().y - 1)),
            Text(RP(ch()), foreground, background),
        } END_EACH,

        EACH(Range(0, size().y), y, _) {
            Goto(0, y),
            Text(RP(ch()), foreground, background),
            Goto(RP((size().x - 1) * 2), y),
            Text(RP(ch()), foreground, background),
        } END_EACH,
    });
}

#endif
