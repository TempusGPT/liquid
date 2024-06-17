#include "MainPage.hpp"
#include "libs/router.hpp"
#include <ncurses.h>

using namespace liquid;

auto MainPage() -> Element {
    auto input = Input();

    input({ Key::Enter }, []() {
        navigate("/play");
    });

    return Group({
        Cursor(0, 0),
        Text("====== Welcome To Snake Game! ======", Color::Green, Color::Black),
        Cursor(0, 1),
        Text("조작 방법", Color::Yellow, Color::Black),
        Cursor(2, 3),
        Group({
            Text("- ", Color::White, Color::Black),
            Text("뱀은", Color::White, Color::Black),
            Text(" 머리", Color::Cyan, Color::Black),
            Text("가 향하는 방향으로 계속해서 이동합니다.", Color::White, Color::Black),
        }),
        Cursor(2, 4),
        Group({
            Text("- ", Color::White, Color::Black),
            Text("방향키( ⭠ ⭡ ⭢ ⭣)", Color::Red, Color::Black),
            Text("를 이용하여 방향을 바꿔보세요!", Color::White, Color::Black),
        }),

        Cursor(0, 6),
        Text("게임 오버 조건", Color::Yellow, Color::Black),
        Cursor(2, 8),
        Group({
            Text("- ", Color::White, Color::Black),
            Text("뱀의", Color::White, Color::Black),
            Text(" 머리", Color::Cyan, Color::Black),
            Text("가 자신의 몸과 부딪히면 게임이 종료됩니다.", Color::White, Color::Black),
        }),
        Cursor(2, 9),
        Group({
            Text("- ", Color::White, Color::Black),
            Text("뱀의", Color::White, Color::Black),
            Text(" 머리", Color::Cyan, Color::Black),
            Text("가 벽에 부딪혀도 게임이 종료됩니다.", Color::White, Color::Black),
        }),
        Cursor(2, 10),
        Group({
            Text("- ", Color::White, Color::Black),
            Text("뱀의", Color::White, Color::Black),
            Text(" 진행 방향", Color::Green, Color::Black),
            Text("과 반대 방향으로 방향키를 입력하면 게임이 종료됩니다.", Color::White, Color::Black),
        }),
        Cursor(2, 11),
        Group({
            Text("- ", Color::White, Color::Black),
            Text("몸의 길이", Color::Green, Color::Black),
            Text("가 3보다 작아지면 즉시 게임이 종료됩니다.", Color::White, Color::Black),
        }),

        Cursor(0, 13),
        Text("아이템", Color::Yellow, Color::Black),
        Cursor(2, 15),
        Group({
            Text("- ", Color::White, Color::Black),
            Text("성장", Color::Red, Color::Black),
            Text(" 아이템을 먹으면 몸의 길이가 1 증가합니다.", Color::White, Color::Black),
        }),
        Cursor(2, 16),
        Group({
            Text("- ", Color::White, Color::Black),
            Text("독", Color::Magenta, Color::Black),
            Text(" 아이템을 먹으면 몸의 길이가 1 감소합니다.", Color::White, Color::Black),
        }),

        Cursor(0, 18),
        Text("그 외", Color::Yellow, Color::Black),
        Cursor(2, 20),
        Group({
            Text("- ", Color::White, Color::Black),
            Text("임의로 생성되는", Color::White, Color::Black),
            Text(" 게이트", Color::Blue, Color::Black),
            Text("를 통해 반대편 게이트로 이동하세요.", Color::White, Color::Black),
        }),
        Cursor(2, 21),
        Group({
            Text("- ", Color::White, Color::Black),
            Text("최대한 오랜 시간 동안", Color::White, Color::Black),
            Text(" 게이트", Color::Blue, Color::Black),
            Text("와", Color::White, Color::Black),
            Text(" 성장 아이템", Color::Red, Color::Black),
            Text("을 통해 높은", Color::White, Color::Black),
            Text(" 점수", Color::Yellow, Color::Black),
            Text("를 획득 하세요!", Color::White, Color::Black),
        }),

        Cursor(0, 23),
        Text("Good Luck!!", Color::Yellow, Color::Black),
        Cursor(0, 24),
        Text("====== Press Enter to Start ======", Color::Green, Color::Black),
    });
}