#include "Student.h"
#include <sstream>
#include <vector>

static std::vector<std::string> splitFields(const std::string& line, char delim) {
    std::vector<std::string> fields;
    std::stringstream ss(line);
    std::string field;
    while (std::getline(ss, field, delim)) {
        fields.push_back(field);
    }
    return fields;
}

std::string Student::serialize() const {
    std::ostringstream oss;
    oss << regNo << '|' << name << '|' << department << '|'
        << semester << '|' << cgpa << '|' << attendancePercent;
    return oss.str();
}

Student Student::deserialize(const std::string& line) {
    std::vector<std::string> f = splitFields(line, '|');
    Student s;
    if (f.size() < 6) return s;
    s.regNo = f[0];
    s.name = f[1];
    s.department = f[2];
    s.semester = std::stoi(f[3]);
    s.cgpa = std::stod(f[4]);
    s.attendancePercent = std::stoi(f[5]);
    return s;
}
