#include <stdio.h>
#include "dynamics.h"
#include "system.h"
#include "write.h"
#include "odes.h"

void run_simulation (double timeStep, double totalRunTime, cfgspace system) 
{
	int numTimePoints = totalRunTime / timeStep;

	printf("\nSolver: %s\n"
		"Coordinates: %s\n"
		"\nRunning simulation...\n", 
		solver_method(), 
		coordinates_type()); 

	for (int t = 0; t < 2; t++)
	{
		/* write current system state to output */ 

		write_system_state (t, timeStep, system); 

		/* apply field forces */

		vector *acceleration = new_vector_array (
			system.N, system.J); 

		apply_field_forces (system, acceleration);

		/* integrate system to new state */ 

		integrate_system_state (t, timeStep, system, acceleration);

		/* project constraints */

#if 0
		int numIterations = 10; 

		for (int i = 0; i < numIterations; i++)
		{
			resolve_holonomic_constraints (t, timeStep, system);
		}	

		/* update velocities */ 

		for (int n = 0; n < system.N; n++)
		{
			system.particle[n].newVelocity = 
				vector_div(
					vector_subt(
						system.particle[n].position, 
						system.particle[n].newPosition),
					timeStep); 
		}
#endif

		/* update state for next time step */

		for (int n = 0; n < system.N; n++)
		{
			system.particle[n].position = 
				system.particle[n].newPosition; 

			system.particle[n].velocity = 
				system.particle[n].newVelocity;
		}	

	}

	printf("Done.\n"); 	
}

char *coordinates_type ()
{
	return "x, y, z (rectangular)"; 
}

char *solver_method ()
{
	return "Gauss Seidel"; 
}
