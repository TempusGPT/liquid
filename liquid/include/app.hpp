#ifndef LIQUID_APP_HPP
#define LIQUID_APP_HPP

#include "component.hpp"

#include <string>

class App {
public:
    App();
    ~App();
    App &route(const std::string &id, const Page &page);
    int run(const std::string &pageId);

private:
    void render();
    void process();
};

App createApp();
void exitApp();
void loadPage(const std::string &pageId);
void playBeep();

#endif
