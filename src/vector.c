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
	vector v3 = new_vector(v1.J); 
	
	for (int j = 0; j < v1.J; j++)
	{
		v3.coordinate[j] = v1.coordinate[j] + v2.coordinate[j]; 
	}

	return v3; 
}

vector vector_add_3 (vector v1, vector v2, vector v3)
{
	vector v4 = new_vector(v1.J); 
	
	for (int j = 0; j < v1.J; j++)
	{
		v4.coordinate[j] = v1.coordinate[j] + 
			v2.coordinate[j] + v3.coordinate[j];  
	}

	return v4; 
}

vector vector_subt (vector v1, vector v2)
{
	vector v3 = new_vector(v1.J); 
	
	for (int j = 0; j < v1.J; j++)
	{
		v3.coordinate[j] = v2.coordinate[j] - v1.coordinate[j]; 
	}

	return v3; 
}

vector vector_mult (vector v1, double a)
{
	vector v2 = new_vector(v1.J); 
	
	for (int j = 0; j < v1.J; j++)
	{
		v2.coordinate[j] = v1.coordinate[j] * a; 
	}

	return v2; 
}

vector vector_div (vector v1, double a)
{
	vector v2 = new_vector(v1.J); 
	
	for (int j = 0; j < v1.J; j++)
	{
		v2.coordinate[j] = v1.coordinate[j] / a; 
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

double vector_mag_sq (vector v1)
{
	double magnitude_sq; 

	for (int j = 0; j < v1.J; j++)
	{
		magnitude_sq += v1.coordinate[j] * v1.coordinate[j]; 
	}

	return magnitude_sq; 
}

double vector_mag (vector v1)
{
	double magnitude = sqrt(vector_mag_sq(v1)); 
	return magnitude; 
}

vector vector_unit (vector v1)
{
	double magnitude = vector_mag(v1);
	vector unit = vector_div(v1, magnitude); 

	return unit; 	
}	
