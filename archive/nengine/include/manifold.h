#ifndef MANIFOLD_H
#define MANIFOLD_H

#include "vector.h"

typedef struct state {
	double mass; 
	vector position;
	vector newPosition; 	
	vector velocity;
        vector newVelocity; 	
	vector momentum;
	vector newMomentum; 	
} state;

typedef struct cnstr {
	double *holonomic; 
	double *semiholonomic; 
	double *inequality; 
} cnstr; 

typedef struct dynamic {
	int N;			/* number of particles */  
	int J;			/* number of coordinates */  
	int K_H;		/* number of holonomic constraints */ 
       	int K_S; 		/* number of semiholonomic constraints */
	int K_I; 		/* number of inequality constraints */ 	
	state *particle;
	cnstr constraint;  
} dynamic; 

state *new_particle_array (int N, int J);

cnstr new_constraint_array (int K_H, int K_S, int K_I); 

#endif
