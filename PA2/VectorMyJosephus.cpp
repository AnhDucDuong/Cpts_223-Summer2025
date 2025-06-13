#include "VectorMyJosephus.h"
#include <iostream>

VectorMyJosephus::VectorMyJosephus(int m, int n, const std::vector<std::string>& names) : M(m), N(n) {
    for (int i = 0; i < N; ++i) {
        circle.emplace_back(i, names[i]);
    }
}

VectorMyJosephus::~VectorMyJosephus() {
    clear();
}

void VectorMyJosephus::clear() {
    circle.clear();
}

int VectorMyJosephus::currentSize() const {
    return circle.size();
}

bool VectorMyJosephus::isEmpty() const {
    return circle.empty();
}

Destination VectorMyJosephus::eliminateDestination() {
    int index = 0;
    std::cout << "Starting elimination loop with size: " << circle.size() << "\n";
    while (circle.size() > 1) {
        index = (index + M - 1) % circle.size();
        std::cout << "Eliminating: " << circle[index].getName() << "\n";
        circle.erase(circle.begin() + index);
    }
    std::cout << "Final Winner: " << circle[0].getName() << "\n";
    return circle[0];
}

void VectorMyJosephus::printAllDestinations() const {
    for (const auto& d : circle) {
        d.printDestinationName();
    }
}
