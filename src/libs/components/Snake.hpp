#ifndef COMPONENTS_SNAKE_HPP
#define COMPONENTS_SNAKE_HPP

#include "libs/vector.hpp"
#include "liquid.hpp"

#include <list>
#include <queue>

using namespace liquid;

struct SnakeRef {
    std::function<void()> grow;
    std::function<void()> shrink;
    std::function<bool(const Vector&)> isOverlap;
};

auto Snake(
    State<SnakeRef>& ref,
    const Prop<int>& initialLength,
    const Prop<Vector>& fieldSize,
    const Prop<std::function<void(Vector)>>& onMove,
    const Prop<std::function<void(int)>>& onDeath
) -> Element {
    auto input = Input();
    auto effect = Effect();
    auto direction = State(Vector::right());
    auto directionQueue = State<std::queue<Vector>>();

    auto initialPos = std::list<Vector>();
    for (auto i = 0; i < initialLength(); i++) {
        initialPos.push_front({ i + 1, fieldSize().y / 2 });
    }
    auto position = State(initialPos);

    auto handleDirectionChange = [&](const Vector& direction) {
        return [=]() mutable {
            auto newDirectionQueue = directionQueue();
            newDirectionQueue.push(direction);
            directionQueue.set(newDirectionQueue);
        };
    };

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
        auto pos = position();
        return std::find(++pos.begin(), pos.end(), headPos) != pos.end();
    };

    auto grow = [=]() mutable {
        auto newCoords = position();
        newCoords.push_back(newCoords.back());
        position.set(newCoords);
    };

    auto shrink = [=]() mutable {
        auto newCoords = position();
        newCoords.pop_back();
        position.set(newCoords);
    };

    auto isOverlap = [=](const Vector& other) {
        auto pos = position();
        return std::find(pos.begin(), pos.end(), other) != pos.end();
    };

    ref.set({ grow, shrink, isOverlap });
    input({ Key::UpArrow }, handleDirectionChange(Vector::up()));
    input({ Key::DownArrow }, handleDirectionChange(Vector::down()));
    input({ Key::LeftArrow }, handleDirectionChange(Vector::left()));
    input({ Key::RightArrow }, handleDirectionChange(Vector::right()));

    effect([=]() {
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

        return [=]() {
            clearTimer(id);
        };
    });

    return Group({
        EACH(position(), pos, i) {
            Cursor(pos.x * 2, pos.y),
            Text(i == 0 ? "●" : "○", Color::Cyan),
        } END_EACH,
    });
}

#endif
