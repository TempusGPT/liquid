#ifndef LIBS_GAME_STAGE_HPP
#define LIBS_GAME_STAGE_HPP

#include "libs/vector.hpp"

#include <list>
#include <string>
#include <unordered_set>

struct Stage {
public:
    std::string name;
    std::list<Vector> snake;
    std::unordered_set<Vector> wall;
    std::unordered_set<Vector> immuneWall;

    Stage(const std::string& path);
};

#endif
