#pragma once
// matrix source: https://people.cs.clemson.edu/~dhouse/courses/405/notes/quadrics.pdf

class Quadric
{
public:
	enum QuadricType
	{
		Sphere, Cylinder, Ellipsoid, Paraboloid, Paraboloid2
	};

	Quadric(Matrix4x4 a);
	Quadric(QuadricType t);
	//~Quadric();

	const Matrix4x4 SphereMat = Matrix4x4(
		1, 0, 0, 0, 
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, -1);

	const Matrix4x4 CylinderMat = Matrix4x4(
		1, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, -1);

	const Matrix4x4 EllipsoidMat = Matrix4x4(
		1, 0, 0, 0,
		0, 0.5f, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, -1);

	const Matrix4x4 ParaboloidMat = Matrix4x4(
		1, 0, 0, 0,
		0, -1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, -1);

	const Matrix4x4 Paraboloid2Mat = Matrix4x4(
		1, 0, 0, 0,
		0, -1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	Matrix4x4 a;
};