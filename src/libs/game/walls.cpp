#include "walls.hpp"
#include "libs/random.hpp"
#include "libs/range.hpp"

#include <array>
#include <vector>

using namespace liquid;

auto Walls(const Prop<Vector>& fieldSize, const Prop<Color>& color, Ref<WallsRef>& ref) -> Element {
    auto positions = std::vector<Vector>();

    for (auto x = -1; x <= fieldSize->x; x += 1) {
        positions.push_back(Vector { x, -1 });
        positions.push_back(Vector { x, fieldSize->y });
    }

    for (auto y = -1; y <= fieldSize->y; y += 1) {
        positions.push_back(Vector { -1, y });
        positions.push_back(Vector { fieldSize->x, y });
    }

    auto calculateGate = [=]() {
        auto pos = positions[random(0, positions.size() - 1)];

        while (
            pos.x == -1 && pos.y == -1 ||
            pos.x == fieldSize->x && pos.y == -1 ||
            pos.x == fieldSize->x && pos.y == fieldSize->y ||
            pos.x == -1 && pos.y == fieldSize->y
        ) {
            pos = positions[random(0, positions.size() - 1)];
        }

        if (pos.x == -1) {
            return Gate { pos, Vector::right() };
        } else if (pos.x == fieldSize->x) {
            return Gate { pos, Vector::left() };
        } else if (pos.y == -1) {
            return Gate { pos, Vector::down() };
        } else {
            return Gate { pos, Vector::up() };
        }
    };

    auto gates = std::array<Gate, 2>();
    gates[0] = calculateGate();
    gates[1] = calculateGate();

    while (gates[0].position == gates[1].position) {
        gates[1] = calculateGate();
    }

    auto gate = [=](const Vector& pos) -> std::optional<Gate> {
        if (pos == gates[0].position) {
            return gates[1];
        }

        if (pos == gates[1].position) {
            return gates[0];
        }

        return std::nullopt;
    };

    *ref = { gate };

    return Group({
        EACH(positions, pos, _) {
            Cursor(pos.x * 2, pos.y),
            WHEN(pos != gates[0].position && pos != gates[1].position) {
                Text("■", color),
            } END_WHEN,
        } END_EACH,
    });
}
