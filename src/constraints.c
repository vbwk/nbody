#include "constraints.h"

vector gs_distance_constraint (vector pos1, vector pos2, 
	double w1, double w2, double constraint)
{
	vector r = vector_subt(pos1, pos2);
	vector rHat = vector_unit(r); 
       	double rMag = vector_mag(r);

	vector correction = vector_mult(rHat, (rMag - constraint));

	return correction; 	
}
