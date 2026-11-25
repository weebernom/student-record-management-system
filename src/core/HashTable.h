#pragma once
#include "StudentList.h"
#include <string>
#include <vector>

// Separate-chaining hash table mapping regNo -> StudentNode*, for O(1)
// average-case lookup on top of the StudentList's O(n) linked storage.
class HashTable {
public:
    explicit HashTable(int bucketCount = 101);

    void insert(const std::string& regNo, StudentNode* node);
    bool remove(const std::string& regNo);
    StudentNode* find(const std::string& regNo) const;
    void clear();

private:
    struct Entry {
        std::string key;
        StudentNode* value;
        Entry* next;
    };

    std::vector<Entry*> buckets;
    int bucketCount;

    unsigned long hash(const std::string& key) const;
};
