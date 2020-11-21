#ifndef DYNAMICS_H
#define DYNAMICS_H

#include "vector.h"
#include "init.h"

void run_simulation (double timeStep, double totalRunTime, cfgspace system);  

int num_coordinates (); 

char *coordinates_type (); 

char *solver_method (); 

#endif
