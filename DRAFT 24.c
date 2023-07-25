/*

SEMESTER PROJECT: FLIGHT RESERVATION SYSTEM
COURSE CODE: CSE2100

GROUP MEMBERS:
	Romain Seedharie, USI: 1044710
	Zoloni Chase, USI: 1042755
	Navindra Deonarine, USI: 1044011
	Parthiv Birbal, USI: 1044705
	Asmaa Rajab, USI: 1045211
	Esther Lokhnauth, USI: 1044644

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//THE FOLLOWING STRUCT REPRENST A NODE FOR FLIGHT INFORMATION FOR THE CIRCULART LINK LIST
typedef struct f_node 
{
    struct f_node* prev;
    char f_number[10];
    char f_service[100];
    char f_destination[100]; 
    char f_departure[100]; 
    char dep_date[20];
    char dep_time[20];
    int f_duration;
    char arriv_time[20];
    int seats;
    float prince;
    struct f_node* next;
} f_node;

//THE FOLLOWING STRUCT REPRENST A NODE FOR EACH PASSENGER INFORMATION FOR THE BINARY SEARCH TREE
typedef struct p_node 
{
    struct p_node* left;
    char p_full_name[100];
    char email[100]; 
    char password[20]; 
    char p_dob[20]; 
    char p_address[100];
    char passport_no[20];
    char id_card_no[20]; 
    char reserved_flight_no[10]; 
    struct p_node* right;
} p_node;

// =========================================================================== FUNCTION DECLERATIONS =================================================================================
void calculate_arrival_time_funct(f_node* flight);
void edit_flight_info_funct(f_node* tail);
f_node* add_to_empty_funct(char* f_number, char* f_service, char* f_destination, char* f_departure, char* dep_date, char* dep_time, int f_duration, int seats, float prince);
f_node* add_at_end_funct(f_node* tail, char* f_number, char* f_service, char* f_destination, char* f_departure, char* dep_date, char* dep_time, int f_duration, int seats, float prince);
void f_print(f_node* tail);
void view_by_destination_funct(f_node* tail, char* destination);
f_node* search_funct(f_node* tail, char* search_number);
void create_new_flight_funct(f_node** tail);
void view_all_flight_funct(f_node* tail);
void search_by_destination_funct(f_node* tail);
p_node* insert_p_node_funct(p_node* root, char* p_full_name, char* email, char* password, char* p_dob, char* p_address, char* passport_no, char* id_card_no);
p_node* search_p_funct(p_node* root, char* email, char* password);


//============================================================================ FUNCTION DEFINITIONS ===================================================================================
//THE FOLLOWING CREATES AND INITILIZES A NEW FLIGHT NODE 
f_node* createFlightNode(char f_number[], char f_service[], char f_destination[], char f_departure[], char dep_date[], char dep_time[], int f_duration, int seats) 
{
    f_node* newNode = (f_node*)malloc(sizeof(f_node));
    strcpy(newNode->f_number, f_number);
    strcpy(newNode->f_service, f_service);
    strcpy(newNode->f_destination, f_destination);
    strcpy(newNode->f_departure, f_departure);
    strcpy(newNode->dep_date, dep_date);
    strcpy(newNode->dep_time, dep_time);
    newNode->f_duration = f_duration;
    newNode->seats = seats;
    newNode->next = NULL;
    return newNode;
}

//THE FOLLOWING CALCULATES THE ARRIVAL TIME FOR FLIGHT USING THE DEPARTURE TIME AND THE FLIGHT DURATION
void calculate_arrival_time_funct(f_node* flight) 
{
    int departure_hour, departure_minute;
    sscanf(flight->dep_time, "%d:%d", &departure_hour, &departure_minute);
    int departure_time_minutes = departure_hour * 60 + departure_minute;
    int arrival_time_minutes = departure_time_minutes + flight->f_duration;

    int arrival_hour = arrival_time_minutes / 60;
    int arrival_minute = arrival_time_minutes % 60;

    arrival_hour %= 24; 

    snprintf(flight->arriv_time, sizeof(flight->arriv_time), "%02d:%02d", arrival_hour, arrival_minute);
}


//THE FOOLOWING REASTE A CIRCULAR LINK LIST WITH A NODE WHEN IT IS EMPTY
f_node* add_to_empty_funct(char* f_number, char* f_service, char* f_destination, char* f_departure, char* dep_date, char* dep_time, int f_duration, int seats, float prince) 
{
    f_node* temp = malloc(sizeof(f_node));
    temp->prev = temp;
    strcpy(temp->f_number, f_number);
    strcpy(temp->f_service, f_service);
    strcpy(temp->f_destination, f_destination);
    strcpy(temp->f_departure, f_departure);
    strcpy(temp->dep_date, dep_date);
    strcpy(temp->dep_time, dep_time);
    temp->f_duration = f_duration;
    calculate_arrival_time_funct(temp); 
    temp->seats = seats;
    temp->prince = prince;
    temp->next = temp;
    return temp;
}

//ASSIST IN ADDING A NEW NODE AT THE END OF THE LINK LIST
f_node* add_at_end_funct(f_node* tail, char* f_number, char* f_service, char* f_destination, char* f_departure, char* dep_date, char* dep_time, int f_duration, int seats, float prince) 
{
    f_node* newPrev = add_to_empty_funct(f_number, f_service, f_destination, f_departure, dep_date, dep_time, f_duration, seats, prince);
    if (tail == NULL) 
	{
        return newPrev;
    }
    f_node* temp = tail->next;
    newPrev->next = temp;
    newPrev->prev = tail;
    tail->next = newPrev;
    temp->prev = newPrev;
    tail = newPrev;
    return tail;
}


//PRINTS ALL INFORMATION IN THE CIRCULAR LIST
void f_print(f_node* tail) 
{
    if (tail == NULL) 
	{
        printf("No element in the list.\n");
    } 
	else 
	{
        f_node* temp = tail->next;
        do 
		{
        	printf("-------------------------------------------------------------\n");
            printf("\nFlight Number:\t\t%s\n", temp->f_number);
            printf("Airline Service:\t%s\n", temp->f_service);
            printf("Flight Destination:\t%s\n", temp->f_destination);
            printf("Flight Departure:\t%s\n", temp->f_departure);
            printf("Departure Date:\t\t%s\n", temp->dep_date);
            printf("Departure Time:\t\t%s\n", temp->dep_time);
            printf("Flight Duration:\t%d minutes\n", temp->f_duration);
            printf("Arrival Time:\t\t%s\n", temp->arriv_time);
            printf("Seat Availability:\t%d\n", temp->seats);
            printf("Ticket Price:\t\t$%.2f\n", temp->prince);
            printf("-------------------------------------------------------------\n");
            temp = temp->next;
        } while (temp != tail->next);
    }
}

//PRINTS INFORMATION RELATING TO A FLIGHT BASED ON THE DESTINATION ENTERED BY THE USER
void view_by_destination_funct(f_node* tail, char* destination) 
{
    if (tail == NULL) 
	{
        printf("No flight information available.\n");
        return;
    }

    f_node* temp = tail->next; 
    printf("FLIGHTS TO %s:\n", destination);
    int found = 0;

    do 
	{
        if (strcasecmp(temp->f_destination, destination) == 0) 
		{
            printf("-------------------------------------------------------------\n");
            printf("Flight Number: %s\n", temp->f_number);
            printf("Airline Service: %s\n", temp->f_service);
            printf("Destination: %s\n", temp->f_destination);
            printf("Departure: %s\n", temp->f_departure);
            printf("Departure Date: %s\n", temp->dep_date);
            printf("Departure Time: %s\n", temp->dep_time);
            printf("Flight Duration: %d minutes\n", temp->f_duration);
            printf("Arrival Time: %s\n", temp->arriv_time);
            printf("Seats Available: %d\n", temp->seats);
            printf("-------------------------------------------------------------\n");
            found = 1;
        }
        temp = temp->next;
    } while (temp != tail->next);

    if (!found) 
	{
        printf("No flights to %s.\n", destination);
    }
}


// ASSIST IN SEARCHING FOR A FLIGHT BASED ON ITS FLIGHT NUMBER WITHIN THE CIRCULAR LIST
f_node* search_funct(f_node* tail, char* search_number) 
{
    f_node* temp = tail;
    while (temp != NULL) 
	{
        if (strcmp(temp->f_number, search_number) == 0) 
		{
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

//THE FOLLOWING ALLOWS THE USER TO ADD A NEW DONE FOR THE FLIGHT INFORMATION IN THE CIRCULAR LIST
void create_new_flight_funct(f_node** tail) 
{
    char f_number[10];
    char f_service[100];
    char f_destination[100];
    char dep_date[20];
    char dep_time[20];
    int f_duration;
    int seats;
    float prince;

    printf("Enter Flight Number: ");
    scanf("%s", f_number);
    printf("Enter Airline Service: ");
    scanf(" %[^\n]s", f_service);
    printf("Enter Flight Destination: ");
    scanf(" %[^\n]s", f_destination);
    
    // Set the departure directly as "Guyana"
    char f_departure[] = "Guyana";
    
	printf("Enter Departure Date (YYYY-MM-DD): ");
    scanf(" %[^\n]s", dep_date);
    printf("Enter Departure Time (HH:MM): ");
    scanf(" %[^\n]s", dep_time);
    printf("Enter Flight Duration (minutes): ");
    scanf("%d", &f_duration);
    printf("Enter Number of Seats Available: ");
    scanf("%d", &seats);
    printf("Enter flight fare: ");
    scanf("%f", &prince);

    *tail = add_at_end_funct(*tail, f_number, f_service, f_destination, f_departure, dep_date, dep_time, f_duration, seats, prince);
    printf("-------------------------------------------------------------\n");
	printf("Flight information added successfully!\n\n\n");
}

//CALLS THE PRINT FUNCTION IF THE CIRCULAR LINK LIST HAVE EXISITNG NODES
void view_all_flight_funct(f_node* tail) 
{
    if (tail == NULL) 
	{
        printf("No flight information available.\n\n\n");
    } 
	else 
	{
        f_print(tail);
    }
}

// ALLOWS USER TO ENTER A DESTIONATION AND IT CALLS THE view_by_destination_funct() TO FIND THAT CORRESPOND FLIGHT TO TAHT DESTINATION
void search_by_destination_funct(f_node* tail) 
{
    char destination[100];
    printf("Enter the destination to search_funct: ");
    scanf(" %[^\n]", destination);
    view_by_destination_funct(tail, destination);
}


//INSERT A NEW NODE FOR THE PASSENGER INTO THE BINARY TREE
p_node* insert_p_node_funct(p_node* root, char* p_full_name, char* email, char* password, char* p_dob, char* p_address, char* passport_no, char* id_card_no) 
{
    if (root == NULL) 
	{
        p_node* new_passenger = (p_node*)malloc(sizeof(p_node));
        strcpy(new_passenger->p_full_name, p_full_name);
        strcpy(new_passenger->email, email);
        strcpy(new_passenger->password, password);
        strcpy(new_passenger->p_dob, p_dob);
        strcpy(new_passenger->p_address, p_address);
        strcpy(new_passenger->passport_no, passport_no);
        strcpy(new_passenger->id_card_no, id_card_no);
        new_passenger->left = NULL;
        new_passenger->right = NULL;
        return new_passenger;
    }

    if (strcmp(email, root->email) < 0) 
	{
        root->left = insert_p_node_funct(root->left, p_full_name, email, password, p_dob, p_address, passport_no, id_card_no);
    } 
	else if (strcmp(email, root->email) > 0) 
	{
        root->right = insert_p_node_funct(root->right, p_full_name, email, password, p_dob, p_address, passport_no, id_card_no);
    }

    return root;
}

//ASSIST IN SEARCHIONG FOR A PAASSENGER USING THEIR EMAIL AND PASSWORD
p_node* search_p_funct(p_node* root, char* email, char* password) 
{
    if (root == NULL || strcmp(root->email, email) == 0 && strcmp(root->password, password) == 0) 
	{
        return root;
    }

    if (strcmp(email, root->email) < 0) 
	{
        return search_p_funct(root->left, email, password);
    } 
	else 
	{
        return search_p_funct(root->right, email, password);
    }
}

// HELPS TO CREATE A PASSENGER NODE AND INSETING IT IN THE BINARY TREE INORDER TO REGISTER A NEW USER
p_node* register_user_funct(p_node* root, char p_full_name[], char email[], char password[], char p_dob[], char p_address[], char passport_no[], char id_card_no[]) 
{
    p_node* newNode = (p_node*)malloc(sizeof(p_node));
    strcpy(newNode->p_full_name, p_full_name);
    strcpy(newNode->email, email);
    strcpy(newNode->password, password);
    strcpy(newNode->p_dob, p_dob);
    strcpy(newNode->p_address, p_address);
    strcpy(newNode->passport_no, passport_no);
    strcpy(newNode->id_card_no, id_card_no);
    newNode->left = NULL;
    newNode->right = NULL;

    if (root == NULL)
        return newNode;

    p_node* current = root;
    p_node* parent = NULL;

    while (current != NULL) 
	{
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


// SIMILAR TO search_p_funct. BUT WE USE THIS DUPLICATE TO AVOID A SPECIFIC ERROR WHICH WE HAD PROBLEM WITH
p_node* search_user_funct(p_node* root, char email[], char password[]) 
{
    if (root == NULL || (strcmp(root->email, email) == 0 && strcmp(root->password, password) == 0)) 
	{
        return root;
    }

    if (strcmp(email, root->email) < 0) 
	{
        return search_user_funct(root->left, email, password);
    } 
	else 
	{
        return search_user_funct(root->right, email, password);
    }
}


// PRINTS THE ODES IN THE BINARY TREE WHICH ARE THE PASSENGER USER INFORMATION
void print_p_node_funct(p_node* user) 
{
    printf("Full Name: %s\n", user->p_full_name);
    printf("Email: %s\n", user->email);
    printf("Date of Birth: %s\n", user->p_dob);
    printf("Home Address: %s\n", user->p_address);
    printf("Passport Number: %s\n", user->passport_no);
    printf("National ID: %s\n\n\n", user->id_card_no);
}



// THE FOLLOWING JUST RETURN THE search()
f_node* search_flight_funct(f_node* tail, char* search_number) 
{
    return search_funct(tail, search_number);
}



// ALLOW THE ADMIN USER TO EDIT A FLIGHT NODE FROM THE CIRCULAR LINK LIST
void edit_flight_info_funct(f_node* tail) 
{
    char f_number[10];
    printf("|======================== F L I G H T   E D I T   M E N U ========================|\n\n");
    printf("Enter the flight number to edit: ");
    scanf("%s", f_number);

    f_node* flight = search_flight_funct(tail, f_number);

    if (flight == NULL) 
	{
        printf("Flight with the provided number not found.\n");
    } 
	else 
	{
        printf("\n-------------------------------------------------------------\n");
        printf("Flight Number: %s\n", flight->f_number);
        printf("Airline Service: %s\n", flight->f_service);
        printf("Destination: %s\n", flight->f_destination);
        printf("Departure: %s\n", flight->f_departure);
        printf("Departure Date: %s\n", flight->dep_date);
        printf("Departure Time: %s\n", flight->dep_time);
        printf("Flight Duration: %d minutes\n", flight->f_duration);
        printf("Arrival Time: %s\n", flight->arriv_time);
        printf("Seats Available: %d\n", flight->seats);
        printf("Ticket Price: $%.2f\n", flight->prince);
        printf("\n-------------------------------------------------------------");

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

        switch (infoChoice) 
		{
            case 1:
                printf("Enter Airline Service: ");
                scanf(" %[^\n]s", flight->f_service);
                break;
            case 2:
                printf("Enter Flight Destination: ");
                scanf(" %[^\n]s", flight->f_destination);
                break;
            case 3:
                printf("Enter Departure Date (YYYY-MM-DD): ");
                scanf(" %[^\n]s", flight->dep_date);
                break;
            case 4:
                printf("Enter Departure Time (HH:MM): ");
                scanf(" %[^\n]s", flight->dep_time);
                calculate_arrival_time_funct(flight);
                break;
            case 5:
                printf("Enter Flight Duration (minutes): ");
                scanf("%d", &flight->f_duration);
                calculate_arrival_time_funct(flight);
                break;
            case 6:
                printf("Enter Number of Seats Available: ");
                scanf("%d", &flight->seats);
                break;
            default:
                printf("Invalid choice. No changes made.\n");
                break;
        }

        printf("Flight information updated successfully!\n\n\n");
    }
}


// THE FOLLOWING GRANTS THE ADMIN THE ABILITY TO REMOVE AN ENTIRE FLIGHT NODE BASED ON IT FLIGHT NUMBER 
void remove_flight_funct(f_node** tail, char f_number[]) 
{
    if (*tail == NULL) 
	{
        printf("No flights in the list.\n");
        return;
    }

    f_node* current = (*tail)->next; 
    f_node* prev = *tail;
    int found = 0;

    do 
	{
        if (strcmp(current->f_number, f_number) == 0) 
		{
            if (current == (*tail)->next && current->next == current) 
			{
                free(current);
                *tail = NULL;
            } 
			else if (current == (*tail)->next) 
			{
                (*tail)->next = current->next;
                current->next->prev = *tail;
                free(current);
            } 
			else if (current == *tail) 
			{
                (*tail)->next->prev = prev;
                prev->next = (*tail)->next;
                *tail = prev;
                free(current);
            } 
			else 
			{
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

    if (found) 
	{
        printf("Flight with number %s removed successfully!\n", f_number);
    } 
	else 
	{
        printf("Flight with number %s not found.\n", f_number);
    }
}

//============================================================================= MAIN FUNCTION ===================================================================================
int main() 
{
	char f_number[10];
	f_node* tail = NULL;
    p_node* passenger_tree = NULL; 
    f_node* flightList = NULL;
    f_node* flight_tail = NULL;
    p_node* passenger_root = NULL;
    
    int choice;
    int choice2;
    while (1) 
	{
    	system("cls"); 
        printf("|========================== F L I G H T   R E S E R V A T I O N   S Y S T E M ============================|\n\n");
        printf("1. Admin Login\n");
        printf("2. Passenger Login\n");
        printf("3. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
		{
            case 1: 
			{
                system("cls"); 
                // Admin section
                
                printf("|========================== A D M I N   L O G I N ==========================|\n\n");
                
                    char password[20];
                    printf("Enter the password: ");
                    scanf("%s", password);
                    system("cls"); 
				while(1)
				{
				
                    if (strcmp(password, "admin123") == 0) 
					{
                        
                        printf("|========================== A D M I N   M E N U ==========================|\n\n");
                        printf("1. Create New Flight Information\n");
                        printf("2. Edit Flight Information\n");
                        printf("3. View All Flight Information\n");
                        printf("4. Search Flight by Destination\n");
                        printf("5. Remove a Flight Entry\n");
                        printf("6. Back to Login\n");
                        printf("\nEnter your choice: ");
                        scanf("%d", &choice);

                        switch (choice) 
						{
                            case 1:
                                system("cls"); 
                                printf("|================ C R E A T E   N E W   F L I G H T   I N F O R M A T I O N ================|\n\n");
                                create_new_flight_funct(&tail);
                                break;
                            case 2:
                                system("cls"); 
                                edit_flight_info_funct(tail);
                                break;
							case 3:
                                system("cls"); 
                                printf("|================ V I E W   A L L   F L I G H T   I N F O R M A T I O N ================|\n\n");
                                view_all_flight_funct(tail);
                                break;
                            case 4:
                                system("cls"); 
                                printf("|================ S E A R C H   F L I G H T   B Y   D E S T I N A T I O N ================|\n\n");
                                search_by_destination_funct(tail);
                                break;
                            case 5:
                            	system("cls"); 
							    char removeFlightNumber[10];
							    printf("|======================== R E M O V E   F L I G H T =========================|\n\n");
							    printf("Enter the flight number to remove: ");
							    scanf("%s", removeFlightNumber);
							    remove_flight_funct(&tail, removeFlightNumber);
							    break;
                            case 6:
							    system("cls"); 
                                break;
                            default:
                                printf("Invalid choice. Please try again.\n");
                        }
                        if (choice == 6) 
						{
                            break;
                        }
                    } 
					else 
					{
                        printf("Invalid password. Please try again.\n\n");
                        break;
                    }
                }break;
                
            }
            case 2:
                system("cls"); 
                int choice;
                printf("|================= P A S S E N G E R   L O G I N   O P T I O N S =================|\n\n");
                printf("1. Sign up\n");
                printf("2. Login\n");
                printf("3. Return to previous page\n\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch (choice) 
				{
                    case 1: 
					{
                        char full_name[100], email[100], password[100], dob[20], home_address[100],
                            passport_num[20], id_no[20];

                        system("cls"); 
						printf("============================\n");
                        printf("          SIGN UP\n");
                        printf("============================\n\n");
                        printf("Full Name: ");
                        scanf(" %[^\n]s", full_name);
                        printf("Email: ");
                        scanf(" %[^\n]s", email);
                        printf("Password: ");
                        scanf(" %[^\n]s", password);
                        printf("Date of Birth (YYYY-MM-DD): ");
                        scanf(" %[^\n]s", dob);
                        printf("Home Address: ");
                        scanf(" %[^\n]s", home_address);
                        printf("Passport Number: ");
                        scanf(" %[^\n]s", passport_num);
                        printf("National ID: ");
                        scanf(" %[^\n]s", id_no);
                        
                        passenger_tree = register_user_funct(passenger_tree, full_name, email, password, dob, home_address, passport_num, id_no);
                        system("cls"); 
						printf("\nUser registered successfully!\n");
                        break;
                    }
                    case 2: 
					{
                        char email[100], password[100];
                        printf("\n============================\n");
                        printf("          LOGIN\n");
                        printf("============================\n\n");
                        printf("Email: ");
                        scanf(" %[^\n]s", email);
                        printf("Password: ");
                        scanf(" %[^\n]s", password);

                        p_node* user = search_user_funct(passenger_tree, email, password);
                        if (user != NULL) 
						{
                            system("cls"); 
							printf("\nLogged in Successful!\n\n");
							
							do 
							{
	                            printf("|================ P A S S E N G E R   O P T I O N S ================|\n\n");
								printf("1. View Personal Info\n");
								printf("2. View all flights available\n");
								printf("3. View Flight by Destination\n");
								printf("4. Reserve a Flight\n");
								printf("5. View reserved flight\n");
								printf("6. Return to previous page\n\n");
								printf("Enter your choice: ");
								scanf("%d", &choice2);
								
								switch (choice2) 
								{
								    case 1:
								    	system("cls"); 
								        printf("|================ P A S S E N G E R   P E R S O L A L   O P T I O N S ================|\n\n");
								        print_p_node_funct(user);
								        break;
								    case 2:
								    	system("cls"); 
								    	printf("|================ V I E W   A L L   F L I G H T   I N F O R M A T I O N ================|\n\n");
								    	view_all_flight_funct(tail);
								        break;
								    case 3:
								        system("cls"); 
	                                	printf("|================ S E A R C H   F L I G H T   B Y   D E S T I N A T I O N ================|\n\n");
								        search_by_destination_funct(tail);
								        break;
								    case 4:
									{
										system("cls"); 
										printf("|================ R E S E R V E   A   F L I G H T ================|\n\n");
										printf("Enter the flight number of the flight you wish to reserve: ");
										scanf("%s", f_number);
										
										f_node* flight = search_flight_funct(tail, f_number);
										
										if (flight == NULL) 
										{
										    printf("Invalid flight number. Please try again.\n");
										    break;
										}
										
										if (flight->seats == 0) 
										{
											printf("No seats available for the selected flight.\n");
										    printf("Please wait for a new flight to be announced with your desired destination");
										    break;
										}
										
										flight->seats--;
										strcpy(user->reserved_flight_no, f_number);
										
										printf("Flight reservation successful!\n");
										printf("Remaining seats for %s: %d\n", flight->f_number, flight->seats);
										break;
									}
									case 5:
									{
										system("cls"); 
										if (user->reserved_flight_no[0] == '\0') 
										{
										    printf("You have not reserved any flights yet.\n");
										} 
										else 
										{
										    printf("|================ F L I G H T   I N F O R M A T I O N   O N   R E S E R V E D   F L I G H T ================|\n\n");
										    f_node* reserved_flight = search_flight_funct(tail, user->reserved_flight_no);
										    if (reserved_flight == NULL) 
											{
										        printf("Error: The flight with the reserved flight number not found.\n");
										    } 
											else 
											{
										        printf("Flight Number: %s\n", reserved_flight->f_number);
										        printf("Airline Service: %s\n", reserved_flight->f_service);
										        printf("Destination: %s\n", reserved_flight->f_destination);
										        printf("Departure: %s\n", reserved_flight->f_departure);
										        printf("Departure Date: %s\n", reserved_flight->dep_date);
										        printf("Departure Time: %s\n", reserved_flight->dep_time);
										        printf("Flight Duration: %d minutes\n", reserved_flight->f_duration);
										        printf("Arrival Time: %s\n", reserved_flight->arriv_time);
										        printf("Seats Available: %d\n", reserved_flight->seats);
										        printf("Ticket Price: $%.2f\n", reserved_flight->prince);
										    }
										}
										break;
									}
									case 6:
								        break;
								    default:
								        printf("Invalid choice\n");
								        break;
								}
								while (getchar() != '\n');
                            } while (choice2 != 6); 
                        } 
						else 
						{
                            printf("\nInvalid email or password. Please try again.\n");
                        }
                        break;
                    }
                    case 3:
                        printf("You selected Return to previous page.\n");
                        break;
                    default:
                        printf("Invalid choice.\n");
                        break;
                }
                break;
            case 3:
            	system("cls"); 
                printf("You have exited the program.\n");
                return 0; 
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

