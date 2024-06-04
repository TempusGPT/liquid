#include "parser.hpp"

#include <fstream>

auto parseStage(const std::string& path) -> ParseResult {
    auto file = std::ifstream(path);
    auto line = std::string();
    auto state = ParseResult();

    for (auto y = 0; std::getline(file, line); y += 1) {
        for (auto x = 0; x < line.size(); x += 1) {
            if (line[x] == 'W') {
                state.wall.insert({ x, y });
            } else if (line[x] == 'I') {
                state.immuneWall.insert({ x, y });
            } else if (line[x] == 'S') {
                state.snake.push_front({ x, y });
            }
        }
    }

    return state;
}
