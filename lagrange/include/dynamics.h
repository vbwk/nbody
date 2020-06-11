#ifndef DYNAMICS_H
#define DYNAMICS_H

void get_new_state (int t, double timeStep, int numParticles, 
	int numCoordinates, double mass[], double constraint[], 
	double state[], double **newVelocity); 

void apply_fields (int numParticles, int numCoordinates, double mass[], 
	double state[], double **force); 

/*
void project_constraints (int numParticles, double mass[], 
	double constraint[], struct Vec3 **position);  

void resolve_collisions (int numParticles, double mass[], 
	struct Vec3 **position, struct Vec3 **velocity); 
*/ 

#endif
