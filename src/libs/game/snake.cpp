#include "snake.hpp"

#include <list>
#include <queue>
#include <unordered_set>

using namespace liquid;

auto Snake(
    const Prop<std::list<Vector>>& initialPosition,
    const Prop<Color>& color,
    const Prop<std::function<Vector(Transform)>>& onMove,
    const Prop<std::function<void()>>& onDeath,
    Ref<SnakeRef>& ref
) -> Element {
    auto effect = Effect();
    auto direction = State(Vector::right());
    auto directionQueue = Ref<std::queue<Vector>>();
    auto position = State(*initialPosition);

    auto currentDirection = [=]() mutable {
        if (!directionQueue->empty()) {
            direction = directionQueue->front();
            directionQueue->pop();
        }

        return *direction;
    };

    auto isSuicide = [=]() {
        auto set = std::unordered_set(position->begin(), position->end());
        return set.size() != position->size();
    };

    auto grow = [=]() mutable {
        position->push_back(position->back());
        position = *position;
    };

    auto shrink = [=]() mutable {
        position->pop_back();
        position = *position;
    };

    auto isOverlap = [=](const Vector& other) {
        auto pos = *position;
        return std::find(pos.begin(), pos.end(), other) != pos.end();
    };

    auto changeDirection = [=](const Vector& dir) mutable {
        directionQueue->push(dir);
    };

    *ref = { grow, shrink, changeDirection, isOverlap };

    effect([=]() {
        auto id = setInterval(100, [=]() mutable {
            auto dir = currentDirection();
            auto newHead = (*onMove)({ position->front() + dir, dir });

            position->pop_back();
            position->push_front(newHead);
            position = *position;

            if (isSuicide()) {
                (*onDeath)();
            }
        });

        return [=]() {
            clearTimer(id);
        };
    });

    return Group({
        EACH(*position, pos, i) {
            Cursor(pos.x * 2, pos.y),

            WHEN(i == 0) {
                Text("●", color),
            } OTHERWISE {
                Text("○", color),
            } END_WHEN,
        } END_EACH,
    });
}
