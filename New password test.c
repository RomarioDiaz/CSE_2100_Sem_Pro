#include <stdio.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_NAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char username[MAX_NAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User users[MAX_USERS];
int numUsers = 0;

int signUp() {
    if (numUsers >= MAX_USERS) {
        printf("Maximum number of users reached.\n");
        return 0;
    }

    User newUser;

    printf("Enter a username: ");
    scanf("%s", newUser.username);

    printf("Enter a password: ");
    scanf("%s", newUser.password);

    users[numUsers++] = newUser;

    printf("Sign up successful!\n");
    return 1;
}

int login() {
    char username[MAX_NAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    scanf("%s", username);

    printf("Enter your password: ");
    scanf("%s", password);

    for (int i = 0; i < numUsers; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            printf("Login successful!\n");
            return 1;
        }
    }

    printf("Invalid username or password.\n");
    return 0;
}

int main() {
    int choice;
    int loggedIn = 0;

    do {
        printf("\n1. Sign Up\n2. Login\n3. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                signUp();
                break;
            case 2:
                if (!loggedIn) {
                    loggedIn = login();
                } else {
                    printf("Already logged in.\n");
                }
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}
