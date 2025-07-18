#pragma once

template<typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d, Node* n = nullptr) : data(d), next(n) {}
    };

    Node* head;

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        clear();
    }

    void insertFront(const T& data) {
        head = new Node(data, head);
    }

    void printAll(void (*printFunc)(T)) const {
        Node* curr = head;
        while (curr) {
            printFunc(curr->data);
            curr = curr->next;
        }
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            // only delete the node, not the data
            delete temp;
        }
    }
};
