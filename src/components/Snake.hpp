#ifndef COMPONENTS_SNAKE_HPP
#define COMPONENTS_SNAKE_HPP

#include "libs/vector.hpp"
#include "liquid.hpp"

#include <list>
#include <queue>

using namespace liquid;

struct SnakeRef {
    std::function<void()> grow;
    std::function<bool(const Vector&)> isOverlap;
};

auto Snake(
    Signal<SnakeRef>& ref,
    const Prop<int>& initialLength,
    const Prop<Vector>& fieldSize,
    const Prop<std::function<void(Vector)>>& onMove,
    const Prop<std::function<void(int)>>& onDeath
) -> Element {
    auto input = Input();
    auto effect = Effect();
    auto direction = Signal(Vector::right());
    auto directionQueue = Signal<std::queue<Vector>>();

    auto initialPos = std::list<Vector>();
    for (auto i = 0; i < initialLength(); i++) {
        initialPos.push_front({ i + 1, fieldSize().y / 2 });
    }
    auto position = Signal(initialPos);

    ref.set({
        [=]() mutable {
            auto newCoords = position();
            newCoords.push_back(newCoords.back());
            position.set(newCoords);
        },
        [=](const Vector& other) {
            auto pos = position();
            return std::find(pos.begin(), pos.end(), other) != pos.end();
        },
    });

    auto enqueueDirection = [=](const Vector& direction) mutable {
        auto newDirectionQueue = directionQueue();
        newDirectionQueue.push(direction);
        directionQueue.set(newDirectionQueue);
    };

    input.bind({ Key::UpArrow }, [=]() mutable { enqueueDirection(Vector::up()); });
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

    auto isOutOfField = [=](const Vector& headPos) {
        auto [width, height] = fieldSize();
        return headPos.x < 0 || headPos.x >= width || headPos.y < 0 || headPos.y >= height;
    };

    auto isSuicide = [=](const Vector& headPos) {
        auto coords = position();
        return std::find(++coords.begin(), coords.end(), headPos) != coords.end();
    };

    auto id = setInterval(200, [=]() mutable {
        auto newPos = position();
        auto headPos = newPos.front() + currentDirection();

        if (isOutOfField(headPos) || isSuicide(headPos)) {
            onDeath()(newPos.size());
            return;
        }

        newPos.pop_back();
        newPos.push_front(headPos);
        position.set(newPos);
        onMove()(headPos);
    });

    effect.cleanup([=]() {
        clearTimer(id);
    });

    return Group({
        EACH(position(), pos, i) {
            Goto(pos.x * 2, pos.y),
            Text(i == 0 ? "●" : "○", Color::Cyan),
        } END_EACH,
    });
}

#endif
