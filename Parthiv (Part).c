#include <stdio.h>
#include <string.h>


int caribbean_funct();
int american_funct();




typedef struct
{
	char airline[100];
    char flight_number[5];
    char departure_airport[100];
    
	struct{
		int dd;
		int mm;
		int yyyy;
	}departure_date;
	
	struct{
		int hh;
		int mm;
	}departure_time;
	
    char arrival_airport[50];
    
	struct{
		int dd;
		int mm;
		int yyyy;
	}arrival_date;
	
	struct{
		int hh;
		int mm;
	}arrival_time;
	
    char aircraft_type[50];
    
    struct{
		int hh;
		int mm;
	}flight_duration;
	
    char flight_status[20];
    int seat_availability;
    int fare_information;
    char connecting_flights[200];
    char baggage_allowance[100];
    char gate_info[20];

}flight_info[3];

flight_info caribbean_air;
flight_info american_air;
flight_info jetblue_air;
flight_info British_air;




int caribbean_funct(){
	
	char text_file_name[100];
	int i;
	

	printf("\n1.Caribbean Airlines 1");
	printf("\n2.Caribbean Airlines 2");
	printf("\n3.Caribbean Airlines 3");
	printf("\n0.EXIT");
	printf("\nEnter Your Choice: ");
	scanf("%d",&i);
		

	
	if (i == 1){
		strcpy(text_file_name,"Caribbean Air Line 1.txt");
	}else if (i == 2){
		strcpy(text_file_name,"Caribbean Air Line 2.txt");
	}else if (i == 3){
		strcpy(text_file_name,"Caribbean Air Line 3.txt");
	}
	
		
	FILE* fp;
	
	fp = fopen(text_file_name,"r");
	
    if (fp == NULL) {
        printf("ERROR FAILED TO OPEN\n");
        return 1;
    }
    
    		printf("_____________________________________________");
    		printf("\ni = %d\n", i);
    		printf("Text file name: %s\n",text_file_name);    		
    		printf("_____________________________________________");
			
			fscanf(fp, "%s", caribbean_air[i].airline);
		    printf("\nAirline service: %s\n", caribbean_air[i].airline);
		    
		    fscanf(fp, "%s", caribbean_air[i].flight_number);
		    printf("Flight Number: %s\n", caribbean_air[i].flight_number);
		    
    		fscanf(fp, "%s", caribbean_air[i].departure_airport);
    		printf("Departure Airport: %s\n", caribbean_air[i].departure_airport);
    		
    		fscanf(fp, "%d", &caribbean_air[i].departure_date.dd);
    		fscanf(fp, "%d", &caribbean_air[i].departure_date.mm);
    		fscanf(fp, "%d", &caribbean_air[i].departure_date.yyyy);
			printf("Departure date: %d/%d/%d\n", caribbean_air[i].departure_date.dd, caribbean_air[i].departure_date.mm, caribbean_air[i].departure_date.yyyy);

			fscanf(fp, "%d", &caribbean_air[i].departure_time.hh);
    		fscanf(fp, "%d", &caribbean_air[i].departure_time.mm);
			printf("Departure time: %d:%d\n", caribbean_air[i].departure_time.hh, caribbean_air[i].departure_time.mm);
			
			fscanf(fp, "%s", caribbean_air[i].arrival_airport);
    		printf("Arrival Airport: %s\n", caribbean_air[i].arrival_airport);
    		
    		fscanf(fp, "%d", &caribbean_air[i].arrival_date.dd);
    		fscanf(fp, "%d", &caribbean_air[i].arrival_date.mm);
    		fscanf(fp, "%d", &caribbean_air[i].arrival_date.yyyy);
			printf("Arrival date: %d/%d/%d\n", caribbean_air[i].arrival_date.dd, caribbean_air[i].arrival_date.mm, caribbean_air[i].arrival_date.yyyy);

			fscanf(fp, "%d", &caribbean_air[i].arrival_time.hh);
    		fscanf(fp, "%d", &caribbean_air[i].arrival_time.mm);
			printf("Arrival time: %d:%d\n", caribbean_air[i].arrival_time.hh, caribbean_air[i].arrival_time.mm);

			fscanf(fp, "%s", caribbean_air[i].aircraft_type);
		    printf("Aircraft Type: %s\n", caribbean_air[i].aircraft_type);
		    
		    fscanf(fp, "%d", &caribbean_air[i].flight_duration.hh);
    		fscanf(fp, "%d", &caribbean_air[i].flight_duration.mm);
			printf("Flight Duration: %dhr %dmin\n", caribbean_air[i].flight_duration.hh, caribbean_air[i].flight_duration.mm);
			
			fscanf(fp, "%s", caribbean_air[i].flight_status);
		    printf("Flight Status: %s\n", caribbean_air[i].flight_status);

			fscanf(fp, "%d", &caribbean_air[i].seat_availability);
		    printf("Seats currently available: %d\n", caribbean_air[i].seat_availability);

			fscanf(fp, "%d", &caribbean_air[i].fare_information);
		    printf("Price: $%d\n", caribbean_air[i].fare_information);
		    
		    fscanf(fp, "%s", caribbean_air[i].connecting_flights);
		    printf("Connecting flight stops: %s\n", caribbean_air[i].connecting_flights);
		    
		    fscanf(fp, "%s", caribbean_air[i].baggage_allowance);
		    printf("Baggage Allowances: %s\n", caribbean_air[i].baggage_allowance);
		    
		    fscanf(fp, "%s", caribbean_air[i].gate_info);
		    printf("Gate: %s\n", caribbean_air[i].gate_info);
}
int american_funct(){
	
	char text_file_name[100];
	int i;
	

	printf("\n1.American Airlines 1");
	printf("\n2.American Airlines 2");
	printf("\n3.American Airlines 3");
	printf("\n0.EXIT");
	printf("\nEnter Your Choice: ");
	scanf("%d",&i);
		

	
	if (i == 1){
		strcpy(text_file_name,"American Air Line 1.txt");
	}else if (i == 2){
		strcpy(text_file_name,"American Air Line 2.txt");
	}else if (i == 3){
		strcpy(text_file_name,"American Air Line 3.txt");
	}
	
		
	FILE* fp;
	
	fp = fopen(text_file_name,"r");
	
    if (fp == NULL) {
        printf("ERROR FAILED TO OPEN\n");
        return 1;
    }
    
    		printf("_____________________________________________");
    		printf("\ni = %d\n", i);
    		printf("Text file name: %s\n",text_file_name);    		
    		printf("_____________________________________________");
			
			fscanf(fp, "%s", american_air[i].airline);
		    printf("\nAirline service: %s\n", american_air[i].airline);
		    
		    fscanf(fp, "%s", american_air[i].flight_number);
		    printf("Flight Number: %s\n", american_air[i].flight_number);
		    
    		fscanf(fp, "%s", american_air[i].departure_airport);
    		printf("Departure Airport: %s\n", american_air[i].departure_airport);
    		
    		fscanf(fp, "%d", &american_air[i].departure_date.dd);
    		fscanf(fp, "%d", &american_air[i].departure_date.mm);
    		fscanf(fp, "%d", &american_air[i].departure_date.yyyy);
			printf("Departure date: %d/%d/%d\n", american_air[i].departure_date.dd, american_air[i].departure_date.mm, american_air[i].departure_date.yyyy);

			fscanf(fp, "%d", &american_air[i].departure_time.hh);
    		fscanf(fp, "%d", &american_air[i].departure_time.mm);
			printf("Departure time: %d:%d\n", american_air[i].departure_time.hh, american_air[i].departure_time.mm);
			
			fscanf(fp, "%s", american_air[i].arrival_airport);
    		printf("Arrival Airport: %s\n", american_air[i].arrival_airport);
    		
    		fscanf(fp, "%d", &american_air[i].arrival_date.dd);
    		fscanf(fp, "%d", &american_air[i].arrival_date.mm);
    		fscanf(fp, "%d", &american_air[i].arrival_date.yyyy);
			printf("Arrival date: %d/%d/%d\n", american_air[i].arrival_date.dd, american_air[i].arrival_date.mm, american_air[i].arrival_date.yyyy);

			fscanf(fp, "%d", &american_air[i].arrival_time.hh);
    		fscanf(fp, "%d", &american_air[i].arrival_time.mm);
			printf("Arrival time: %d:%d\n", american_air[i].arrival_time.hh, american_air[i].arrival_time.mm);

			fscanf(fp, "%s", american_air[i].aircraft_type);
		    printf("Aircraft Type: %s\n", american_air[i].aircraft_type);
		    
		    fscanf(fp, "%d", &american_air[i].flight_duration.hh);
    		fscanf(fp, "%d", &american_air[i].flight_duration.mm);
			printf("Flight Duration: %dhr %dmin\n", american_air[i].flight_duration.hh, american_air[i].flight_duration.mm);
			
			fscanf(fp, "%s", american_air[i].flight_status);
		    printf("Flight Status: %s\n", american_air[i].flight_status);

			fscanf(fp, "%d", &american_air[i].seat_availability);
		    printf("Seats currently available: %d\n", american_air[i].seat_availability);

			fscanf(fp, "%d", &american_air[i].fare_information);
		    printf("Price: $%d\n", american_air[i].fare_information);
		    
		    fscanf(fp, "%s", american_air[i].connecting_flights);
		    printf("Connecting flight stops: %s\n", american_air[i].connecting_flights);
		    
		    fscanf(fp, "%s", american_air[i].baggage_allowance);
		    printf("Baggage Allowances: %s\n", american_air[i].baggage_allowance);
		    
		    fscanf(fp, "%s", american_air[i].gate_info);
		    printf("Gate: %s\n", american_air[i].gate_info);
	
}



void display(){}
void append() {}





int main(){
	int choice;
	do{
		printf("\n1.Caribbean Airlines Flight information");
		printf("\n2.American Airlines Flight information");
		printf("\n3.British Airlines Flight information");
		printf("\n0.EXIT");
		
		printf("\nEnter Your Choice: ");
		scanf("%d",&choice);
		
		switch (choice){
			case 1:
				caribbean_funct();
				break;
			case 2:
				american_funct();
				break;
			case 3:
				append();
				break;
		}
	}while(choice!=0);

return 0;

}

