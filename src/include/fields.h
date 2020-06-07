#ifndef FIELDS_H
#define FIELDS_H

#include "vec3.h"

void uniform_gravity (int numParticles, double mass[], 
	struct Vec3 **forceAccumulator);

void newtonian_gravity (int numParticles, double mass[], 
	struct Vec3 position[], struct Vec3 **forceAccumulator);

#endif
