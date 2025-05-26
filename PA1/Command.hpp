#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>

class Command {
public:
    std::string command;
    std::string description;
    int points;

    Command(std::string cmd = "", std::string desc = "", int pts = 1)
        : command(cmd), description(desc.empty() ? "No description provided" : desc), points(pts) {
    }
};

#endif
