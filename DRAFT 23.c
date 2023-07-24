#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//THE FOLLOWING STRUCT REPRENST A NODE FOR FLIGHT INFORMATION FOR THE CIRCULART LINK LIST
typedef struct flight_node {
    struct flight_node* prev;
    char flight_number[10];
    char airline_service[100];
    char flight_destination[100]; 
    char flight_departure[100]; 
    char departure_date[20];
    char departure_time[20];
    int flight_duration;
    char arrival_time[20];
    int seat_available;
    float flight_fare;
    struct flight_node* next;
} flight_node;

//THE FOLLOWING STRUCT REPRENST A NODE FOR EACH PASSENGER INFORMATION FOR THE BINARY SEARCH TREE
typedef struct passenger_node {
    struct passenger_node* left;
    char full_name[100];
    char email[100]; 
    char password[20]; 
    char date_of_birth[20]; 
    char home_address[100];
    char passport_number[20];
    char national_id[20]; 
    char reservedFlightNo[10]; 
    struct passenger_node* right;
} passenger_node;

// Function prototypes
void calculateArrivalTime(flight_node* flight);
void editFlightInformation(flight_node* tail);
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

//THE FOLLOWING CREATES AND INITILIZES A NEW FLIGHT NODE 
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

//THE FOLLOWING CALCULATES THE ARRIVAL TIME FOR FLIGHT USING THE DEPARTURE TIME AND THE FLIGHT DURATION
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


//ADDS A NEW NODE FOR A FLIGHT AT THE END OF THE CIRCULAR LINK LIST
flight_node* addToEmpty(char* flight_number, char* airline_service, char* flight_destination, char* flight_departure, char* departure_date, char* departure_time, int flight_duration, int seat_available, float flight_fare) {
    flight_node* temp = malloc(sizeof(flight_node));
    temp->prev = temp;
    strcpy(temp->flight_number, flight_number);
    strcpy(temp->airline_service, airline_service);
    strcpy(temp->flight_destination, flight_destination);
    strcpy(temp->flight_departure, flight_departure);
    strcpy(temp->departure_date, departure_date);
    strcpy(temp->departure_time, departure_time);
    temp->flight_duration = flight_duration;
    calculateArrivalTime(temp); // Calculate the arrival time based on departure time and flight duration
    temp->seat_available = seat_available;
    temp->flight_fare = flight_fare;
    temp->next = temp;
    return temp;
}

flight_node* addAtEnd(flight_node* tail, char* flight_number, char* airline_service, char* flight_destination, char* flight_departure, char* departure_date, char* departure_time, int flight_duration, int seat_available, float flight_fare) {
    flight_node* newPrev = addToEmpty(flight_number, airline_service, flight_destination, flight_departure, departure_date, departure_time, flight_duration, seat_available, flight_fare);
    if (tail == NULL) {
        return newPrev;
    }
    flight_node* temp = tail->next;
    newPrev->next = temp;
    newPrev->prev = tail;
    tail->next = newPrev;
    temp->prev = newPrev;
    tail = newPrev;
    return tail;
}

void print(flight_node* tail) {
    if (tail == NULL) {
        printf("No element in the list.\n");
    } else {
        flight_node* temp = tail->next;
        do {
        	printf("-------------------------------------------------------------\n");
            printf("\nFlight Number:\t\t%s\n", temp->flight_number);
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
        } while (temp != tail->next);
    }
}

void viewByDestination(flight_node* tail, char* destination) {
    if (tail == NULL) {
        printf("No flight information available.\n");
        return;
    }

    flight_node* temp = tail->next; // Start from the first node in the circular list
    printf("FLIGHTS TO %s:\n", destination);
    int found = 0;

    do {
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
    } while (temp != tail->next);

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
	printf("Flight information added successfully!\n\n\n");
}

