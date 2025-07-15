#ifndef HEAPPRIORITYQUEUE_H
#define HEAPPRIORITYQUEUE_H

#include "PrinterJob.h"

using namespace std;

class HeapPriorityQueue {
private:
    static const int MAX_SIZE = 100;
    PrinterJob heap[MAX_SIZE];
    int size;

    void percolateUp(int index);
    void percolateDown(int index);

public:
    HeapPriorityQueue();
    ~HeapPriorityQueue();

    HeapPriorityQueue(const HeapPriorityQueue& other);
    HeapPriorityQueue& operator=(const HeapPriorityQueue& other);

    void enqueue(const string& str, int priority);
    void printJobs();
};

#endif // HEAPPRIORITYQUEUE_H
