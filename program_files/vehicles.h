#ifndef VEHICLES_H_
#define VEHICLES_H_
#include <stdio.h>
#include <stdlib.h>

//structure of linked list for vehicle neighbors'
typedef struct neighbor_list{
	int neighbor;
	struct neighbor_list *next;
}LLIST;

//structure of vehicles
typedef struct vehicle{
	int pid;
	float xloc;
	float yloc;
	float speed;
	float theta;
	LLIST *head;
}CAR;

void addVehicle(float[]); //adds vehicle
void addNeighbor(CAR*, CAR*); //adds neighbor
void delNeighbor(CAR*, int); //deletes neighbor
void updateLocation(int); //updates x and y coordinates
void updateNeighbors();//updates neighbors of all vehicles
void printNeighbor(CAR *c);
void printNeighborToFile(char**, CAR*, FILE*);//char, char);
int searchNeighbor(CAR *c, int key);//searches for a neighbor in a list
void printDetails(char**, char, char);//prints vehicle details
void readInput(int, char**, int);//reads input from file
char writeOutput(int, char**);//writes output to file
void execute(char**, int, char, char);//holds while loop that calls update and print functions

#endif /* VEHICLES_H_ */
