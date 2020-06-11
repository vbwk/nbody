#include <stdlib.h>
#include "vector.h"

#include <stdio.h>

double *vec_mult (double v1[], double v2[], int numCoordinates) 
{
	for (int i = 0; i < numCoordinates; i++)
	{
		v1[i] *= v2[i]; 
	}

	return v1; 
}

void vec_to_n (int numParticles, double v1[], double **nv1)
{
	int particleIndex = 0; 
	for (int i = 0; i < numParticles; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			(*nv1)[j + i * particleIndex] = v1[j]; 
		}

		particleIndex += 3;
	}	
}

void make_generalized (int numCoordinates, double jacobian[], 
	double cartesianVector[], double **generalizedVector)
{
	for (int i = 0; i < numCoordinates; i++) 
	{
		for (int j = 0; j < 6; j++)
		{
			(*generalizedVector)[i] += 
				cartesianVector[j] * jacobian[j];
		}
	}
}	

void make_generalized_state (int numParticles, 
	int numStateVars, double jacobian[], 
	double cartesianState[], double **generalizedState)
{
	*generalizedState = calloc(
		numStateVars, sizeof(double));

	int numCartesianVars = numParticles * 6; 

	for (int i = 0; i < numStateVars; i++)
	{
		for (int j = 0; j < numCartesianVars; j++)
		{
			(*generalizedState)[i] += cartesianState[j] * 
				jacobian[j + i * numCartesianVars];
		}
	}
}

