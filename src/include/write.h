#ifndef WRITE_H
#define WRITE_H

#include "vector.h"
#include "manifold.h"
#include "init.h"

void initialize_output_files (params simulation, config manifold); 

void write_system_state (int t, params simulation, config manifold); 

#endif
