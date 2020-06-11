#ifndef INIT_H
#define INIT_H

#include <time.h>

void set_parameters (int argc, char *argv[], char **initSpecifier, 
	double *timeStep, double *totalRunTime); 

void set_parameters_manually (char ***initSpecifier, 
	double **timeStep, double **totalRunTime); 

void make_init_file (); 

void check_optional_parameters (int argc, char *argv[], 
	double **timeStep, double **totalRunTime); 

void initialize_system (char *initSpecifier, int *numParticles, 
	int *numConstraints, int *numCoordinates, int *numStateVars, 
	double **mass, double **reducedMass, double **constraint, 
	double **state); 

void write_system_state (int t, double timeStep, 
	int numStateVars, double state[]); 

double diffclock (clock_t clock1, clock_t clock2);

double *get_reduced_mass (double *mass, 
	int numParticles, int numCoordinates); 

double *get_jacobian (int numParticles); 

double *get_state_jacobian (int numParticles);

double *get_inv_state_jacobian (int numParticles); 

int num_generalized_coordinates (); 

char *coordinates_type ();

char *solver_method (); 

char *usage_message (); 

char *system_name (); 

#endif
