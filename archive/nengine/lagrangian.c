#include <stdio.h>
#include <stdlib.h>
#include "dynamics.h"
#include "system.h"
#include "write.h"
#include "odes.h"

void run_simulation (double timeStep, int totalRunTime, 
	int numParticles, int numConstraints, double mass[], 
	double constraint[], struct Vector initialState[])
{
	printf("\nSolver: %s\n", solver_method()); 

	int numCoordinates = num_generalized_coordinates ();

	struct Vector *state = make_generalized_state (initialState); 

	for (int i = 0; i < state->numObj; i++)
		for (int j = 0; j < state->numDoF; j++)
			printf("%f\n", state[i].component[j]); 	

#if 0
	transform_to_generalized_coordinates (
		numParticles, initialState, 
		&numCoordinates, &numStateVariables, 
		&state); 

	int numTimePoints = totalRunTime / timeStep;
	printf("\nRunning simulation...\n"); 

	for (int t = 0; t < 1; t++)
	{
		/* write current system state to output */ 

		write_system_state (numStateVariables, state); 

		/* accumulate forces */ 

		double *force; 

		apply_field_forces (numParticles, numCoordinates, 
			mass, state, &force);

#if 0
		/* integrate system to new state */ 

		double *newState = calloc(numCoordinates, sizeof(double));

		integrate_system_state (t, timeStep, numCoordinates,
			state, force, &newState); 	

#endif
	}

	printf("Done.\n"); 
#endif

}

char *solver_method ()
{
	return "Lagrangian"; 
}
