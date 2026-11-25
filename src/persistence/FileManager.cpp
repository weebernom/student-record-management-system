#include "FileManager.h"
#include <fstream>

bool FileManager::save(const StudentRepository& repo, const std::string& path) {
    std::ofstream out(path, std::ios::trunc);
    if (!out.is_open()) return false;
    for (const Student& s : repo.all()) {
        out << s.serialize() << '\n';
    }
    return true;
}

bool FileManager::load(StudentRepository& repo, const std::string& path) {
    std::ifstream in(path);
    if (!in.is_open()) return false; // ok if file doesn't exist yet
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        repo.addStudent(Student::deserialize(line));
    }
    return true;
}
