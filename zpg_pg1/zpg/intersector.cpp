#include "stdafx.h"

bool Intersector::intersect(Sphere sphere, Ray &ray)
{
	Vector3 S = sphere.s;
	float r2 = sphere.r2;
	Vector3 A = ray.org;
	Vector3 u = Vector3(ray.dir).Normalized();

	Vector3 A_S = (A - S);

	float c = (A_S).SqrL2Norm() - r2;
	float b = 2 * (A_S.x * u.x + A_S.y * u.y + A_S.z * u.z);
	float a = 1;

	float D = b * b - 4 * a * c;
	if (D < 0) {
		ray.geomID == RTC_INVALID_GEOMETRY_ID;
		return false;
	}
	
	float t = 0;
	if (D == 0) {
		t = -b * 0.5f;
	}
	else {
		float t1 = (-b + D) * 0.5f;
		float t2 = (-b - D) * 0.5f;
		t = MIN(t1, t2);
	}

	ray.geomID = 0;
	ray.tfar = t;
	ray.tnear = 0.01f;
	Vector3 normal = ((A + u * t) - S).Normalized();
	ray.Ng[0] = normal.x;
	ray.Ng[1] = normal.y;
	ray.Ng[2] = normal.z;
}
