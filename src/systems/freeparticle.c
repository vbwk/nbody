#include "system.h"
#include "fields.h"
#include "constraints.h"

void apply_field_forces (config manifold, vector *acceleration)
{
	vector *force = new_vector_array (manifold.N, manifold.J);

	/* accumulate forces */


	
	/* compute acceleration */ 	

	for (int n = 0; n < manifold.N; n++)
	{
		acceleration[n] = vector_div (
			force[n], manifold.particle[n].mass); 
	}
}

void project_constraints (config manifold)
{
	/* configure constraints here */

}

char *system_name () 
{
	return "freeparticle"; 
}
