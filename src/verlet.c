#include "odes.h"

void integrate_system_state (int t, params simulation,
	config manifold, vector *acceleration)
{
	if (t == 0)
	{
		for (int n = 0; n < manifold.N; n++)
		{
			manifold.particle[n].newVelocity = 
				vector_add(
					manifold.particle[n].velocity, 
					vector_mult(
						acceleration[n], 
						(simulation.timeStep * 0.5)));

			manifold.particle[n].newPosition = 
				vector_add(
					manifold.particle[n].position, 
					vector_mult(
						manifold.particle[n].newVelocity, 
						(simulation.timeStep * 0.5))); 

		}
	}

	else 
	{
		for (int n = 0; n < manifold.N; n++)
		{
			manifold.particle[n].newVelocity = 
				vector_add(
					manifold.particle[n].velocity, 
					vector_mult(
						acceleration[n], 
						simulation.timeStep));

			manifold.particle[n].newPosition = 
				vector_add(
					manifold.particle[n].position, 
					vector_mult(
						manifold.particle[n].newVelocity, 
						simulation.timeStep)); 
		}	
	}

}

char *integration_method ()
{
	return "Verlet"; 
}
