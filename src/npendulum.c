#include "dynamics.h"
#include "fields.h"
#include "constraints.h"

void apply_fields (int numParticles, double mass[], 
	struct Vec3 position[], struct Vec3 velocity[], 
	struct Vec3 **forceAccumulator)
{
	uniform_gravity (numParticles, mass, forceAccumulator); 	
}

void project_constraints (int numParticles, double mass[], 
	double constraint[], struct Vec3 **position) 
	
{
	for (int i = 0; i < numParticles; i++)
	{
		if (i == 0)
		{
			struct Vec3 initialGuess = (*position)[i];
			struct Vec3 otherPosition = { 0, 0, 0 }; 
		        struct Vec3 newGuess; 	
			
			distance_constraint (initialGuess, otherPosition, 
				constraint[i], &newGuess);

			(*position)[i] = newGuess; 	
		}

		else
		{
			struct Vec3 initialGuess = (*position)[i];
			struct Vec3 otherPosition = (*position)[i-1]; 
		        struct Vec3 newGuess; 	
			
			distance_constraint (initialGuess, otherPosition, 
				constraint[i], &newGuess);

			(*position)[i] = newGuess; 	
		}
	}
}
