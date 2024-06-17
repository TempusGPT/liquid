#include "stage.hpp"

#include <fstream>
#include <sstream>

Stage::Stage() {}

Stage::Stage(const std::string& name) : name(name) {
    auto file = std::ifstream("./src/assets/" + name + ".txt");
    auto line = std::string();

    for (auto y = 0; std::getline(file, line); y += 1) {
        for (auto x = 0; x < line.size(); x += 1) {
            if (line[x] == 'W') {
                wall.insert({ x, y });
            } else if (line[x] == 'I') {
                immuneWall.insert({ x, y });
            } else if (line[x] == 'S') {
                snake.push_front({ x, y });
            }
        }
    }
}
