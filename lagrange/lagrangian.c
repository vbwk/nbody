#include <stdlib.h>
#include "dynamics.h"
#include "init.h"
#include "odes.h"
#include <stdio.h>

void get_new_state (int t, double timeStep, int numParticles, 
	int numCoordinates, double reducedMass[], double constraint[], 
	double state[], double **newState)
{
	/* accumulate forces */

	double *force = calloc(numCoordinates, sizeof(double));

	apply_fields (numParticles, numCoordinates, reducedMass, 
		state, &force);

	/* integrate system to new state */

	double *acceleration = vec_mult (force, reducedMass, 
		numCoordinates);

	*newState = calloc(numCoordinates, sizeof(double)); 

	integrate_system_state (t, timeStep, numCoordinates, 
		state, acceleration, newState);

}	

char *coordinates_type ()
{
	return "Generalized coordinates"; 
}	

char *solver_method () 
{
	return "Lagrangian"; 
}
