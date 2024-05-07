#include "include/app.hpp"
#include "include/color.hpp"
#include "include/input.hpp"
#include "include/timer.hpp"

#include <clocale>
#include <ncurses.h>
#include <string>
#include <thread>

namespace liquid {
    static auto isDirty = true;
    static auto isActive = true;

    auto render(const Element& element, const Options& options) -> int {
        setlocale(LC_ALL, "");
        initscr();
        resize_term(options.height, options.width);

        detail::initializeInput();
        detail::initializeColor();

        while (isActive) {
            detail::processInput();
            detail::processTimer();

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

    auto beep() -> void {
        ::beep();
    }

    auto exit() -> void {
        isActive = false;
    }

    namespace detail {
        auto markDirty() -> void {
            isDirty = true;
        }
    }
}