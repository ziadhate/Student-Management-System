#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    int id;
    char name[50];
    int age;
    float gpa;
    struct student* next;
};

struct student* head = NULL;

void addStudent();
void displayStudents();
void searchStudentByID(int id);
void updateStudent(int id);
void deleteStudent(int id);
float calculateAverageGPA();
void searchHighestGPA();

int main() {
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    int choice, id;
    while (1) {
        printf("\n===== Student Management System =====\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student by ID\n");
        printf("4. Update Student Information\n");
        printf("5. Delete Student\n");
        printf("6. Calculate Average GPA\n");
        printf("7. Find Student with Highest GPA\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            addStudent();
            break;
        case 2:
            displayStudents();
            break;
        case 3:
            printf("Enter ID to search: ");
            scanf("%d", &id);
            searchStudentByID(id);
            break;
        case 4:
            printf("Enter ID to update: ");
            scanf("%d", &id);
            updateStudent(id);
            break;
        case 5:
            printf("Enter ID to delete: ");
            scanf("%d", &id);
            deleteStudent(id);
            break;
        case 6:
            printf("Average GPA: %.2f\n", calculateAverageGPA());
            break;
        case 7:
            searchHighestGPA();
            break;
        case 8:
            printf("Exiting program...\n");
            exit(0);
        default:
            printf("Invalid choice! Try again.\n");
        }
    }
}

void addStudent() {
    struct student* newStudent, * temp;
    int id;
    char name[50];
    int age;
    float gpa;
    printf("Enter Student ID: ");
    scanf("%d", &id);
    temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            printf("Student with this ID already exists!\n");
            return;
        }
        temp = temp->next;
    }
    printf("Enter Name: ");
    scanf(" %[^\n]", name);
    printf("Enter Age: ");
    scanf("%d", &age);
    printf("Enter GPA: ");
    scanf("%f", &gpa);
    newStudent = (struct student*)malloc(sizeof(struct student));
    if (newStudent == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    newStudent->id = id;
    strcpy(newStudent->name, name);
    newStudent->age = age;
    newStudent->gpa = gpa;
    newStudent->next = NULL;
    if (head == NULL) {
        head = newStudent;
    }
    else {
        temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newStudent;
    }
    printf("Student added successfully!\n");
}

void displayStudents() {
    struct student* temp = head;
    if (temp == NULL) {
        printf("No students in the system.\n");
        return;
    }
    printf("\n--- Student List ---\n");
    while (temp != NULL) {
        printf("ID: %d | Name: %s | Age: %d | GPA: %.2f\n",
            temp->id, temp->name, temp->age, temp->gpa);
        temp = temp->next;
    }
}

void searchStudentByID(int id) {
    struct student* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            printf("ID: %d | Name: %s | Age: %d | GPA: %.2f\n",
                temp->id, temp->name, temp->age, temp->gpa);
            return;
        }
        temp = temp->next;
    }
    printf("Student not found.\n");
}

void updateStudent(int id) {
    struct student* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            printf("Enter new Name: ");
            scanf(" %[^\n]", temp->name);
            printf("Enter new Age: ");
            scanf("%d", &temp->age);
            printf("Enter new GPA: ");
            scanf("%f", &temp->gpa);
            printf("Student updated successfully!\n");
            return;
        }
        temp = temp->next;
    }
    printf("Student not found.\n");
}

void deleteStudent(int id) {
    struct student* temp = head, * prev = NULL;
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Student not found.\n");
        return;
    }
    if (prev == NULL) {
        head = temp->next;
    }
    else {
        prev->next = temp->next;
    }
    free(temp);
    printf("Student deleted successfully!\n");
}

float calculateAverageGPA() {
    struct student* temp = head;
    int count = 0;
    float sum = 0.0;
    if (temp == NULL) {
        return 0.0;
    }
    while (temp != NULL) {
        sum += temp->gpa;
        count++;
        temp = temp->next;
    }
    return (count == 0) ? 0.0 : (sum / count);
}

void searchHighestGPA() {
    struct student* temp = head;
    struct student* highest = NULL;
    if (temp == NULL) {
        printf("No students in the system.\n");
        return;
    }
    highest = temp;
    temp = temp->next;
    while (temp != NULL) {
        if (temp->gpa > highest->gpa) {
            highest = temp;
        }
        temp = temp->next;
    }
    printf("Highest GPA Student: ID: %d | Name: %s | Age: %d | GPA: %.2f\n",
        highest->id, highest->name, highest->age, highest->gpa);
}
