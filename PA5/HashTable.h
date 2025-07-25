#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <string>

template <typename K, typename V>
class HashTable {
private:
    struct Entry {
        K key;
        V value;
        Entry* next;
        Entry(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
    };

    size_t capacity;
    size_t size;
    std::vector<Entry*> table;

    size_t hash(const K& key) const {
        std::hash<K> hasher;
        return hasher(key) % capacity;
    }

public:
    HashTable(size_t cap = 101) : capacity(cap), size(0), table(cap, nullptr) {}

    ~HashTable() {
        for (Entry* head : table) {
            while (head) {
                Entry* temp = head;
                head = head->next;
                delete temp;
            }
        }
    }

    void insert(const K& key, const V& value) {
        size_t idx = hash(key);
        Entry* head = table[idx];

        while (head) {
            if (head->key == key) {
                head->value = value;
                return;
            }
            head = head->next;
        }

        Entry* newEntry = new Entry(key, value);
        newEntry->next = table[idx];
        table[idx] = newEntry;
        ++size;
    }

    bool get(const K& key, V& value) const {
        size_t idx = hash(key);
        Entry* head = table[idx];

        while (head) {
            if (head->key == key) {
                value = head->value;
                return true;
            }
            head = head->next;
        }

        return false;
    }

    bool containsKey(const K& key) const {
        V dummy;
        return get(key, dummy);
    }

    bool remove(const K& key) {
        size_t idx = hash(key);
        Entry* head = table[idx];
        Entry* prev = nullptr;

        while (head) {
            if (head->key == key) {
                if (prev) prev->next = head->next;
                else table[idx] = head->next;
                delete head;
                --size;
                return true;
            }
            prev = head;
            head = head->next;
        }

        return false;
    }

    size_t getSize() const {
        return size;
    }

    size_t getCapacity() const {
        return capacity;
    }
};

#endif
