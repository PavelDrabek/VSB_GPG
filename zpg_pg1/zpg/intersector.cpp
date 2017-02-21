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
	} else {
		float sqrtD = sqrt(D);
		float t1 = (-b + sqrtD) * 0.5f;
		float t2 = (-b - sqrtD) * 0.5f;
		if (t1 < ray.tnear && t2 < ray.tnear) {
			ray.geomID == RTC_INVALID_GEOMETRY_ID;
			return false;
		} else if (t1 > ray.tnear && t2 > ray.tnear) {
			t = MIN(t1, t2);
		} else if (t1 > ray.tnear) {
			t = t1;
		} else if (t2 > ray.tnear) {
			t = t2;
		} else {
			ray.geomID == RTC_INVALID_GEOMETRY_ID;
			return false;
		}
	}

	ray.geomID = 0;
	ray.tfar = t;
	Vector3 normal = ((A + u * t) - S).Normalized();
	ray.collided_normal = normal;
	ray.Ng[0] = normal.x;
	ray.Ng[1] = normal.y;
	ray.Ng[2] = normal.z;

	return true;
}
