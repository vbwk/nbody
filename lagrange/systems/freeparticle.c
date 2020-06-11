#include "dynamics.h"
#include "fields.h"
#include "constraints.h"

void apply_fields (int numParticles, double mass[], 
	struct Vec3 position[], struct Vec3 velocity[], 
	struct Vec3 **forceAccumulator)
{
	uniform_gravity (numParticles, mass, forceAccumulator); 	
}

void apply_constraints (int numParticles, double mass[], 
	double position[], double velocity[], double **forceAccumulator)
{

}
