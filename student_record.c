#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int roll;
    char name[50];
    float marks;
    struct Student *next;
};

struct Student *head = NULL;

// Function declarations
void loadFromFile();
void saveToFile();
void addStudent();
void displayStudents();
void searchStudent();
void deleteStudent();
void sortByMarks();
void sortByName();

int main() {
    int choice;

    loadFromFile();

    while (1) {
        printf("\n===== Student Record System =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Delete Student\n");
        printf("5. Sort by Marks\n");
        printf("6. Sort by Name\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: sortByMarks(); saveToFile(); break;
            case 6: sortByName(); saveToFile(); break;
            case 7: saveToFile(); exit(0);
            default: printf("Invalid Choice!\n");
        }
    }
}

// Load records from file
void loadFromFile() {
    FILE *fp = fopen("students.txt", "r");
    if(fp == NULL) return;

    struct Student *newNode, *temp;

    while(1) {
        newNode = (struct Student*)malloc(sizeof(struct Student));

        if(fscanf(fp, "%d,%49[^,],%f\n",
            &newNode->roll,
            newNode->name,
            &newNode->marks) != 3) {
            free(newNode);
            break;
        }

        newNode->next = NULL;

        if(head == NULL)
            head = newNode;
        else {
            temp = head;
            while(temp->next != NULL)
                temp = temp->next;
            temp->next = newNode;
        }
    }

    fclose(fp);
}

// Save records to file
void saveToFile() {
    FILE *fp = fopen("students.txt", "w");
    struct Student *temp = head;

    while(temp != NULL) {
        fprintf(fp, "%d,%s,%.2f\n",
            temp->roll,
            temp->name,
            temp->marks);

        temp = temp->next;
    }

    fclose(fp);
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

    saveToFile();
    printf("Student Added Successfully!\n");
}

// Display
void displayStudents() {
    struct Student *temp = head;

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
    struct Student *temp = head;

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
    saveToFile();

    printf("Record Deleted Successfully!\n");
}

// Sort by Marks
void sortByMarks() {
    struct Student *i, *j;
    int r;
    char n[50];
    float m;

    for(i=head;i!=NULL;i=i->next) {
        for(j=i->next;j!=NULL;j=j->next) {
            if(i->marks > j->marks) {

                r=i->roll; i->roll=j->roll; j->roll=r;
                strcpy(n,i->name); strcpy(i->name,j->name); strcpy(j->name,n);
                m=i->marks; i->marks=j->marks; j->marks=m;
            }
        }
    }

    printf("Sorted by Marks Successfully!\n");
}

// Sort by Name
void sortByName() {
    struct Student *i, *j;
    int r;
    char n[50];
    float m;

    for(i=head;i!=NULL;i=i->next) {
        for(j=i->next;j!=NULL;j=j->next) {
            if(strcmp(i->name,j->name)>0) {

                r=i->roll; i->roll=j->roll; j->roll=r;
                strcpy(n,i->name); strcpy(i->name,j->name); strcpy(j->name,n);
                m=i->marks; i->marks=j->marks; j->marks=m;
            }
        }
    }

    printf("Sorted by Name Successfully!\n");
}