#ifndef CONSTRAINTS_H
#define CONSTRAINTS_H

#include "vec3.h"

void distance_constraint (struct Vec3 position, 
	struct Vec3 otherPosition, double constraint, 
	struct Vec3 *newPosition);  

#endif
