#include "walls.hpp"
#include "libs/random.hpp"
#include "libs/range.hpp"

#include <vector>

using namespace liquid;

auto Walls(
    const Prop<Vector>& fieldSize,
    const Prop<Color>& wallColor,
    const Prop<Color>& gateColor,
    Ref<WallsRef>& ref
) -> Element {
    auto positions = std::vector<Vector>();

    for (auto x = 0; x < fieldSize->x; x += 1) {
        positions.push_back(Vector { x, -1 });
        positions.push_back(Vector { x, fieldSize->y });
    }

    for (auto y = 0; y < fieldSize->y; y += 1) {
        positions.push_back(Vector { -1, y });
        positions.push_back(Vector { fieldSize->x, y });
    }

    auto createGate = [=]() -> Gate {
        auto index = random(0, positions.size() - 1);
        auto pos = positions[index];

        if (pos.x == -1) {
            return { pos, Vector::right() };
        } else if (pos.x == fieldSize->x) {
            return { pos, Vector::left() };
        } else if (pos.y == -1) {
            return { pos, Vector::down() };
        } else {
            return { pos, Vector::up() };
        }
    };

    auto blueGate = createGate();
    auto orangeGate = createGate();
    while (blueGate.position == orangeGate.position) {
        orangeGate = createGate();
    }

    auto getGate = [=](const Vector& pos) -> std::optional<Gate> {
        if (pos == blueGate.position) {
            return orangeGate;
        }

        if (pos == orangeGate.position) {
            return blueGate;
        }

        return std::nullopt;
    };

    *ref = { getGate };

    return Group({
        Cursor(-2, -1),
        Text("■", wallColor),
        Cursor(-2, fieldSize->y),
        Text("■", wallColor),
        Cursor(fieldSize->x * 2, -1),
        Text("■", wallColor),
        Cursor(fieldSize->x * 2, fieldSize->y),
        Text("■", wallColor),

        EACH(positions, pos, _) {
            Cursor(pos.x * 2, pos.y),

            WHEN(pos == blueGate.position || pos == orangeGate.position) {
                Text("■", gateColor),
            } OTHERWISE {
                Text("■", wallColor),
            } END_WHEN,
        } END_EACH,
    });
}
