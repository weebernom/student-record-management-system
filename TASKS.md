# Task Breakdown — Student Record Management System

4 members, 4 ownership areas mapped to the existing code structure in `src/`.
Each person works on their own files and commits under their **own GitHub
account** — the instructor explicitly checks for commits from all members,
spread across multiple days, not a single dump.

## Member 1 — Muhammad Momin (2025581)
**Area: Project setup + Core model + Linked List**
- `CMakeLists.txt`, `src/main.cpp`
- `src/core/Student.h` / `.cpp` — the record struct + serialize/deserialize
- `src/core/StudentList.h` / `.cpp` — singly linked list, merge sort
- DSA concepts: Linked List, Merge Sort, Time Complexity Analysis
- Everyone else's work builds on this, so it should land first.

## Member 2 — Qasim Malik (2025597)
**Area: Hash Table + Repository layer**
- `src/core/HashTable.h` / `.cpp` — separate-chaining hash table
- `src/core/StudentRepository.h` / `.cpp` — ties list + hash table together
- DSA concepts: Hashing, combined data structure usage
- Depends on Member 1's `Student`/`StudentList` existing first.

## Member 3 — Noor Uddin Malik (2025376)
**Area: File handling + Admin/Faculty feature logic**
- `src/persistence/FileManager.h` / `.cpp` — save/load records to disk
- Admin-specific logic: add/update/delete student, manage faculty
- Faculty-specific logic: record/update attendance & grades
- DSA concepts: File Handling
- Depends on Member 2's `StudentRepository` existing first.

## Member 4 — Muhammad Furqan (2025514)
**Area: GUI + Student role + integration/testing**
- `src/gui/MainFrame.h` / `.cpp` — wxWidgets interface, wires everything together
- Student-role view (read-only access to own record)
- End-to-end testing, screenshots for documentation, final polish
- Depends on everyone else's pieces existing first — naturally lands last.

## Suggested commit timeline (spread across ~2 weeks)

| Day | Who | Commit |
|---|---|---|
| 1 | Momin | Project scaffold, CMakeLists, `Student` struct |
| 2 | Momin | `StudentList` (linked list) + merge sort |
| 3 | Qasim | `HashTable` implementation |
| 4 | Qasim | `StudentRepository` integrating list + hash table |
| 5 | Noor | `FileManager` save/load |
| 6 | Noor | Admin feature logic (add/update/delete wired to repository) |
| 7 | Furqan | `MainFrame` GUI shell, wired to repository |
| 8 | Noor | Faculty feature logic (attendance/grades) |
| 9 | Furqan | Student-role read-only view |
| 10 | Everyone | Bug fixes from testing (each commits their own fixes) |
| 11 | Furqan | Screenshots + documentation polish |
| 12 | Momin | Final review + README updates |

## Before anyone pushes

1. Each member needs **collaborator access** on the GitHub repo
   (https://github.com/weebernom/student-record-management-system) — send
   their GitHub usernames so they can be added, or have them fork + open a
   pull request instead.
2. Each member should set their own git identity locally so commits are
   attributed correctly:
   ```bash
   git config user.name "Your Name"
   git config user.email "your-github-email@example.com"
   ```
3. Commit in small, logical pieces as you finish each file — not one giant
   commit with everything at the end.
