#include "HeapPriorityQueue.h"
#include <iostream>

using namespace std;

// Constructor
HeapPriorityQueue::HeapPriorityQueue() {
    size = 0;
}

// Destructor
HeapPriorityQueue::~HeapPriorityQueue() {
    // Nothing dynamic to clean up
}

// Copy Constructor
HeapPriorityQueue::HeapPriorityQueue(const HeapPriorityQueue& other) {
    size = other.size;
    for (int i = 0; i < size; ++i) {
        heap[i] = other.heap[i];
    }
}

// Copy Assignment Operator
HeapPriorityQueue& HeapPriorityQueue::operator=(const HeapPriorityQueue& other) {
    if (this != &other) {
        size = other.size;
        for (int i = 0; i < size; ++i) {
            heap[i] = other.heap[i];
        }
    }
    return *this;
}

// Insert job into heap and maintain order
void HeapPriorityQueue::enqueue(const string& str, int priority) {
    if (size >= MAX_SIZE) {
        cout << "Heap is full. Cannot add more jobs.\n";
        return;
    }

    heap[size] = PrinterJob(str, priority);
    percolateUp(size);
    size++;
}

// Print and remove jobs in priority order
void HeapPriorityQueue::printJobs() {
    if (size == 0) {
        cout << "No jobs in the queue.\n";
        return;
    }

    cout << "Printing jobs in priority order:\n";
    while (size > 0) {
        cout << heap[0].printString << " (Priority: " << heap[0].priority << ")\n";
        heap[0] = heap[size - 1];
        size--;
        percolateDown(0);
    }
}

// Maintain heap after insertion
void HeapPriorityQueue::percolateUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[index] < heap[parent]) {
            swap(heap[index], heap[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

// Maintain heap after removal
void HeapPriorityQueue::percolateDown(int index) {
    while (2 * index + 1 < size) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = left;

        if (right < size && heap[right] < heap[left]) {
            smallest = right;
        }

        if (heap[smallest] < heap[index]) {
            swap(heap[smallest], heap[index]);
            index = smallest;
        } else {
            break;
        }
    }
}
