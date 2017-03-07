#pragma once
#include "stdafx.h"

#define EXPECT(expr, cmnt) if (expr) { printf("PASSED\t"); } else{ printf("NOT PASSED "); finalTest &= false; } printf(cmnt);printf("\n");


namespace Testing
{
	static bool test_sphere_intersect()
	{
		bool finalTest = true;
		Ray ray = Ray(Vector3(0.f, 0.f, -5.f), Vector3(0.f, 0.f, 1.f), 0.001);
		Sphere sphere_area = Sphere( Vector3(0.f, 0.f, 0.f), 1.f );
		Intersector::intersect(sphere_area, ray);
		EXPECT(ray.isCollided() == true, "Collision");
		Vector3 position = ray.eval(ray.tfar);
		EXPECT(ray.isCollided() == true, "Collision");
		return finalTest;
	}
	static bool test_sphere_not_intersect()
	{
		bool finalTest = true;
		Ray ray = Ray(Vector3(0.f, 0.f, -5.f), Vector3(0.f, 0.f, -1.f), 0.001);
		Sphere sphere_area = Sphere{ Vector3(0.f, 0.f, 0.f), 1.f };
		Intersector::intersect(sphere_area, ray);
		EXPECT(ray.isCollided() == false, "Not Collision");
		return finalTest;
	}
	static bool test_normal()
	{
		bool finalTest = true;
		Ray ray = Ray(Vector3(0.f, 0.f, -5.f), Vector3(0.f, 0.f, 1.f), 0.001);
		Sphere sphere_area = Sphere{ Vector3(0.f, 0.f, 0.f), 2.f };
		Intersector::intersect(sphere_area, ray);
		Vector3 position = ray.collidedPosition();
		Vector3 normal = ray.collided_normal;
		EXPECT(position == Vector3(0.f, 0.f, -2.f), "Position");
		EXPECT(normal == Vector3(0.f, 0.f, -1.f), "Normal");
		Ray passThrough = Ray(position, Vector3(0.f, 0.f, 1.f), 0.01f);
		Intersector::intersect(sphere_area, passThrough);
		Vector3 passThroughCollision = passThrough.collidedPosition();
		Vector3 passthroughNormal = passThrough.collided_normal;
		EXPECT(passThroughCollision == Vector3(0.f, 0.f, 2.f), "Passthrough colision");
		EXPECT(passthroughNormal == Vector3(0.f, 0.f, 1.f), "Passthrough normal colision");

		Ray reflected = Ray(position, Vector3(0.f, 0.f, -1.f), 0.01f);
		Intersector::intersect(sphere_area, reflected);
		EXPECT(reflected.isCollided() == false, "Reflection collision");
		return finalTest;
	}
	static bool test_reflection()
	{
		bool finalTest = true;

		float n1 = 1.1111f;
		float n2 = 1.0f;
		Vector3 n(0, 1, 0);
		Vector3 rd = Vector3(-0.636f, -0.771f, 0).Normalized();
		Vector3 rs = n.Reflect(rd);

		Vector3 lr = Tracer::GetRetractDir(rd, n, n1, n2);
		float R = Tracer::GetFresnelR(rd, n, n1, n2);

		printf("R = %f\n", R);
		printf("lr = (%f, %f, %f)\n", lr.x, lr.y, lr.z);
		printf("rs = (%f, %f, %f)\n", rs.x, rs.y, rs.z);

		Ray ray = Ray(Vector3(2.f, 0.f, -5.f), Vector3(0.f, 0.f, 1.f), 0.001);
		Sphere sphere_area = Sphere{ Vector3(0.f, 0.f, 0.f), 2.f };
		Intersector::intersect(sphere_area, ray);
		Vector3 position = ray.collidedPosition();
		Vector3 normal = ray.collided_normal;
		EXPECT(position == Vector3(2.f, 0.f, 0.f), "Position");
		EXPECT(normal == Vector3(1.f, 0.f, 0.f), "Normal");
		Ray passThrough = Ray(position, Vector3(0.f, 0.f, 1.f), 0.01f);
		Intersector::intersect(sphere_area, passThrough);
		Vector3 passThroughCollision = passThrough.collidedPosition();
		Vector3 passthroughNormal = passThrough.collided_normal;
		EXPECT(passThroughCollision == Vector3(0.f, 0.f, 2.f), "Passthrough colision");
		EXPECT(passthroughNormal == Vector3(0.f, 0.f, 1.f), "Passthrough normal colision");

		Ray reflected = Ray(position, Vector3(0.f, 0.f, -1.f), 0.01f);
		Intersector::intersect(sphere_area, reflected);
		EXPECT(reflected.isCollided() == false, "Reflection collision");
		return finalTest;
	}

	static bool testAll()
	{
		bool result = true;
		result &= test_sphere_intersect();
		result &= test_sphere_not_intersect();
		result &= test_normal();
		result &= test_reflection();

		return result;
	}
}