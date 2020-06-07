#include <math.h>
#include "vec3.h"

/* assign one vector to another */ 
struct Vec3 vec3_assign(struct Vec3 v1, struct Vec3 v2)
{
	v1.x = v2.x; 
	v1.y = v2.y; 
	v1.z = v2.z; 
	return v1; 
}

/* add two vectors */ 
struct Vec3 vec3_add(struct Vec3 v1, struct Vec3 v2)
{
	v1.x += v2.x; 
	v1.y += v2.y; 
	v1.z += v2.z; 
	return v1; 
}

/* subtract two vectors */ 
struct Vec3 vec3_subt(struct Vec3 v1, struct Vec3 v2)
{
	v2.x -= v1.x; 
	v2.y -= v1.y; 
	v2.z -= v1.z; 
	return v2; 
}

/* add vector and scalar */ 
struct Vec3 vec3_add_scalar(struct Vec3 v1, double k)
{
	v1.x += k; 
	v1.y += k; 
	v1.z += k; 
	return v1; 
}

/* subtract scalar from vector */ 
struct Vec3 vec3_subt_scalar(struct Vec3 v1, double k)
{
	v1.x -= k; 
	v1.y -= k; 
	v1.z -= k; 
	return v1; 
}

/* scalar multiply */ 
struct Vec3 vec3_mult(struct Vec3 v1, double k)
{
	v1.x *= k; 
	v1.y *= k; 
	v1.z *= k; 
	return v1; 
}

/* dot product */ 
double vec3_dot(struct Vec3 v1, struct Vec3 v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; 
}

/* cross product */ 
struct Vec3 vec3_cross(struct Vec3 v1, struct Vec3 v2)
{
	struct Vec3 v3; 
	v3.x = v1.y * v2.z - v1.z * v2.y; 
	v3.y = v1.z * v2.x - v1.x * v2.z; 
	v3.z = v1.x * v2.y - v1.y * v2.x; 
	return v3; 
}

/* magnitude squared */ 
double vec3_mag_squared(struct Vec3 v)
{
	return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);  
}

/* magnitude */ 
double vec3_mag(struct Vec3 v)
{
	return sqrt(vec3_mag_squared(v));
}	

/* magnitude cubed */ 
double vec3_mag_cubed(struct Vec3 v)
{
	return pow(vec3_mag(v), 3); 
}

/* euclidean distance */ 
double vec3_eucl_dist(struct Vec3 v1, struct Vec3 v2)
{
	return vec3_mag(vec3_subt(v1, v2)); 
}

/* manhattan distance */ 
double vec3_manh_dist(struct Vec3 v1, struct Vec3 v2)
{
	struct Vec3 v3; 
	v3 = vec3_subt(v1, v2); 
	return v3.x + v3.y + v3.z; 
}

/* make negative */ 
struct Vec3 vec3_neg(struct Vec3 v)
{
	v.x = -v.x; 
	v.y = -v.y; 
	v.z = -v.z; 
	return v; 
}


/* Vec3 array methods */ 

/* assign one vector to another */ 
struct Vec3 *vec3n_assign(struct Vec3 v1[], struct Vec3 v2[], int N)
{
	int i; 
	for (i = 0; i < N; i++)
	{
		v1[i].x = v2[i].x; 
		v1[i].y = v2[i].y; 
		v1[i].z = v2[i].z; 
	}
	return v1; 
}

/* add two vectors */ 
struct Vec3 *vec3n_add(struct Vec3 v1[], struct Vec3 v2[], int N)
{
	int i; 
	for (i = 0; i < N; i++)
	{
		v1[i].x += v2[i].x; 
		v1[i].y += v2[i].y; 
		v1[i].z += v2[i].z; 
	}
	return v1; 
} 

/* subtract two vectors */ 
struct Vec3 *vec3n_subt(struct Vec3 v1[], struct Vec3 v2[], int N) 
{
	int i;  
	for (i = 0; i < N; i++)
	{
		v1[i].x -= v2[i].x; 
		v1[i].y -= v2[i].y; 
		v1[i].z -= v2[i].z;
	}	
			
	return v1; 
}

/* add vector and scalar */ 
struct Vec3 *vec3n_add_scalar(struct Vec3 v1[], double k, int N) 
{
	int i;  
	for (i = 0; i < N; i++)
	{
		v1[i].x += k; 
		v1[i].y += k; 
		v1[i].z += k; 
	}	
			
	return v1; 
}

/* subtract vector and scalar */ 
struct Vec3 *vec3n_subt_scalar(struct Vec3 v1[], double k, int N) 
{
	int i;  
	for (i = 0; i < N; i++)
	{
		v1[i].x -= k; 
		v1[i].y -= k; 
		v1[i].z -= k; 
	}	
			
	return v1; 
}

/* scalar multiply */ 
struct Vec3 *vec3n_mult(struct Vec3 v1[], double k, int N) 
{
	int i;  
	for (i = 0; i < N; i++)
	{
		v1[i].x *= k; 
		v1[i].y *= k; 
		v1[i].z *= k; 
	}	
			
	return v1; 
}
