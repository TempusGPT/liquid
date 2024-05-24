#include "snake.hpp"

#include <list>
#include <queue>
#include <unordered_set>

using namespace liquid;

auto Snake(
    const Prop<int>& initialLength,
    const Prop<Vector>& fieldSize,
    const Prop<Color>& color,
    const Prop<std::function<Vector(Vector)>>& onMove,
    const Prop<std::function<void()>>& onDeath,
    Ref<SnakeRef>& ref
) -> Element {
    auto input = Input();
    auto effect = Effect();
    auto direction = State(Vector::right());
    auto directionQueue = Ref<std::queue<Vector>>();

    auto position = State<std::list<Vector>>();
    for (auto i = 0; i < *initialLength; i++) {
        position->push_front({ i + 1, fieldSize->y / 2 });
    }

    auto handleDirectionChange = [&](const Vector& direction) {
        return [=]() mutable {
            directionQueue->push(direction);
        };
    };

    auto currentDirection = [=]() mutable {
        if (!directionQueue->empty()) {
            direction = directionQueue->front();
            directionQueue->pop();
        }

        return *direction;
    };

    auto isOutOfField = [=]() {
        auto headPos = position->front();
        auto [width, height] = *fieldSize;
        return headPos.x < 0 || headPos.x >= width || headPos.y < 0 || headPos.y >= height;
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

    *ref = { grow, shrink, isOverlap, changeDirection };
    input({ Key::UpArrow }, handleDirectionChange(Vector::up()));
    input({ Key::DownArrow }, handleDirectionChange(Vector::down()));
    input({ Key::LeftArrow }, handleDirectionChange(Vector::left()));
    input({ Key::RightArrow }, handleDirectionChange(Vector::right()));

    effect([=]() {
        auto id = setInterval(100, [=]() mutable {
            auto head = (*onMove)(position->front() + currentDirection());
            position->pop_back();
            position->push_front(head);
            position = *position;

            if (isOutOfField() || isSuicide()) {
                (*onDeath)();
                return;
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
                Text("●", Color::Cyan),
            } OTHERWISE {
                Text("○", Color::Cyan),
            } END_WHEN,
        } END_EACH,
    });
}
