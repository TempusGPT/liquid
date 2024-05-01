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
    const std::shared_ptr<SnakeRef>& ref,
    const Prop<int>& initialLength,
    const Prop<Vector>& fieldSize,
    const Prop<std::function<void(Vector)>>& onMove,
    const Prop<std::function<void(int)>>& onDeath
) -> Element {
    auto input = Input();
    auto effect = Effect();
    auto direction = State(Vector::right());
    auto directionQueue = std::make_shared<std::queue<Vector>>();

    auto initialPos = std::list<Vector>();
    for (auto i = 0; i < initialLength(); i++) {
        initialPos.push_front({ i + 1, fieldSize().y / 2 });
    }
    auto position = State(initialPos);

    auto headPosition = Derived<Vector>(RP(position().front()));

    auto handleDirectionChange = [&](const Vector& direction) {
        return [=]() mutable {
            directionQueue->push(direction);
        };
    };

    auto currentDirection = [=]() mutable {
        if (!directionQueue->empty()) {
            direction.set(directionQueue->front());
            directionQueue->pop();
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

    *ref = { grow, shrink, isOverlap };
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
        Text(RP("(%0%, %1%)"_fmt % headPosition().x % headPosition().y)),

        EACH(position(), pos, i) {
            Cursor(pos.x * 2, pos.y),
            Text(i == 0 ? "●" : "○", Color::Cyan),
        } END_EACH,
    });
}

#endif
