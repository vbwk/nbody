#ifndef DYNAMICS_H
#define DYNAMICS_H

#include "vec3.h"

void get_new_state (double t, double timeStep, int numParticles, 
	double mass[], double constraint[], struct Vec3 position[], 
	struct Vec3 velocity[], struct Vec3 **newPosition, 
	struct Vec3 **newVelocity);  

void apply_fields (int numParticles, double mass[], 
	struct Vec3 position[], struct Vec3 velocity[], 
	struct Vec3 **forceAccumulator); 

void project_constraints (int numParticles, double mass[], 
	double constraint[], struct Vec3 **position);  

void resolve_collisions (int numParticles, double mass[], 
	struct Vec3 **position, struct Vec3 **velocity); 

#endif
