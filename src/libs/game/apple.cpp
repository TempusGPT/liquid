#include "apple.hpp"
#include "libs/random.hpp"

using namespace liquid;

auto Apple(
    Ref<AppleRef>& ref,
    const Prop<Vector>& fieldSize,
    const Prop<Color>& color
) -> Element {
    auto position = State<Vector>({ fieldSize->x / 2, fieldSize->y / 2 });

    auto refresh = [=]() mutable {
        position = {
            random(0, fieldSize->x - 1),
            random(0, fieldSize->y - 1),
        };
    };

    *ref = { GET(*position), refresh };

    return Group({
        Cursor(GET(position->x * 2), GET(position->y)),
        Text("●", color),
    });
}
