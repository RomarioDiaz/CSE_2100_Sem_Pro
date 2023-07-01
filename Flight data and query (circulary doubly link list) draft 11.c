#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

int main() {
    flight_node* tail = NULL;

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
                int admin_choice;
                printf("\nAdmin Menu:\n");
                printf("1. Create New Flight Information\n");
                printf("2. View All Flight Information\n");
                printf("3. Search Flight by Destination\n");
                printf("4. Back to Login\n");
                printf("Enter your choice: ");
                scanf("%d", &admin_choice);

                switch (admin_choice) {
                    case 1:
                    	system("cls"); // Clear screen on Windows
                    	printf("==CREATING NEW FLIGHT INFORMATION==");
                        createNewFlightInfo(&tail);
                        break;
                    case 2:
                    	system("cls"); // Clear screen on Windows
                    	printf("==VIEW ALL FLIGHT INFORMATION==");
                    	viewAllFlightInfo(tail);
                        break;
                    case 3:
                    	system("cls"); // Clear screen on Windows
                    	printf("==VIEW FLIGHT BY DESTINATION==");
                        searchByDestination(tail);
                        break;
                    case 4:
                        printf("Returning to Login.\n");
                        system("cls"); // Clear screen on Windows
                        break;
                    default:
                        printf("Invalid choice. Please try again.\n");
                }

                if (admin_choice == 4) {
                    break; // Break the admin menu loop and go back to the login menu
                }
            }
        } else if (choice == 2) {
            // Passenger section
            system("cls");
            printf("=== Passenger Login ===\n");
            while (1) {
                int passenger_choice;
                printf("\nPassenger Menu:\n");
                printf("1. View All Flight Information\n");
                printf("2. Search Flight by Destination\n");
                printf("3. Back to Login\n");
                printf("Enter your choice: ");
                scanf("%d", &passenger_choice);

                switch (passenger_choice) {
                    case 1:
						system("cls"); // Clear screen on Windows
                    	printf("==VIEW ALL FLIGHT INFORMATION==\n");
                        viewAllFlightInfo(tail);
                        break;
                    case 2:
                    	system("cls"); // Clear screen on Windows
                        printf("==VIEW FLIGHT BY DESTINATION==\n");
                        searchByDestination(tail);
                        break;
                    case 3:
                    	system("cls"); // Clear screen on Windows
                        printf("Returning to Login.\n");
                        break;
                    default:
                        printf("Invalid choice. Please try again.\n");
                }

                if (passenger_choice == 3) {
                    break; // Break the passenger menu loop and go back to the login menu
                }
            }
        } else if (choice == 3) {
            printf("Exiting...\n");
            break; // Exit the program
        } else {
            printf("Invalid choice. Please try again.\n");
        }

        printf("\n");
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
	system("cls"); // Clear screen on Windows
	printf("==VIEW FLIGHT BY DESTINATION==");
    if (tail == NULL) {
        printf("No element in the list.\n");
    } else {
        flight_node* temp = tail->next;
        int found = 0;

        do {
            if (strcasecmp(temp->flight_destination, destination) == 0) {
                printf("\nFlight Number:\t\t%s\n", temp->flight_number);
                printf("Airline Service:\t%s\n", temp->airline_service);
                printf("Flight Destination:\t%s\n", temp->flight_destination);
                printf("Flight Departure:\t%s\n", temp->flight_departure);
                printf("Departure Date:\t\t%s\n", temp->departure_date);
                printf("Departure Time:\t\t%s\n", temp->departure_time);
                printf("Flight Duration:\t%d minutes\n", temp->flight_duration);
                printf("Arrival Time:\t\t%s\n", temp->arrival_time);
                printf("Seat Availability:\t%d\n", temp->seat_available);
                printf("\n");
                found = 1;
            }
            temp = temp->next;
        } while (temp != tail->next);

        if (!found) {
            printf("No flights found for the destination: %s\n", destination);
        }
    }
}

flight_node* search(flight_node* tail, char* search_number) {
    if (tail == NULL) {
        printf("No element in the list.\n");
        return NULL;
    } else {
        flight_node* temp = tail->next;
        do {
            if (strcmp(temp->flight_number, search_number) == 0) {
                return temp;
            }
            temp = temp->next;
        } while (temp != tail->next);
    }
    printf("Flight not found.\n");
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

    // Set the departure directly as "Guyana"
    char flight_departure[] = "Guyana";

    printf("\n\nEnter Flight Number: ");
    scanf("%s", flight_number);
    printf("Enter Airline Service: ");
    scanf(" %[^\n]s", airline_service);
    printf("Enter Flight Destination: ");
    scanf(" %[^\n]s", flight_destination);
    printf("Enter Departure Date (DD/MM/YYYY): ");
    scanf(" %[^\n]s", departure_date);
    printf("Enter Departure Time (HH:MM): ");
    scanf(" %[^\n]s", departure_time);
    printf("Enter Flight Duration (in minutes): ");
    scanf("%d", &flight_duration);
    printf("Enter Seat Availability: ");
    scanf("%d", &seat_available);
    printf("Enter flight fare: ");
    scanf("%f", &flight_fare);

    *tail = addAtEnd(*tail, flight_number, airline_service, flight_destination, flight_departure, departure_date, departure_time, flight_duration, seat_available, flight_fare);

    printf("Flight information created successfully!\n");
}

void viewAllFlightInfo(flight_node* tail) {
    printf("All Flight Information\n");
    print(tail);
}

void searchByDestination(flight_node* tail) {
    char destination[100];
    printf("\nEnter Destination: ");
    scanf(" %[^\n]s", destination);
    printf("Flights to Destination: %s\n", destination);
    viewByDestination(tail, destination);
}
