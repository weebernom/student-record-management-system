#pragma once
#include <string>

enum class Role { Admin, Faculty, Student };

struct Student {
    std::string regNo;
    std::string name;
    std::string department;
    int semester = 1;
    double cgpa = 0.0;
    int attendancePercent = 100;

    std::string serialize() const;
    static Student deserialize(const std::string& line);
};
