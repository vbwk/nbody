#ifndef DYNAMICS_H
#define DYNAMICS_H

#include "manifold.h"

void run_simulation (params simulation, config manifold); 

char *coordinates_type (); 

char *solver_method (); 

#endif
