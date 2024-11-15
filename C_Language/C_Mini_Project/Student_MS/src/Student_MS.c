/*
 =================================================================================================================
 Name        : Student_MS.c
 Author      : Abdelrahman Tharwat
 Description : Student Management System, a C language program designed to manage student information efficiently.
 =================================================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Student info structure */
typedef struct
{
	int id; /*Student ID*/
	char name[50]; /*Student Name*/
	int age; /*Student Age*/
	float gpa; /*Student GPA*/
} Student; /*Renaming the "struct student" keyword to Student*/

/*Linked list Structure Definition */
typedef struct node
{
	Student data; /*As each node instance take place in memory,	 we make an instance from student struct*/
	struct node *next; /*Pointer of same type of struct to point at next struct node*/
} Node; /*Renaming the "struct node" keyword to Student*/

Node *head = NULL; /*head pointer to point at first node */


// Functions Declaration
void addStudent(const Student *const ptr); /*Adding a new distinct student to the list*/
void displayStudents(void); /*Prints all available students in the list*/
void searchStudentByID(int id); /*Prints student's info using his/her ID*/
void updateStudent(int id); /*Updates student's info using his/her ID*/
float calculateAverageGPA(void); /*Returns the total Avg. GPA of all students*/
void searchHighestGPA(void); /*Prints info of student with the highest GPA*/
void deleteStudent(int id); /*Removes a student from the list using his/her ID and frees the Memory allocation from the heap*/
void printStudInfo(const Student *const ptr); /*Prints student info in a tabular format*/

int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
	int input; /*variable declaring to store repetitive switch case input*/
	unsigned char countInvalid = 0; /*counter for many consecutive bad input to prevent bad program infinite looping*/
	Student storeStudInfo; /*an instance of Student struct to store the input variables*/

	// Special print for the start of the program (A Linux tool called figlet was used to generate this ASCII art)

	printf( "=============================================================================\n");
	printf( "   _____ __            __           __ \n"
			"  / ___// /___  ______/ /__  ____  / /_\n"
			"  \\__ \\/ __/ / / / __  / _ \\/ __ \\/ __/\n"
			" ___/ / /_/ /_/ / /_/ /  __/ / / / /_  \n"
			"/____/\\__/\\__,_/\\__,_/\\___/_/ /_/\\__/  \n");
	printf( "    __  ___                                            __ \n"
			"   /  |/  /___ _____  ____ ____  ____ ___  ___  ____  / /_\n"
			"  / /|_/ / __ `/ __ \\/ __ `/ _ \\/ __ `__ \\/ _ \\/ __ \\/ __/\n"
			" / /  / / /_/ / / / / /_/ /  __/ / / / / /  __/ / / / /_  \n"
			"/_/  /_/\\__,_/_/ /_/\\__, /\\___/_/ /_/ /_/\\___/_/ /_/\\__/  \n"
			"                   /____/                                 \n");
	printf( "   _____            __               \n"
			"  / ___/__  _______/ /____  ____ ___ \n"
			"  \\__ \\/ / / / ___/ __/ _ \\/ __ `__ \\\n"
			" ___/ / /_/ (__  ) /_/  __/ / / / / /\n"
			"/____/\\__, /____/\\__/\\___/_/ /_/ /_/ \n"
			"     /____/                          \n");

	printf( "=============================================================================\n");

	//infinite looping as user will prompt to end the program
	while (1)
	{
		//Display System options for the user
		printf(" 1- Add Student\n");
		printf(" 2- Display Students\n");
		printf(" 3- Search Student by ID\n");
		printf(" 4- Update Student Information\n");
		printf(" 5- Calculate Students Average GPA\n");
		printf(" 6- Search for student with Highest GPA\n");
		printf(" 7- Delete Student\n");
		printf(" 8- Exit Program\n");

		printf(" Enter choice: ");
		scanf("%d", &input); /*User choice input*/

		if (countInvalid > 10) /*count till 10 consecutive non valid input*/
		{
			printf(" ERROR: Program failure, reason: NON Integer input ");
			return 1; /*Stop the program*/
		}

		switch (input)
		{
		case 1:
			//Storing user input in the previously declared student instance
			printf(" Enter Student ID: ");
			scanf("%d", &storeStudInfo.id);
			getchar(); /*to clear the \n from the input buffer*/
			printf(" Enter Student Name: ");
			fgets(storeStudInfo.name,sizeof(storeStudInfo.name),stdin); /*to take multiple spaced string*/
			storeStudInfo.name[strcspn(storeStudInfo.name, "\n")] = 0; /*to remove the \n from string array as it is a confirmation character*/
			printf(" Enter Student Age: ");
			scanf("%d", &storeStudInfo.age);
			printf(" Enter Student GPA: ");
			scanf("%f", &storeStudInfo.gpa);
			addStudent(&storeStudInfo);
			countInvalid = 0; /*resets the invalid counts*/
			break;
		case 2:
			displayStudents();
			break;
		case 3:
			printf(" Enter Student ID to search for: ");
			scanf("%d", &storeStudInfo.id);
			searchStudentByID(storeStudInfo.id);
			countInvalid = 0;
			break;
		case 4:
			printf(" Enter Student ID to update his/her info: ");
			scanf("%d", &storeStudInfo.id);
			updateStudent(storeStudInfo.id);
			countInvalid = 0;
			break;
		case 5:
			printf(" Total Average students GPA = %.2f\n",
					calculateAverageGPA()); /*Calling and printing the return of the call*/
			countInvalid = 0;
			break;
		case 6:
			searchHighestGPA();
			countInvalid = 0;
			break;
		case 7:
			printf(" Enter Student ID to delete from the system: ");
			scanf("%d", &storeStudInfo.id);
			deleteStudent(storeStudInfo.id);
			countInvalid = 0;
			break;
		case 8:
			printf("-----------------------------------------------------------------------------\n");
			printf(" Program Exit\n");
			printf("-----------------------------------------------------------------------------\n");
			printf(" BYE!\n");
			return 0; /*End of the Program*/
		default:
			printf(" Invalid option choice\n");
			countInvalid++; /*increment after invalid input*/
		}
		printf("\n-----------------------------------------------------------------------------\n");
	}
}

