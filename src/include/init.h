#ifndef INIT_H
#define INIT_H

#include <time.h>
#include "vec3.h"

void set_parameters (int argc, char *argv[], char **initSpecifier, 
	double *timeStep, double *totalRunTime); 

void check_optional_parameters (int argc, char *argv[], double **timeStep, 
	double **totalRunTime); 

void initialize_system (char *initSpecifier, int *numParticles, 
	int *numConstraints, double **mass, double **constraint, 
	struct Vec3 **position, struct Vec3 **velocity); 

void write_system_state (int t, double timeStep, int numParticles, 
	struct Vec3 position[], struct Vec3 velocity[]); 

double diffclock (clock_t clock1, clock_t clock2); 

char *usage (); 

#endif
