#include <stdlib.h>
#include "manifold.h"

state *new_particle_array (int N, int J)
{
	state *particle = malloc(N * sizeof(state)); 

	for (int n = 0; n < N; n++)
	{
		particle[n].position = new_vector(J); 
		particle[n].newPosition = new_vector(J); 
		particle[n].velocity = new_vector(J); 
		particle[n].newVelocity = new_vector(J); 
		particle[n].newMomentum = new_vector(J); 
	} 

	return particle; 	
}

cnstr new_constraint_array (int K_H, int K_S, int K_I)
{
	cnstr constraint; 

	constraint.holonomic = calloc(K_H, sizeof(double)); 
	constraint.semiholonomic = calloc(K_S, sizeof(double)); 
	constraint.inequality = calloc(K_I, sizeof(double)); 

	return constraint; 	
}	
