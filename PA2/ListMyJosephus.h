#ifndef LISTMYJOSEPHUS_H
#define LISTMYJOSEPHUS_H
#include <vector>
#include <list>
#include "Destination.h"

class ListMyJosephus {
private:
    int M, N;
    std::list<Destination> circle;

public:
    ListMyJosephus(int m, int n, const std::vector<std::string>& names);
    ~ListMyJosephus();

    void clear();
    int currentSize() const;
    bool isEmpty() const;
    Destination eliminateDestination();
    void printAllDestinations() const;
};

#endif
