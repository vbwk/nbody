#include <stdlib.h>
#include <math.h>
#include "vector.h"

vector new_vector (int numCoordinates)
{
	vector v1;  

	v1.J = numCoordinates; 
	v1.coordinate = calloc(numCoordinates, sizeof(double));

	return v1; 	
}

vector *new_vector_array (int numBodies, int numCoordinates)
{
	vector *v1 = malloc(numBodies * sizeof(vector)); 

	for (int n = 0; n < numBodies; n++)
	{
		v1[n].J = numCoordinates; 
		v1[n].coordinate = calloc(numCoordinates, sizeof(double)); 
	}

	return v1; 
}

vector vector_add (vector v1, vector v2)
{
	for (int j = 0; j < v1.J; j++)
	{
		v1.coordinate[j] += v2.coordinate[j]; 
	}

	return v1; 
}

vector vector_add_3 (vector v1, vector v2, vector v3)
{
	for (int j = 0; j < v1.J; j++)
	{
		v1.coordinate[j] += v2.coordinate[j] + v3.coordinate[j];  
	}

	return v1; 
}

vector vector_subt (vector v1, vector v2)
{
	for (int j = 0; j < v1.J; j++)
	{
		v1.coordinate[j] -= v2.coordinate[j]; 
	}

	return v1; 
}

vector vector_mult (vector v1, double a)
{
	for (int j = 0; j < v1.J; j++)
	{
		v1.coordinate[j] *= a; 
	}

	return v1; 
}

vector vector_div (vector v1, double a)
{
	for (int j = 0; j < v1.J; j++)
	{
		v1.coordinate[j] *= (1 / a); 
	}

	return v1; 
}

double vector_dot (vector v1, vector v2)
{
	double dot_product = 0;

	for (int j = 0; j < v1.J; j++)
	{
		dot_product += v1.coordinate[j] * v2.coordinate[j]; 
	}	
	
	return dot_product; 
}
