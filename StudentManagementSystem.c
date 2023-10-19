#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 5
#define MAX_STUDENTS 10
#define MAX_NAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 20
#define MAX_EMAIL_LENGTH 30
#define MAX_ROLE_LENGTH 20

struct User {
    char name[MAX_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char username[MAX_NAME_LENGTH];
    int rollNumber;
    float marks;
    char role[MAX_ROLE_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

struct Student {
    char name[MAX_NAME_LENGTH];
    int roll_number;
};

struct User users[MAX_USERS];
int userCount = 0;

struct Student students[MAX_STUDENTS];
int studentCount = 0;

// User Define Functions
void loadUsersFromFile();
void saveUsersToFile();
void registerUser();
int login();
void addStudentRecord();
void updateStudentRecord();
void deleteStudentRecord();
void displayStudentRecords();
void admin();

int main() {
    int choice;
    int loggedInUserIndex = -1;

    // Load user data from a file
    loadUsersFromFile();

    while (1) {
    /* //printf("\n\n\n\n\n");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t        = WELCOME TO STUDENT RECORD MANAGEMENT SYSTEM =");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\n\n\n\n"); */
	    printf("\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loggedInUserIndex = login();
                if (loggedInUserIndex == 1) {
                    printf("User login successful.\n");
                    // Perform regular user tasks
                } else if (loggedInUserIndex == 2) {
 	   	  	   	    printf("Admin login successful.\n");
                    // Perform regular admin tasks
                    admin();
  	  		    } else {
                    printf("Login failed.\n");
                }
                break;
            case 3:
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void admin() {
    int ch;

    while (1) {
		  
        // system("cls");
        printf("\n");
        printf("-------------------------------------\n");
        printf("Admin Panel\n");
        printf("-------------------------------------\n");
        printf("1. Update Student Record\n");
        printf("2. Delete Student Record\n");
        printf("3. Display Student Records\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                updateStudentRecord();
                break;
            case 2:
                deleteStudentRecord();
                break;
            case 3:
                displayStudentRecords();
                break;
            case 4:
                printf("Exiting the program.\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    
}

// Function to read user data from a text file
void loadUsersFromFile() {
    FILE *file = fopen("Login_User_Data.txt", "r");
    if (file == NULL) {
        // If the file does not exist, create a default admin account
        struct User adminUser;
        if (strcmp(adminUser.name, "Admin") != 0) {
		   strcpy(adminUser.name, "Admin");
           strcpy(adminUser.email, "admin@gmail.com");
           strcpy(adminUser.role, "Admin");
           strcpy(adminUser.username, "admin");
           strcpy(adminUser.password, "admin123");
           adminUser.rollNumber = 0;
           adminUser.marks = 100.0;
           
           users[userCount++] = adminUser;
           saveUsersToFile();  	  
        }
        return;
    }

    while (fscanf(file, "%s %s %d %.2f %s %s %s\n", users[userCount].name, users[userCount].email, users[userCount].rollNumber, users[userCount].marks, users[userCount].username, users[userCount].role, users[userCount].password) == 7) {
        userCount++;
    }

    fclose(file);
}

// Function to write user data to a text file
void saveUsersToFile() {
    FILE *file = fopen("Login_User_Data.txt", "w");
    if (file == NULL) {
        printf("Error saving users.\n");
        return;
    }

    for (int i = 0; i < userCount; i++) {
        fprintf(file, "%s %s %d %.2f %s %s %s\n", users[i].name, users[i].email, users[i].rollNumber, users[i].marks, users[i].username, users[i].role, users[i].password);
    }

    fclose(file);
}

// Function to register a new user
void registerUser() {
    if (userCount >= MAX_USERS) {
        printf("Maximum number of users reached.\n");
        return;
    }

    struct User newUser;

	// First Name
    printf("Enter first name: ");
    scanf("%s", newUser.name);
    
    // Email
    printf("Enter email: ");
    scanf("%s", newUser.email);
    
    // Role
    strcpy(newUser.role, "Student");
    
    // Username
    printf("Enter username: ");
    scanf("%s", newUser.username);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, newUser.username) == 0) {
            printf("Username already exists. Please choose a different one.\n");
            return;
        }
    }

	// Password
    printf("Enter password: ");
    scanf("%s", newUser.password);
    
    // Roll Number
    printf("Enter roll number: ");
    scanf("%d", &newUser.rollNumber);
    
    for (int i = 0; i < userCount; i++) {
        if (users[i].rollNumber == newUser.rollNumber) {
            printf("Roll number already exists. Please choose a different one.\n");
            return;
        }
    }
    
    // Marks
    printf("Enter marks of last exam: ");
    scanf("%f", &newUser.marks);

    users[userCount++] = newUser;
    saveUsersToFile();

    printf("Registration successful!\n");
}

// Function to authenticate a user
int login() {
    char username[MAX_NAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0 && strcmp(users[i].role, "Student") == 0) {
            printf("Login successful. Welcome, %s!\n", users[i].name);
            return 1;
        } else if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0 && strcmp(users[i].role, "Admin") == 0) {
 	  	    printf("Admin Login successful. Welcome, %s!\n", users[i].name);
            return 2;
	   	}
    }
    
    return -1;
}

// Function to add a student record
/* void addStudentRecord() {
    if (userCount >= MAX_USERS) {
        printf("Maximum number of students reached.\n");
        return;
    }

    struct Student newStudent;

    printf("Enter student name: ");
    scanf("%s", newStudent.name);
    printf("Enter student roll number: ");
    scanf("%d", &newStudent.roll_number);

    students[studentCount++] = newStudent;
    
    // Append the new student record to the file
    FILE *file = fopen("Student_Records.txt", "a");
    if (file == NULL) {
        printf("Error opening the student records file.\n");
        return;
    }

    fprintf(file, "%s %d\n", newStudent.name, newStudent.roll_number);

    fclose(file);

    printf("Student record added successfully!\n");
} */

// Function to update a student record by roll number
void updateStudentRecord() {
    int roll_Number;
    int ch;

    printf("Enter the roll number of the student to update: ");
    scanf("%d", &roll_Number);

    for (int i = 0; i < userCount; i++) {
        if(strcmp(users[i].name, "Admin") != 0){
			if (users[i].rollNumber == roll_Number) {
			   printf("What whould you like to update : \n");
			   printf("1 : First Name\n");
			   printf("2 : User Name\n");
			   printf("3 : Marks\n");
			   printf("Enter your Choice : ");
			   scanf("%d", &ch);
			   
			   if (ch == 1){
			   	  // Name
			   	  printf("Enter updated name: ");
			   	  scanf("%s", users[i].name);
			   } else if (ch == 2){
 	 	  	   	 // User Name
			   	 printf("Enter updated user name: ");
			   	 scanf("%s", users[i].username);
			   } else if (ch == 3){
 	 	  	   	 // Marks
			   	 printf("Enter updated marks: ");
			   	 scanf("%f", &users[i].marks);
			   } else{
 	 	  	   	 printf("Thank You!!!");
			   }

			   saveUsersToFile();
      		   printf("Student record updated successfully!\n");
           	   return;
	        }
		}
    }

    printf("Student not found.\n");
}

// Function to delete a student record by roll number
void deleteStudentRecord() {
    int rollNumber;

    printf("Enter the roll number of the student to delete: ");
    scanf("%d", &rollNumber);

    for (int i = 0; i < userCount; i++) {
		if(strcmp(users[i].name, "Admin") != 0){
 			if (users[i].rollNumber == rollNumber) {
	            for (int j = i; j < userCount - 1; j++) {
	                users[j] = users[j + 1];
	            }
	            userCount--;
	            printf("Student record deleted successfully!\n");
	            saveUsersToFile();
	            return;
	        }
		}
    }

    printf("Student not found.\n");
}

// Function to display all student records
void displayStudentRecords() {
    printf("\n--- Students Records ---\n");

	FILE *file = fopen("Login_User_Data.txt", "r");
    if (file == NULL) {
        printf("No student records found.\n");
        return;
    }

	for (int i = 0; i < userCount; i++) {
		if(strcmp(users[i].name, "Admin") != 0){
	 		 printf("Name: %s\n", users[i].name);
     		 printf("Email: %s\n", users[i].email);
        	 printf("Roll Number: %d\n", users[i].rollNumber);
        	 printf("Marks: %.2f\n", users[i].marks);
        	 printf("Username: %s\n", users[i].username);
        	 printf("------------------------\n");
	 	}
    }

    fclose(file);
}