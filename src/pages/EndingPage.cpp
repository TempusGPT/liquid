#include "EndingPage.hpp"
#include "libs/game/stores.hpp"
#include "libs/router.hpp"

using namespace liquid;

auto EndingPage() -> Element {
    auto input = Input();

    input({ Key::Enter }, []() {
        stage::reset();
        navigate("/");
    });

    return Group({
        Cursor(0, 0),
        Text("================== 축하합니다! ==================", Color::Green, Color::Black),
        Cursor(0, 2),
        Text("당신은 모든 스테이지를 클리어했습니다!", Color::White, Color::Black),
        Cursor(0, 4),
        Text("앞으로도 스네이크 게임과 함께 즐거운 시간을 보내세요!", Color::Yellow, Color::Black),
        Cursor(0, 6),
        Text("==================================================", Color::Green, Color::Black),
        Cursor(0, 7),
    });
}
