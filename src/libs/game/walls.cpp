#include "walls.hpp"
#include "libs/random.hpp"

#include <vector>

using namespace liquid;

auto Walls(
    const Prop<Vector>& fieldSize,
    const Prop<std::unordered_set<Vector>>& wallPositions,
    const Prop<std::unordered_set<Vector>>& immuneWallPositions,
    const Prop<Color>& wallColor,
    const Prop<Color>& gateColor,
    const Prop<Color>& exitColor,
    const Prop<bool>& exitGateOpen,
    Ref<WallsRef>& ref
) -> Element {
    auto createGate = [=]() {
        auto index = random(0, wallPositions->size() - 1);
        auto iterator = wallPositions->begin();
        std::advance(iterator, index);
        return *iterator;
    };

    auto exitGate = createGate();

    auto blueGate = createGate();
    while (blueGate == exitGate) {
        blueGate = createGate();
    }

    auto orangeGate = createGate();
    while (orangeGate == exitGate || orangeGate == blueGate) {
        orangeGate = createGate();
    }

    auto isExit = [=](const Vector& pos) -> bool {
        return pos == exitGate;
    };

    auto isOverlap = [=](const Vector& pos) -> bool {
        return (
            wallPositions->find(pos) != wallPositions->end() ||
            immuneWallPositions->find(pos) != immuneWallPositions->end()
        );
    };

    auto getGate = [=](const Transform& transform) -> std::optional<Transform> {
        auto canExitTo = [=](const Vector& pos) {
            return (
                !isOverlap(pos) &&
                pos.x >= 0 &&
                pos.x < fieldSize->x &&
                pos.y >= 0 &&
                pos.y < fieldSize->y
            );
        };

        auto gateTransform = [=](const Vector& gate) -> Transform {
            if (canExitTo(gate + transform.direction)) {
                return { gate, transform.direction };
            } else if (canExitTo(gate + transform.direction.rotateRight())) {
                return { gate, transform.direction.rotateRight() };
            } else if (canExitTo(gate + transform.direction.rotateLeft())) {
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

    *ref = { isExit, isOverlap, getGate };

    return Group({
        EACH(*immuneWallPositions, pos, _) {
            Cursor(pos.x * 2, pos.y),
            Text("■", wallColor),
        } END_EACH,

        EACH(*wallPositions, pos, _) {
            Cursor(pos.x * 2, pos.y),

            WHEN(*exitGateOpen && pos == exitGate) {
                Text("■", exitColor),
            } OR(pos == blueGate || pos == orangeGate) {
                Text("■", gateColor),
            } OTHERWISE {
                Text("■", wallColor),
            } END_WHEN,
        } END_EACH,
    });
}
