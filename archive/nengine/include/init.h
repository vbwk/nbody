#ifndef INIT_H
#define INIT_H

#include "vector.h"
#include "manifold.h"

typedef struct par {
	char *initSpecifier;
       	double timeStep; 
	double totalRunTime; 
} par; 	

void set_parameters (int argc, char *argv[], par *simulation); 

void skip_line (FILE *initFile); 

#endif
