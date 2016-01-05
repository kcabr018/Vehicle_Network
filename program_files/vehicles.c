//**********************************************************
// Author:      Kevin Cabrera
// Description: Performs the majority of the functionality
//              of the program such as populating the car 
//              list, updating distance between vehicles,
//              displaying vehicle's neighbor lists, etc
//**********************************************************
#include "vehicles.h"
#include <math.h>
#include <unistd.h>
#define PI 3.14159265

int i = 0, outfilearg;
CAR cars[50];

// adds new vehicle
void addVehicle(float specs[]) {
	CAR c;
	LLIST *start, *ptr;

	//assigns specs to vehicle
	c.pid = i + 1;
	c.xloc = specs[0];
	c.yloc = specs[1];
	c.speed = specs[2];
	c.theta = specs[3];
	c.head = NULL;

	cars[i] = c;	//adds car to car array list
	i++;
}
//add neighbor to neighbor list
void addNeighbor(CAR *c, CAR *newCar) {
	if (searchNeighbor(c, newCar->pid) == 0)
	{
		LLIST *ptr = (LLIST*)malloc(sizeof(LLIST));
		ptr->neighbor = newCar->pid;
		ptr->next = NULL;

		ptr->next = c->head;
		c->head = ptr;
	}
}

//delete neighbor from neighbor list
void delNeighbor(CAR *c, int neighbor) {
	LLIST *temp, *prev;

	if (c->head != NULL)
	{
		if (c->head->neighbor == neighbor)
		{
			temp = c->head;
			c->head = c->head->next;
			free(temp);
		}
		else
		{
			prev = c->head;
			while (prev->next != NULL && prev->next->neighbor != neighbor)
				prev = prev->next;
			temp = prev->next;
			if (temp != NULL)
			{
				prev->next = temp->next;
				free(temp);
			}
		}
		temp = NULL;
	}
}

//updates x and y coordinates
void updateLocation(int N) {
	int j;

	for (j = 0; j<i; j++) {
		cars[j].xloc = cars[j].xloc + cars[j].speed * cos(cars[j].theta * (PI / 180)) * N;
		cars[j].yloc = cars[j].yloc + cars[j].speed * sin(cars[j].theta * (PI / 180)) * N;
	}
}

//updates neighbor list of all vehicles
void updateNeighbors() {
	int j, k;
	float dist;

	for (j = 0; j < i; j++)
	{
		for (k = j + 1; k < i; k++)
		{
			dist = sqrt(pow(cars[j].xloc - cars[k].xloc, 2) + pow(cars[j].yloc - cars[k].yloc, 2));
			if (dist <= 250)
			{
				addNeighbor(&cars[j], &cars[k]);
				addNeighbor(&cars[k], &cars[j]);
			}
			else
			{
				delNeighbor(&cars[j], cars[k].pid);
				delNeighbor(&cars[k], cars[j].pid);
			}
		}
	}
}

//prints new neighbors for each vehicle
void printNeighbor(CAR *c)
{
	LLIST *ptr;
	ptr = c->head;

	while (ptr != NULL)
	{
		if (ptr->next != NULL)
			printf("Vehicle %d, ", ptr->neighbor);
		else
			printf("Vehicle %d", ptr->neighbor);
		ptr = ptr->next;
	}
	printf("\n");
}

//prints neighbor to file
void printNeighborToFile(char **argv, CAR *c, FILE* fr) { //, char last) {//char fileoutput, char last) {
	LLIST *ptr;
	ptr = c->head;

	while (ptr != NULL) {
		if (ptr->next == NULL) {
			fprintf(fr, "Vehicle %d\n", ptr->neighbor);
		}
		else {
			fprintf(fr, "Vehicle %d, ", ptr->neighbor);
		}
		ptr = ptr->next;
	}
}

//Searches for neighbor in neighbor list
int searchNeighbor(CAR *c, int key) {
	LLIST *ptr;
	ptr = c->head;
	while (ptr != NULL)
	{
		if (ptr->neighbor == key)
			return 1;
		ptr = ptr->next;
	}
	return 0;
}

