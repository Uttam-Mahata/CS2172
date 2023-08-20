#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    char *name;
    int roll;
    char telephone[11];
    char *address;
} Student;

typedef struct SReg {
    int maxStuds;
    int count;
    Student **arrStudPtr;
} SReg;

Student *createStudentRecord() {
    Student *newStudent = (Student *)malloc(sizeof(Student));
    if (newStudent == NULL) {
        return NULL;
    }

    newStudent->name = (char *)malloc(100 * sizeof(char));
    if (newStudent->name == NULL) {
        free(newStudent);
        return NULL;
    }

    newStudent->address = (char *)malloc(200 * sizeof(char));
    if (newStudent->address == NULL) {
        free(newStudent->name);
        free(newStudent);
        return NULL;
    }

    printf("Enter student name: ");
    scanf("%s", newStudent->name);
    printf("Enter roll number: ");
    scanf("%d", &newStudent->roll);
    printf("Enter telephone number: ");
    scanf("%s", newStudent->telephone);
    printf("Enter address: ");
    getchar();
    fgets(newStudent->address, 200, stdin);
    newStudent->address[strcspn(newStudent->address, "\n")] = '\0';

    return newStudent;
}

Student *createStudentRecordFromFile(FILE *file) {
    Student *newStudent = (Student *)malloc(sizeof(Student));
    if (newStudent == NULL) {
        return NULL;
    }

    newStudent->name = (char *)malloc(100 * sizeof(char));
    if (newStudent->name == NULL) {
        free(newStudent);
        return NULL;
    }

    newStudent->address = (char *)malloc(200 * sizeof(char));
    if (newStudent->address == NULL) {
        free(newStudent->name);
        free(newStudent);
        return NULL;
    }

    fscanf(file, "%s%d%s\n", newStudent->name, &newStudent->roll, newStudent->telephone);
    fgets(newStudent->address, 200, file);
    newStudent->address[strcspn(newStudent->address, "\n")] = '\0';

    return newStudent;
}

void freeStudentRecord(Student *sp) {
    free(sp->name);
    free(sp->address);
    free(sp);
}

int deleteStudent(SReg *sr, int r) {
    for (int i = 0; i < sr->count; i++) {
        if (sr->arrStudPtr[i]->roll == r) {
            freeStudentRecord(sr->arrStudPtr[i]);
            for (int j = i; j < sr->count - 1; j++) {
                sr->arrStudPtr[j] = sr->arrStudPtr[j + 1];
            }
            sr->count--;
            return 1;
        }
    }
    return 0;
}

int modifyStudent(SReg *sr, Student s) {
    for (int i = 0; i < sr->count; i++) {
        if (sr->arrStudPtr[i]->roll == s.roll) {
            free(sr->arrStudPtr[i]->name);
            free(sr->arrStudPtr[i]->address);
            sr->arrStudPtr[i]->name = strdup(s.name);
            sr->arrStudPtr[i]->roll = s.roll;
            strcpy(sr->arrStudPtr[i]->telephone, s.telephone);
            sr->arrStudPtr[i]->address = strdup(s.address);
            return 1;
        }
    }
    return 0;
}

int compareStudents(const void *a, const void *b) {
    return strcmp((*(Student **)a)->name, (*(Student **)b)->name);
}

void sortStudents(SReg *sr) {
    qsort(sr->arrStudPtr, sr->count, sizeof(Student *), compareStudents);
}

int getCount(SReg *sr) {
    return sr->count;
}

void exportStudents(SReg *sr, const char *fname) {
    FILE *file = fopen(fname, "w");
    if (file == NULL) {
        printf("Error opening file for export.\n");
        return;
    }

    fprintf(file, "%d\n", sr->count);
    for (int i = 0; i < sr->count; i++) {
        fprintf(file, "%s\n%d\n%s\n%s\n", sr->arrStudPtr[i]->name, sr->arrStudPtr[i]->roll,
                sr->arrStudPtr[i]->telephone, sr->arrStudPtr[i]->address);
    }

    fclose(file);
}