// Functions Definition
void addStudent(const Student *const ptr)
{
	if (head == NULL) /*checking for empty list*/
	{
		head = (Node*) malloc(sizeof(Node)); /*allocating a new memory in the heap with Node size*/
		if (head == NULL) /*check if the allocation request failed*/
		{
			printf("-----------------------------------------------------------------------------\n\n");
			printf(" Memory allocation failed\n");
			return;
		}
		//assigning the first node in the list with the user input
		head->data.id = ptr->id;
		unsigned char i = 0;
		for (; ptr->name[i]; i++)
		{
			head->data.name[i] = ptr->name[i];
		}
		head->data.name[i] = '\0';
		head->data.age = ptr->age;
		head->data.gpa = ptr->gpa;
		head->next = NULL;
		printf("-----------------------------------------------------------------------------\n\n");
		printf(" New Student Added to the system\n");
		return;
	}
	if (head->data.id == ptr->id) /*check for already reserved id in the first node*/
	{
		printf("-----------------------------------------------------------------------------\n\n");
		printf(" ID (%d) already reserved\n", ptr->id);
		return;
	}
	Node *link = head; /*initializing a new pointer to traverse over the list*/
	while (link->next != NULL) /*looping over next node to stop at the last element of the list*/
	{
		if (link->next->data.id == ptr->id) /*check for already reserved id in each node in the list*/
		{
			printf("-----------------------------------------------------------------------------\n\n");
			printf(" ID (%d) already reserved\n", ptr->id);
			return;
		}
		link = link->next;
	}
	Node *new = (Node*) malloc(sizeof(Node)); /*allocating a new memory in the heap with Node size*/
	if (new == NULL) /*check if the allocation request failed*/
	{
		printf("-----------------------------------------------------------------------------\n\n");
		printf(" Memory allocation failed\n");
		return;
	}
	//assigning a new node with the user input
	new->data.id = ptr->id;
	unsigned char i = 0;
	for (; ptr->name[i]; i++)
	{
		new->data.name[i] = ptr->name[i];
	}
	new->data.name[i] = '\0';
	new->data.age = ptr->age;
	new->data.gpa = ptr->gpa;
	new->next = NULL;
	link->next = new; /*adding the new node in the end of the list*/
	printf("-----------------------------------------------------------------------------\n\n");
	printf(" New Student is added to the system\n");
}

