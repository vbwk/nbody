#include <stdlib.h>
#include "odes.h"

#include <stdio.h>

void integrate_system_state (int t, double timeStep, 
	int numCoordinates, double state[], 
	double acceleration[], double **newState)
{
	if (t == 0)
	{
		for (int i = 0; i < numCoordinates; i++)
		{
			(*newState)[i + numCoordinates] = 
				state[i + numCoordinates] + 
				acceleration[i] * timeStep * 0.5; 

			(*newState)[i] = state[i] + 
				(*newState)[i + numCoordinates] * 
				timeStep * 0.5; 
		}
	}

	else 
	{
		for (int i = 0; i < numCoordinates; i++)
		{
			(*newState)[i + numCoordinates] = 
				state[i + numCoordinates] + 
				acceleration[i] * timeStep;  

			(*newState)[i] = state[i] + 
				state[i + numCoordinates] * 
				timeStep;  
		}
	}
}

char *integration_method ()
{
	return "Verlet"; 
}
