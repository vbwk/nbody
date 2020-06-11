#include <stdio.h>
#include "init.h"

void write_system_state (int t, double timeStep, 
	int numStateVars, double state[])
{
	FILE *timeData = fopen("./outfiles/time.csv", "a"); 
	FILE *stateData = fopen("./outfiles/genstate.csv", "a");

	fprintf(timeData, "%f\n", t * timeStep);

	for (int i = 0; i < numStateVars; i++) 
	{
		fprintf(stateData, "%f\n", state[i]); 
	}

	fclose(timeData); 
	fclose(stateData); 
}
