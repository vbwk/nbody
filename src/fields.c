#include "fields.h"

void uniform_gravity (int numParticles, double mass[], 
	struct Vec3 **forceAccumulator)
{
	double G = 9.81;

	for (int i = 0; i < numParticles; i++)
	{
		(*forceAccumulator)[i].z += 
			mass[i] * -G;
	}
}

void newtonian_gravity (int numParticles, double mass[], 
	struct Vec3 position[], struct Vec3 **forceAccumulator)
{

}