//prints details of each vehicle
void printDetails(char **argv, char toscreen, char fileoutput) {
	int j;
	FILE *fr;

	if (fileoutput == 'y') {
		fr = fopen(argv[outfilearg], "a");
	}
	else {
		fr = fopen("result.txt", "a");
	}

	if (toscreen == 'y') {
		for (j = 0; j<i; j++) {

			printf("Vehicle %d at location %.2f, %.2f moving with velocity %.2f, its neighbors are: ",
				cars[j].pid, cars[j].xloc, cars[j].yloc, cars[j].speed);
			printNeighbor(&cars[j]);
			if (j + 1 == i) {
				puts("");
			}
			fprintf(fr, "Vehicle %d at location %.2f, %.2f moving with velocity %.2f, its neighbors are: ",
				cars[j].pid, cars[j].xloc, cars[j].yloc, cars[j].speed);
			if (j + 1 == i) {
				printNeighborToFile(argv, &cars[j], fr);
				fprintf(fr, "\n");
			}
			else
				printNeighborToFile(argv, &cars[j], fr);
		}
	}
	else {
		for (j = 0; j<i; j++) {

			fprintf(fr, "Vehicle %d at location %.2f, %.2f moving with velocity %.2f, its neighbors are: ",
				cars[j].pid, cars[j].xloc, cars[j].yloc, cars[j].speed);
			if (j + 1 == i) {
				printNeighborToFile(argv, &cars[j], fr);
				fprintf(fr, "\n");
			}
			else
				printNeighborToFile(argv, &cars[j], fr);
		}
	}

	fclose(fr);
}

//reads input from file
void readInput(int argc, char **argv, int fileindex) {
	int j, bsCount = 0, N = 0;
	FILE *fp;
	char bs, fileoutput, input[20];

	for (j = 0; j<argc; j++) {
		if (strncmp(argv[j], "-t", 3) == 0) {
			N = atoi(argv[j + 1]);

			if (N < 0) {
				puts("Error: Expecting valid argument following -t");
				exit(0);
			}
			else {

			}
		}
	}

	for (j = 0; j<argc; j++) {
		if (strncmp(argv[j], "-b", 3) == 0) {
			bs = 'b';
			bsCount++;
		}
		else if (strncmp(argv[j], "-s", 3) == 0) {
			bs = 's';
			bsCount++;
		}
	}
	if (bsCount == 2) {
		puts("Error: Expecting argument either -b OR -s");
		exit(0);
	}
	else {
		fp = fopen(argv[fileindex], "r");
		if (!fp) {
			printf("Could not open %s\n", argv[fileindex]);
			exit(0);
		}
		else {
			while (fscanf(fp, "%s", input) != EOF) {
				stringtokenizer(input);
			}
			fileoutput = writeOutput(argc, argv);
			if (bs == 's') {
				execute(argv, N, 'n', fileoutput);
			}
			else {
				execute(argv, N, 'y', fileoutput);
			}
		}
	}
}

//writes output to file
char writeOutput(int argc, char **argv) {
	int j;

	for (j = 0; j<argc; j++) {
		if (strncmp(argv[j], "-o", 3) == 0) {
			if (argv[j + 1] == NULL || strncmp(argv[j + 1], "-f", 3) == 0 || strncmp(argv[j + 1], "-o", 3) == 0 ||
				strncmp(argv[j + 1], "-b", 3) == 0 || strncmp(argv[j + 1], "-s", 3) == 0 ||
				strncmp(argv[j + 1], "-t", 3) == 0) {
				puts("Error: Expecting argument following -o");
				exit(0);
			}
			else {
				outfilearg = j + 1;
				return 'y';
			}
		}
		else if (j + 1 == argc)
			return 'n';
	}
}

//while loop that orchestrates the update of location and neighbors for each time interval
void execute(char **argv, int N, char toscreen, char fileoutput) {
	CAR c;

	while (!NULL) {
		updateNeighbors(&c);
		printDetails(argv, toscreen, fileoutput);
		updateLocation(N);
		sleep(N);
	}
}
