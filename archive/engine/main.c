#include <stdio.h>
#include "vec3.h"
#include "init.h"
#include "dynamics.h"

int main (int argc, char *argv[])
{
	/* set simulation parameters */ 

	char *initSpecifier;
	double timeStep, totalRunTime; 

	set_parameters (argc, argv, &initSpecifier, 
		&timeStep, &totalRunTime); 

	/* initialize system */ 

	int numParticles, numConstraints; 
	double *mass, *constraint;  
	struct Vec3 *position, *velocity; 

	initialize_system (initSpecifier, &numParticles, &numConstraints,
		&mass, &constraint, &position, &velocity);

	/* run simulation */ 	

	int numTimePoints = totalRunTime / timeStep;
        printf("\nRunning simulation...\n"); 

        clock_t startTime = clock(); 

	for (int t = 0; t < numTimePoints; t++)
	{
		/* write current state to output files */

		write_system_state (t, timeStep, numParticles, 
			position, velocity); 

		/* get new state */

		struct Vec3 *newPosition, *newVelocity; 

		get_new_state (t, timeStep, numParticles, 
			mass, constraint, position, velocity, 
			&newPosition, &newVelocity);

#if 0
		/* resolve collisions */

		resolve_collisions (numParticles, mass, 
			&newPosition, &newVelocity); 	
#endif

		/* move particles to new state */

		position = newPosition; 
		velocity = newVelocity;
	}

	clock_t endTime = clock();

	printf("Done. Elapsed Time: %f s \n", 
		diffclock(endTime, startTime) / 10);

	printf("\nEnd of program.\n\n");
}	
