#include <stdlib.h>
#include "dynamics.h"
#include "system.h"
#include "odes.h"

void get_new_state (double t, double timeStep, int numParticles, 
	double mass[], double constraint[], struct Vec3 position[], 
	struct Vec3 velocity[], struct Vec3 **newPosition, 
	struct Vec3 **newVelocity) 
{
	/* accumulate forces */ 

	struct Vec3 *forceAccumulator = calloc(numParticles, 
			sizeof(struct Vec3)); 

	apply_fields (numParticles, mass, position, velocity, 
		&forceAccumulator); 

	apply_constraints (numParticles, mass, position, velocity, 
		&forceAccumulator); 

	/* integrate system to new state */

	struct Vec3 *acceleration = forceAccumulator;  

	*newPosition = calloc(numParticles, sizeof(struct Vec3)); 
        *newVelocity = calloc(numParticles, sizeof(struct Vec3));

	integrate_system_state (t, timeStep, numParticles, mass, 
		position, velocity, acceleration, newPosition, 
		newVelocity); 

	free(forceAccumulator);
}
