#ifndef COMPONENTS_SNAKE_HPP
#define COMPONENTS_SNAKE_HPP

#include "libs/vector.hpp"
#include "liquid.hpp"

#include <list>
#include <queue>

using namespace Liquid;

Element Snake(const Vector &fieldSize) {
    auto input = useInput();
    auto positions = createSignal<std::list<Vector>>({ { 2, 0 }, { 1, 0 }, { 0, 0 } });
    auto direction = createSignal(Vector::right());
    auto directionQueue = createSignal<std::queue<Vector>>({});

    auto currentDirection = [=]() mutable {
        auto newDirectionQueue = directionQueue();
        if (!newDirectionQueue.empty()) {
            direction.set(directionQueue().front());
            newDirectionQueue.pop();
            directionQueue.set(newDirectionQueue);
        }

        return direction();
    };

    auto enqueueDirection = [=](Vector direction) mutable {
        auto newDirectionQueue = directionQueue();
        newDirectionQueue.push(direction);
        directionQueue.set(newDirectionQueue);
    };

    input.bind({ Key::UpArrow }, [=]() mutable { enqueueDirection(Vector::up()); });
    input.bind({ Key::DownArrow }, [=]() mutable { enqueueDirection(Vector::down()); });
    input.bind({ Key::LeftArrow }, [=]() mutable { enqueueDirection(Vector::left()); });
    input.bind({ Key::RightArrow }, [=]() mutable { enqueueDirection(Vector::right()); });

    setInterval(200, [=]() mutable {
        auto newPositions = positions();
        auto headPosition = newPositions.front() + currentDirection();
        newPositions.pop_back();
        newPositions.push_front(headPosition);
        positions.set(newPositions);
    });

    return Group({
        EACH(positions(), pos, i) {
            Goto(pos.x * 2, pos.y),
            Text(i == 0 ? "ㅎ" : "ㅇ"),
        } END_EACH,
    });
}

#endif
