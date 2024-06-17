#include "ContinuePage.hpp"
#include "libs/game/stores.hpp"
#include "libs/router.hpp"

using namespace liquid;

auto ContinuePage() -> Element {
    auto input = Input();

    input({ Key::Enter }, []() {
        stage::moveNext();
        navigate("/play");
    });

    return Group({
        Cursor(0, 0),
        Text("============= 스테이지 클리어! ============", Color::Blue, Color::Black),
        Cursor(0, 2),
        Text(
            GET("축하합니다! %0% 스테이지를 클리어 하셨습니다."_f % stage::current().name),
            Color::Yellow,
            Color::Black
        ),
        Cursor(0, 4),
        Text("다음 스테이지는 점점 더 어려워집니다!", Color::White, Color::Black),
        Cursor(0, 6),
        Text("다음 스테이지로 가려면 Enter 키를 누르세요.", Color::Green, Color::Black),
        Cursor(0, 8),
        Text("=========== 계속해서 도전하세요! ===========", Color::Blue, Color::Black),
    });
}
