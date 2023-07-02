#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


//password : admin123
typedef struct flight_node {
    struct flight_node* prev;
    char flight_number[10]; // Assuming a maximum length of 10 characters for the flight number
    char airline_service[100]; // Assuming a maximum length of 100 characters for the airline service
    char flight_destination[100]; // Assuming a maximum length of 100 characters for the flight destination
    char flight_departure[100]; // Assuming a maximum length of 100 characters for the flight departure
    char departure_date[20]; // Assuming a maximum length of 20 characters for the departure date
    char departure_time[20]; // Assuming a maximum length of 20 characters for the departure time
    int flight_duration; // Duration of the flight in minutes
    char arrival_time[20]; // Assuming a maximum length of 20 characters for the arrival time
    int seat_available; // Number of available seats
    float flight_fare; // Fare for the flight
    struct flight_node* next;
} flight_node;

typedef struct passenger_node {
	struct passenger_node* left;
    char full_name[100]; // Assuming a maximum length of 100 characters for the full name
    char email[100]; // Assuming a maximum length of 100 characters for the email
    char password[20]; // Assuming a maximum length of 20 characters for the password
    char date_of_birth[20]; // Assuming a maximum length of 20 characters for the date of birth
    char home_address[100]; // Assuming a maximum length of 100 characters for the home address
    char passport_number[20]; // Assuming a maximum length of 20 characters for the passport number
    char national_id[20]; // Assuming a maximum length of 20 characters for the national ID
    struct passenger_node* right;
} passenger_node;

// Function prototypes
void calculateArrivalTime(flight_node* flight);

flight_node* addToEmpty(char* flight_number, char* airline_service, char* flight_destination, char* flight_departure, char* departure_date, char* departure_time, int flight_duration, int seat_available, float flight_fare);
flight_node* addAtEnd(flight_node* tail, char* flight_number, char* airline_service, char* flight_destination, char* flight_departure, char* departure_date, char* departure_time, int flight_duration, int seat_available, float flight_fare);
void print(flight_node* tail);
void viewByDestination(flight_node* tail, char* destination);
flight_node* search(flight_node* tail, char* search_number);
void createNewFlightInfo(flight_node** tail);
void viewAllFlightInfo(flight_node* tail);
void searchByDestination(flight_node* tail);
passenger_node* insertPassenger(passenger_node* root, char* full_name, char* email, char* password, char* date_of_birth, char* home_address, char* passport_number, char* national_id);
passenger_node* searchPassenger(passenger_node* root, char* email, char* password);

