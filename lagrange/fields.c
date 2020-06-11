#include <stdlib.h>
#include "fields.h"
#include "vector.h"
#include "init.h"
#include <stdio.h>

void uniform_gravity (int numParticles, int numCoordinates, 
	double mass[], double **force)
{
	double G = 9.81;
	double cartesianGravity[3] = { 0, 0, -G };
        double *cartesianForce = calloc(numParticles * 3, sizeof(double)); 

	vec_to_n(numParticles, cartesianGravity, &cartesianForce); 

	double *jacobian = get_jacobian (numParticles);

	make_generalized (numCoordinates, jacobian, 
		cartesianForce, force);

	// for (int i = 0; i < numCoordinates; i++) printf("%f\n", (*force)[i]); 

	// free(jacobian); 
}

void newtonian_gravity (int numParticles, double mass[], 
	double state[], double **force)
{

}
