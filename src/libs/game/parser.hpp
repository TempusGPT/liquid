#ifndef LIBS_GAME_PARSER_HPP
#define LIBS_GAME_PARSER_HPP

#include "libs/vector.hpp"

#include <list>
#include <string>
#include <unordered_set>

struct ParseResult {
    std::list<Vector> snake;
    std::unordered_set<Vector> wall;
    std::unordered_set<Vector> immuneWall;
};

auto parseStage(const std::string& path) -> ParseResult;

#endif
