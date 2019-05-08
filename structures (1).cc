#include <stdio.h>
#include <string.h>
#include "structures.h"

void getOnePerson(person_t *p)
{   //name
	printf("Enter full name: ");
	scanf("%s[^\n]\n", p->name); //name here is a pointer because its an array
	//ssn
	printf("Enter ssn: ");
	scanf("%s[^\n]\n", p->ssn);
	//year of birth
	printf("Enter year of birth: ");
	scanf("%d[^\n]\n", &p->yearOfBirth); //what in tarnation 
}

void printOnePerson(person_t p)//this is passed by value not by reference
{
	printf("%s:%s:%d\n",p.name,p.ssn,p.yearOfBirth);
}

void getPeople(person_t p[], int n)
{
	for(int i = 0; i < n; i++)
	{
		getOnePerson(&p[i]);
	}
}

void printPeople(person_t p[], int n)
{
	for(int i = 0; i < n; i++)
	{
		printOnePerson(p[i]);
	}
}

/*int main()
{
	person_t p0, p1, p2;
	person_t people[3];

	//Getting first person into p0.
	getOnePerson(&p0);
	//Getting next two p1 and p2 people using an array.
	people[0] = p1;
	people[1] = p2;
	getPeople(people, 2);
	
	//Printing the first person.
	printOnePerson(p0);

	//printing from the array.
	printPeople(people, 2);

	return 0;
}
*/
