#include "stdafx.h"

Sphere::Sphere(Vector3 s, float r) 
{
	this->r = r;
	this->s = s;

	r2 = r *r;
}