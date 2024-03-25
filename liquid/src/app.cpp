#include "include/app.hpp"
#include "include/color.hpp"
#include "include/input.hpp"
#include "include/reactivity.hpp"
#include "include/timer.hpp"

#include <clocale>
#include <ncurses.h>
#include <string>
#include <thread>

namespace Liquid {
    static auto isDirty = true;
    static auto isActive = true;
    static auto currentPath = createSignal("/");

    auto render(const Element& element) -> int {
        setlocale(LC_ALL, "");
        initscr();
        Internal::initializeInput();
        Internal::initializeColor();

        while (isActive) {
            Internal::processInput();
            Internal::processTimer();

            if (isDirty) {
                isDirty = false;
                clear();
                element.render(0, 0);
                refresh();
            }

            std::this_thread::yield();
        }

        endwin();
        return 0;
    }

    auto path() -> std::string {
        return currentPath();
    }

    auto navigate(const std::string& path) -> void {
        currentPath.set(path);
    }

    auto exit() -> void {
        isActive = false;
    }

    auto beep() -> void {
        ::beep();
    }

    namespace Internal {
        auto markDirty() -> void {
            isDirty = true;
        }
    }
}