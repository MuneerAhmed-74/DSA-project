# DSA-project

Patient Registration and Management System, a console application in C++ built for the Data Structures and Algorithms course.

## Features

- Register, update, delete, search and display patients
- Auto-generated patient IDs (P-001, P-002, ...)
- Input validation: age range, 11-digit contact number, gender selection menu, automatic name capitalization
- Update a single field (name, age, gender or contact) from a menu
- Patients are stored in a vector (dynamic array) and kept sorted by ID
- Binary search for looking up a patient by ID
- Records are loaded from `patients.txt` on start and saved on exit

## Build and run

```
g++ main.cpp PatientList.cpp -o main
./main
```

On Windows run `main.exe` instead of `./main`.

## Project structure

| File | Purpose |
|------|---------|
| `Patient.h` | `Patient` struct and ID formatting |
| `PatientList.h` / `PatientList.cpp` | Patient storage, sorting, searching and file handling |
| `main.cpp` | Menu and user input |

## Notes

- `patients.txt` is created at runtime and is ignored by git.
- Data is saved when the program exits normally through option 0.
