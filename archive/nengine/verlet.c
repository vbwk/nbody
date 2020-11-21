#include <stdio.h>
#include <stdlib.h>
#include "odes.h"

void integrate_system_state (int t, double timeStep,
	cfgspace system, vector *acceleration)
{
	if (t == 0)
	{
		for (int n = 0; n < system.N; n++)
		{
			system.particle[n].newVelocity = 
				vector_add(
					system.particle[n].velocity, 
					vector_mult(
						acceleration[n], 
						timeStep * 0.5));

			system.particle[n].newPosition = 
				vector_add(
					system.particle[n].position, 
					vector_mult(
						system.particle[n].newVelocity, 
						timeStep * 0.5)); 
		}	
	}

	else 
	{
		for (int n = 0; n < system.N; n++)
		{
			system.particle[n].newVelocity = 
				vector_add(
					system.particle[n].velocity, 
					vector_mult(
						acceleration[n], 
						timeStep));

			system.particle[n].newPosition = 
				vector_add(
					system.particle[n].position, 
					vector_mult(
						system.particle[n].newVelocity, 
						timeStep)); 
		}	
	}

}

char *integration_method ()
{
	return "Verlet"; 
}
