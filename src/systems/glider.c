#include <math.h>
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
	/* configure newton-raphson constraints here */

}

void apply_lagrange_multipliers (config manifold, vector *acceleration)
{
	vector *constraintAcc = new_vector_array (manifold.N, manifold.J);

	double G = 9.81; 
	double height = 40; 
	double base = 100; 
	double theta = atan(height / base); 

	constraintAcc[0].coordinate[0] = -9.81 * cos(theta) * sin(theta); 
       	constraintAcc[0].coordinate[1] = -9.81 * cos(theta) * cos(theta); 

	for (int n =  0; n < manifold.N; n++)
	{
		acceleration[n] = vector_add (
			acceleration[n], constraintAcc[0]); 
	}	
}

void resolve_collisions (config manifold)
{
	double wallMass = 10000;
	double restitution = 0.6; 

	for (int i = 0; i < manifold.N; i++)
	{
		if (manifold.particle[i].position.coordinate[0] < 0)
		{
			vector newPosition = new_vector (manifold.J); 
			vector newVelocity = new_vector (manifold.J); 

			double weight = (manifold.particle[i].mass - wallMass) / 
				(manifold.particle[i].mass + wallMass); 

			newVelocity = vector_mult(manifold.particle[i].newVelocity, weight); 
			newVelocity = vector_mult(newVelocity, restitution); 
			newPosition = vector_add(manifold.particle[i].newPosition, 
					vector_mult(newVelocity, 0.01)); 

			manifold.particle[i].newPosition = newPosition; 
			manifold.particle[i].newVelocity = newVelocity;
		}
	}
}

char *system_name () 
{
	return "glider"; 
}
