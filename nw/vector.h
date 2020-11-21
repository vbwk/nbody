#ifndef VECTOR_H
#define VECTOR_H

typedef struct vector {
	int J; 
	double *coordinate; 
} vector;  

vector new_vector (int numCoordinates);

vector *new_vector_array (int numBodies, int numCoordinates); 

vector vector_add (vector v1, vector v2); 

vector vector_add_3 (vector v1, vector v2, vector v3); 

vector vector_subt (vector v1, vector v2); 

vector vector_mult (vector v1, double a); 

vector vector_div (vector v1, double a);

double vector_dot (vector v1, vector v2);

double vector_mag_sq (vector v1); 

double vector_mag (vector v1); 

vector vector_unit (vector v1); 

#endif
