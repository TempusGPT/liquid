#include "PlayPage.hpp"
#include "libs/game/apple.hpp"
#include "libs/game/snake.hpp"
#include "libs/game/walls.hpp"
#include "libs/router.hpp"
#include "libs/vector.hpp"
#include <list>

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
            snake->isOverlap(poisonedApple->position()) ||
            walls->isOverlap(honeyApple->position()) ||
            walls->isOverlap(poisonedApple->position())
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

    auto handleSnakeMove = [=](const Transform& transform) {
        if (transform.position == honeyApple->position()) {
            snake->grow();
            refreshHoneyApple();
        }

        if (transform.position == poisonedApple->position()) {
            snake->shrink();
            refreshPoisonedApple();
        }

        auto gate = walls->getGate(transform);
        if (gate) {
            snake->changeDirection(gate->direction);
            return gate->position + gate->direction;
        }

        return transform.position;
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

#pragma region Temp

    auto wallPositions = std::unordered_set<Vector>();
    auto immuneWallPositions = std::unordered_set<Vector>();

    immuneWallPositions.insert({ -1, -1 });
    immuneWallPositions.insert({ -1, FIELD_SIZE.y });
    immuneWallPositions.insert({ FIELD_SIZE.x, -1 });
    immuneWallPositions.insert({ FIELD_SIZE.x, FIELD_SIZE.y });

    for (auto x = 0; x < FIELD_SIZE.x; x += 1) {
        wallPositions.insert({ x, -1 });
        wallPositions.insert({ x, FIELD_SIZE.y });
    }

    for (auto y = 0; y < FIELD_SIZE.y; y += 1) {
        wallPositions.insert({ -1, y });
        wallPositions.insert({ FIELD_SIZE.x, y });
    }

    auto snakePosition = std::list<Vector>();
    for (auto i = 0; i < 4; i++) {
        snakePosition.push_front({ i + 1, FIELD_SIZE.y / 2 });
    }

#pragma endregion

    return Group({
        Cursor(2, 1),
        Walls(wallPositions, immuneWallPositions, Color::White, Color::Blue, walls),
        Cursor(2, 1),
        Snake(snakePosition, Color::Cyan, handleSnakeMove, handleSnakeDeath, snake),
        Cursor(2, 1),
        Apple(FIELD_SIZE, Color::Red, honeyApple),
        Cursor(2, 1),
        Apple(FIELD_SIZE, Color::Magenta, poisonedApple),
    });
}
