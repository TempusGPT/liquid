#ifndef LIQUID_APP_HPP
#define LIQUID_APP_HPP

#include <clocale>
#include <functional>
#include <thread>

#include "ncurses.h"
#include "elements.hpp"
#include "primitives.hpp"

namespace Liquid
{
    class App
    {
    public:
        App()
        {
            setlocale(LC_ALL, "");
            initscr();

            // input
            keypad(stdscr, true);
            nodelay(stdscr, true);
            curs_set(0);
            noecho();
        }

        int start(const Element &page)
        {
            currentPage = page;

            while (true)
            {
                if (hasChanged)
                {
                    clear();
                    currentPage();
                    refresh();
                    hasChanged = false;
                }
                std::this_thread::yield();

                if (getch() == 'q')
                {
                    break;
                }
            }

            endwin();
            delete this;
            return 0;
        }

    private:
        Element currentPage;
    };
}

Liquid::App &createApp()
{
    const auto app = std::make_shared<Liquid::App>();
    return *app;
}

#endif
