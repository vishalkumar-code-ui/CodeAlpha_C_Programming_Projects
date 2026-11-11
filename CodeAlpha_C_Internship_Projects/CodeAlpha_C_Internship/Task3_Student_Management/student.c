#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_FILE "students.dat"
#define NAME_LEN 60

typedef struct {
    int id;
    char name[NAME_LEN];
    float marks;
} Student;

static void clearLine(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {}
}

static int findStudent(int id, Student *found) {
    FILE *fp = fopen(DATA_FILE, "rb");
    Student s;
    if (!fp) return 0;
    while (fread(&s, sizeof s, 1, fp) == 1) {
        if (s.id == id) {
            if (found) *found = s;
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

static void addStudent(void) {
    Student s;
    FILE *fp;
    printf("Student ID: ");
    if (scanf("%d", &s.id) != 1) { clearLine(); puts("Invalid ID."); return; }
    clearLine();
    if (findStudent(s.id, NULL)) { puts("That ID already exists."); return; }
    printf("Student name: ");
    if (!fgets(s.name, sizeof s.name, stdin)) return;
    s.name[strcspn(s.name, "\n")] = '\0';
    if (s.name[0] == '\0') { puts("Name cannot be empty."); return; }
    printf("Marks (0-100): ");
    if (scanf("%f", &s.marks) != 1 || s.marks < 0 || s.marks > 100) {
        clearLine(); puts("Enter marks from 0 to 100."); return;
    }
    fp = fopen(DATA_FILE, "ab");
    if (!fp) { perror("Could not open student file"); return; }
    if (fwrite(&s, sizeof s, 1, fp) != 1) puts("Could not save record.");
    else puts("Student added successfully.");
    fclose(fp);
}

static void displayStudents(void) {
    FILE *fp = fopen(DATA_FILE, "rb");
    Student s;
    int count = 0;
    if (!fp) { puts("No student records yet."); return; }
    printf("\n%-8s %-30s %s\n", "ID", "NAME", "MARKS");
    while (fread(&s, sizeof s, 1, fp) == 1) {
        printf("%-8d %-30s %.2f\n", s.id, s.name, s.marks);
        count++;
    }
    if (!count) puts("No student records yet.");
    fclose(fp);
}

static void searchStudent(void) {
    int id;
    Student s;
    printf("Enter student ID: ");
    if (scanf("%d", &id) != 1) { clearLine(); puts("Invalid ID."); return; }
    if (findStudent(id, &s))
        printf("Found: ID=%d, Name=%s, Marks=%.2f\n", s.id, s.name, s.marks);
    else puts("Student not found.");
}

static void updateStudent(void) {
    int id, updated = 0;
    Student s;
    FILE *fp;
    printf("Enter student ID to update: ");
    if (scanf("%d", &id) != 1) { clearLine(); puts("Invalid ID."); return; }
    clearLine();
    fp = fopen(DATA_FILE, "rb+");
    if (!fp) { puts("No student records found."); return; }
    while (fread(&s, sizeof s, 1, fp) == 1) {
        if (s.id == id) {
            printf("New name: ");
            if (!fgets(s.name, sizeof s.name, stdin)) break;
            s.name[strcspn(s.name, "\n")] = '\0';
            printf("New marks (0-100): ");
            if (scanf("%f", &s.marks) != 1 || s.marks < 0 || s.marks > 100 || s.name[0] == '\0') {
                clearLine(); puts("Invalid details; record unchanged."); fclose(fp); return;
            }
            fseek(fp, -(long)sizeof s, SEEK_CUR);
            if (fwrite(&s, sizeof s, 1, fp) == 1) updated = 1;
            break;
        }
    }
    fclose(fp);
    puts(updated ? "Student updated." : "Student not found or update failed.");
}

static void deleteStudent(void) {
    int id, deleted = 0;
    Student s;
    FILE *in = fopen(DATA_FILE, "rb");
    FILE *out;
    if (!in) { puts("No student records found."); return; }
    printf("Enter student ID to delete: ");
    if (scanf("%d", &id) != 1) { clearLine(); fclose(in); puts("Invalid ID."); return; }
    out = fopen("students.tmp", "wb");
    if (!out) { fclose(in); perror("Could not create temporary file"); return; }
    while (fread(&s, sizeof s, 1, in) == 1) {
        if (s.id == id) deleted = 1;
        else if (fwrite(&s, sizeof s, 1, out) != 1) {
            puts("File write error."); fclose(in); fclose(out); remove("students.tmp"); return;
        }
    }
    fclose(in); fclose(out);
    if (remove(DATA_FILE) != 0 || rename("students.tmp", DATA_FILE) != 0)
        puts("Could not replace data file.");
    else puts(deleted ? "Student deleted." : "Student ID not found.");
}

int main(void) {
    int choice;
    for (;;) {
        printf("\n=== Student Management System ===\n");
        printf("1. Add\n2. Display\n3. Search\n4. Update\n5. Delete\n0. Exit\nChoose: ");
        if (scanf("%d", &choice) != 1) { clearLine(); puts("Please enter a number."); continue; }
        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 0: puts("Goodbye."); return 0;
            default: puts("Invalid menu option.");
        }
    }
}
