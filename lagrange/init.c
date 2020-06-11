#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "init.h"

void set_parameters (int argc, char *argv[], char **initSpecifier, 
	double *timeStep, double *totalRunTime)
{
	*timeStep = 0.01; 
	*totalRunTime = 20;

	if (argc < 2)
	{
		set_parameters_manually (&initSpecifier, 
			&timeStep, &totalRunTime); 
	}

	else
	{
		*initSpecifier = argv[1];

		if (argc > 2)
		{
			check_optional_parameters (argc, argv, 
				&timeStep, &totalRunTime); 
		}
	}

	FILE *stateData = fopen("./outfiles/genstate.csv", "w"); 
	FILE *timeData = fopen("./outfiles/time.csv", "w");
	FILE *metaData = fopen("./outfiles/meta.txt", "w");

	fprintf(metaData, "%s\n%f\n%f\n", system_name(), 
		*timeStep, *totalRunTime);

	fclose(stateData); 
	fclose(timeData); 
	fclose(metaData); 
}

void set_parameters_manually (char ***initSpecifier, 
	double **timeStep, double **totalRunTime)
{
	printf(usage_message());

	printf("Options:\n" 
		"[1] Set parameters manually\n"
		"[0] Exit\n");

	int usageOption; 
	scanf("%d", &usageOption); 

	if (usageOption != 1) exit(0); 

        printf("\nInitial conditions:\n"
		"[Enter m to create new init file]\n"); 

	char initOption[30]; 
	scanf("%s", initOption);

	if (strcmp(initOption, "m") == 0) 
	{
		make_init_file(); 
	}

	else 
	{
		**initSpecifier = (char*) malloc(strlen(initOption) + 1);
		strcpy(**initSpecifier, initOption);
	}

	printf("\nTime step:\n"); 
	scanf("%lf", &**timeStep);

	printf("\nTotal run time:\n"); 
	scanf("%lf", &**totalRunTime); 	
}

void make_init_file () 
{
	printf("\nBollocks.\n\n"); 
	exit(0); 
}

void check_optional_parameters (int argc, char *argv[], 
	double **timeStep, double **totalRunTime)
{
	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-' && argv[i+1] != NULL)
		{
			int option = argv[i][1]; 
			switch (option)
			{
			
				case 'D': case 'd':
					**timeStep = atof(argv[i+1]); 
					break;

				case 'T': case 't':
					**totalRunTime = atof(argv[i+1]); 
					break;

				default:
					printf("Illegal option\n"); 
					exit(0);

			}
		}
	}
}	

void initialize_system (char *initSpecifier, int *numParticles, 
	int *numConstraints, int *numCoordinates, int *numStateVars, 
	double **mass, double **reducedMass, double **constraint, 
	double **state)
{
	char filePath[50]; 
	strcpy(filePath, "./systems/initial_conditions/");
        strcat(filePath, system_name());  
	strcat(filePath, "_"); 	
	strcat(filePath, initSpecifier); 
	strcat(filePath, ".txt");

	FILE *initFile; 
	initFile = fopen(filePath, "r"); 

	if (!initFile) 
	{
		perror("Init file error"); 
		exit(0);
	}	

	char systemName[50];  
	fgets(systemName, 50, initFile); 	

	char buffer[50]; 
	*numParticles = atoi(fgets(buffer, 50, initFile));
	*numConstraints = atoi(fgets(buffer, 50, initFile)); 	

	*mass = calloc(*numParticles, sizeof(double));

	for (int i = 0; i < *numParticles; i++)
	{
		(*mass)[i] = atof(fgets(buffer, 50, initFile)); 
	}

	double *cartesianState = calloc(*numParticles * 6, sizeof(double));

	for (int i = 0; i < *numParticles; i++) 
	{
		for (int j = 0; j < 6; j++) 
		{
			cartesianState[i * 6 + j] = 
				atof(fgets(buffer, 50, initFile));
		}
	}

	*constraint = calloc(*numConstraints, sizeof(double)); 

	for (int i = 0; i < *numConstraints; i++)
	{
		(*constraint)[i] = atof(fgets(buffer, 50, initFile));
	}

	if (strcmp(coordinates_type(), "Generic") != 0)
	{
	        double *jacobian = get_state_jacobian (*numParticles);
		*numCoordinates = num_generalized_coordinates ();
		*numStateVars = *numCoordinates * 2; 

		make_generalized_state (*numParticles, *numStateVars, 
			jacobian, cartesianState, state);

		free(jacobian); 
	}

	*reducedMass = get_reduced_mass (*mass, *numParticles, 
		*numCoordinates); 

	FILE *metaData = fopen("./outfiles/meta.txt", "a");

	fprintf(metaData, "%s\n%d\n%d\n", initSpecifier, 
		*numParticles, *numConstraints);

	for (int i = 0; i < *numParticles; i++)
	{
		fprintf(metaData, "%f\n", (*mass)[i]); 
	}

	for (int i = 0; i < *numConstraints; i++)
	{
		fprintf(metaData, "%f\n", (*constraint)[i]); 
	}	

	fclose(metaData); 

	perror("\nInitialization");

	printf("\nSystem: %s\n"
		"Number of particles: %d\n"
		"Number of constraints: %d\n"
		"Initial conditions: %s\n",
		system_name(), 
		*numParticles, 
		*numConstraints, 
		initSpecifier); 

	printf("\nSolver: %s\n"
		"Coordinates type: %s\n"
		"Number of coordinates: %d\n",
		solver_method(), 
		coordinates_type(),
		*numCoordinates);  
}

double diffclock (clock_t clock1, clock_t clock2)
{
	double diffticks = clock1 - clock2; 
	double diffms = (diffticks * 10) / CLOCKS_PER_SEC; 
	return diffms; 
}

char *usage_message ()
{
	return "\nUsage: ./a.out initfile [-D timestep] [-T totalruntime]\n\n"; 
}
