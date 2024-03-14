#include "include/app.hpp"
#include "include/color.hpp"
#include "include/input.hpp"
#include "include/macro.hpp"
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

    Element Route(const std::string &path, const Component<> &component) {
        return WHEN(path == currentPath()) {
            component(),
        } END_WHEN;
    }

    int render(const Element &element) {
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
                element.render();
                refresh();
            }

            std::this_thread::yield();
        }

        endwin();
        return 0;
    }

    void navigate(const std::string &path) {
        currentPath.set(path);
    }

    void exitApp() {
        isActive = false;
    }

    void playBeep() {
        beep();
    }

    namespace Internal {
        void markDirty() {
            isDirty = true;
        }
    }
}