#include <string>

#include "liquid.hpp"
#include "pages/MainMenu.hpp"

int main()
{
    return createApp()
        .route("MainMenu", MainMenu)
        .run("MainMenu");
}