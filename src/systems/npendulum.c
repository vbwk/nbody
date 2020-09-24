#include "system.h"
#include "fields.h"
#include "constraints.h"

void apply_field_forces (config manifold, vector *acceleration)
{
	vector *force = new_vector_array (manifold.N, manifold.J);

	/* accumulate forces */ 

	uniform_gravity (manifold, force);

	/* compute acceleration */ 

	for (int n = 0; n < manifold.N; n++)
	{
		acceleration[n] = vector_div (
			force[n], manifold.particle[n].mass); 
	}
}

void project_constraints (config manifold)
{
	/* gauss-seidel distance constraints with particle 0 at origin */ 

	for (int n = 0; n < manifold.N; n++)
	{
		if (n == 0)
		{
			vector pos1 = manifold.particle[n].newPosition;
		       	vector pos2 = new_vector(manifold.J);
			double w1 = 1 / manifold.particle[n].mass; 
			double w2 = 0; 
			double constraint = manifold.constraint.holonomic[n]; 

			vector correction = gs_distance_constraint (
				pos1, pos2, w1, w2, constraint); 

			manifold.particle[n].newPosition = vector_add(
				manifold.particle[n].newPosition, correction); 
		}

		else
		{
			vector pos1 = manifold.particle[n].newPosition;
			vector pos2 = manifold.particle[n - 1].position; 
			double w1 = 1 / manifold.particle[n].mass; 
			double w2 = 1 / manifold.particle[n - 1].mass; 
			double constraint = manifold.constraint.holonomic[n]; 

			vector correction = gs_distance_constraint (
				pos1, pos2, w1, w2, constraint);

			manifold.particle[n].newPosition = vector_add(
				manifold.particle[n].newPosition, correction); 
		}
	}	
}

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
