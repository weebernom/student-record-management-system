#pragma once
#include "Student.h"
#include <vector>
#include <functional>

struct StudentNode {
    Student data;
    StudentNode* next;
    explicit StudentNode(const Student& s) : data(s), next(nullptr) {}
};

// Singly linked list holding all student records in insertion order.
class StudentList {
public:
    StudentList() = default;
    ~StudentList();

    StudentList(const StudentList&) = delete;
    StudentList& operator=(const StudentList&) = delete;

    void pushBack(const Student& s);
    bool removeByRegNo(const std::string& regNo);
    StudentNode* findByRegNo(const std::string& regNo) const;

    std::vector<Student> toVector() const;
    void forEach(const std::function<void(const Student&)>& fn) const;

    int size() const { return count; }

    // In-place merge sort by a comparison function (e.g. by CGPA, by name).
    void sort(const std::function<bool(const Student&, const Student&)>& less);

private:
    StudentNode* head = nullptr;
    StudentNode* tail = nullptr;
    int count = 0;

    static StudentNode* mergeSort(StudentNode* node, const std::function<bool(const Student&, const Student&)>& less);
    static StudentNode* merge(StudentNode* a, StudentNode* b, const std::function<bool(const Student&, const Student&)>& less);
};
