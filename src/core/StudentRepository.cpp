#include "StudentRepository.h"

StudentRepository::StudentRepository() : index(101) {}

void StudentRepository::rebuildIndex() {
    index.clear();
    for (const Student& s : list.toVector()) {
        StudentNode* node = list.findByRegNo(s.regNo);
        if (node) index.insert(s.regNo, node);
    }
}

bool StudentRepository::addStudent(const Student& s) {
    if (index.find(s.regNo)) return false;
    list.pushBack(s);
    StudentNode* node = list.findByRegNo(s.regNo);
    index.insert(s.regNo, node);
    return true;
}

bool StudentRepository::removeStudent(const std::string& regNo) {
    if (!index.find(regNo)) return false;
    index.remove(regNo);
    return list.removeByRegNo(regNo);
}

std::optional<Student> StudentRepository::findStudent(const std::string& regNo) const {
    StudentNode* node = index.find(regNo);
    if (!node) return std::nullopt;
    return node->data;
}

bool StudentRepository::updateStudent(const Student& s) {
    StudentNode* node = index.find(s.regNo);
    if (!node) return false;
    node->data = s;
    return true;
}

std::vector<Student> StudentRepository::all() const {
    return list.toVector();
}

void StudentRepository::sortByName() {
    list.sort([](const Student& a, const Student& b) { return a.name < b.name; });
    rebuildIndex();
}

void StudentRepository::sortByCgpa() {
    list.sort([](const Student& a, const Student& b) { return a.cgpa > b.cgpa; });
    rebuildIndex();
}

void StudentRepository::sortByRegNo() {
    list.sort([](const Student& a, const Student& b) { return a.regNo < b.regNo; });
    rebuildIndex();
}
