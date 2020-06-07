#include <stdlib.h>
#include "odes.h"

void integrate_system_state (double t, double timeStep, 
	int numParticles, double mass[], struct Vec3 position[], 
	struct Vec3 velocity[], struct Vec3 acceleration[], 
	struct Vec3 **newPosition, struct Vec3 **newVelocity)
{
	if (t = 0)
	{
		for (int i = 0; i < numParticles; i++)
		{
			(*newVelocity)[i] = 
				vec3_add(velocity[i], vec3_mult(
				vec3_mult(acceleration[i], timeStep), 
				0.5));  

			(*newPosition)[i] = 
				vec3_add(position[i], vec3_mult(
				vec3_mult((*newVelocity)[i], timeStep), 
				0.5)); 
		}
	}

	else 
	{
		for (int i = 0; i < numParticles; i++)
		{
			(*newVelocity)[i] = 
				vec3_add(velocity[i], vec3_mult( 
				acceleration[i], timeStep)); 

			(*newPosition)[i] = 
				vec3_add(position[i], vec3_mult(
				(*newVelocity)[i], timeStep)); 
		}
	}
}

char *integration_method ()
{
	return "Verlet"; 
}
