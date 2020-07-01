#include "manifold.h"
#include "init.h"
#include "write.h"
#include "dynamics.h"

int main (int argc, char *argv[])
{
	params simulation; 

	simulation.timeStep = 0.01; 
	simulation.totalRunTime = 20; 
	simulation.initSpecifier = argv[1];

	/* initialize system manifold */ 

	config manifold = initialize_system_manifold (simulation); 

	/* initialize file output */ 

	initialize_output_files (simulation, manifold);

	/* run simulation */ 

	run_simulation (simulation, manifold); 	
}