void viewAllFlightInfo(flight_node* tail) {
    if (tail == NULL) {
        printf("No flight information available.\n\n\n");
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

// Function to register a new user
passenger_node* registerUser(passenger_node* root, char full_name[], char email[], char password[],
                        char date_of_birth[], char home_address[], char passport_number[],
                        char national_id[]) {
    passenger_node* newNode = (passenger_node*)malloc(sizeof(passenger_node));
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

    passenger_node* current = root;
    passenger_node* parent = NULL;

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
passenger_node* searchUser(passenger_node* root, char email[], char password[]) {
    if (root == NULL || (strcmp(root->email, email) == 0 && strcmp(root->password, password) == 0)) {
        return root;
    }

    if (strcmp(email, root->email) < 0) {
        return searchUser(root->left, email, password);
    } else {
        return searchUser(root->right, email, password);
    }
}


// Function to print user details
void printUserDetails(passenger_node* user) {
    printf("Full Name: %s\n", user->full_name);
    printf("Email: %s\n", user->email);
    printf("Date of Birth: %s\n", user->date_of_birth);
    printf("Home Address: %s\n", user->home_address);
    printf("Passport Number: %s\n", user->passport_number);
    printf("National ID: %s\n\n\n", user->national_id);
}

flight_node* searchFlight(flight_node* tail, char* search_number) {
    return search(tail, search_number);
}


void viewReservedFlight(passenger_node* root, flight_node* tail, char* email, char* password) {
    passenger_node* passenger = searchPassenger(root, email, password);

    if (passenger == NULL) {
        printf("No user found with the provided email and password.\n");
        return;
    }

    printf("\nFlight(s) Reserved by %s:\n", passenger->full_name);

    int found = 0;
    flight_node* temp = tail;
    do {
        // Check if the current flight destination matches the user's home address
        if (strcasecmp(temp->flight_destination, passenger->home_address) == 0) {
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
    } while (temp != tail->next);

    if (!found) {
        printf("No flights reserved for %s.\n", passenger->full_name);
    }
}

void editFlightInformation(flight_node* tail) {
    char flight_number[10];
    printf("|======================== F L I G H T   E D I T   M E N U ========================|\n\n");
    printf("Enter the flight number to edit: ");
    scanf("%s", flight_number);

    flight_node* flight = searchFlight(tail, flight_number);

    if (flight == NULL) {
        printf("Flight with the provided number not found.\n");
    } else {
        // Display current flight information
        printf("\n-------------------------------------------------------------\n");
        printf("Flight Number: %s\n", flight->flight_number);
        printf("Airline Service: %s\n", flight->airline_service);
        printf("Destination: %s\n", flight->flight_destination);
        printf("Departure: %s\n", flight->flight_departure);
        printf("Departure Date: %s\n", flight->departure_date);
        printf("Departure Time: %s\n", flight->departure_time);
        printf("Flight Duration: %d minutes\n", flight->flight_duration);
        printf("Arrival Time: %s\n", flight->arrival_time);
        printf("Seats Available: %d\n", flight->seat_available);
        printf("Ticket Price: $%.2f\n", flight->flight_fare);
        printf("\n-------------------------------------------------------------");

        // Allow the user to select which information to modify
        int infoChoice;
        printf("\nSelect which information to change:\n");
        printf("1. Airline Service\n");
        printf("2. Flight Destination\n");
        printf("3. Departure Date\n");
        printf("4. Departure Time\n");
        printf("5. Flight Duration\n");
        printf("6. Number of Seats Available\n");
        printf("Enter your choice: ");
        scanf("%d", &infoChoice);

        switch (infoChoice) {
            case 1:
                printf("Enter Airline Service: ");
                scanf(" %[^\n]s", flight->airline_service);
                break;
            case 2:
                printf("Enter Flight Destination: ");
                scanf(" %[^\n]s", flight->flight_destination);
                break;
            case 3:
                printf("Enter Departure Date (YYYY-MM-DD): ");
                scanf(" %[^\n]s", flight->departure_date);
                break;
            case 4:
                printf("Enter Departure Time (HH:MM): ");
                scanf(" %[^\n]s", flight->departure_time);
                // Recalculate the arrival time based on the updated departure time and flight duration
                calculateArrivalTime(flight);
                break;
            case 5:
                printf("Enter Flight Duration (minutes): ");
                scanf("%d", &flight->flight_duration);
                // Recalculate the arrival time based on the updated departure time and flight duration
                calculateArrivalTime(flight);
                break;
            case 6:
                printf("Enter Number of Seats Available: ");
                scanf("%d", &flight->seat_available);
                break;
            default:
                printf("Invalid choice. No changes made.\n");
                break;
        }

        printf("Flight information updated successfully!\n\n\n");
    }
}


// Function to remove a flight from the linked list
void removeFlight(flight_node** tail, char flight_number[]) {
    if (*tail == NULL) {
        printf("No flights in the list.\n");
        return;
    }

    flight_node* current = (*tail)->next; // Start from the first node in the circular list
    flight_node* prev = *tail;
    int found = 0;

    do {
        if (strcmp(current->flight_number, flight_number) == 0) {
            // Remove the flight node from the linked list
            if (current == (*tail)->next && current->next == current) {
                // Only one node in the list
                free(current);
                *tail = NULL;
            } else if (current == (*tail)->next) {
                // Removing the first node in the list
                (*tail)->next = current->next;
                current->next->prev = *tail;
                free(current);
            } else if (current == *tail) {
                // Removing the last node in the list
                (*tail)->next->prev = prev;
                prev->next = (*tail)->next;
                *tail = prev;
                free(current);
            } else {
                // Removing a node from the middle of the list
                current->next->prev = prev;
                prev->next = current->next;
                free(current);
            }

            found = 1;
            break;
        }

        prev = current;
        current = current->next;
    } while (current != (*tail)->next);

    if (found) {
        printf("Flight with number %s removed successfully!\n", flight_number);
    } else {
        printf("Flight with number %s not found.\n", flight_number);
    }
}


int main() {
	char flight_number[10];
	flight_node* tail = NULL;
    passenger_node* passenger_tree = NULL; // Changed variable name to passenger_tree
    flight_node* flightList = NULL;
    flight_node* flight_tail = NULL;
    passenger_node* passenger_root = NULL;
    
    int choice;
    int choice2;
    while (1) {
    	system("cls"); // Clear screen on Windows
        printf("|======================== F L I G H T   R E S E R V A T I O N   S Y S T E M ==========================|\n\n");
        printf("1. Admin Login\n");
        printf("2. Passenger Login\n");
        printf("3. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                system("cls"); // Clear screen on Windows
                // Admin section
                
                printf("|======================== A D M I N   L O G I N ========================|\n\n");
                
                    char password[20];
                    printf("Enter the password: ");
                    scanf("%s", password);
                    system("cls"); // Clear screen on Windows
				while(1){
				
                    if (strcmp(password, "admin123") == 0) {
                        
                        printf("|======================== A D M I N   M E N U ========================|\n\n");
                        printf("1. Create New Flight Information\n");
                        printf("2. Edit Flight Information\n");
                        printf("3. View All Flight Information\n");
                        printf("4. Search Flight by Destination\n");
                        printf("5. Remove a Flight Entry\n");
                        printf("6. Back to Login\n");
                        printf("\nEnter your choice: ");
                        scanf("%d", &choice);

                        switch (choice) {
                            case 1:
                                system("cls"); // Clear screen on Windows
                                printf("|============== C R E A T E   N E W   F L I G H T   I N F O R M A T I O N ==============|\n\n");
                                createNewFlightInfo(&tail);
                                break;
                            case 2:
                                system("cls"); // Clear screen on Windows
                                editFlightInformation(tail);
                                break;
							case 3:
                            	//editFlightInfo(flightList);
                                system("cls"); // Clear screen on Windows
                                printf("|============== V I E W   A L L   F L I G H T   I N F O R M A T I O N ==============|\n\n");
                                viewAllFlightInfo(tail);
                                break;
                            case 4:
                                system("cls"); // Clear screen on Windows
                                printf("|============== S E A R C H   F L I G H T   B Y   D E S T I N A T I O N ==============|\n\n");
                                searchByDestination(tail);
                                break;
                            case 5:
                            	system("cls"); // Clear screen on Windows
							    char removeFlightNumber[10];
							    printf("|====================== R E M O V E   F L I G H T =======================|\n\n");
							    printf("Enter the flight number to remove: ");
							    scanf("%s", removeFlightNumber);
							    removeFlight(&tail, removeFlightNumber);
							    break;
                                
                            case 6:
							    system("cls"); // Clear screen on Windows
                                break;
                            default:
                                printf("Invalid choice. Please try again.\n");
                        }

                        if (choice == 6) {
                            break; // Break the admin menu loop and go back to the login menu
                        }
                    } else {
                        printf("Invalid password. Please try again.\n\n");
                        break;
                    }
                }break;
                
            }
            case 2:
                system("cls"); // Clear screen on Windows
                int choice;
                printf("|============== P A S S E N G E R   L O G I N   O P T I O N S ==============|\n\n");
                printf("1. Sign up\n");
                printf("2. Login\n");
                printf("3. Return to previous page\n\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch (choice) {
                    case 1: {
                        char fullName[100], email[100], password[100], dateOfBirth[20], homeAddress[100],
                            passportNumber[20], nationalID[20];

                        system("cls"); // Clear screen on Windows
						printf("============================\n");
                        printf("          SIGN UP\n");
                        printf("============================\n\n");
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
                        passenger_tree = registerUser(passenger_tree, fullName, email, password, dateOfBirth,
                                                     homeAddress, passportNumber, nationalID);
                        system("cls"); // Clear screen on Windows
						printf("\nUser registered successfully!\n");
                        break;
                    }
                    case 2: {
                        char email[100], password[100];
                        printf("\n============================\n");
                        printf("          LOGIN\n");
                        printf("============================\n\n");
                        printf("Email: ");
                        scanf(" %[^\n]s", email);
                        printf("Password: ");
                        scanf(" %[^\n]s", password);

                        // Search user
                        passenger_node* user = searchUser(passenger_tree, email, password);
                        if (user != NULL) {
                            system("cls"); // Clear screen on Windows
							printf("\nLogged in Successful!\n\n");
							
							do {
	                            printf("|============== P A S S E N G E R   O P T I O N S ==============|\n\n");
								printf("1. View Personal Info\n");
								printf("2. View all flights available\n");
								printf("3. View Flight by Destination\n");
								printf("4. Reserve a Flight\n");
								printf("5. View reswerved flight\n");
								printf("6. Return to previous page\n\n");
								printf("Enter your choice: ");
								scanf("%d", &choice2);
								
								switch (choice2) {
								    case 1:
								    	system("cls"); // Clear screen on Windows
								        printf("|============== P A S S E N G E R   P E R S O L A L   O P T I O N S ==============|\n\n");
								        printUserDetails(user);// needed to be as a case
								        break;
								    case 2:
								    	system("cls"); // Clear screen on Windows
								    	printf("|============== V I E W   A L L   F L I G H T   I N F O R M A T I O N ==============|\n\n");
								    	viewAllFlightInfo(tail);
								        break;
								    case 3:
								        system("cls"); // Clear screen on Windows
	                                	printf("|============== S E A R C H   F L I G H T   B Y   D E S T I N A T I O N ==============|\n\n");
								        searchByDestination(tail);
								        break;
								    case 4:{
										    system("cls"); // Clear screen on Windows
										    printf("|============== R E S E R V E   A   F L I G H T ==============|\n\n");
										    printf("Enter the flight number of the flight you wish to reserve: ");
										    scanf("%s", flight_number);
										
										    flight_node* flight = searchFlight(tail, flight_number);
										
										    if (flight == NULL) {
										        printf("Invalid flight number. Please try again.\n");
										        break;
										    }
										
										    if (flight->seat_available == 0) {
										        printf("No seats available for the selected flight.\n");
										        printf("Please wait for a new flight to be announced with your desired destination");
										        break;
										    }
										
										    // Perform the flight reservation
										    flight->seat_available--;
										    strcpy(user->reservedFlightNo, flight_number);
										
										    printf("Flight reservation successful!\n");
										    printf("Remaining seats for %s: %d\n", flight->flight_number, flight->seat_available);
										    break;
										}
									case 5:{
										    // VIEW INFO ON THE FLIGHT RESERVED
										    system("cls"); // Clear screen on Windows
										    if (user->reservedFlightNo[0] == '\0') {
										        printf("You have not reserved any flights yet.\n");
										    } else {
										        printf("|============== F L I G H T   I N F O R M A T I O N   O N   R E S E R V E D   F L I G H T ==============|\n\n");
										        flight_node* reserved_flight = searchFlight(tail, user->reservedFlightNo);
										        if (reserved_flight == NULL) {
										            printf("Error: The flight with the reserved flight number not found.\n");
										        } else {
										            printf("Flight Number: %s\n", reserved_flight->flight_number);
										            printf("Airline Service: %s\n", reserved_flight->airline_service);
										            printf("Destination: %s\n", reserved_flight->flight_destination);
										            printf("Departure: %s\n", reserved_flight->flight_departure);
										            printf("Departure Date: %s\n", reserved_flight->departure_date);
										            printf("Departure Time: %s\n", reserved_flight->departure_time);
										            printf("Flight Duration: %d minutes\n", reserved_flight->flight_duration);
										            printf("Arrival Time: %s\n", reserved_flight->arrival_time);
										            printf("Seats Available: %d\n", reserved_flight->seat_available);
										            printf("Ticket Price: $%.2f\n", reserved_flight->flight_fare);
										        }
										    }
										    break;
										}
									case 6:
								        break;
								    default:
								        printf("Invalid choice\n");
								        // Code to handle an invalid choice
								        break;
							}
							while (getchar() != '\n');
                           } while (choice2 != 6); 
                        } else {
                            printf("\nInvalid email or password. Please try again.\n");
                        }
                        break;
                    }
                    case 3:
                        printf("You selected Return to previous page.\n");
                        // Add your logic to return to the previous page here
                        break;
                    default:
                        printf("Invalid choice.\n");
                        // Add logic to handle an invalid choice
                        break;
                }
                break;
            case 3:
            	system("cls"); // Clear screen on Windows
                printf("Exiting the program. Goodbye!\n");
                return 0; // Exit the program
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

