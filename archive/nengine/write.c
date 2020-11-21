#include <stdio.h>
#include "write.h"

void write_system_state (int t, double timeStep, cfgspace system) 
{
	FILE *timeData = fopen("./outfiles/time.csv", "a"); 
	FILE *positionData = fopen("./outfiles/position.csv", "a"); 
	FILE *velocityData = fopen("./outfiles/velocity.csv", "a"); 

	fprintf(timeData, "%f\n", t * timeStep);

	for (int n = 0; n < system.N; n++)
	{
		fprintf(positionData, "%f, %f, %f\n", 
			system.particle[n].position.coordinate[0], 
			system.particle[n].position.coordinate[1], 
			system.particle[n].position.coordinate[2]);
	}	

	for (int n = 0; n < system.N; n++)
	{
		fprintf(velocityData, "%f, %f, %f\n", 
			system.particle[n].velocity.coordinate[0],
			system.particle[n].velocity.coordinate[1],
			system.particle[n].velocity.coordinate[2]);
	}	

	fclose(timeData); 
	fclose(positionData); 
	fclose(velocityData); 
}
