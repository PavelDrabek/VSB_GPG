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

bool Intersector::intersect(Quadric quadric, Ray &ray)
{
	Matrix4x4 m = quadric.a;
	Vector3 A = ray.org;
	Vector3 u = Vector3(ray.dir).Normalized();

	float a11 = m.data[0];
	float a12 = m.data[1];
	float a13 = m.data[2];
	float a14 = m.data[3];
	float a22 = m.data[5];
	float a23 = m.data[6];
	float a24 = m.data[7];
	float a33 = m.data[10];
	float a34 = m.data[11];
	float a44 = m.data[15];

	float c = a11*A.x*A.x + a22*A.y*A.y + a33*A.z*A.z 
		+ 2*a12*A.x*A.y + 2*a13*A.x*A.z + 2*a23*A.y*A.z 
		+ 2*a14*A.x + 2*a24*A.y + 2*a34*A.z;
	float b = 2*a11*A.x*A.x + 2*a22*A.y*u.y + 2*a33*A.z*u.z 
		+ 2*a12*A.x*u.y + 2*a12*u.x*A.y + 2*a13*A.x*u.z + 2*a13*u.x*A.z
		+ 2*a23*A.y*u.z + 2*a23*u.y*A.z + 2*a14*u.x 
		+ 2*a14*u.x + 2*a24*u.y + 2*a34*u.z;
	float a = a11*u.x*u.x + a22*u.y*u.y + a33*u.z*u.z
		+ 2*a12*u.x*u.y + 2*a13*u.x*u.z + 2*a23*u.x*u.z;

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
		float sqrtD = sqrt(D);
		float t1 = (-b + sqrtD) * 0.5f;
		float t2 = (-b - sqrtD) * 0.5f;
		if (t1 < ray.tnear && t2 < ray.tnear) {
			ray.geomID == RTC_INVALID_GEOMETRY_ID;
			return false;
		}
		else if (t1 > ray.tnear && t2 > ray.tnear) {
			t = MIN(t1, t2);
		}
		else if (t1 > ray.tnear) {
			t = t1;
		}
		else if (t2 > ray.tnear) {
			t = t2;
		}
		else {
			ray.geomID == RTC_INVALID_GEOMETRY_ID;
			return false;
		}
	}

	Vector3 P = (A + u * t);
	float nx = 2 * a11*P.x + 2 * a12*P.y + 2 * a13*P.z + 2 * a14;
	float ny = 2 * a12*P.x + 2 * a22*P.y + 2 * a23*P.z + 2 * a24;
	float nz = 2 * a33*P.x + 2 * a12*P.y + 2 * a13*P.z + 2 * a14;

	ray.geomID = 0;
	ray.tfar = t;
	Vector3 normal = ((A + u * t) - S).Normalized();
	ray.collided_normal = normal;
	ray.Ng[0] = normal.x;
	ray.Ng[1] = normal.y;
	ray.Ng[2] = normal.z;

	return true;
}