void displayStudents(void)
{
	if (head == NULL) /*checking for empty list*/
	{
		printf("-----------------------------------------------------------------------------\n\n");
		printf(" List is empty, no student to display!\n");
		return;
	}
	Node *link = head; /*initializing a new pointer to traverse over the list*/
	printf( "-----------------------------------------------------------------------------\n\n");
	printf(	"|------------------------------------------------------------------------|\n"
			"|                   Student Name                   | ID | Age |   GPA    |\n"
			"|------------------------------------------------------------------------|\n");
	while (link != NULL) /*prints each student info till it becomes a NULL pointer*/
	{
		printStudInfo(&link->data);
		link = link->next;
	}

}

void searchStudentByID(int id)
{
	if (head == NULL) /*checking for empty list*/
	{
		printf("-----------------------------------------------------------------------------\n\n");
		printf(" List is empty, no student to display!\n");
		return;
	}
	Node *link = head; /*initializing a new pointer to traverse over the list*/
	while (link != NULL) /*looping over the list to find the input id till it becomes a NULL pointer*/
	{
		if (link->data.id == id)
		{
			printf( "-----------------------------------------------------------------------------\n\n");
			printf(	"|------------------------------------------------------------------------|\n"
					"|                   Student Name                   | ID | Age |   GPA    |\n"
					"|------------------------------------------------------------------------|\n");
			printStudInfo(&link->data);
			return;
		}
		link = link->next;
	}
	//prints student not found as it did not return while looping
	printf("-----------------------------------------------------------------------------\n\n");
	printf(" Student with ID (%d) not found.\n", id);

}

void updateStudent(int id)
{
	if (head == NULL) /*checking for empty list*/
	{
		printf("-----------------------------------------------------------------------------\n\n");
		printf(" List is empty, no student to update!\n");
		return;
	}
	Node *link = head; /*initializing a new pointer to traverse over the list*/
	while (link != NULL) /*looping over the list to find the input id till it becomes a NULL pointer*/
	{
		if (link->data.id == id) /*if ID present it prompts user to fill student details*/
		{
			getchar(); /*to clear the \n from the input buffer*/
			printf(" Enter Student Name: ");
			fgets(link->data.name,sizeof(link->data.name),stdin); /*to take multiple spaced string*/
			link->data.name[strcspn(link->data.name, "\n")] = 0; /*to remove the \n from string array as it is a confirmation character*/
			printf(" Enter Student Age: ");
			scanf("%d", &link->data.age);
			printf(" Enter Student GPA: ");
			scanf("%f", &link->data.gpa);
			printf("-----------------------------------------------------------------------------\n\n");
			printf(" Student details with ID (%d) updated successfully\n",
					link->data.id);
			return;
		}
		link = link->next;
	}
	//prints student not found as it did not return while looping
	printf("-----------------------------------------------------------------------------\n\n");
	printf(" Student with ID (%d) not found.\n", id);
}

float calculateAverageGPA(void)
{
	if (head == NULL) /*checking for empty list*/
	{
		printf("-----------------------------------------------------------------------------\n\n");
		printf(" List is empty, no GPA to display!\n");
		return 0;
	}
	Node *link = head; /*initializing a new pointer to traverse over the list*/
	float sum = link->data.gpa; /*initializing a float variable with the GPA of the first Node*/
	float count = 1; /*counter starts from 1 as first node summed up*/
	while (link->next != NULL) /*looping over next node as we summed up the first node*/
	{
		sum += link->next->data.gpa;
		count++;
		link = link->next;
	}
	printf("-----------------------------------------------------------------------------\n\n");
	return sum / count;
}

