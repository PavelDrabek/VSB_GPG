#pragma once

class Intersector
{
public:

	Intersector(std::string directory);
	~Intersector();

	static bool intersect(Sphere sphere, Ray &ray);
	static bool intersect(Quadric quadric, Ray &ray);
	static float t(float a, float b, float c);
	static float t(float t1, float t2);
};