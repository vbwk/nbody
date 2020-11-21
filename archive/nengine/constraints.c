#include <stdio.h>
#include <math.h>
#include "constraints.h"

void distance_constraint (vector pos1, 
	vector pos2, vector *newEstimate) 
{
	vector r = vector_subt(pos1, pos2);
        double rMag = vector_mag(r);
	vector rHat = vector_div(r, rMag);

	vector correction = vector_mult(rHat, (rMag - 1)); 

	*newEstimate = vector_add(pos1, correction); 	
	
#if 0
	struct Vec3 r = vec3_subt(position, otherPosition); 
	double rMag = vec3_mag(r);
	struct Vec3 rHat = vec3_mult(r, (1 / rMag));

	struct Vec3 correction = vec3_mult(
		rHat, (rMag - constraint)); 

	*newPosition = vec3_add(position, correction);
#endif

}
