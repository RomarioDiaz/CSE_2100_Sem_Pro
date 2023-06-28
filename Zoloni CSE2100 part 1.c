#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct person {
	char name[100],password[100],email[100],address[100];
	int passport_num,year,day,month,id_num,mobile;	
};

int main(){
	char verify_pass[100];
	int choice,i,tries=4,people;
	struct person* persons; // to dynamically allocate memory, we need to declare this point
	
	
	printf("Please choose an option:\n");
printf("1. Login\n");
printf("2. Create an account\n");
printf("Enter your choice: ");
scanf("%d",&choice);
getchar(); //without getchar() the two print statements will print in the same line because i used fgets and scanf

switch(choice){
	case 1: //login
	persons = (struct person*)malloc(sizeof(struct person));
	printf("Enter your name:");
	fgets(persons->name,100,stdin); // -> because it is a pointer to the person struct
	
	printf("Enter your email address:");
	fgets(persons->email,100,stdin);
		printf("Enter password:");
	fgets(persons->password,100,stdin);
	
	printf("Welcome Back %s",persons->name);
	free(persons);
		break;
		
		
		
		case 2: //create
		persons = (struct person*)malloc(sizeof(struct person));
		printf("Enter your name:");
	    fgets(persons->name,100,stdin);
	
	printf("Enter your email address:");
	scanf("%s",&persons->email);
	
	printf("Create a password:");
	scanf("%s",&persons->password);
		
	for(i =0; i<4; i++){
	
	printf("Verify password:");
	scanf("%s",&verify_pass);
	if(strcmp(persons->password,verify_pass)!=0){
		tries--;
		if(tries == 0){
			printf("Try again later");
			free(persons); //since this operation is completed,it will free the allocated memory
			return;
		}
		printf("Incorrect password. Try again %d times\n",tries);
		
	} else{
		break;
	}
}

	printf("Enter your date of birth (DD/MM/YYYY):");
	scanf("%d/%d/%d",&(persons->day),&(persons->month),&(persons->year));
	if(persons->year > 2005){
		printf("Not old enough");
		free(persons); 
		return;
	} else{
		
	}
	printf("Enter your passport number:");
	scanf("%d",&persons->passport_num);
	
	printf("Enter ID number:");
	scanf("%d",&persons->id_num);
    printf("Account created \n");
	
	break;	
	}
	free(persons);
		printf("Would you like to book a flight?\n");
		printf("1. Yes\n");
		printf("2. No\n");
		printf("Select option:");
		scanf("%d",&choice);
		
	switch(choice){	
	case 1: //Book a flight
	printf("Enter number of persons travelling:");
	
	scanf("%d",&people);
	
	persons = (struct person*)malloc(people * sizeof(struct person));
	//dynamically allocate because we dont know the exact amount of people
	
	for(i=1; i<=people; i++){
	printf("Enter person %d name:",i);
	getchar();
	fgets(persons[i].name,100,stdin);

	printf("Enter person %d email address:",i);
	fgets(persons[i].email,100,stdin);
	
	printf("Enter person %d address:",i);
	fgets(persons[i].address,100,stdin);
	
	
	printf("Enter person %d phone number:",i);
	scanf("%d",&persons[i].mobile);

	printf("Enter person %d date of birth (DD/MM/YYYY):",i);
	scanf("%d/%d/%d",&persons[i].day,&persons[i].month,&persons[i].year);

	printf("Enter person %d passport number:",i);
	scanf("%d",&persons[i].passport_num);
	
	printf("Enter person %d ID number:",i);
	scanf("%d",&persons[i].id_num);
	
	
	
		
}
break;

case 2:
	return 0;
	free(persons);
	break;
	
}
free(persons);
}



