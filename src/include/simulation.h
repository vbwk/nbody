#ifndef SIMULATION_H
#define SIMULATION_H

#include "vector.h"
#include "manifold.h"

typedef struct params {
	char *initSpecifier; 
	double timeStep; 
	double totalRunTime; 
	int numTimePoints;
       	char *systemName; 	
} params; 

#endif
