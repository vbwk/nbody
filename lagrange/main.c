#include <stdio.h>
#include "vector.h"
#include "dynamics.h"
#include "init.h"

int main (int argc, char *argv[])
{
	/* set simulation parameters */ 

	char *initSpecifier;
	double timeStep, totalRunTime; 

	set_parameters (argc, argv, &initSpecifier, 
		&timeStep, &totalRunTime); 

	/* initialize system */ 

	int numParticles, numConstraints;
	int numCoordinates, numStateVars; 
	double *mass, *reducedMass, *constraint, *state; 

	initialize_system (initSpecifier, &numParticles, 
		&numConstraints, &numCoordinates, &numStateVars, 
		&mass, &reducedMass, &constraint, &state);

	/* run simulation */ 	

	int numTimePoints = totalRunTime / timeStep;
        printf("\nRunning simulation...\n"); 

        clock_t startTime = clock(); 

	for (int t = 0; t < 10; t++)
	{
		/* write current state to output */

		write_system_state (t, timeStep, 
			numStateVars, state);

		/* get new state */

		double *newState; 

		get_new_state (t, timeStep, numParticles, 
			numCoordinates, reducedMass, constraint,
		        state, &newState); 	

#if 0
		/* resolve collisions */

		resolve_collisions (numParticles, mass, 
			&newPosition, &newVelocity); 	
#endif

		/* move particles to new state */

		for (int i = 0; i < numCoordinates; i++)
		{
			state[i] = newState[i]; 
		}

	}

	clock_t endTime = clock();

	printf("Done. Elapsed Time: %f s \n", 
		diffclock(endTime, startTime) / 10);

	printf("\nEnd of program.\n\n");
}	
