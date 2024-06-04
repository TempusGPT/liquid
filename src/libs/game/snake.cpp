#include "snake.hpp"

#include <list>
#include <queue>
#include <unordered_set>

using namespace liquid;

auto Snake(
    const Prop<std::list<Vector>>& initialPositions,
    const Prop<Color>& color,
    const Prop<std::function<std::optional<Transform>(Transform)>>& onMove,
    const Prop<std::function<void()>>& onDeath,
    Ref<SnakeRef>& ref
) -> Element {
    auto effect = Effect();
    auto direction = State(Vector::right());
    auto directionQueue = Ref<std::queue<Vector>>();
    auto positions = State(*initialPositions);

    auto currentDirection = [=]() mutable {
        if (!directionQueue->empty()) {
            direction = directionQueue->front();
            directionQueue->pop();
        }

        return *direction;
    };

    auto isSuicide = [=]() {
        auto set = std::unordered_set(positions->begin(), positions->end());
        return set.size() != positions->size();
    };

    auto isOverlap = [=](const Vector& other) {
        auto pos = *positions;
        return std::find(pos.begin(), pos.end(), other) != pos.end();
    };

    auto length = [=]() {
        return positions->size();
    };

    auto grow = [=]() mutable {
        positions->push_back(positions->back());
        positions = *positions;
    };

    auto shrink = [=]() mutable {
        positions->pop_back();
        positions = *positions;
    };

    auto changeDirection = [=](const Vector& dir) mutable {
        directionQueue->push(dir);
    };

    *ref = { isOverlap, length, grow, shrink, changeDirection };

    effect([=]() {
        auto id = setInterval(100, [=]() mutable {
            auto dir = currentDirection();
            auto pos = positions->front() + dir;
            auto transform = (*onMove)({ pos, dir });

            if (transform) {
                positions->pop_back();
                positions->push_front(transform->position);
                positions = *positions;

                direction = transform->direction;
                while (directionQueue->size() > 1) {
                    directionQueue->pop();
                }
            }

            if (!transform || isSuicide()) {
                (*onDeath)();
            }
        });

        return [=]() {
            clearTimer(id);
        };
    });

    return Group({
        EACH(*positions, pos, i) {
            Cursor(pos.x * 2, pos.y),

            WHEN(i == 0) {
                Text("●", color),
            } OTHERWISE {
                Text("○", color),
            } END_WHEN,
        } END_EACH,
    });
}
