#ifndef INIT_H
#define INIT_H

#include <stdio.h>
#include "simulation.h"

config initialize_system_manifold (params simulation); 

void skip_line (FILE *initFile);

void print_init_message (params simulation, config manifold); 

char *system_name (); 

#endif
