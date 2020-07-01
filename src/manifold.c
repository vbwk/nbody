#include <stdlib.h>
#include "manifold.h"

#include <stdio.h>

state *new_particle_state (int N, int J)
{
	state *particle = malloc(N * sizeof(state)); 

	for (int n = 0; n < N; n++)
	{
		particle[n].position = new_vector(J); 
		particle[n].newPosition = new_vector(J); 
		particle[n].velocity = new_vector(J); 
		particle[n].newVelocity = new_vector(J); 
		particle[n].momentum = new_vector(J); 
		particle[n].newMomentum = new_vector(J); 
	} 

	return particle; 
}

cnstr initialize_constraints (config manifold) 
{
	cnstr constraint; 
	
	constraint.holonomic = 
		calloc(manifold.K_H, sizeof(double)); 

	constraint.semiholonomic = 
		calloc(manifold.K_S, sizeof(double)); 

	constraint.inequality = 
		calloc(manifold.K_I, sizeof(double)); 

	return constraint; 
}

