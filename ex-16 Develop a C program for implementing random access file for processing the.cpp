#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "employees.dat"

struct Employee {
    int id;
    char name[30];
    float salary;
};

void addEmployee() {
    FILE *fp = fopen(FILENAME, "ab"); // append in binary mode
    struct Employee emp;

    printf("Enter Employee ID: ");
    scanf("%d", &emp.id);
    printf("Enter Name: ");
    scanf("%s", emp.name);
    printf("Enter Salary: ");
    scanf("%f", &emp.salary);

    fwrite(&emp, sizeof(emp), 1, fp);
    fclose(fp);
    printf("Employee added successfully.\n");
}

void displayAll() {
    FILE *fp = fopen(FILENAME, "rb");
    struct Employee emp;

    printf("\n--- Employee Records ---\n");
    while (fread(&emp, sizeof(emp), 1, fp)) {
        printf("ID: %d, Name: %s, Salary: %.2f\n", emp.id, emp.name, emp.salary);
    }
    fclose(fp);
}

void updateEmployee() {
    FILE *fp = fopen(FILENAME, "rb+");
    struct Employee emp;
    int id, found = 0;

    printf("Enter Employee ID to update: ");
    scanf("%d", &id);

    while (fread(&emp, sizeof(emp), 1, fp)) {
        if (emp.id == id) {
            found = 1;
            printf("Enter new name: ");
            scanf("%s", emp.name);
            printf("Enter new salary: ");
            scanf("%f", &emp.salary);

            fseek(fp, -sizeof(emp), SEEK_CUR); // move back to overwrite
            fwrite(&emp, sizeof(emp), 1, fp);
            printf("Employee updated successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Employee ID not found.\n");
    }

    fclose(fp);
}

void searchEmployee() {
    FILE *fp = fopen(FILENAME, "rb");
    struct Employee emp;
    int id, found = 0;

    printf("Enter Employee ID to search: ");
    scanf("%d", &id);

    while (fread(&emp, sizeof(emp), 1, fp)) {
        if (emp.id == id) {
            printf("ID: %d, Name: %s, Salary: %.2f\n", emp.id, emp.name, emp.salary);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Employee not found.\n");
    }

    fclose(fp);
}

int main() {
    int choice;

    while (1) {
        printf("\n--- Employee Management ---\n");
        printf("1. Add Employee\n");
        printf("2. Display All Employees\n");
        printf("3. Update Employee\n");
        printf("4. Search Employee\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: displayAll(); break;
            case 3: updateEmployee(); break;
            case 4: searchEmployee(); break;
            case 5: exit(0);
            default: printf("Invalid choice.\n");
        }
    }

    return 0;
}