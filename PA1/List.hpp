#ifndef LIST_HPP
#define LIST_HPP

#include "Node.hpp"
#include <iostream>

template <typename T>
class List {
private:
    Node<T>* pHead;

public:
    List() : pHead(nullptr) {}

    ~List() {
        while (pHead) {
            Node<T>* temp = pHead;
            pHead = pHead->pNext;
            delete temp;
        }
    }

    void insertAtFront(const T& data) {
        Node<T>* newNode = new Node<T>(data);
        newNode->pNext = pHead;
        pHead = newNode;
    }

    bool removeNode(const std::string& key) {
        Node<T>* pCur = pHead;
        Node<T>* prev = nullptr;

        while (pCur != nullptr && pCur->data.command != key) {
            prev = pCur;
            pCur = pCur->pNext;
        }

        if (!pCur) return false;

        if (prev)
            prev->pNext = pCur->pNext;
        else
            pHead = pCur->pNext;

        delete pCur;
        return true;
    }

    void displayAll() const {
        Node<T>* pCur = pHead;
        while (pCur) {
            std::cout << pCur->data.command << ": "
                << pCur->data.description
                << " (" << pCur->data.points << " pts)\n";
            pCur = pCur->pNext;
        }
    }

    Node<T>* getpHead() const { return pHead; }

    bool exists(const std::string& cmd) const {
        Node<T>* pCur = pHead;
        while (pCur) {
            if (pCur->data.command == cmd)
                return true;
            pCur = pCur->pNext;
        }
        return false;
    }
};

#endif
