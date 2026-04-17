#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int roll;
    char name[50];
    float marks;
    struct Student* next;
};

struct Student* head = NULL;

// Functions
void addStudent();
void displayStudents();
void searchStudent();
void deleteStudent();
void sortByMarks();
void sortByName();

int main() {
    int choice;

    while(1) {
        printf("\n===== Student Record System =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Delete Student\n");
        printf("5. Sort by Marks\n");
        printf("6. Sort by Name\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: sortByMarks(); break;
            case 6: sortByName(); break;
            case 7: exit(0);
            default: printf("Invalid Choice!\n");
        }
    }
}

// Add Student
void addStudent() {
    struct Student *newNode, *temp;

    newNode = (struct Student*)malloc(sizeof(struct Student));

    printf("Enter Roll No: ");
    scanf("%d", &newNode->roll);

    printf("Enter Name: ");
    scanf(" %[^\n]", newNode->name);

    printf("Enter Marks: ");
    scanf("%f", &newNode->marks);

    newNode->next = NULL;

    if(head == NULL)
        head = newNode;
    else {
        temp = head;
        while(temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }

    printf("Student Added Successfully!\n");
}

// Display
void displayStudents() {
    struct Student* temp = head;

    if(head == NULL) {
        printf("No Records Found!\n");
        return;
    }

    while(temp != NULL) {
        printf("\nRoll: %d", temp->roll);
        printf("\nName: %s", temp->name);
        printf("\nMarks: %.2f\n", temp->marks);
        temp = temp->next;
    }
}

// Search
void searchStudent() {
    int roll;
    struct Student* temp = head;

    printf("Enter Roll No to Search: ");
    scanf("%d", &roll);

    while(temp != NULL) {
        if(temp->roll == roll) {
            printf("\nStudent Found:");
            printf("\nName: %s", temp->name);
            printf("\nMarks: %.2f\n", temp->marks);
            return;
        }
        temp = temp->next;
    }

    printf("Student Not Found!\n");
}

// Delete
void deleteStudent() {
    int roll;
    struct Student *temp = head, *prev = NULL;

    printf("Enter Roll No to Delete: ");
    scanf("%d", &roll);

    while(temp != NULL && temp->roll != roll) {
        prev = temp;
        temp = temp->next;
    }

    if(temp == NULL) {
        printf("Student Not Found!\n");
        return;
    }

    if(prev == NULL)
        head = temp->next;
    else
        prev->next = temp->next;

    free(temp);
    printf("Record Deleted Successfully!\n");
}

// Sort by Marks
void sortByMarks() {
    struct Student *i, *j;
    int rollTemp;
    char nameTemp[50];
    float marksTemp;

    for(i = head; i != NULL; i = i->next) {
        for(j = i->next; j != NULL; j = j->next) {
            if(i->marks > j->marks) {

                rollTemp = i->roll;
                i->roll = j->roll;
                j->roll = rollTemp;

                strcpy(nameTemp, i->name);
                strcpy(i->name, j->name);
                strcpy(j->name, nameTemp);

                marksTemp = i->marks;
                i->marks = j->marks;
                j->marks = marksTemp;
            }
        }
    }

    printf("Sorted by Marks Successfully!\n");
}

// Sort by Name
void sortByName() {
    struct Student *i, *j;
    int rollTemp;
    char nameTemp[50];
    float marksTemp;

    for(i = head; i != NULL; i = i->next) {
        for(j = i->next; j != NULL; j = j->next) {
            if(strcmp(i->name, j->name) > 0) {

                rollTemp = i->roll;
                i->roll = j->roll;
                j->roll = rollTemp;

                strcpy(nameTemp, i->name);
                strcpy(i->name, j->name);
                strcpy(j->name, nameTemp);

                marksTemp = i->marks;
                i->marks = j->marks;
                j->marks = marksTemp;
            }
        }
    }

    printf("Sorted by Name Successfully!\n");
}