#include <stdlib.h>
#include "fields.h"

#define G 9.81

void uniform_gravity (config manifold, vector *force)
{
	for (int n = 0; n < manifold.N; n++)
	{
		force[n].coordinate[1] += 
			manifold.particle[n].mass * -G; 
	}
}	

