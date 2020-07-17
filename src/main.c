#include <stdio.h>
#include <stdlib.h>
#include "simulation.h"
#include "init.h"
#include "write.h"
#include "dynamics.h"

void usage_message ()
{
	printf("\nUsage:\n"
		"./a.out <init> "
		"-dt <time step> "
		"-tt <total run time>\n\n");
	exit(0); 	
}

int main (int argc, char *argv[])
{
	if (argc < 2) usage_message (); 

	params simulation; 

	simulation.initSpecifier = argv[1];
	simulation.timeStep = 0.01; 
	simulation.totalRunTime = 100; 

	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-' && argv[i+1] != NULL)
		{
			int option = argv[i][1]; 
			switch(option)
			{
				case 'd':
				simulation.timeStep = 
					atof(argv[i+1]); 
				break; 

				case 't':
				simulation.totalRunTime = 
					atof(argv[i+1]); 
				break; 

				default:
				printf("Illegal parameter\n"); 
				exit(0); 
			}
		}
	}

	/* initialize system manifold */ 

	config manifold = initialize_system_manifold (simulation); 

	/* initialize file output */ 

	initialize_output_files (simulation, manifold);

	/* run simulation */ 

	run_simulation (simulation, manifold); 	
}

