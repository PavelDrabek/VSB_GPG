#pragma once

class Intersector
{
public:

	Intersector(std::string directory);
	~Intersector();

	static bool intersect(Sphere sphere, Ray &ray);

};