#pragma once
#include <iostream>
#include <functional>

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
    };

    Node* head;

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        Node* current = head;
        while (current) {
            Node* tmp = current;
            current = current->next;
            delete tmp;
        }
    }

    void insertFront(T value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    void printAll(std::function<void(T)> callback) const {
        Node* current = head;
        while (current) {
            callback(current->data);
            current = current->next;
        }
    }

    std::vector<T> toVector() const {
        std::vector<T> result;
        Node* current = head;
        while (current) {
            result.push_back(current->data);
            current = current->next;
        }
        return result;
    }
};