int main() {
    flight_node* tail = NULL;
    passenger_node* passenger_root = NULL;

    int choice;
    while (1) {
        printf("=== Flight Reservation System ===\n");
        printf("1. Admin Login\n");
        printf("2. Passenger Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            system("cls"); // Clear screen on Windows
            // Admin section
            printf("=== Admin Login ===\n");
            while (1) {
                char password[20];
                printf("Enter the password: ");
                scanf("%s", password);

                if (strcmp(password, "admin123") == 0) {
                    system("cls"); // Clear screen on Windows
                    printf("=== Admin Menu ===\n");
                    printf("1. Create New Flight Information\n");
                    printf("2. View All Flight Information\n");
                    printf("3. Search Flight by Destination\n");
                    printf("4. Back to Login\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice);

                    switch (choice) {
                        case 1:
                            system("cls"); // Clear screen on Windows
                            printf("== CREATE NEW FLIGHT INFORMATION ==\n");
                            createNewFlightInfo(&tail);
                            break;
                        case 2:
                            system("cls"); // Clear screen on Windows
                            printf("== VIEW ALL FLIGHT INFORMATION ==\n");
                            viewAllFlightInfo(tail);
                            break;
                        case 3:
                            system("cls"); // Clear screen on Windows
                            printf("== SEARCH FLIGHT BY DESTINATION ==\n");
                            searchByDestination(tail);
                            break;
                        case 4:
                            system("cls"); // Clear screen on Windows
                            printf("Returning to Login.\n");
                            break;
                        default:
                            printf("Invalid choice. Please try again.\n");
                    }

                    if (choice == 4) {
                        break; // Break the admin menu loop and go back to the login menu
                    }
                } else {
                    printf("Invalid password. Please try again.\n");
                }
            }
        } else if (choice == 2) {
            system("cls"); // Clear screen on Windows
            // Passenger section
            printf("=== Passenger Login ===\n");
            while (1) {
                char email[100];
                char password[20];
                printf("Enter your email: ");
                scanf("%s", email);
                printf("Enter your password: ");
                scanf("%s", password);

                passenger_node* passenger = searchPassenger(passenger_root, email, password);
                if (passenger != NULL) {
                    system("cls"); // Clear screen on Windows
                    printf("Welcome, %s!\n", passenger->full_name);
                    while (1) {
                        printf("\nPassenger Menu:\n");
                        printf("1. View All Flight Information\n");
                        printf("2. Search Flight by Destination\n");
                        printf("3. Back to Login\n");
                        printf("Enter your choice: ");
                        scanf("%d", &choice);

                        switch (choice) {
                            case 1:
                                system("cls"); // Clear screen on Windows
                                printf("== VIEW ALL FLIGHT INFORMATION ==\n");
                                viewAllFlightInfo(tail);
                                break;
                            case 2:
                                system("cls"); // Clear screen on Windows
                                printf("== SEARCH FLIGHT BY DESTINATION ==\n");
                                searchByDestination(tail);
                                break;
                            case 3:
                                system("cls"); // Clear screen on Windows
                                printf("Returning to Login.\n");
                                break;
                            default:
                                printf("Invalid choice. Please try again.\n");
                        }

                        if (choice == 3) {
                            break; // Break the passenger menu loop and go back to the login menu
                        }
                    }
                    break; // Break the passenger login loop and go back to the login menu
                } else {
                    printf("Invalid email or password. Please try again.\n");
                }
            }
        } else if (choice == 3) {
            printf("Exiting the program. Goodbye!\n");
            break; // Exit the program
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void calculateArrivalTime(flight_node* flight) {
	int departure_hour, departure_minute;
    sscanf(flight->departure_time, "%d:%d", &departure_hour, &departure_minute);
    int departure_time_minutes = departure_hour * 60 + departure_minute;
    int arrival_time_minutes = departure_time_minutes + flight->flight_duration;

    int arrival_hour = arrival_time_minutes / 60;
    int arrival_minute = arrival_time_minutes % 60;

    arrival_hour %= 24; // Ensure arrival hour stays within 24-hour range

    snprintf(flight->arrival_time, sizeof(flight->arrival_time), "%02d:%02d", arrival_hour, arrival_minute);
}

flight_node* addToEmpty(char* flight_number, char* airline_service, char* flight_destination, char* flight_departure, char* departure_date, char* departure_time, int flight_duration, int seat_available, float flight_fare) {
    flight_node* new_flight = (flight_node*)malloc(sizeof(flight_node));
    new_flight->prev = NULL;
    strcpy(new_flight->flight_number, flight_number);
    strcpy(new_flight->airline_service, airline_service);
    strcpy(new_flight->flight_destination, flight_destination);
    strcpy(new_flight->flight_departure, flight_departure);
    strcpy(new_flight->departure_date, departure_date);
    strcpy(new_flight->departure_time, departure_time);
    new_flight->flight_duration = flight_duration;
    calculateArrivalTime(new_flight);
    new_flight->seat_available = seat_available;
    new_flight->flight_fare = flight_fare;
    new_flight->next = NULL;
    return new_flight;
}

flight_node* addAtEnd(flight_node* tail, char* flight_number, char* airline_service, char* flight_destination, char* flight_departure, char* departure_date, char* departure_time, int flight_duration, int seat_available, float flight_fare) {
    if (tail == NULL) {
        return addToEmpty(flight_number, airline_service, flight_destination, flight_departure, departure_date, departure_time, flight_duration, seat_available, flight_fare);
    }

    flight_node* new_flight = (flight_node*)malloc(sizeof(flight_node));
    strcpy(new_flight->flight_number, flight_number);
    strcpy(new_flight->airline_service, airline_service);
    strcpy(new_flight->flight_destination, flight_destination);
    strcpy(new_flight->flight_departure, flight_departure);
    strcpy(new_flight->departure_date, departure_date);
    strcpy(new_flight->departure_time, departure_time);
    new_flight->flight_duration = flight_duration;
    calculateArrivalTime(new_flight);
    new_flight->seat_available = seat_available;
    new_flight->flight_fare = flight_fare;
    new_flight->next = NULL;

    tail->next = new_flight;
    new_flight->prev = tail;
    tail = new_flight;

    return tail;
}

void print(flight_node* tail) {
    flight_node* temp = tail;
    printf("FLIGHT INFORMATION:\n");
    while (temp != NULL) {
        	printf("\n-------------------------------------------------------------\n");
            printf("Flight Number:\t\t%s\n", temp->flight_number);
            printf("Airline Service:\t%s\n", temp->airline_service);
            printf("Flight Destination:\t%s\n", temp->flight_destination);
            printf("Flight Departure:\t%s\n", temp->flight_departure);
            printf("Departure Date:\t\t%s\n", temp->departure_date);
            printf("Departure Time:\t\t%s\n", temp->departure_time);
            printf("Flight Duration:\t%d minutes\n", temp->flight_duration);
            printf("Arrival Time:\t\t%s\n", temp->arrival_time);
            printf("Seat Availability:\t%d\n", temp->seat_available);
            printf("Ticket Price:\t\t$%.2f\n", temp->flight_fare);
            printf("-------------------------------------------------------------\n");
        temp = temp->next;
    }
}

void viewByDestination(flight_node* tail, char* destination) {
    flight_node* temp = tail;
    printf("FLIGHTS TO %s:\n", destination);
    int found = 0;
    while (temp != NULL) {
        if (strcasecmp(temp->flight_destination, destination) == 0) {
        	printf("-------------------------------------------------------------\n");
            printf("Flight Number: %s\n", temp->flight_number);
            printf("Airline Service: %s\n", temp->airline_service);
            printf("Destination: %s\n", temp->flight_destination);
            printf("Departure: %s\n", temp->flight_departure);
            printf("Departure Date: %s\n", temp->departure_date);
            printf("Departure Time: %s\n", temp->departure_time);
            printf("Flight Duration: %d minutes\n", temp->flight_duration);
            printf("Arrival Time: %s\n", temp->arrival_time);
            printf("Seats Available: %d\n", temp->seat_available);
            printf("-------------------------------------------------------------\n");
            found = 1;
        }
        temp = temp->next;
    }
    if (!found) {
        printf("No flights to %s.\n", destination);
    }
}

flight_node* search(flight_node* tail, char* search_number) {
    flight_node* temp = tail;
    while (temp != NULL) {
        if (strcmp(temp->flight_number, search_number) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void createNewFlightInfo(flight_node** tail) {
    char flight_number[10];
    char airline_service[100];
    char flight_destination[100];
    char departure_date[20];
    char departure_time[20];
    int flight_duration;
    int seat_available;
    float flight_fare;

    printf("Enter Flight Number: ");
    scanf("%s", flight_number);
    printf("Enter Airline Service: ");
    scanf(" %[^\n]s", airline_service);
    printf("Enter Flight Destination: ");
    scanf(" %[^\n]s", flight_destination);
    
    // Set the departure directly as "Guyana"
    char flight_departure[] = "Guyana";
    
	printf("Enter Departure Date (YYYY-MM-DD): ");
    scanf(" %[^\n]s", departure_date);
    printf("Enter Departure Time (HH:MM): ");
    scanf(" %[^\n]s", departure_time);
    printf("Enter Flight Duration (minutes): ");
    scanf("%d", &flight_duration);
    printf("Enter Number of Seats Available: ");
    scanf("%d", &seat_available);
    printf("Enter flight fare: ");
    scanf("%f", &flight_fare);

    *tail = addAtEnd(*tail, flight_number, airline_service, flight_destination, flight_departure, departure_date, departure_time, flight_duration, seat_available, flight_fare);
    printf("-------------------------------------------------------------\n");
	printf("Flight information added successfully!\n");
}

void viewAllFlightInfo(flight_node* tail) {
    if (tail == NULL) {
        printf("No flight information available.\n");
    } else {
        print(tail);
    }
}

void searchByDestination(flight_node* tail) {
    char destination[100];
    printf("Enter the destination to search: ");
    scanf(" %[^\n]", destination);
    viewByDestination(tail, destination);
}

passenger_node* insertPassenger(passenger_node* root, char* full_name, char* email, char* password, char* date_of_birth, char* home_address, char* passport_number, char* national_id) {
    if (root == NULL) {
        passenger_node* new_passenger = (passenger_node*)malloc(sizeof(passenger_node));
        strcpy(new_passenger->full_name, full_name);
        strcpy(new_passenger->email, email);
        strcpy(new_passenger->password, password);
        strcpy(new_passenger->date_of_birth, date_of_birth);
        strcpy(new_passenger->home_address, home_address);
        strcpy(new_passenger->passport_number, passport_number);
        strcpy(new_passenger->national_id, national_id);
        new_passenger->left = NULL;
        new_passenger->right = NULL;
        return new_passenger;
    }

    if (strcmp(email, root->email) < 0) {
        root->left = insertPassenger(root->left, full_name, email, password, date_of_birth, home_address, passport_number, national_id);
    } else if (strcmp(email, root->email) > 0) {
        root->right = insertPassenger(root->right, full_name, email, password, date_of_birth, home_address, passport_number, national_id);
    }

    return root;
}

passenger_node* searchPassenger(passenger_node* root, char* email, char* password) {
    if (root == NULL || strcmp(root->email, email) == 0 && strcmp(root->password, password) == 0) {
        return root;
    }

    if (strcmp(email, root->email) < 0) {
        return searchPassenger(root->left, email, password);
    } else {
        return searchPassenger(root->right, email, password);
    }
}

//Its making me re-enter the password after i do something as admin, i have to fix that 
//I need to fix something else with the sign in login part cause i cant sign up, only log in 
//
