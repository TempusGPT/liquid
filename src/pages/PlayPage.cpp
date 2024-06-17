#include "PlayPage.hpp"
#include "libs/game/apple.hpp"
#include "libs/game/mission.hpp"
#include "libs/game/snake.hpp"
#include "libs/game/stage.hpp"
#include "libs/game/stores.hpp"
#include "libs/game/walls.hpp"
#include "libs/router.hpp"
#include "libs/vector.hpp"

#include <fstream>
#include <string>

using namespace liquid;

constexpr auto FIELD_SIZE = Vector { 25, 25 };
constexpr auto REFRESH_INTERVAL = 10000;
constexpr auto MIN_SNAKE_LENGTH = 3;

auto PlayPage() -> Element {
    auto input = Input();
    auto effect = Effect();

    auto walls = Ref<WallsRef>();
    auto snake = Ref<SnakeRef>();
    auto mission = Ref<MissionRef>();
    auto exitOpen = State<bool>();

    auto honeyApple = Ref<AppleRef>();
    auto poisonApple = Ref<AppleRef>();
    auto goldenApple = Ref<AppleRef>();
    auto honeyAppleRefreshId = Ref(0);
    auto poisonAppleRefreshId = Ref(0);

    auto refreshHoneyApple = [=]() {
        do {
            honeyApple->refresh();
        } while (
            honeyApple->position() == poisonApple->position() ||
            honeyApple->position() == goldenApple->position() ||
            snake->isOverlap(honeyApple->position()) ||
            walls->isOverlap(honeyApple->position())
        );
    };

    auto refreshPoisonedApple = [=]() {
        do {
            poisonApple->refresh();
        } while (
            poisonApple->position() == honeyApple->position() ||
            poisonApple->position() == goldenApple->position() ||
            snake->isOverlap(poisonApple->position()) ||
            walls->isOverlap(poisonApple->position())
        );
    };

    auto refreshGoldenApple = [=]() {
        do {
            goldenApple->refresh();
        } while (
            goldenApple->position() == honeyApple->position() ||
            goldenApple->position() == poisonApple->position() ||
            snake->isOverlap(goldenApple->position()) ||
            walls->isOverlap(goldenApple->position())
        );
    };

    auto handleSnakeMove = [=](const Transform& transform) -> std::optional<Transform> {
        auto checkApple = [=](const Transform& transform) mutable -> std::optional<Transform> {
            if (transform.position == honeyApple->position()) {
                snake->grow();
                refreshHoneyApple();
                clearTimer(*honeyAppleRefreshId);
                *honeyAppleRefreshId = setInterval(REFRESH_INTERVAL, refreshHoneyApple);
                score::eatHoneyApple();
            }

            if (transform.position == poisonApple->position()) {
                snake->shrink();
                refreshPoisonedApple();
                clearTimer(*poisonAppleRefreshId);
                *poisonAppleRefreshId = setInterval(REFRESH_INTERVAL, refreshPoisonedApple);
                score::eatPoisonApple();

                if (snake->length() < MIN_SNAKE_LENGTH) {
                    return std::nullopt;
                }
            }

            if (transform.position == goldenApple->position()) {
                exitOpen = true;
            }

            return transform;
        };

        if (*exitOpen && walls->isExit(transform.position)) {
            score::enterExit();

            if (mission->isComplete()) {
                return transform;
            } else {
                return std::nullopt;
            }
        }

        if (walls->isOverlap(transform.position)) {
            auto gate = walls->getGate(transform);

            if (gate) {
                score::enterGate();
                return checkApple({ gate->position + gate->direction, gate->direction });
            } else {
                return std::nullopt;
            }
        }

        return checkApple(transform);
    };

    auto handleSnakeDeath = []() {
        navigate("/gameover");
    };

    auto handleMissionComplete = []() {
        if (stage::isLast()) {
            navigate("/ending");
        } else {
            navigate("/continue");
        }
    };

    auto changeDirection = [&](const Vector& direction) {
        return [=]() mutable {
            snake->changeDirection(direction);
        };
    };

    auto stage = stage::current();
    score::initialize();

    input({ Key::UpArrow }, changeDirection(Vector::up()));
    input({ Key::DownArrow }, changeDirection(Vector::down()));
    input({ Key::LeftArrow }, changeDirection(Vector::left()));
    input({ Key::RightArrow }, changeDirection(Vector::right()));

    effect([=]() mutable {
        untrack([=]() {
            refreshHoneyApple();
            refreshPoisonedApple();
            refreshGoldenApple();
        });

        *honeyAppleRefreshId = setInterval(REFRESH_INTERVAL, refreshHoneyApple);
        *poisonAppleRefreshId = setInterval(REFRESH_INTERVAL, refreshPoisonedApple);

        return [=]() {
            clearTimer(*honeyAppleRefreshId);
            clearTimer(*poisonAppleRefreshId);
        };
    });

    return Group({
        Snake(
            stage.snake,
            stage::interval(),
            Color::Cyan,
            handleSnakeMove,
            handleSnakeDeath,
            snake
        ),

        Cursor(0, 0),
        Walls(
            FIELD_SIZE,
            stage.wall,
            stage.immuneWall,
            Color::White,
            Color::Blue,
            Color::Yellow,
            GET(*exitOpen),
            walls
        ),

        Cursor(0, 0),
        Apple(FIELD_SIZE, Color::Red, honeyApple),
        Cursor(0, 0),
        Apple(FIELD_SIZE, Color::Magenta, poisonApple),
        WHEN(!*exitOpen) {
            Cursor(0, 0),
            Apple(FIELD_SIZE, Color::Yellow, goldenApple),
        } END_WHEN,

        Cursor(FIELD_SIZE.x * 2, 0),
        Mission(5, 1, 1, 1, handleMissionComplete, mission),

        Cursor(FIELD_SIZE.x * 2, 20),
        Text(GET("Exit Open: %0%"_f % *exitOpen)),
        Cursor(FIELD_SIZE.x * 2, 21),
        Text(GET("Exit Entered: %0%"_f % score::exit())),
    });
}
