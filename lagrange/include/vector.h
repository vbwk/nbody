#ifndef VECTOR_H
#define VECTOR_H

double *vec_mult (double v1[], double v2[], int numCoordinates);  

void vec_to_n (int numParticles, double v1[], double **nv1); 

void make_generalized_state (int numParticles, 
	int numStateVars, double jacobian[], 
	double cartesianState[], double **generalizedState); 

void make_generalized (int numCoordinates, double jacobian[], 
	double cartesianVector[], double **generalizedVector); 

#endif
