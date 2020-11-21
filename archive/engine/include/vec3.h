#ifndef VEC3_H
#define VEC3_H

struct Vec3 
{
	double x; 
	double y; 
	double z; 
}; 

struct PolVec3
{
	double rho; 
	double phi; 
	double z; 
}; 

struct SphVec3
{
	double r; 
	double theta; 
	double phi; 
}; 

/* Vec3 function declarations */ 

struct Vec3 vec3_assign(struct Vec3 v1, struct Vec3 v2); 

struct Vec3 vec3_add(struct Vec3 v1, struct Vec3 v2); 

struct Vec3 vec3_subt(struct Vec3 v1, struct Vec3 v2);

struct Vec3 vec3_add_scalar(struct Vec3 v1, double k);

struct Vec3 vec3_subt_scalar(struct Vec3 v1, double k); 

struct Vec3 vec3_mult(struct Vec3 v1, double k); 

double vec3_dot(struct Vec3 v1, struct Vec3 v2); 

struct Vec3 vec3_cross(struct Vec3 v1, struct Vec3 v2); 

double vec3_mag_squared(struct Vec3 v); 

double vec3_mag(struct Vec3 v); 

double vec3_mag_cubed(struct Vec3 v); 

double vec3_eucl_dist(struct Vec3 v1, struct Vec3 v2); 

double vec3_manh_dist(struct Vec3 v1, struct Vec3 v2); 

struct Vec3 vec3_neg(struct Vec3 v); 

struct Vec3 *vec3n_assign(struct Vec3 v1[], struct Vec3 v2[], int N); 

struct Vec3 *vec3n_add(struct Vec3 v1[], struct Vec3 v2[], int N); 

struct Vec3 *vec3n_subt(struct Vec3 v1[], struct Vec3 v2[], int N) ; 

struct Vec3 *vec3n_add_scalar(struct Vec3 v1[], double k, int N); 

struct Vec3 *vec3n_subt_scalar(struct Vec3 v1[], double k, int N); 

struct Vec3 *vec3n_mult(struct Vec3 v1[], double k, int N); 

#endif
