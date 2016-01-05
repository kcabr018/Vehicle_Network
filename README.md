# Vehicle_Network
This program simulates a network of vehicles. At execution, the program reads vehicle data from a file and populates a list of vehicles, their positions, their speed, and their angle of travel. At a user-defined interval, data regarding each vehicle: its current position, speed, and list of vehicles within a range of 250m, will be displayed. Input data is in the following form:
2.7,10.1,5.0,45
6.7,13.7,9.3,67
100,100,4.5,12
Each row of the above input is a vehicle. Four different values are inputted, all separated by commas. The first and second values are the x and y position of the vehicle. The third value is the speed and fourth value the degree of travel (0 to 360). The vehicles in the vehicle list made by the program are numbered based on their order in the input data.

A file is to be made for the input data. The command to run the program takes the following form:
./prog -t 5 -f input.txt
prog: name of the executable created by my makefile
-t 5: the interval at which the vehicle network data is to be displayed. This example gives a 5 second delay
-f input.txt: means that input.txt is the file containing the input data of the program. 
For the command, -t and -f must be included.

