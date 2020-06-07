#include "constraints.h"

void distance_constraint (struct Vec3 position, 
	struct Vec3 otherPosition, double constraint, 
	struct Vec3 *newPosition)
{
	struct Vec3 r = vec3_subt(position, otherPosition); 
	double rMag = vec3_mag(r);
	struct Vec3 rHat = vec3_mult(r, (1 / rMag));

	struct Vec3 correction = vec3_mult(
		rHat, (rMag - constraint)); 

	*newPosition = vec3_add(position, correction); 
}	
