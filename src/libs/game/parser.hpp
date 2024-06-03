#ifndef LIBS_GAME_PARSER_HPP
#define LIBS_GAME_PARSER_HPP

#include "libs/vector.hpp"

#include <list>
#include <string>

struct ParseResult {
    const std::list<Vector>& snake;
};

ParseResult parse(const std::string& path);

#endif
