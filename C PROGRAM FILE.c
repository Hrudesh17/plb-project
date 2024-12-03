#include <stdio.h>
#include <string.h>

#define MAX_COURSES 10
#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];
    int id;
    char courses[MAX_COURSES][MAX_NAME_LENGTH];
    int courseCount;
} Student;

Student students[MAX_STUDENTS];
int studentCount = 0;

void registerStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("Maximum student limit reached.\n");
        return;
    }
    printf("Enter student ID: ");
    int id;
    scanf("%d", &id);

    // Check if student already exists
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            printf("Student ID already exists.\n");
            return;
        }
    }

    students[studentCount].id = id;
    printf("Enter student name: ");
    getchar(); // Consume newline left by scanf
    fgets(students[studentCount].name, MAX_NAME_LENGTH, stdin);
    strtok(students[studentCount].name, "\n"); // Remove trailing newline
    students[studentCount].courseCount = 0;

    studentCount++;
    printf("Student registered successfully.\n");
}

void addCourse() {
    printf("Enter student ID: ");
    int id;
    scanf("%d", &id);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            if (students[i].courseCount >= MAX_COURSES) {
                printf("Maximum course limit reached for this student.\n");
                return;
            }

            printf("Enter course name: ");
            getchar(); // Consume newline left by scanf
            fgets(students[i].courses[students[i].courseCount], MAX_NAME_LENGTH, stdin);
            strtok(students[i].courses[students[i].courseCount], "\n"); // Remove trailing newline
            students[i].courseCount++;

            printf("Course added successfully.\n");
            return;
        }
    }
    printf("Student ID not found.\n");
}

void viewCourses() {
    printf("Enter student ID: ");
    int id;
    scanf("%d", &id);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            printf("Courses for %s:\n", students[i].name);
            for (int j = 0; j < students[i].courseCount; j++) {
                printf("%d. %s\n", j + 1, students[i].courses[j]);
            }
            return;
        }
    }
    printf("Student ID not found.\n");
}

void removeCourse() {
    printf("Enter student ID: ");
    int id;
    scanf("%d", &id);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            printf("Enter course name to remove: ");
            char courseName[MAX_NAME_LENGTH];
            getchar(); // Consume newline left by scanf
            fgets(courseName, MAX_NAME_LENGTH, stdin);
            strtok(courseName, "\n"); // Remove trailing newline

            for (int j = 0; j < students[i].courseCount; j++) {
                if (strcmp(students[i].courses[j], courseName) == 0) {
                    // Shift remaining courses
                    for (int k = j; k < students[i].courseCount - 1; k++) {
                        strcpy(students[i].courses[k], students[i].courses[k + 1]);
                    }
                    students[i].courseCount--;
                    printf("Course removed successfully.\n");
                    return;
                }
            }
            printf("Course not found.\n");
            return;
        }
    }
    printf("Student ID not found.\n");
}

void menu() {
    printf("\n--- Course Registration System ---\n");
    printf("1. Register Student\n");
    printf("2. Add Course\n");
    printf("3. View Courses\n");
    printf("4. Remove Course\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;

    do {
        menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerStudent();
                break;
            case 2:
                addCourse();
                break;
            case 3:
                viewCourses();
                break;
            case 4:
                removeCourse();
                break;
            case 5:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
