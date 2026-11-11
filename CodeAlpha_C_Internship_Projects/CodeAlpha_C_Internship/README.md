# CodeAlpha C Programming Internship Projects

This repository contains all four tasks listed in the supplied CodeAlpha C Programming task sheet.

## Projects
1. **Task 1 – Basic Calculator** (`Task1_Calculator/calculator.c`): addition, subtraction, multiplication and division using `switch`.
2. **Task 2 – Matrix Operations** (`Task2_Matrix_Operations/matrix.c`): addition, multiplication and transpose using functions and 2D arrays. Maximum dimension: 10 x 10.
3. **Task 3 – Student Management System** (`Task3_Student_Management/student.c`): add, display, search, update and delete student records using a structure and binary file storage.
4. **Task 4 – Banking System** (`Task4_Banking_System/bank.c`): deposit, withdraw, balance enquiry and exit using functions, a structure and binary file storage. A demo account is created on first run.

## Requirements
- A C compiler such as GCC (C99 or later).
- Windows: install MinGW-w64 and use `gcc` in Command Prompt.
- Linux/macOS: install GCC or Clang.

## Compile and run
Run these commands from the repository root (use `gcc` or `clang`):

```bash
gcc -std=c99 -Wall -Wextra -pedantic Task1_Calculator/calculator.c -o calculator
./calculator

gcc -std=c99 -Wall -Wextra -pedantic Task2_Matrix_Operations/matrix.c -o matrix
./matrix

gcc -std=c99 -Wall -Wextra -pedantic Task3_Student_Management/student.c -o student
./student

gcc -std=c99 -Wall -Wextra -pedantic Task4_Banking_System/bank.c -o bank
./bank
```

On Windows, run the generated `.exe` files instead of `./program`.

## Data files
- Student records are stored in `students.dat` in the current working directory.
- Banking account data is stored in `account.dat` in the current working directory.

Keep these data files with the corresponding executable if you want to retain records between runs. They are generated automatically. These are educational demonstration programs, not production banking software.

## Suggested GitHub repository name
`CodeAlpha_C_Programming_Projects`

## Before submission
1. Compile and run each program on your own computer.
2. Try valid and invalid inputs and take screenshots of successful runs.
3. Create a public GitHub repository with the suggested name and upload this folder.
4. Record a short explanation video and include the repository link in your LinkedIn post tagging `@CodeAlpha`.
5. Submit the repository link through the submission form shared by CodeAlpha.

Do not publish personal banking information or real student data in the demo files.
