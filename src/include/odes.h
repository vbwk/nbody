#ifndef ODES_H
#define ODES_H

#include "vec3.h"

void integrate_system_state (double t, double timeStep, 
	int numParticles, double mass[], struct Vec3 position[], 
	struct Vec3 velocity[], struct Vec3 acceleration[], 
	struct Vec3 **newPosition, struct Vec3 **newVelocity); 

char *integration_method (); 

#endif
