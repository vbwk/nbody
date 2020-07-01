#ifndef SYSTEM_H
#define SYSTEM_H

#include "vector.h"
#include "manifold.h"

void apply_field_forces (config manifold, vector *acceleration); 

void project_constraints (config manifold); 

int num_generalized_coordinates (); 

char *generalized_coordinate_type (); 

char *system_name (); 

#endif
