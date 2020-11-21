#ifndef DYNAMICS_H
#define DYNAMICS_H

#include "vector.h"

typedef struct Simulation {
	char *systemName; 
	char *initSpecifier; 
	double timeStep; 
	double totalRunTime; 
	int numTimePoints;
} Simulation; 

typedef struct ConfigState {
	double mass; 
	vector position; 
	vector newPosition; 
	vector velocity; 
	vector newVelocity; 
	vector momentum; 
	vector newMomentum; 
} ConfigState; 

typedef struct Constraint {
	double *holonomic; 
	double *semiholonomic; 
	double *inequality; 
} Constraint; 

typedef struct Manifold {
	int N; 
	int J; 
	int K_H; 
	int K_S; 
	int K_I; 
	ConfigState *particle; 
	Constraint constraint; 
} Manifold; 

#endif
