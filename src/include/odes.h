#ifndef ODES_H
#define ODES_H

#include "simulation.h"

void integrate_system_state (int t, params simulation,
	config manifold, vector *acceleration);

char *integration_method (); 

#endif
