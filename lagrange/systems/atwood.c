#include <stdlib.h>
#include "vector.h"
#include "fields.h"
#include "init.h"

void apply_fields (int numParticles, int numCoordinates, double mass[], 
	double state[], double **force) 
{
	uniform_gravity (numParticles, numCoordinates, mass, force);
}

#if 0
void project_constraints (int numParticles, double mass[], 
	double constraint[], struct Vec3 **position) 
	
{
	for (int i = 0; i < numParticles; i++)
	{
		if (i == 0)
		{
			struct Vec3 initialGuess = (*position)[i];
			struct Vec3 otherPosition = { 0, 0, 0 }; 
		        struct Vec3 newGuess; 	
			
			distance_constraint (initialGuess, otherPosition, 
				constraint[i], &newGuess);

			(*position)[i] = newGuess; 	
		}

		else
		{
			struct Vec3 initialGuess = (*position)[i];
			struct Vec3 otherPosition = (*position)[i-1]; 
		        struct Vec3 newGuess; 	
			
			distance_constraint (initialGuess, otherPosition, 
				constraint[i], &newGuess);

			(*position)[i] = newGuess; 	
		}
	}
}
#endif

double *get_reduced_mass (double *mass, 
	int numParticles, int numCoordinates)
{
	double *reducedMass = calloc(numCoordinates, sizeof(double)); 

	reducedMass[0] = (mass[0] - mass[1]) / (mass[0] + mass[1]);

	return reducedMass; 
}	

double *get_jacobian (int numParticles)
{
	double *matrix = calloc(6, sizeof(double)); 
	matrix[2] = 1; 
	
	return matrix;
}

double *get_state_jacobian (int numParticles)
{
	int numGC = 2; 
	int numCC = numParticles * 6;

	double *matrix = calloc(numGC * numCC, sizeof(double)); 

	matrix[2] = 1; 
	matrix[12 + 5] = 1;

	return matrix; 	
}

/*
void gcs_to_ccs (int numParticles, int numCoordinates, double mass[], 
	double constraint[], double state[], double **newState) 
{
	*newState = calloc(numParticles * 6, sizeof(double)); 
	
	double *jacobianTranspose = calloc(24, sizeof(double)); 

	jacobianTranspose[0] = -(1 / state[0]); 
	jacobianTranspose[2] = 1;
        jacobianTranspose[8] = -1 + (-constraint[0] / state[0]);
	jacobianTranspose[6] = (1 / state[0]); 
	jacobianTranspose[17] = 1; 
	jacobianTranspose[23] = -1;

	// for (int i = 0; i < 24; i++) printf("%f\n", jacobianTranspose[i]);

	for (int i = 0; i < 12; i++) 
	{
		(*newState)[i] += state[0] * jacobianTranspose[i]; 
	}

	for (int i = 0; i < 12; i++)
	{
		(*newState)[i] += state[1] * jacobianTranspose[12 + i]; 
	}

	for (int i = 0; i < 12; i++) printf("%f\n", (*newState)[i]); 
}
*/ 

int num_generalized_coordinates () 
{
	return 1; 
}

char *system_name () 
{
	return "atwood"; 
}
