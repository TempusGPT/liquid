#ifndef LIQUID_APP_HPP
#define LIQUID_APP_HPP

#include <clocale>
#include <functional>
#include <thread>
#include <unordered_map>
#include <ncurses.h>

#include "elements.hpp"
#include "reactive.hpp"
#include "input.hpp"

namespace Liquid
{
    struct ExitAppException
    {
    };

    Element currentPage;
    std::unordered_map<std::string, std::function<Element()>> routes;

    class App
    {
    public:
        App()
        {
            setlocale(LC_ALL, "");
            initscr();
            initInput();
        }

        ~App()
        {
            endwin();
        }

        App &route(const std::string &id, const std::function<Element()> &page)
        {
            routes[id] = page;
            return *this;
        }

        int run(const std::string &pageId)
        {
            currentPage = routes[pageId]();

            while (true)
            {
                try
                {
                    processInput();

                    if (isDirty)
                    {
                        isDirty = false;
                        clear();
                        currentPage();
                        refresh();
                    }
                }
                catch (const ExitAppException &exitApp)
                {
                    break;
                }

                std::this_thread::yield();
            }

            return 0;
        }
    };
}

Liquid::App createApp()
{
    return Liquid::App();
}

void exitApp()
{
    throw Liquid::ExitAppException{};
}

void loadPage(const std::string &pageId)
{
    Liquid::currentPage = Liquid::routes[pageId]();
    Liquid::isDirty = true;
}

#endif
