#include "walls.hpp"
#include "libs/random.hpp"
#include "libs/range.hpp"

#include <vector>

using namespace liquid;

auto Walls(
    const Prop<std::unordered_set<Vector>>& wallPositions,
    const Prop<std::unordered_set<Vector>>& immuneWallPositions,
    const Prop<Color>& wallColor,
    const Prop<Color>& gateColor,
    Ref<WallsRef>& ref
) -> Element {
    auto createGate = [=]() {
        auto index = random(0, wallPositions->size() - 1);
        auto iterator = wallPositions->begin();
        std::advance(iterator, index);
        return *iterator;
    };

    auto blueGate = createGate();
    auto orangeGate = createGate();
    while (blueGate == orangeGate) {
        orangeGate = createGate();
    }

    auto isOverlap = [=](const Vector& pos) -> bool {
        return (
            wallPositions->find(pos) != wallPositions->end() ||
            immuneWallPositions->find(pos) != immuneWallPositions->end()
        );
    };

    auto getGate = [=](const Transform& transform) -> std::optional<Transform> {
        auto wallExists = [=](const Vector& pos) {
            return isOverlap(pos) || pos.x < -1 || pos.x > 23 || pos.y < -1 || pos.y > 23;
        };

        auto gateTransform = [=](const Vector& gate) -> Transform {
            if (!wallExists(gate + transform.direction)) {
                return { gate, transform.direction };
            } else if (!wallExists(gate + transform.direction.rotateRight())) {
                return { gate, transform.direction.rotateRight() };
            } else if (!wallExists(gate + transform.direction.rotateLeft())) {
                return { gate, transform.direction.rotateLeft() };
            } else {
                return { gate, transform.direction.rotateRight().rotateRight() };
            }
        };

        if (transform.position == blueGate) {
            return gateTransform(orangeGate);
        } else if (transform.position == orangeGate) {
            return gateTransform(blueGate);
        } else {
            return std::nullopt;
        }
    };

    *ref = { isOverlap, getGate };

    return Group({
        EACH(*immuneWallPositions, pos, _) {
            Cursor(pos.x * 2, pos.y),
            Text("■", wallColor),
        } END_EACH,

        EACH(*wallPositions, pos, _) {
            Cursor(pos.x * 2, pos.y),

            WHEN(pos == blueGate || pos == orangeGate) {
                Text("■", gateColor),
            } OTHERWISE {
                Text("■", wallColor),
            } END_WHEN,
        } END_EACH,
    });
}
