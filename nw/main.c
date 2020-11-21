#include <stdio.h>
#include <stdlib.h>
#include "dynamics.h"
#include "init.h"
#include "system.h"

Simulation simulation; 
Manifold manifold; 

int main(int argc, char *argv[])
{
	simulation.initSpecifier = argv[1]; 
	simulation.timeStep = atof(argv[2]); 
	simulation.totalRunTime = atof(argv[3]); 

	initialize_manifold(manifold); 

}