void loadStudents(SReg *sr, const char *fname) {
    FILE *file = fopen(fname, "r");
    if (file == NULL) {
        printf("Error opening file for loading.\n");
        return;
    }

    int count;
    fscanf(file, "%d", &count);
    for (int i = 0; i < count; i++) {
        Student *newStudent = createStudentRecordFromFile(file);
        if (newStudent != NULL) {
            sr->arrStudPtr[sr->count] = newStudent;
            sr->count++;
        } else {
            printf("Memory allocation error.\n");
            break;
        }
    }

    fclose(file);
}

int main() {
    SReg sr;
    printf("Enter maximum number of students: ");
    scanf("%d", &sr.maxStuds);

    sr.count = 0;
    sr.arrStudPtr = (Student **)malloc(sr.maxStuds * sizeof(Student *));
    if (sr.arrStudPtr == NULL) {
        printf("Memory allocation error.\n");
        return 1;
    }

    int choice;
    do {
        printf("\n1. Add Student\n2. Print All Students\n3. Delete Student\n4. Modify Student\n");
        printf("5. Sort Students\n6. Get Student Count\n7. Export Students\n8. Load Students\n9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                if (sr.count < sr.maxStuds) {
                    Student *newStudent = createStudentRecord();
                    if (newStudent != NULL) {
                        sr.arrStudPtr[sr.count] = newStudent;
                        sr.count++;
                    } else {
                        printf("Memory allocation error.\n");
                    }
                } else {
                    printf("Student register is full.\n");
                }
                break;
            }
            case 2: {
                printf("\nStudent Records:\n");
                for (int i = 0; i < sr.count; i++) {
                    printf("\nStudent %d:\n", i + 1);
                    printf("Roll: %d\n", sr.arrStudPtr[i]->roll);
                    printf("Name: %s\n", sr.arrStudPtr[i]->name);
                    printf("Telephone: %s\n", sr.arrStudPtr[i]->telephone);
                    printf("Address: %s\n", sr.arrStudPtr[i]->address);
                }
                break;
            }
            case 3: {
                int rollToDelete;
                printf("Enter roll number to delete: ");
                scanf("%d", &rollToDelete);
                if (deleteStudent(&sr, rollToDelete)) {
                    printf("Student deleted.\n");
                } else {
                    printf("Student not found.\n");
                }
                break;
            }
            case 4: {
                Student modifiedStudent;
                printf("Enter roll number of student to modify: ");
                scanf("%d", &modifiedStudent.roll);
                printf("Enter modified student details:\n");
                printf("Name: ");
                scanf("%s", modifiedStudent.name);
                printf("Telephone: ");
                scanf("%s", modifiedStudent.telephone);
                printf("Address: ");
                getchar();
                fgets(modifiedStudent.address, 200, stdin);
                modifiedStudent.address[strcspn(modifiedStudent.address, "\n")] = '\0';
                if (modifyStudent(&sr, modifiedStudent)) {
                    printf("Student modified.\n");
                } else {
                    printf("Student not found.\n");
                }
                break;
            }
            case 5:
                sortStudents(&sr);
                printf("Students sorted by name.\n");
                break;
            case 6:
                printf("Number of students: %d\n", getCount(&sr));
                break;
            case 7: {
                char exportFileName[100];
                printf("Enter export file name: ");
                scanf("%s", exportFileName);
                exportStudents(&sr, exportFileName);
                printf("Students exported to %s.\n", exportFileName);
                break;
            }
            case 8: {
                char loadFileName[100];
                printf("Enter load file name: ");
                scanf("%s", loadFileName);
                loadStudents(&sr, loadFileName);
                printf("Students loaded from %s.\n", loadFileName);
                break;
            }
            case 9:
                printf("Exiting.\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 9);


    for (int i = 0; i < sr.count; i++) {
        freeStudentRecord(sr.arrStudPtr[i]);
    }
    free(sr.arrStudPtr);

    return 0;
}

