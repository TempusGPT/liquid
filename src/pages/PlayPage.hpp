#ifndef PAGES_PLAYPAGE_HPP
#define PAGES_PLAYPAGE_HPP

#include "libs/components/Apple.hpp"
#include "libs/components/Frame.hpp"
#include "libs/components/Snake.hpp"
#include "libs/router.hpp"
#include "liquid.hpp"

using namespace liquid;

constexpr Vector FIELD_SIZE = { 23, 23 };

auto PlayPage() -> Element {
    auto effect = Effect();
    auto snake = std::make_shared<SnakeRef>();
    auto apple = std::make_shared<AppleRef>();
    auto poisonedApple = std::make_shared<AppleRef>();

    auto isAppleOverlap = [=]() {
        return apple->position() == poisonedApple->position() ||
               snake->isOverlap(apple->position()) ||
               snake->isOverlap(poisonedApple->position());
    };

    auto refreshApple = [=]() {
        do {
            apple->refresh();
        } while (isAppleOverlap());
    };

    auto refreshPoisonedApple = [=]() {
        do {
            poisonedApple->refresh();
        } while (isAppleOverlap());
    };

    auto handleSnakeMove = [=](const Vector& head) {
        if (head == apple->position()) {
            snake->grow();
            refreshApple();
        }

        if (head == poisonedApple->position()) {
            snake->shrink();
            refreshPoisonedApple();
        }
    };

    auto handleSnakeDeath = [](int) {
        navigate("/");
    };

    effect([=]() {
        untrack([=]() {
            refreshApple();
            refreshPoisonedApple();
        });
    });

    return Group({
        Frame("■", FIELD_SIZE + Vector { 2, 2 }, Color::Green),
        Cursor(2, 1),
        Snake(snake, 4, FIELD_SIZE, handleSnakeMove, handleSnakeDeath),
        Cursor(2, 1),
        Apple(apple, FIELD_SIZE, Color::Red),
        Cursor(2, 1),
        Apple(poisonedApple, FIELD_SIZE, Color::Magenta),
    });
}

#endif
