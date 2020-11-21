#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "init.h"
#include "system.h"

void set_parameters (int argc, char *argv[], par *simulation)
{
	
#if 0
	*initSpecifier = argv[1]; 
	*timeStep = 0.01; 
	*totalRunTime = 20;

	FILE *positionData = fopen("./outfiles/position.csv", "w"); 
	FILE *velocityData = fopen("./outfiles/velocity.csv", "w"); 
	FILE *timeData = fopen("./outfiles/time.csv", "w");
	FILE *metaData = fopen("./outfiles/meta.txt", "w");

	fprintf(metaData, "%s\n%f\n%f\n", system_name(), 
		*timeStep, *totalRunTime);

	fclose(metaData); 
#endif

}

/*
cfgspace initialize_system (char *initSpecifier) 
{
	char filePath[50];
	snprintf(filePath, sizeof(filePath), 
		"./systems/initial_conditions/%s_%s.txt",
		system_name(), initSpecifier); 

	FILE *initFile = fopen(filePath, "r"); 

	if (!initFile)
	{
		perror("Init file error"); 
		exit(0);
	}

	char buffer[50];

	cfgspace system;  

	system.N = atoi(fgets(buffer, 50, initFile)); 
	system.J = atoi(fgets(buffer, 50, initFile)); 
	system.K = atoi(fgets(buffer, 50, initFile)); 

	system.particle = new_particle_array (system.N, system.J); 

	for (int n = 0; n < system.N; n++)
	{
		skip_line(initFile); 

		system.particle[n].mass = atof(fgets(buffer, 50, initFile)); 

		skip_line(initFile); 

		for (int j = 0; j < system.J; j++)
		{
			system.particle[n].position.coordinate[j] = 
				atof(fgets(buffer, 50, initFile)); 
		}

		for (int j = 0; j < system.J; j++)
		{
			system.particle[n].velocity.coordinate[j] = 
				atof(fgets(buffer, 50, initFile)); 
		}
	}

	fclose(initFile); 	

	FILE *metaData = fopen("./outfiles/meta.txt", "a");

	fprintf(metaData, "%s\n%d\n%d\n", initSpecifier, 
		system.N, system.K);

	for (int n = 0; n < system.N; n++)
	{
		fprintf(metaData, "%f\n", system.particle[n].mass); 
	}

	fclose(metaData); 	

	perror("\nInitialization"); 

	printf("\nSystem: %s\n"
		"Number of particles: %d\n"
		"Number of constraints: %d\n"
		"Initial conditions: %s\n",
		system_name(), 
		system.N, 
		system.K,
		initSpecifier);

	return system; 
}
*/ 

void skip_line (FILE *initFile)
{
	char buffer[50]; 
	fgets(buffer, 50, initFile); 
}

