#include "Destination.h"

Destination::Destination(int pos, const std::string& cityName) : position(pos), name(cityName) {}
Destination::~Destination() {}

void Destination::printPosition() const {
    std::cout << "Position: " << position << std::endl;
}

void Destination::printDestinationName() const {
    std::cout << "Destination: " << name << std::endl;
}

int Destination::getPosition() const {
    return position;
}

std::string Destination::getName() const {
    return name;
}
