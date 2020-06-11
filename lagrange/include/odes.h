#ifndef ODES_H
#define ODES_H

#include "vector.h"

void integrate_system_state (int t, double timeStep, 
	int numCoordinates, double state[], 
	double acceleration[], double **newState); 

char *integration_method (); 

#endif
