#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//password : admin123 or admin
// Flight Node Structure
typedef struct flight_node {
    char flight_number[20];
    char airline_service[50];
    char flight_destination[50];
    char flight_departure[50];
    char departure_date[20];
    char departure_time[20];
    int flight_duration;
    int seat_available;
    struct flight_node* next;
} flight_node;

// User Node Structure
typedef struct user_node {
    char full_name[100];
    char email[100];
    char password[100];
    char date_of_birth[20];
    char home_address[100];
    char passport_number[20];
    char national_id[20];
    struct user_node* left;
    struct user_node* right;
} user_node;

// Function to create a new flight node
flight_node* createFlightNode(char flight_number[], char airline_service[], char flight_destination[],
                              char flight_departure[], char departure_date[], char departure_time[],
                              int flight_duration, int seat_available) {
    flight_node* newNode = (flight_node*)malloc(sizeof(flight_node));
    strcpy(newNode->flight_number, flight_number);
    strcpy(newNode->airline_service, airline_service);
    strcpy(newNode->flight_destination, flight_destination);
    strcpy(newNode->flight_departure, flight_departure);
    strcpy(newNode->departure_date, departure_date);
    strcpy(newNode->departure_time, departure_time);
    newNode->flight_duration = flight_duration;
    newNode->seat_available = seat_available;
    newNode->next = NULL;
    return newNode;
}

// Function to add a flight at the end of the list
flight_node* addFlight(flight_node* tail, char flight_number[], char airline_service[], char flight_destination[],
                       char flight_departure[], char departure_date[], char departure_time[],
                       int flight_duration, int seat_available) {
    flight_node* newNode = createFlightNode(flight_number, airline_service, flight_destination,
                                            flight_departure, departure_date, departure_time,
                                            flight_duration, seat_available);

    if (tail == NULL) {
        newNode->next = newNode;
        return newNode;
    }

    newNode->next = tail->next;
    tail->next = newNode;
    return newNode;
}

// Function to print the flight list
void printFlights(flight_node* tail) {
    if (tail == NULL) {
        printf("No flights available.\n");
        return;
    }

    flight_node* current = tail->next;
    do {
        printf("\nFlight Number: %s\n", current->flight_number);
        printf("Airline Service: %s\n", current->airline_service);
        printf("Destination: %s\n", current->flight_destination);
        printf("Departure: %s\n", current->flight_departure);
        printf("Departure Date: %s\n", current->departure_date);
        printf("Departure Time: %s\n", current->departure_time);
        printf("Duration: %d minutes\n", current->flight_duration);
        printf("Seat Availability: %d\n", current->seat_available);
        current = current->next;
    } while (current != tail->next);
}

// Function to view flights by destination
void viewFlightsByDestination(flight_node* tail, char flight_destination[]) {
    if (tail == NULL) {
        printf("No flights available.\n");
        return;
    }

    flight_node* current = tail->next;
    int found = 0;

    do {
        if (strcmp(current->flight_destination, flight_destination) == 0) {
            printf("\nFlight Number: %s\n", current->flight_number);
            printf("Airline Service: %s\n", current->airline_service);
            printf("Destination: %s\n", current->flight_destination);
            printf("Departure: %s\n", current->flight_departure);
            printf("Departure Date: %s\n", current->departure_date);
            printf("Departure Time: %s\n", current->departure_time);
            printf("Duration: %d minutes\n", current->flight_duration);
            printf("Seat Availability: %d\n", current->seat_available);
            found = 1;
        }
        current = current->next;
    } while (current != tail->next);

    if (!found)
        printf("No flights available for the given destination.\n");
}

// Function to register a new user
user_node* registerUser(user_node* root, char full_name[], char email[], char password[],
                        char date_of_birth[], char home_address[], char passport_number[],
                        char national_id[]) {
    user_node* newNode = (user_node*)malloc(sizeof(user_node));
    strcpy(newNode->full_name, full_name);
    strcpy(newNode->email, email);
    strcpy(newNode->password, password);
    strcpy(newNode->date_of_birth, date_of_birth);
    strcpy(newNode->home_address, home_address);
    strcpy(newNode->passport_number, passport_number);
    strcpy(newNode->national_id, national_id);
    newNode->left = NULL;
    newNode->right = NULL;

    if (root == NULL)
        return newNode;

    user_node* current = root;
    user_node* parent = NULL;

    while (current != NULL) {
        parent = current;

        if (strcmp(email, current->email) < 0)
            current = current->left;
        else
            current = current->right;
    }

    if (strcmp(email, parent->email) < 0)
        parent->left = newNode;
    else
        parent->right = newNode;

    return root;
}

