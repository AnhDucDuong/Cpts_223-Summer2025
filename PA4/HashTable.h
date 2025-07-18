#pragma once
#include <functional>

template<typename K, typename V>
class HashTable {
private:
    struct Entry {
        K key;
        V value;
        Entry* next;
        Entry(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
    };

    Entry** table;
    size_t capacity;
    std::hash<K> hasher;

    size_t getIndex(const K& key) const {
        return hasher(key) % capacity;
    }

public:
    HashTable(size_t cap = 10007) : capacity(cap) {
        table = new Entry*[capacity];
        for (size_t i = 0; i < capacity; ++i) table[i] = nullptr;
    }

    ~HashTable() {
        for (size_t i = 0; i < capacity; ++i) {
            Entry* curr = table[i];
            while (curr) {
                Entry* temp = curr;
                curr = curr->next;
                delete temp;
            }
        }
        delete[] table;
    }

    void insert(const K& key, const V& value) {
        size_t idx = getIndex(key);
        Entry* newEntry = new Entry(key, value);
        newEntry->next = table[idx];
        table[idx] = newEntry;
    }

    bool get(const K& key, V& outVal) const {
        size_t idx = getIndex(key);
        Entry* curr = table[idx];
        while (curr) {
            if (curr->key == key) {
                outVal = curr->value;
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

    bool exists(const K& key) const {
        V dummy;
        return get(key, dummy);
    }
};
