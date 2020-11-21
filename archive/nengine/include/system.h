#ifndef SYSTEM_H
#define SYSTEM_H

#include "vector.h"
#include "init.h"

#if 0
void apply_field_forces (cfgspace system, vector *acceleration); 

void resolve_holonomic_constraints (int t, double timeStep, cfgspace system); 
#endif

int num_generalized_coordinates (); 

char *generalized_coordinate_type (); 

char *system_name (); 

#endif
