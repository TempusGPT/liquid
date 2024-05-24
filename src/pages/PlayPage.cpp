#include "PlayPage.hpp"
#include "libs/game/apple.hpp"
#include "libs/game/snake.hpp"
#include "libs/game/walls.hpp"
#include "libs/router.hpp"
#include "libs/vector.hpp"

using namespace liquid;

constexpr Vector FIELD_SIZE = { 23, 23 };

auto PlayPage() -> Element {
    auto input = Input();
    auto effect = Effect();

    auto walls = Ref<WallsRef>();
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

        auto gate = walls->getGate(head);
        if (gate) {
            snake->changeDirection(gate->direction);
            return gate->position + gate->direction;
        }

        return head;
    };

    auto handleSnakeDeath = []() {
        navigate("/");
    };

    auto changeDirection = [&](const Vector& direction) {
        return [=]() mutable {
            snake->changeDirection(direction);
        };
    };

    input({ Key::UpArrow }, changeDirection(Vector::up()));
    input({ Key::DownArrow }, changeDirection(Vector::down()));
    input({ Key::LeftArrow }, changeDirection(Vector::left()));
    input({ Key::RightArrow }, changeDirection(Vector::right()));

    effect([=]() {
        untrack([=]() {
            refreshHoneyApple();
            refreshPoisonedApple();
        });
    });

    return Group({
        Cursor(2, 1),
        Walls(FIELD_SIZE, Color::White, Color::Blue, walls),
        Cursor(2, 1),
        Snake(4, FIELD_SIZE, Color::Cyan, handleSnakeMove, handleSnakeDeath, snake),
        Cursor(2, 1),
        Apple(FIELD_SIZE, Color::Red, honeyApple),
        Cursor(2, 1),
        Apple(FIELD_SIZE, Color::Magenta, poisonedApple),
    });
}
