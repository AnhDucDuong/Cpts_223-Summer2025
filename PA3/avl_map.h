#ifndef AVL_MAP_H
#define AVL_MAP_H

#include <stack>
#include <utility>
#include <cstddef>
#include <optional>

template <typename Key, typename Value>
class avl_map {
    struct Node {
        Key   key;            // key for this node
        Value val;            // value stored
        int   height = 1;     // height of the subtree
        Node* pLeft = nullptr;
        Node* pRight = nullptr;
        Node* pParent = nullptr;

        Node(const Key& k, const Value& v, Node* p = nullptr)
            : key(k), val(v), pParent(p) {}
    };

    Node* pRoot = nullptr;     // root of the AVL tree
    std::size_t m_size = 0;    // total number of key-value pairs

    static int h(Node* pNode) {
        return pNode ? pNode->height : 0;
    }

    static int balance_factor(Node* pNode) {
        return h(pNode->pLeft) - h(pNode->pRight);
    }

    static void update(Node* pNode) {
        pNode->height = 1 + std::max(h(pNode->pLeft), h(pNode->pRight));
    }

    static Node* rotate_left(Node* pX) {
        Node* pY = pX->pRight;
        pX->pRight = pY->pLeft;
        if (pY->pLeft) pY->pLeft->pParent = pX;
        pY->pLeft = pX;
        pY->pParent = pX->pParent;
        pX->pParent = pY;
        update(pX);
        update(pY);
        return pY;  // This tree just did a spin move
    }

    static Node* rotate_right(Node* pY) {
        Node* pX = pY->pLeft;
        pY->pLeft = pX->pRight;
        if (pX->pRight) pX->pRight->pParent = pY;
        pX->pRight = pY;
        pX->pParent = pY->pParent;
        pY->pParent = pX;
        update(pY);
        update(pX);
        return pX;
    }

    static Node* rebalance(Node* pNode) {
        update(pNode);
        int bf = balance_factor(pNode);

        if (bf > 1) {
            if (balance_factor(pNode->pLeft) < 0)
                pNode->pLeft = rotate_left(pNode->pLeft);
            return rotate_right(pNode);
        }

        if (bf < -1) {
            if (balance_factor(pNode->pRight) > 0)
                pNode->pRight = rotate_right(pNode->pRight);
            return rotate_left(pNode);
        }

        return pNode;  // Balanced like a Zen master 🧘
    }

    static Node* insert(Node* pNode, const Key& k, const Value& v, Node* pParent, bool& inserted) {
        if (!pNode) {
            inserted = true;
            return new Node(k, v, pParent);
        }

        if (k < pNode->key)
            pNode->pLeft = insert(pNode->pLeft, k, v, pNode, inserted);
        else if (k > pNode->key)
            pNode->pRight = insert(pNode->pRight, k, v, pNode, inserted);
        else
            pNode->val = v;  // key exists, overwrite value

        return rebalance(pNode);
    }

    static Node* min_node(Node* pNode) {
        while (pNode->pLeft)
            pNode = pNode->pLeft;
        return pNode;
    }

    static Node* erase(Node* pNode, const Key& k, bool& erased) {
        if (!pNode) return nullptr;

        if (k < pNode->key)
            pNode->pLeft = erase(pNode->pLeft, k, erased);
        else if (k > pNode->key)
            pNode->pRight = erase(pNode->pRight, k, erased);
        else {
            erased = true;

            if (!pNode->pLeft || !pNode->pRight) {
                Node* pChild = pNode->pLeft ? pNode->pLeft : pNode->pRight;
                if (pChild) pChild->pParent = pNode->pParent;
                delete pNode;
                return pChild;
            }

            Node* pSucc = min_node(pNode->pRight);
            pNode->key = pSucc->key;
            pNode->val = pSucc->val;
            pNode->pRight = erase(pNode->pRight, pSucc->key, erased);
        }

        return rebalance(pNode);  // Tree hits the gym again
    }

    static Node* find(Node* pNode, const Key& k) {
        while (pNode) {
            if (k < pNode->key)
                pNode = pNode->pLeft;
            else if (k > pNode->key)
                pNode = pNode->pRight;
            else
                return pNode;
        }
        return nullptr;  // Not found. Sad.
    }

public:
    class iterator {
        Node* pCur;

        void ascend() {
            Node* pTmp = pCur->pRight;
            while (pTmp && pTmp->pLeft)
                pTmp = pTmp->pLeft;
            pCur = pTmp;
        }

    public:
        explicit iterator(Node* p = nullptr) : pCur(p) {}

        Value& operator*()  const { return pCur->val; }
        Value* operator->() const { return &pCur->val; }
        const Key& key()    const { return pCur->key; }

        iterator& operator++() {
            if (!pCur) return *this;

            if (pCur->pRight) {
                ascend();
                return *this;
            }

            Node* p = pCur->pParent;
            while (p && pCur == p->pRight) {
                pCur = p;
                p = p->pParent;
            }

            pCur = p;
            return *this;  // Onward to the next key!
        }

        bool operator==(iterator rhs) const { return pCur == rhs.pCur; }
        bool operator!=(iterator rhs) const { return !(*this == rhs); }
    };

    std::size_t size()  const { return m_size; }
    bool empty()        const { return m_size == 0; }

    iterator insert(const Key& k, const Value& v) {
        bool inserted = false;
        pRoot = insert(pRoot, k, v, nullptr, inserted);
        if (inserted) ++m_size;
        return iterator(find(pRoot, k));
    }

    bool erase(const Key& k) {
        bool erased = false;
        pRoot = erase(pRoot, k, erased);
        if (erased) --m_size;
        return erased;
    }

    iterator find(const Key& k) const {
        return iterator(find(pRoot, k));
    }

    iterator begin() const {
        return iterator(min_node(pRoot));
    }

    iterator end() const {
        return iterator(nullptr);  // Like reaching EOF but for trees
    }

    ~avl_map() {
        clear(pRoot);
    }

private:
    static void clear(Node* pNode) {
        if (!pNode) return;
        clear(pNode->pLeft);
        clear(pNode->pRight);
        delete pNode;  // May you rest in heap peace 🪦
    }
};

#endif // AVL_MAP_H
