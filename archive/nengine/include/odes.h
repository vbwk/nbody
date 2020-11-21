#ifndef ODES_H
#define ODES_H

#include "vector.h"
#include "init.h"

void integrate_system_state (int t, double timeStep,
	cfgspace system, vector *acceleration);

char *integration_method (); 

#endif
