#pragma once
#include "StudentList.h"
#include "HashTable.h"
#include <optional>

// Combines the linked list (ordered storage) with the hash table
// (fast lookup) behind one interface used by the GUI and persistence layers.
class StudentRepository {
public:
    StudentRepository();

    bool addStudent(const Student& s);          // fails if regNo already exists
    bool removeStudent(const std::string& regNo);
    std::optional<Student> findStudent(const std::string& regNo) const;
    bool updateStudent(const Student& s);        // regNo must already exist

    std::vector<Student> all() const;
    int count() const { return list.size(); }

    void sortByName();
    void sortByCgpa();
    void sortByRegNo();

private:
    StudentList list;
    HashTable index;

    void rebuildIndex();
};
