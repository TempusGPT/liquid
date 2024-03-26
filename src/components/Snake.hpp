#ifndef COMPONENTS_SNAKE_HPP
#define COMPONENTS_SNAKE_HPP

#include "libs/vector.hpp"
#include "liquid.hpp"

#include <list>
#include <queue>

using namespace Liquid;

auto Snake(
    const Prop<int>& initialLength,
    const Prop<Vector>& fieldSize,
    const Prop<std::function<void(Vector)>>& onMove,
    const Prop<std::function<void(int)>>& onDeath
) -> Element {
    auto input = useInput();
    auto lifecycle = useLifecycle();
    auto direction = createSignal(Vector::right());
    auto directionQueue = createSignal<std::queue<Vector>>({});

    auto initialPosition = std::list<Vector>();
    for (auto i = 0; i < initialLength(); i++) {
        initialPosition.push_front({ i + 1, fieldSize().y / 2 });
    }
    auto position = createSignal(initialPosition);

    auto enqueueDirection = [=](const Vector& direction) mutable {
        auto newDirectionQueue = directionQueue();
        newDirectionQueue.push(direction);
        directionQueue.set(newDirectionQueue);
    };

    input.bind({ Key::UpArrow }, [=]() mutable { beep(); enqueueDirection(Vector::up()); });
    input.bind({ Key::DownArrow }, [=]() mutable { enqueueDirection(Vector::down()); });
    input.bind({ Key::LeftArrow }, [=]() mutable { enqueueDirection(Vector::left()); });
    input.bind({ Key::RightArrow }, [=]() mutable { enqueueDirection(Vector::right()); });

    auto currentDirection = [=]() mutable {
        auto newDirectionQueue = directionQueue();
        if (!newDirectionQueue.empty()) {
            direction.set(newDirectionQueue.front());
            newDirectionQueue.pop();
            directionQueue.set(newDirectionQueue);
        }

        return direction();
    };

    auto isOutOfField = [=](const Vector& head) {
        auto [x, y] = fieldSize();
        return head.x < 0 || head.x >= x || head.y < 0 || head.y >= y;
    };

    auto isSuicide = [=](const Vector& head) {
        auto pos = position();
        return std::find(++pos.begin(), pos.end(), head) != pos.end();
    };

    auto id = setInterval(200, [=]() mutable {
        auto newPosition = position();
        auto headPosition = newPosition.front() + currentDirection();

        if (isOutOfField(headPosition) || isSuicide(headPosition)) {
            onDeath()(newPosition.size());
            return;
        }

        newPosition.pop_back();
        newPosition.push_front(headPosition);
        position.set(newPosition);
        onMove()(headPosition);
    });

    lifecycle.cleanup([=]() {
        clearTimer(id);
    });

    return Group({
        EACH(position(), pos, i) {
            Goto(pos.x * 2, pos.y),
            Text(i == 0 ? "●" : "○"),
        } END_EACH,
    });
}

#endif
