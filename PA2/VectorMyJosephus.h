#ifndef VECTORMYJOSEPHUS_H
#define VECTORMYJOSEPHUS_H

#include <vector>
#include "Destination.h"

class VectorMyJosephus {
private:
    int M, N;
    std::vector<Destination> circle;

public:
    VectorMyJosephus(int m, int n, const std::vector<std::string>& names);
    ~VectorMyJosephus();

    void clear();
    int currentSize() const;
    bool isEmpty() const;
    Destination eliminateDestination();
    void printAllDestinations() const;
};

#endif
