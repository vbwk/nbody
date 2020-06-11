#ifndef FIELDS_H
#define FIELDS_H

void uniform_gravity (int numParticles, int numCoordinates, 
	double mass[], double **force); 

void newtonian_gravity (int numParticles, double mass[], 
	double state[], double **force); 

#endif
