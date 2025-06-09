#include "ListMyJosephus.h"
#include <iostream>

ListMyJosephus::ListMyJosephus(int m, int n, const std::vector<std::string>& names) : M(m), N(n) {
    for (int i = 0; i < N; ++i) {
        circle.emplace_back(i, names[i]);
    }
}

ListMyJosephus::~ListMyJosephus() {
    clear();
}

void ListMyJosephus::clear() {
    circle.clear();
}

int ListMyJosephus::currentSize() const {
    return circle.size();
}

bool ListMyJosephus::isEmpty() const {
    return circle.empty();
}

Destination ListMyJosephus::eliminateDestination() {
    auto it = circle.begin();

    std::cout << "Starting elimination loop with size: " << circle.size() << "\n";

    while (circle.size() > 1) {
        std::cout << "Remaining: " << circle.size() << "\n";
        std::cout << "Current head: " << it->getName() << "\n";

        for (int i = 0; i < M - 1; ++i) {
            ++it;
            if (it == circle.end()) it = circle.begin();
        }

        std::cout << "Eliminating: " << it->getName() << "\n";

        auto toErase = it++;
        if (it == circle.end()) it = circle.begin();
        circle.erase(toErase);
    }

    std::cout << "Final Winner: " << circle.front().getName() << "\n";
    return circle.front();
}



void ListMyJosephus::printAllDestinations() const {
    for (const auto& d : circle) {
        d.printDestinationName();
    }
}
