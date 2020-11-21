#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

	FILE *positionData = fopen("./outfiles/position.csv", "w"); 
	FILE *velocityData = fopen("./outfiles/velocity.csv", "w"); 
	FILE *timeData = fopen("./outfiles/time.csv", "w");
	FILE *metaData = fopen("./outfiles/meta.txt", "w");

	fprintf(metaData, "%s\n%f\n%f\n", system_name(), 
		*timeStep, *totalRunTime);

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
	int *numConstraints, double **mass, double **constraint, 
	struct Vec3 **position, struct Vec3 **velocity)
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

	*position = calloc(*numParticles, sizeof(struct Vec3));
	*velocity = calloc(*numParticles, sizeof(struct Vec3)); 

	for (int i = 0; i < *numParticles; i++)
	{
		(*position)[i].x = 
			atof(fgets(buffer, 50, initFile));

		(*position)[i].y = 
			atof(fgets(buffer, 50, initFile));

		(*position)[i].z = 
			atof(fgets(buffer, 50, initFile));

		(*velocity)[i].x =
			atof(fgets(buffer, 50, initFile));

		(*velocity)[i].y =
			atof(fgets(buffer, 50, initFile));

		(*velocity)[i].z =
			atof(fgets(buffer, 50, initFile));
	}

	*constraint = calloc(*numConstraints, sizeof(double)); 

	if (*numConstraints != 0)
	{
		for (int i = 0; i < *numConstraints; i++)
		{
			(*constraint)[i] = atof(fgets(buffer, 50, initFile));
		}	
	}

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
	printf("System: %s\n\n", system_name());
	printf("number of particles:     %d\n", *numParticles); 
	printf("number of constraints:   %d\n", *numConstraints);  
	printf("initial conditions:      %s\n", initSpecifier);
}

void write_system_state (int t, double timeStep, int numParticles, 
	struct Vec3 position[], struct Vec3 velocity[])
{
	FILE *timeData = fopen("./outfiles/time.csv", "a"); 
	FILE *positionData = fopen("./outfiles/position.csv", "a"); 
	FILE *velocityData = fopen("./outfiles/velocity.csv", "a"); 

	fprintf(timeData, "%f\n", t * timeStep); 

	for (int i = 0; i < numParticles; i++)
	{
		fprintf(positionData, "%f, %f, %f\n", 
			position[i].x, position[i].y, position[i].z);

		fprintf(velocityData, "%f, %f, %f\n", 
			velocity[i].x, velocity[i].y, velocity[i].z); 
	}

	fclose(timeData); 
	fclose(positionData); 
	fclose(velocityData); 
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
