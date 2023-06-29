
    /*Info *p1;
    p1 = malloc(sizeof(Info));
    strcpy(p1->name, "Romain");
    strcpy(p1->flight_service, "Caribbean_Airlines");
    strcpy(p1->destination, "Trinidad");

    printf("%s, %s, %s\n", p1->name, p1->flight_service, p1->destination);

    free(p1);*/

  

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char name[50];
    int flight_service[50];
    int destination[50];
} Info;

struct tm* localTime;
    char day[10];

int main() 
{
time_t currentTime;
    struct tm* localTime;
    char dateTime[64];

    // Get current time
    currentTime = time(NULL);

    // Convert to local time
    localTime = localtime(&currentTime);

    // Format date and time
    strftime(dateTime, sizeof(dateTime), "%Y-%m-%d %H:%M:%S", localTime);


    int length = 3;
    int op_1;

 Info *arr;
 Info *arr2;
    arr = malloc(sizeof(Info) * length);
    arr2 = malloc(sizeof(Info) * length);

    printf("What would you like to do?\n");
    printf("1: Enter flight information.\n");
    printf("2: View Flight information.\n");
    printf("3: Make changes to flight information.\n");
    scanf("%d", &op_1);
   
  

/*
    strcpy(arr[0].name, "Romain Seedharie");
    strcpy(arr[0].flight_service, "Caribbean Airlines");
    strcpy(arr[0].destination, "Trinidad");

    strcpy(arr[1].name, "Parthiv Birbal");
    strcpy(arr[1].flight_service, "American Airlines");
    strcpy(arr[1].destination, "Moscow");
*/



if (op_1 == 1 ) { 


    
for (int j=0;j<length;j++)
{ 
    printf("===========================================\n");
printf("Please enter your name: \n");
scanf("%s", arr[j].name);

printf("Please enter your Flight service: \n");
printf("1. CARIBBEAN AIR\n");
printf("2. AMERICAN AIR\n");
printf("3. JETBLUE AIR\n");
printf("4. BRITISH AIR\n");
scanf("%d", arr[j].flight_service);

printf("Please enter your destination: \n");
strftime(day, sizeof(day), "%A", localTime);
// Print current day
printf("%s\n, %s\n", day, dateTime);
printf("FROM:____________________________________TO:\n");
printf("1. GUYANA, GEORGETOWN -------------------TRINIDAD & T., PORT OF SPAIN\n");
printf("2. TRINIDAD & T., PORT OF SPAIN ---------UNITED STATES, NEW YORK\n");
printf("3. UNITED STATES, NEW YORK---------------GUYANA, GEORGETOWN\n");
printf("4. RUSSIA, ST. PETERSBURG----------------TRINIDAD & T., PORT OF SPAIN\n");
scanf("%d", arr[j].destination);
printf("===========================================\n");
}
}


if (op_1 == 2) { 
    /*printf("Passenger Info\n");
    for (int i = 0; i < length; i++) {
        printf("%s-->%s-->%s\n", arr2[i].name, arr2[i].flight_service, arr2[i].destination);
    } 
    }*/


// EVERYTHING BEFORE THIS LINE NEEDS TO BE EDITED BY PARTHIV
// EVERYTHING AFTER THIS LINE IS THE QUERY CODE

//FLIGHTS
printf("FROM:_________________________________TO:\n");
printf("GUYANA, GEORGETOWN -------------------TRINIDAD & T., PORT OF SPAIN\n");
printf("TRINIDAD & T., PORT OF SPAIN ---------UNITED STATES, NEW YORK\n");
printf("UNITED STATES, NEW YORK---------------GUYANA, GEORGETOWN\n");
printf("RUSSIA, ST. PETERSBURG----------------TRINIDAD & T., PORT OF SPAIN\n");

//NOTE: A GREEDY ALGORITHM CAN BE APPLIED HERE
// CONDITION TO SELECT FLIGHTS/ FIND THE FASTEST ROUTE TO DESTINATION
}
arr2 = arr;

  
printf("COPIED ARRAY CHECK\n");
  
        for (int s = 0; s < length; s++) {
            printf("info in array 2:  %d\n, %d\n, %d\n\n", arr2[s].name, arr2[s].flight_service, arr2[s].destination);
 }
 //APPLIED CHANGES

    free(arr);

printf("TRANSACTION TIME: %s\n", dateTime);
    return 0;
}

