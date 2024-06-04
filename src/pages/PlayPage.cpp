#include "PlayPage.hpp"
#include "libs/game/apple.hpp"
#include "libs/game/parser.hpp"
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

    auto refreshHoneyApple = [=]() {
        do {
            honeyApple->refresh();
        } while (
            honeyApple->position() == poisonedApple->position() ||
            snake->isOverlap(honeyApple->position()) ||
            walls->isOverlap(honeyApple->position())
        );
    };

    auto refreshPoisonedApple = [=]() {
        do {
            poisonedApple->refresh();
        } while (
            honeyApple->position() == poisonedApple->position() ||
            snake->isOverlap(poisonedApple->position()) ||
            walls->isOverlap(poisonedApple->position())
        );
    };

    auto handleSnakeMove = [=](const Transform& transform) -> std::optional<Transform> {
        if (transform.position == honeyApple->position()) {
            snake->grow();
            refreshHoneyApple();
        }

        if (transform.position == poisonedApple->position()) {
            snake->shrink();
            refreshPoisonedApple();

            if (snake->length() < 4) {
                return std::nullopt;
            }
        }

        if (walls->isOverlap(transform.position)) {
            auto gate = walls->getGate(transform);

            if (gate) {
                return Transform { gate->position + gate->direction, gate->direction };
            } else {
                return std::nullopt;
            }
        }

        return transform;
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

    auto stage = parseStage("./src/assets/tutorial.txt");

    return Group({
        Walls(stage.wall, stage.immuneWall, Color::White, Color::Blue, walls),
        Cursor(0, 0),
        Snake(stage.snake, Color::Cyan, handleSnakeMove, handleSnakeDeath, snake),
        Cursor(0, 0),
        Apple(FIELD_SIZE, Color::Red, honeyApple),
        Cursor(0, 0),
        Apple(FIELD_SIZE, Color::Magenta, poisonedApple),
    });
}
