#ifndef PAGES_PLAYPAGE_HPP
#define PAGES_PLAYPAGE_HPP

#include "libs/game/apple.hpp"
#include "libs/game/snake.hpp"
#include "libs/game/walls.hpp"
#include "libs/router.hpp"
#include "liquid.hpp"

constexpr Vector FIELD_SIZE = { 23, 23 };

auto PlayPage() -> Element {
    auto effect = Effect();
    auto snake = Ref<SnakeRef>();
    auto honeyApple = Ref<AppleRef>();
    auto poisonedApple = Ref<AppleRef>();

    auto isAppleOverlap = [=]() {
        return (
            honeyApple->position() == poisonedApple->position() ||
            snake->isOverlap(honeyApple->position()) ||
            snake->isOverlap(poisonedApple->position())
        );
    };

    auto refreshHoneyApple = [=]() {
        do {
            honeyApple->refresh();
        } while (isAppleOverlap());
    };

    auto refreshPoisonedApple = [=]() {
        do {
            poisonedApple->refresh();
        } while (isAppleOverlap());
    };

    auto handleSnakeMove = [=](const Vector& head) {
        if (head == honeyApple->position()) {
            snake->grow();
            refreshHoneyApple();
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
            refreshHoneyApple();
            refreshPoisonedApple();
        });
    });

    return Group({
        Walls("■", FIELD_SIZE + Vector { 2, 2 }, Color::Green),
        Cursor(2, 1),
        Snake(snake, 4, FIELD_SIZE, handleSnakeMove, handleSnakeDeath),
        Cursor(2, 1),
        Apple(honeyApple, FIELD_SIZE, Color::Red),
        Cursor(2, 1),
        Apple(poisonedApple, FIELD_SIZE, Color::Magenta),
    });
}

#endif
