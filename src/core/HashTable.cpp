#include "HashTable.h"

HashTable::HashTable(int bucketCount) : buckets(bucketCount, nullptr), bucketCount(bucketCount) {}

unsigned long HashTable::hash(const std::string& key) const {
    // djb2 string hash
    unsigned long h = 5381;
    for (char c : key) h = ((h << 5) + h) + static_cast<unsigned char>(c);
    return h % bucketCount;
}

void HashTable::insert(const std::string& regNo, StudentNode* node) {
    unsigned long idx = hash(regNo);
    Entry* e = new Entry{regNo, node, buckets[idx]};
    buckets[idx] = e;
}

bool HashTable::remove(const std::string& regNo) {
    unsigned long idx = hash(regNo);
    Entry* cur = buckets[idx];
    Entry* prev = nullptr;
    while (cur) {
        if (cur->key == regNo) {
            if (prev) prev->next = cur->next; else buckets[idx] = cur->next;
            delete cur;
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    return false;
}

StudentNode* HashTable::find(const std::string& regNo) const {
    unsigned long idx = hash(regNo);
    Entry* cur = buckets[idx];
    while (cur) {
        if (cur->key == regNo) return cur->value;
        cur = cur->next;
    }
    return nullptr;
}

void HashTable::clear() {
    for (auto& b : buckets) {
        Entry* cur = b;
        while (cur) {
            Entry* next = cur->next;
            delete cur;
            cur = next;
        }
        b = nullptr;
    }
}
