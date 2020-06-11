#include <stdlib.h>
#include "dynamics.h"
#include "odes.h"

void get_new_state (double t, double timeStep, int numParticles, 
	double mass[], double constraint[], struct Vec3 position[], 
	struct Vec3 velocity[], struct Vec3 **newPosition, 
	struct Vec3 **newVelocity)
{
	/* apply field forces */ 

	struct Vec3 *forceAccumulator = calloc(numParticles, 
			sizeof(struct Vec3)); 

	apply_fields (numParticles, mass, position, velocity, 
		&forceAccumulator); 

	/* integrate system to new state */

	struct Vec3 *acceleration = forceAccumulator;  

	*newPosition = calloc(numParticles, sizeof(struct Vec3)); 
        *newVelocity = calloc(numParticles, sizeof(struct Vec3));

	integrate_system_state (t, timeStep, numParticles, mass, 
		position, velocity, acceleration, newPosition, 
		newVelocity); 

	free(forceAccumulator);

	/* project constraints */

	int numIterations = 10; 	

	for (int i = 0; i < numIterations; i++) 
	{
		project_constraints (numParticles, mass, constraint, 
			newPosition);
	}

	/* update velocities */ 

	for (int i = 0; i < numParticles; i++)
	{
		(*newVelocity)[i] = vec3_mult(
			vec3_subt(position[i], (*newPosition)[i]), 
			(1 / timeStep)); 
	}
}	
