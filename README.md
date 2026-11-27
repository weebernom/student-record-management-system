# Student Record Management System

CS-222 (Data Structures & Algorithms) semester project — GIKI, Fall 2025.

A C++ desktop GUI application (wxWidgets) for managing student academic
records. Core data structures are implemented from scratch:

- **Linked list** (`StudentList`) — ordered storage of records, with an
  in-place **merge sort** for sorting by name/CGPA/registration number.
- **Hash table** (`HashTable`, separate chaining) — O(1) average lookup
  by registration number, layered on top of the linked list.
- **File handling** (`FileManager`) — persists records to `data/students.dat`
  next to the executable.

## Project layout

```
src/
  core/         Student model, linked list, hash table, repository
  persistence/  File save/load
  gui/          wxWidgets UI (MainFrame)
  main.cpp      Application entry point
```

## Building on Windows (MSYS2 / MinGW-w64)

Install the toolchain once:

```bash
pacman -S mingw-w64-x86_64-cmake mingw-w64-x86_64-wxwidgets3.2-msw mingw-w64-x86_64-ninja
```

Then build:

```bash
cmake -G Ninja -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

The resulting `StudentRecordManagementSystem.exe` is in `build/`.

## Building on Linux

Install the toolchain once (Debian/Ubuntu):

```bash
sudo apt install build-essential cmake libwxgtk3.2-dev
```

Then build:

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

The resulting executable is `build/StudentRecordManagementSystem`.

## Known issues

- On Windows, `cmake -G Ninja -B build` can fail to locate wxWidgets with an
  error like `wx/version.h file not found in C:/Program;C:/Program` if any
  directory in `PATH` contains a space (e.g. `C:\Program Files\...`). Run the
  configure step from a shell where MSYS2's `mingw64/bin` is placed before
  any space-containing paths, or strip those paths for the command.
