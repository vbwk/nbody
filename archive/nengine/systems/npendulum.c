#include <stdio.h>
#include <stdlib.h>
#include "system.h"

#if 0
void apply_field_forces (cfgspace system, vector *acceleration)
{
	vector *force = new_vector_array (system.N, system.J);

	uniform_gravity (system, force);

	for (int n = 0; n < system.N; n++)
	{
		acceleration[n] = vector_div (
			force[n], system.particle[n].mass); 
	}
}

void resolve_holonomic_constraints (int t, double timeStep, cfgspace system)
{
	for (int n = 0; n < system.N; n++)
	{
		if (n == 0)
		{
		        vector pos1 = system.particle[n].newPosition; 
			vector pos2 = new_vector(system.J);
			vector newEstimate = new_vector(system.J);

			distance_constraint (pos1, 
				pos2, &newEstimate); 

			// system.particle[n].newPosition = newEstimate; 
		}

		else
		{
			vector pos1 = system.particle[n].newPosition; 
			vector pos2 = system.particle[n - 1].newPosition; 
			vector newEstimate; 

			/* distance_constraint (system, pos1, 
				pos2, &newEstimate);*/ 

			// system.particle[n].newPosition = newEstimate; 	
		}
	}



}
#endif

int num_generalized_coordinates ()
{
	return 2; 
}

char *generalized_coordinate_type ()
{
	return "r, φ (2D polar)"; 
}

char *system_name () 
{
	return "npendulum"; 
}

