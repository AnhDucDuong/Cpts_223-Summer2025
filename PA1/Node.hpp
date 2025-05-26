#ifndef NODE_HPP
#define NODE_HPP

template <typename T>
class Node {
public:
    T data;
    Node<T>* pNext;

    Node(const T& newData) : data(newData), pNext(nullptr) {}
};

#endif
