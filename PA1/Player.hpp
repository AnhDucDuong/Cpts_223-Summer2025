#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

struct Player {
    std::string name;
    int score;

    Player(std::string n = "", int s = 0) : name(n), score(s) {}
};

#endif
