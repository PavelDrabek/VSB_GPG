#pragma once
// matrix source: https://people.cs.clemson.edu/~dhouse/courses/405/notes/quadrics.pdf

class Quadric
{
public:
	Quadric(Matrix4x4 a);
	//~Quadric();

	Matrix4x4 SphereMat = Matrix4x4(
		1, 0, 0, 0, 
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	Matrix4x4 Cylinder = Matrix4x4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 1);

	Matrix4x4 a;

};