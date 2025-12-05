#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STUDENT_FILE "students.txt"
#define CREDENTIAL_FILE "CREDENTIAL.txt"

struct Student {
    int roll;
    char name[50];
    float marks;
};

char currentRole[20];
char currentUser[50];

/* Function declarations */
int loginSystem();
void mainMenu();
void adminMenu();
void staffMenu();
void userMenu();
void guestMenu();

/* Student operation functions */
void addStudent();
void viewStudents();
void searchStudent();
void deleteStudent();
void updateStudent();

/* ---------------- LOGIN SYSTEM ---------------- */

int loginSystem() {
    char uname[50], pass[50];
    FILE *fp = fopen(CREDENTIAL_FILE, "r");

    if (!fp) {
        printf("Error: credentials.txt missing!\n");
        exit(1);
    }

    printf("\n===== LOGIN =====\n");
    printf("Username: ");
    scanf("%s", uname);
    printf("Password: ");
    scanf("%s", pass);

    char fileU[50], fileP[50], fileR[20];

    while (fscanf(fp, "%s %s %s", fileU, fileP, fileR) != EOF) {
        if (strcmp(uname, fileU) == 0 && strcmp(pass, fileP) == 0) {
            strcpy(currentUser, fileU);
            strcpy(currentRole, fileR);
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

/* ---------------- MAIN MENU ---------------- */

void mainMenu() {
    if (strcmp(currentRole, "ADMIN") == 0)
        adminMenu();
    else if (strcmp(currentRole, "STAFF") == 0)
        staffMenu();
    else if (strcmp(currentRole, "USER") == 0)
        userMenu();
    else
        guestMenu();
}

/* ---------------- ADMIN MENU ---------------- */

void adminMenu() {
    int ch;
    while (1) {
        printf("\n===== ADMIN MENU =====\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: return;
            default: printf("Invalid choice!\n");
        }
    }
}

/* ---------------- STAFF MENU ---------------- */

void staffMenu() {
    int ch;
    while (1) {
        printf("\n===== STAFF MENU =====\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search Student\n");
        printf("4. Logout\n");
        scanf("%d", &ch);

        switch (ch) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: return;
            default: printf("Invalid choice!\n");
        }
    }
}

/* ---------------- USER MENU ---------------- */

void userMenu() {
    int ch;
    while (1) {
        printf("\n===== USER MENU =====\n");
        printf("1. View Students\n");
        printf("2. Search Student\n");
        printf("3. Logout\n");
        scanf("%d", &ch);

        switch (ch) {
            case 1: viewStudents(); break;
            case 2: searchStudent(); break;
            case 3: return;
            default: printf("Invalid choice!\n");
        }
    }
}

/* ---------------- GUEST MENU ---------------- */

void guestMenu() {
    int ch;
    while (1) {
        printf("\n===== GUEST MENU =====\n");
        printf("1. View Students\n");
        printf("2. Logout\n");
        scanf("%d", &ch);

        switch (ch) {
            case 1: viewStudents(); break;
            case 2: return;
            default: printf("Invalid choice!\n");
        }
    }
}

/* ---------------- STUDENT FUNCTIONS ---------------- */

void addStudent() {
    struct Student s;
    FILE *fp = fopen(STUDENT_FILE, "a");

    printf("Enter Roll: ");
    scanf("%d", &s.roll);
    printf("Enter Name: ");
    scanf("%s", s.name);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fprintf(fp, "%d %s %.2f\n", s.roll, s.name, s.marks);
    fclose(fp);
    printf("Student added!\n");
}

void viewStudents() {
    struct Student s;
    FILE *fp = fopen(STUDENT_FILE, "r");

    if (!fp) {
        printf("No students found!\n");
        return;
    }

    printf("\n===== STUDENT LIST =====\n");
    while (fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) != EOF) {
        printf("Roll: %d | Name: %s | Marks: %.2f\n", s.roll, s.name, s.marks);
    }

    fclose(fp);
}

void searchStudent() {
    int r;
    struct Student s;
    FILE *fp = fopen(STUDENT_FILE, "r");

    printf("Enter Roll to search: ");
    scanf("%d", &r);

    while (fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) != EOF) {
        if (s.roll == r) {
            printf("FOUND: %s | %.2f\n", s.name, s.marks);
            fclose(fp);
            return;
        }
    }

    printf("Student not found.\n");
    fclose(fp);
}

void updateStudent() {
    int r, found = 0;
    struct Student s;
    FILE *fp = fopen(STUDENT_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    printf("Enter Roll to update: ");
    scanf("%d", &r);

    while (fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) != EOF) {
        if (s.roll == r) {
            found = 1;
            printf("Enter New Name: ");
            scanf("%s", s.name);
            printf("Enter New Marks: ");
            scanf("%f", &s.marks);
        }
        fprintf(temp, "%d %s %.2f\n", s.roll, s.name, s.marks);
    }

    fclose(fp);
    fclose(temp);
    remove(STUDENT_FILE);
    rename("temp.txt", STUDENT_FILE);

    if (found) printf("Record Updated!\n");
    else printf("Roll not found.\n");
}

void deleteStudent() {
    int r, found = 0;
    struct Student s;
    FILE *fp = fopen(STUDENT_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    printf("Enter Roll to delete: ");
    scanf("%d", &r);

    while (fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) != EOF) {
        if (s.roll != r)
            fprintf(temp, "%d %s %.2f\n", s.roll, s.name, s.marks);
        else
            found = 1;
    }

    fclose(fp);
    fclose(temp);
    remove(STUDENT_FILE);
    rename("temp.txt", STUDENT_FILE);

    if (found) printf("Student Deleted!\n");
    else printf("Roll not found.\n");
}

/* ---------------- MAIN ---------------- */

int main() {
    if (loginSystem())
        mainMenu();
    else
        printf("Login Failed!\n");

    return 0;
}
