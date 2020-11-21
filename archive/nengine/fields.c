#include <stdio.h>
#include <stdlib.h>
#include "fields.h"
#include "system.h"

#define G 9.81

void uniform_gravity (cfgspace system, vector *force)
{
	for (int n = 0; n < system.N; n++)
	{
		force[n].coordinate[1] += 
			system.particle[n].mass * -G; 
	}
}	

