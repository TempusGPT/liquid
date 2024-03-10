#include <string>

#include "liquid.hpp"
#include "pages/MainMenu.hpp"

int main() {
    return initializeApp()
        .route("MainMenu", MainMenu)
        .run("MainMenu");
}
