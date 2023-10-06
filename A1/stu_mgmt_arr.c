
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 10


typedef struct {
    char name[50];
    int roll;
    char telephone[20];
    char address[100];
} Student;


typedef struct {
    Student students[MAX_STUDENTS];
    int count;
} SReg;


int add(SReg *sr, Student s) {
    for (int i = 0; i < sr->count; i++) {
        if (sr->students[i].roll == s.roll) {
            return 0;
        }
    }
    sr->students[sr->count] = s;
    sr->count++;
    return 1;
}


Student get(SReg sr, int r) {
    Student notFound = {"", 0, "", ""};
    for (int i = 0; i < sr.count; i++) {
        if (sr.students[i].roll == r) {
            return sr.students[i];
        }
    }
    return notFound;
}


int delete(SReg *sr, int r) {
    for (int i = 0; i < sr->count; i++) {
        if (sr->students[i].roll == r) {
            for (int j = i; j < sr->count - 1; j++) {
                sr->students[j] = sr->students[j + 1];
            }
            sr->count--;
            return 1;
        }
    }
    return 0;
}


int modify(SReg *sr, Student s) {
    for (int i = 0; i < sr->count; i++) {
        if (sr->students[i].roll == s.roll) {
            sr->students[i] = s;
            return 1;
        }
    }
    return 0;
}


void sortStudents(SReg *sr) {
    for (int i = 0; i < sr->count - 1; i++) {
        for (int j = i + 1; j < sr->count; j++) {
            if (strcmp(sr->students[i].name, sr->students[j].name) > 0) {
                Student temp = sr->students[i];
                sr->students[i] = sr->students[j];
                sr->students[j] = temp;
            }
        }
    }
}

int getCount(SReg sr) {
    return sr.count;
}

void export(SReg sr, const char *fname) {
    FILE *file = fopen(fname, "w");
    if (file == NULL) {
        printf("Error opening file for export.\n");
        return;
    }

    for (int i = 0; i < sr.count; i++) {
        fprintf(file, "%s,%d,%s,%s\n", sr.students[i].name, sr.students[i].roll, sr.students[i].telephone, sr.students[i].address);
    }

    fclose(file);

}

void load(SReg *sr, const char *fname) {
    FILE *file = fopen(fname, "r");
    if (file == NULL) {
        printf("Error opening file for load.\n");
        return;
    }

    Student s;
    while (fscanf(file, "%[^,],%d,%[^,],%[^\n]\n", s.name, &s.roll, s.telephone, s.address) != EOF) {
        add(sr, s);
    }

    fclose(file);

}


int main() {
    SReg stuReg;
    stuReg.count=0;
    int choice, roll;
    Student tempStudent;

    do {
        printf("\nStudent Register Menu:\n");
        printf("1. Add Student\n");
        printf("2. Get Student\n");
        printf("3. Delete Student\n");
        printf("4. Modify Student\n");
        printf("5. Sort Students\n");
        printf("6. Count Student\n");
        printf("7. Export to File\n");
        printf("8. Load from File\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter student name: ");
                scanf(" %[^\n]s", tempStudent.name);
                printf("Enter roll number: ");
                scanf("%d", &tempStudent.roll);
                printf("Enter telephone: ");
                scanf(" %[^\n]s", tempStudent.telephone);
                printf("Enter address: ");
                scanf(" %[^\n]s", tempStudent.address);
                if (add(&stuReg, tempStudent)) {
                    printf("Student added successfully.\n");
                } else {
                    printf("Student with the same roll number already exists.\n");
                }
                break;

            case 2:
                printf("Enter roll number: ");
                scanf("%d", &roll);
                tempStudent = get(stuReg, roll);
                if (tempStudent.roll == 0) {
                    printf("Student not found.\n");
                } else {
                    printf("Student found:\n");
                    printf("Name: %s\n", tempStudent.name);
                    printf("Roll: %d\n", tempStudent.roll);
                    printf("Telephone: %s\n", tempStudent.telephone);
                    printf("Address: %s\n", tempStudent.address);
                }
                break;

            case 3:
                printf("Enter roll number: ");
                scanf("%d", &roll);
                if (delete(&stuReg, roll)) {
                    printf("Student deleted successfully.\n");
                } else {
                    printf("Student not found.\n");
                }
                break;

            case 4:
                printf("Enter roll number: ");
                scanf("%d", &roll);
                tempStudent = get(stuReg, roll);
                if (tempStudent.roll == 0) {
                    printf("Student not found.\n");
                } else {
                    printf("Enter updated information:\n");
                    printf("Enter student name: ");
                    scanf(" %[^\n]s", tempStudent.name);
                    printf("Enter telephone: ");
                    scanf(" %[^\n]s", tempStudent.telephone);
                    printf("Enter address: ");
                    scanf(" %[^\n]s", tempStudent.address);
                    if (modify(&stuReg, tempStudent)) {
                        printf("Student modified successfully.\n");
                    } else {
                        printf("Student not found.\n");
                    }
                }
                break;

            case 5:
                sortStudents(&stuReg);
                printf("Students sorted by name.\n");
                break;

            case 6:
                printf("Total students: %d\n", getCount(stuReg));
                break;

            case 7:
                printf("Enter file name for export: ");
                char exportFileName[50];
                scanf(" %[^\n]s", exportFileName);
                export(stuReg, exportFileName);
                printf("Student register exported to %s.\n", exportFileName);
                break;

            case 8:
                printf("Enter file name for import: ");
                char importFileName[50];
                scanf(" %[^\n]s", importFileName);
                load(&stuReg, importFileName);
                printf("Student register loaded from %s.\n", importFileName);
                break;

            case 9:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 9);

    return 0;
}

