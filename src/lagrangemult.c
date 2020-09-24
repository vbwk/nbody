#include <stdio.h>
#include "dynamics.h"
#include "write.h"
#include "system.h"
#include "odes.h"

void run_simulation (params simulation, config manifold) 
{
	int numTimePoints = simulation.totalRunTime / simulation.timeStep;

	printf("\nSolver: %s\n"
		"Coordinates: %s\n"
		"\nRunning simulation...\n", 
		solver_method(), 
		coordinates_type()); 

	for (int t = 0; t < numTimePoints; t++)
	{
		/* write current system state to output */ 

		write_system_state (t, simulation, manifold); 

		/* apply field forces */

		vector *acceleration = new_vector_array (
			manifold.N, manifold.J); 

		apply_field_forces (manifold, acceleration);

		/* integrate system to new state */ 

		/* apply lagrange multiplier forces */ 

		apply_lagrange_multipliers (manifold, acceleration); 

		integrate_system_state (t, simulation, manifold, acceleration);

		/* resolve collisions */ 

		resolve_collisions (manifold); 

		/* update state for next time step */

		for (int n = 0; n < manifold.N; n++)
		{
			manifold.particle[n].position = 
				manifold.particle[n].newPosition; 

			manifold.particle[n].velocity = 
				manifold.particle[n].newVelocity;
		}	
	}

	printf("Done.\n\n"); 	
}

char *coordinates_type ()
{
	return "rectangular (x, y, z)"; 
}

char *solver_method ()
{
	return "Lagrange Multipliers"; 
}
