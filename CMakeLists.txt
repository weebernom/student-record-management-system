cmake_minimum_required(VERSION 3.15)
project(StudentRecordManagementSystem CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

add_executable(StudentRecordManagementSystem WIN32
    src/main.cpp
    src/core/Student.cpp
    src/core/StudentList.cpp
    src/core/HashTable.cpp
    src/core/StudentRepository.cpp
    src/persistence/FileManager.cpp
    src/gui/MainFrame.cpp
)

target_link_libraries(StudentRecordManagementSystem PRIVATE ${wxWidgets_LIBRARIES})
