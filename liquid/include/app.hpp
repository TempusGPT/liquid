#ifndef LIQUID_APP_HPP
#define LIQUID_APP_HPP

#include "component.hpp"

#include <string>

class App;

App &initializeApp();

class App {
    friend App &initializeApp();

public:
    static bool isDirty;

    App &route(const std::string &id, const Page &page);
    int run(const std::string &pageId);

private:
    App();
    ~App();

    void render();
    void process();
};

void exitApp();
void loadPage(const std::string &pageId);
void playBeep();

#endif
