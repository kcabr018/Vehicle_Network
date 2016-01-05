//***********************************************
// Author:      Kevin Cabrera
// Description: Parses the input of the program
//              and stores the data in the 
//              appropriate variables to be used 
//              by the vehicle class
//***********************************************
#include "tokenizer.h"
#include "vehicles.h"
#include <stdlib.h>

// parses values of input and separates them into tokens which then go to addVehicle
// to be stored as xloc, yloc, speed, and angle (theta)
void stringtokenizer(char input[]) {
	int i = 0;
	float temp;
	char* strArray[5];
	float inputs[5];
	char *token = strtok(input, ",");

	while(token != NULL)
	{
		strArray[i] = strdup(token);
		token = strtok(NULL, ",");
		i++;
	}

	for (i=0; i<4; i++) {
		temp = strtod(strArray[i], NULL);
		inputs[i] = temp;
	}

	addVehicle(inputs);
}