void searchHighestGPA(void)
{
	if (head == NULL) /*checking for empty list*/
	{
		printf("-----------------------------------------------------------------------------\n\n");
		printf(" List is empty, no GPA to display!\n");
		return;
	}
	Node *link = head; /*initializing a new pointer to traverse over the list*/
	Node *highestGPA = link; /*initializing a new pointer with the traverse pointer to point at the last highest GPA address*/
	while (link != NULL) /*looping over the list to find the input id till it becomes a NULL pointer*/
	{
		if (link->data.gpa > highestGPA->data.gpa) /*comparing the traverse pointer with the last address of largest GPA*/
		{
			highestGPA = link; /*assigning with the new highest GPA address*/
		}
		link = link->next;
	}
	printf( "-----------------------------------------------------------------------------\n\n");
	printf(	"|------------------------------------------------------------------------|\n"
			"|                   Student Name                   | ID | Age |   GPA    |\n"
			"|------------------------------------------------------------------------|\n");
	printStudInfo(&highestGPA->data);

}

void deleteStudent(int id)
{
	if (head == NULL) /*checking for empty list*/
	{
		printf("-----------------------------------------------------------------------------\n\n");
		printf(" List is empty, no student to display!\n");
		return;
	}
	if (head->data.id == id) /*if the first node to delete */
	{
		Node *remove = head; /*initializing a new pointer to free the memory allocation with*/
		head = head->next; /*moving the head to point to the next node*/
		free(remove); /*frees memory allocation*/
		printf("-----------------------------------------------------------------------------\n\n");
		printf(" Student with ID (%d) deleted successfully.\n", id);
		return;
	}
	Node *link = head; /*initializing a new pointer to traverse over the list*/
	while (link->next != NULL)  /*looping over next node to stop right before the node to delete*/
	{
		if (link->next->data.id == id)
		{
			Node *remove = link->next; /*initializing a new pointer to free the memory allocation with node to delete*/
			link->next = link->next->next; /*assigning the next pointer to point at the after node of the delete node */
			free(remove); /*frees memory allocation*/
			printf("-----------------------------------------------------------------------------\n\n");
			printf(" Student with ID (%d) deleted successfully.\n", id);
			return;
		}
		link = link->next;
	}
	//prints student not found as it did not return while looping
	printf("-----------------------------------------------------------------------------\n\n");
	printf(" Student with ID (%d) not found.\n", id);
}

void printStudInfo(const Student *const ptr)
{
	unsigned char size = 0; /*to store how many characters in the string*/
	unsigned char nameSpace = 49; /*a variable to calculate number of spaces after the name variable*/
	unsigned char idSpace = 3; /*a variable to calculate number of spaces after the ID variable*/
	unsigned char ageSpace = 4; /*a variable to calculate number of spaces after the age variable*/
	unsigned char digits = 0; /*to count number of digits in ID and age variables*/
	unsigned char i = 0; /*to loop over with and use it for number of character calculations*/

	for (; ptr->name[i]; i++) /*loop over the string*/
	{
		size++;
	}
	nameSpace = 49 - size; /*subtract the number of spaces with the user input string*/
	digits = ptr->id; /*assigning with id to calculate the number of digits*/
	i = 1; /*as the least number of digits is 1*/
	if (digits) /*if it is not 0*/
	{
		while (digits) /*loop over it until it become 0*/
		{
			digits = digits / 10;
			if (digits) /*check if not 0 after division*/
			{
				i++; /*increment the number of spaces to ignore*/
			}
		}
	}
	idSpace = 3 - i; /*3 is a fixed calculated character size for printing*/

	digits = ptr->age; /*assigning with age to calculate the number of digits*/
	i = 1; /*as the least number of digits is 1*/
	if (digits) /*if it is not 0*/
	{
		while (digits) /*loop over it until it become 0*/
		{
			digits = digits / 10;
			if (digits) /*check if not 0 after division*/
			{
				i++; /*increment the number of spaces to ignore*/
			}
		}
	}
	ageSpace = 4 - i; /*4 is a fixed calculated character size for printing*/

	//printing the variable with intended space calculations for tabular format printing
	printf("| %s", ptr->name);
	while (nameSpace)
	{
		printf(" ");
		nameSpace--;
	}
	printf("| %d", ptr->id);
	while (idSpace)
	{
		printf(" ");
		idSpace--;
	}
	printf("| %d", ptr->age);
	while (ageSpace)
	{
		printf(" ");
		ageSpace--;
	}
	printf("|   %.2f   |\n", ptr->gpa);
	printf("|------------------------------------------------------------------------|\n");

}