// Function to search for a user by email in the binary search tree
user_node* searchUser(user_node* root, char email[]) {
    user_node* current = root;

    while (current != NULL) {
        if (strcmp(email, current->email) == 0)
            return current;
        else if (strcmp(email, current->email) < 0)
            current = current->left;
        else
            current = current->right;
    }

    return NULL;
}

// Function to print user details
void printUserDetails(user_node* user) {
    printf("\nFull Name: %s\n", user->full_name);
    printf("Email: %s\n", user->email);
    printf("Date of Birth: %s\n", user->date_of_birth);
    printf("Home Address: %s\n", user->home_address);
    printf("Passport Number: %s\n", user->passport_number);
    printf("National ID: %s\n", user->national_id);
}

int main() {
    flight_node* tail = NULL;
    user_node* user_tree = NULL;

    // Add some sample flights
    tail = addFlight(tail, "F001", "Airline 1", "Destination 1", "Departure 1", "2023-07-01", "10:00", 120, 50);
    tail = addFlight(tail, "F002", "Airline 2", "Destination 2", "Departure 2", "2023-07-02", "12:00", 180, 100);
    tail = addFlight(tail, "F003", "Airline 3", "Destination 1", "Departure 3", "2023-07-03", "14:00", 90, 20);
    tail = addFlight(tail, "F004", "Airline 4", "Destination 3", "Departure 4", "2023-07-04", "16:00", 150, 80);

    int choice;

    do {
        printf("\n============================\n");
        printf("         MENU SCREEN\n");
        printf("============================\n");
        printf("1. Admin Login\n");
        printf("2. Passenger Login\n");
        printf("3. Exit\n");
        printf("============================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char adminPassword[100];
                printf("Enter admin password: ");
                scanf("%s", adminPassword);

                // Hardcoded admin password check
                if (strcmp(adminPassword, "admin123") == 0) {
                    // Admin capabilities
                    printf("\nAdmin capabilities:\n");
                    // Add your admin functionality here
                } else {
                    printf("Incorrect password. Access denied.\n");
                }
                break;
            }
            case 2: {
                int passengerChoice;

                do {
                    printf("\n============================\n");
                    printf("       PASSENGER LOGIN\n");
                    printf("============================\n");
                    printf("1. Sign Up\n");
                    printf("2. Log In\n");
                    printf("3. Back to Menu\n");
                    printf("============================\n");
                    printf("Enter your choice: ");
                    scanf("%d", &passengerChoice);

                    switch (passengerChoice) {
                        case 1: {
                            char fullName[100], email[100], password[100], dateOfBirth[20], homeAddress[100],
                                 passportNumber[20], nationalID[20];

                            printf("\n============================\n");
                            printf("          SIGN UP\n");
                            printf("============================\n");
                            printf("Full Name: ");
                            scanf(" %[^\n]s", fullName);
                            printf("Email: ");
                            scanf(" %[^\n]s", email);
                            printf("Password: ");
                            scanf(" %[^\n]s", password);
                            printf("Date of Birth (YYYY-MM-DD): ");
                            scanf(" %[^\n]s", dateOfBirth);
                            printf("Home Address: ");
                            scanf(" %[^\n]s", homeAddress);
                            printf("Passport Number: ");
                            scanf(" %[^\n]s", passportNumber);
                            printf("National ID: ");
                            scanf(" %[^\n]s", nationalID);

                            // Register user
                            user_tree = registerUser(user_tree, fullName, email, password, dateOfBirth,
                                                     homeAddress, passportNumber, nationalID);
                            printf("\nUser registered successfully!\n");
                            break;
                        }
                        case 2: {
                            char loginEmail[100], loginPassword[100];
                            printf("\n============================\n");
                            printf("          LOG IN\n");
                            printf("============================\n");
                            printf("Email: ");
                            scanf(" %[^\n]s", loginEmail);
                            printf("Password: ");
                            scanf(" %[^\n]s", loginPassword);

                            // Search for user in the binary search tree
                            user_node* user = searchUser(user_tree, loginEmail);

                            if (user != NULL && strcmp(loginPassword, user->password) == 0) {
                                printf("\nUser logged in successfully!\n");
                                printUserDetails(user);
                                // Add your passenger functionality here
                            } else {
                                printf("Invalid email or password. Login failed.\n");
                            }
                            break;
                        }
                        case 3:
                            break;
                        default:
                            printf("Invalid choice. Please try again.\n");
                            break;
                    }
                } while (passengerChoice != 3);
                break;
            }
            case 3:
                printf("Thank you for using the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 3);

    return 0;
}
//I have to allow the users to see the flights and stuff after they log in
//its now showing the admin capabilities that follows
/*1. Create New Flight Information
2. View All Flight Information
3. Search Flight by Destination
4. Back to Login*/
