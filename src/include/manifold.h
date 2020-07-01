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

typedef struct config {
	int N;			/* number of particles */  
	int J;			/* number of coordinates */  
	int K_H;		/* number of holonomic constraints */ 
       	int K_S; 		/* number of semiholonomic constraints */
	int K_I; 		/* number of inequality constraints */ 	
	state *particle;
	cnstr constraint; 
} config; 

typedef struct params {
	double timeStep; 
	double totalRunTime; 
	int numTimePoints; 
	char *initSpecifier;
       	char *systemName; 	
} params; 

state *new_particle_state (int N, int J);

cnstr initialize_constraints (config manifold); 

#endif
