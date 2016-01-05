//***************************************
// Author:      Kevin Cabrera
// Description: Begins execution of the
//              program.
//***************************************
#include <stdio.h>
#include "vehicles.h"

int main(int argc, char **argv) {
	setbuf(stdout, NULL);
	int i, j;

	if (argc == 1) {
		puts("Error: Expecting argument -t");
		exit(0);
	}

	if (argc > 1)
		for (i = 1; i<argc; i++) {
			if (strncmp(argv[i], "-t", 3) != 0 && strncmp(argv[i], "-f", 3) != 0 &&
				strncmp(argv[i], "-o", 3) != 0 && strncmp(argv[i], "-b", 3) != 0 &&
				strncmp(argv[i], "-s", 3) != 0) {
				if (strncmp(argv[i], "-", 1) == 0)
					if (strncmp(argv[i - 1], "-t", 1) == 0);
					else {
						puts("Incorrect argument(s): Arguments allowed are -t seconds, -f filename, -o filename and -b/-s");
						exit(0);
					}
			}
		}

	for (i = 0; i<argc; i++) {
		if (strncmp(argv[i], "-t", 3) == 0) {
			if (!argv[i + 1] || strncmp(argv[i + 1], "-f", 3) == 0 || strncmp(argv[i + 1], "-o", 3) == 0 ||
				strncmp(argv[i + 1], "-b", 3) == 0 || strncmp(argv[i + 1], "-s", 3) == 0 ||
				strncmp(argv[i + 1], "-t", 3) == 0) {
				puts("Error: Expecting argument following -t");
				exit(0);
			}
			else {
				for (j = 0; j<argc; j++) {
					if (strncmp(argv[j], "-f", 3) == 0) {
						if (!argv[j + 1] || strncmp(argv[j + 1], "-o", 3) == 0 || strncmp(argv[j + 1], "-b", 3) == 0 ||
							strncmp(argv[j + 1], "-s", 3) == 0 || strncmp(argv[j + 1], "-f", 3) == 0 ||
							strncmp(argv[j + 1], "-t", 3) == 0) {
							puts("Error: Expecting argument following -f");
							break;
						}
						else {
							readInput(argc, argv, j + 1);
							break;
						}
					}
					else if (!argv[j + 1]) {
						puts("Error: Expecting argument -f");
						exit(0);
						break;
					}
				}
				break;
			}
		}
		else if (!argv[i + 1]) {
			puts("Error: Expecting argument -t");
			exit(0);
		}
	}
}
