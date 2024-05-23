#include "walls.hpp"
#include "libs/random.hpp"
#include "libs/range.hpp"

#include <array>
#include <vector>

using namespace liquid;

auto Walls(const Prop<Vector>& size, const Prop<Color>& color) -> Element {
    auto positions = std::vector<Vector>();

    for (auto x : Range(0, size->x)) {
        positions.push_back(Vector { x, 0 });
        positions.push_back(Vector { x, size->y - 1 });
    }

    for (auto y : Range(0, size->y)) {
        positions.push_back(Vector { 0, y });
        positions.push_back(Vector { size->x - 1, y });
    }

    auto calculateGatePosition = [=]() {
        auto pos = positions[random(0, positions.size() - 1)];

        while (
            pos.x == 0 && pos.y == 0 ||
            pos.x == size->x - 1 && pos.y == 0 ||
            pos.x == size->x - 1 && pos.y == size->y - 1 ||
            pos.x == 0 && pos.y == size->y - 1
        ) {
            pos = positions[random(0, positions.size() - 1)];
        }

        return pos;
    };

    auto gatePositions = std::array<Vector, 2>();
    gatePositions[0] = calculateGatePosition();
    gatePositions[1] = calculateGatePosition();

    while (gatePositions[0] == gatePositions[1]) {
        gatePositions[1] = calculateGatePosition();
    }

    return EACH(positions, pos, _) {
        Cursor(pos.x * 2, pos.y),
        WHEN(pos != gatePositions[0] && pos != gatePositions[1]) {
            Text("■", color),
        } END_WHEN,
    } END_EACH;
}
