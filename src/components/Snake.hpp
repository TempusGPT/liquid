#ifndef COMPONENTS_SNAKE_HPP
#define COMPONENTS_SNAKE_HPP

#include "libs/vector.hpp"
#include "liquid.hpp"

#include <list>

using namespace Liquid;

Element Snake() {
    auto input = useInput();
    auto snake = createSignal<std::list<Vector>>({ { 2, 0 }, { 1, 0 }, { 0, 0 } });
    auto direction = createSignal(Vector::right());

    input.bind({ Key::UpArrow }, [=]() mutable {
        direction.set(Vector::up());
    });

    input.bind({ Key::DownArrow }, [=]() mutable {
        direction.set(Vector::down());
    });

    input.bind({ Key::LeftArrow }, [=]() mutable {
        direction.set(Vector::left());
    });

    input.bind({ Key::RightArrow }, [=]() mutable {
        direction.set(Vector::right());
    });

    setInterval(200, [=]() mutable {
        auto newSnake = snake();
        newSnake.push_front(newSnake.front() + direction());
        newSnake.pop_back();
        snake.set(newSnake);
    });

    return Group({
        EACH(snake(), s, i) {
            Goto(s.x * 2, s.y),
            Text(i == 0 ? "ㅎ" : "ㅇ"),
        } END_EACH,
    });
}

#endif
