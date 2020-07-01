#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "init.h"

config initialize_system_manifold (params simulation)
{
	simulation.systemName = system_name(); 

	char filepath[50];
	snprintf(filepath, 
		sizeof(filepath), 
		"./systems/initial_conditions/%s_%s.txt",
		simulation.systemName, 
		simulation.initSpecifier); 

	FILE *initFile = fopen(filepath, "r"); 

	if (!initFile)
	{
		perror("init file error"); 
		exit(0);
	}

	char buffer[50];

	config manifold;

	manifold.N = atoi(fgets(buffer, 50, initFile));
	manifold.J = atoi(fgets(buffer, 50, initFile)); 	
	manifold.K_H = atoi(fgets(buffer, 50, initFile)); 
	manifold.K_S = atoi(fgets(buffer, 50, initFile)); 
	manifold.K_I = atoi(fgets(buffer, 50, initFile));

	manifold.particle = new_particle_state (
		manifold.N, manifold.J); 

	for (int n = 0; n < manifold.N; n++)
	{
		skip_line(initFile); 

		manifold.particle[n].mass = 
			atof(fgets(buffer, 50, initFile)); 

		skip_line(initFile); 

		for (int j = 0; j < manifold.J; j++)
		{
			manifold.particle[n].position.coordinate[j] = 
				atof(fgets(buffer, 50, initFile)); 
		}

		for (int j = 0; j < manifold.J; j++)
		{
			manifold.particle[n].velocity.coordinate[j] = 
				atof(fgets(buffer, 50, initFile)); 
		}
	}

	skip_line(initFile); 

	manifold.constraint = initialize_constraints (manifold); 

	for (int k = 0; k < manifold.K_H; k++)
	{
		manifold.constraint.holonomic[k] = 
			atof(fgets(buffer, 50, initFile)); 
	}

	skip_line(initFile); 

	for (int k = 0; k < manifold.K_S; k++)
	{
		manifold.constraint.semiholonomic[k] = 
			atof(fgets(buffer, 50, initFile)); 
	}

	skip_line(initFile); 

	for (int k = 0; k < manifold.K_I; k++)
	{
		manifold.constraint.inequality[k] = 
			atof(fgets(buffer, 50, initFile)); 
	}

	fclose(initFile);

	perror("\nInitialization"); 
	print_init_message (simulation, manifold); 	

	return manifold; 
}

void skip_line (FILE *initFile)
{
	char buffer[50]; 
	fgets(buffer, 50, initFile); 
}

void print_init_message (params simulation, config manifold)
{
	printf("\nSystem: %s\n"
		"Initial conditions: %s\n"
		"Number of particles: %d\n",
		simulation.systemName, 
		simulation.initSpecifier, 
		manifold.N); 
}

