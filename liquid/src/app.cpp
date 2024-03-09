#include "include/app.hpp"

#include "include/color.hpp"
#include "include/component.hpp"
#include "include/input.hpp"
#include "include/reactive.hpp"
#include "include/timer.hpp"

#include <clocale>
#include <functional>
#include <ncurses.h>
#include <thread>
#include <unordered_map>

struct ExitAppException {};

Element pageElement;
std::unordered_map<std::string, Page> routes;

App::App() {
    setlocale(LC_ALL, "");
    initscr();
    Liquid::initInput();
    Liquid::initColor();
}

App::~App() {
    endwin();
}

App &App::route(const std::string &id, const Page &page) {
    routes[id] = page;
    return *this;
}

int App::run(const std::string &pageId) {
    loadPage(pageId);
    process();
    return 0;
}

void App::render() {
    clear();
    pageElement.render();
    refresh();
}

void App::process() {
    while (true) {
        try {
            Liquid::processInput();
            Liquid::processTimer();

            if (Liquid::isDirty) {
                Liquid::isDirty = false;
                render();
            }
        } catch (const ExitAppException &exitApp) {
            return;
        }

        std::this_thread::yield();
    }
}

App createApp() {
    return App();
}

void exitApp() {
    throw ExitAppException();
}

void loadPage(const std::string &pageId) {
    pageElement = routes[pageId]();
    Liquid::isDirty = true;
}

void playBeep() {
    beep();
}
