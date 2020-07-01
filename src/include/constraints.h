#ifndef CONSTRAINTS_H
#define CONSTRAINTS_H

#include "vector.h"
#include "manifold.h"

vector gs_distance_constraint (vector pos1, vector pos2, 
	double w1, double w2, double constraint); 

#endif
