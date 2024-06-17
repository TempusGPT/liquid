#include "GameOverPage.hpp"
#include "libs/game/stores.hpp"
#include "libs/router.hpp"

using namespace liquid;

auto GameOverPage() -> Element {
    auto input = Input();

    input({ Key::Enter }, []() {
        stage::reset();
        navigate("/");
    });

    return Group({
        Cursor(0, 0),
        Text("=============== Game Over ===============", Color::Red, Color::Black),
        Cursor(0, 2),
        Text("아쉽지만 게임이 종료되었습니다.", Color::White, Color::Black),
        Cursor(0, 4),
        Text("다음 번엔 더 높은 점수를 노려보세요.", Color::Yellow, Color::Black),
        Cursor(0, 6),
        Text("게임을 다시 시작하려면 Enter 키를 누르세요.", Color::Green, Color::Black),
        Cursor(0, 8),
        Text("=========================================", Color::Red, Color::Black),
    });
}
