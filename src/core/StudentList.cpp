#include "StudentList.h"

StudentList::~StudentList() {
    StudentNode* cur = head;
    while (cur) {
        StudentNode* next = cur->next;
        delete cur;
        cur = next;
    }
}

void StudentList::pushBack(const Student& s) {
    StudentNode* node = new StudentNode(s);
    if (!head) {
        head = tail = node;
    } else {
        tail->next = node;
        tail = node;
    }
    count++;
}

bool StudentList::removeByRegNo(const std::string& regNo) {
    StudentNode* cur = head;
    StudentNode* prev = nullptr;
    while (cur) {
        if (cur->data.regNo == regNo) {
            if (prev) prev->next = cur->next; else head = cur->next;
            if (cur == tail) tail = prev;
            delete cur;
            count--;
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    return false;
}

StudentNode* StudentList::findByRegNo(const std::string& regNo) const {
    StudentNode* cur = head;
    while (cur) {
        if (cur->data.regNo == regNo) return cur;
        cur = cur->next;
    }
    return nullptr;
}

std::vector<Student> StudentList::toVector() const {
    std::vector<Student> out;
    out.reserve(count);
    StudentNode* cur = head;
    while (cur) {
        out.push_back(cur->data);
        cur = cur->next;
    }
    return out;
}

void StudentList::forEach(const std::function<void(const Student&)>& fn) const {
    StudentNode* cur = head;
    while (cur) {
        fn(cur->data);
        cur = cur->next;
    }
}

StudentNode* StudentList::merge(StudentNode* a, StudentNode* b, const std::function<bool(const Student&, const Student&)>& less) {
    StudentNode dummy(Student{});
    StudentNode* tailPtr = &dummy;
    while (a && b) {
        if (less(b->data, a->data)) {
            tailPtr->next = b; b = b->next;
        } else {
            tailPtr->next = a; a = a->next;
        }
        tailPtr = tailPtr->next;
    }
    tailPtr->next = a ? a : b;
    return dummy.next;
}

StudentNode* StudentList::mergeSort(StudentNode* node, const std::function<bool(const Student&, const Student&)>& less) {
    if (!node || !node->next) return node;

    // Split using slow/fast pointers.
    StudentNode* slow = node;
    StudentNode* fast = node->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    StudentNode* rightHalf = slow->next;
    slow->next = nullptr;

    StudentNode* left = mergeSort(node, less);
    StudentNode* right = mergeSort(rightHalf, less);
    return merge(left, right, less);
}

void StudentList::sort(const std::function<bool(const Student&, const Student&)>& less) {
    head = mergeSort(head, less);
    tail = head;
    if (tail) {
        while (tail->next) tail = tail->next;
    }
}
