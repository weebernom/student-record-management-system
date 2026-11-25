#pragma once
#include "../core/StudentRepository.h"
#include <string>

class FileManager {
public:
    static bool save(const StudentRepository& repo, const std::string& path);
    static bool load(StudentRepository& repo, const std::string& path);
};
