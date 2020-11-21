#ifndef INIT_H
#define INIT_H

#include "dynamics.h"

void initialize_manifold(Manifold manifold); 

void skip_line (FILE *initFile);

void print_init_message (Simulation simulation, Manifold manifold); 

char *system_name (); 

#endif
