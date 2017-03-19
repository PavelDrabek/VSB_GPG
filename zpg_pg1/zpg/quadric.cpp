#include "stdafx.h"

Quadric::Quadric(Matrix4x4 a)
{
	this->a = a;
}

Quadric::Quadric(QuadricType t) {
	switch (t)
	{
	case Quadric::Sphere: a = SphereMat; break;
	case Quadric::Cylinder: a = CylinderMat; break;
	case Quadric::Ellipsoid: a = EllipsoidMat; break;
	case Quadric::Paraboloid: a = ParaboloidMat; break;
	case Quadric::Paraboloid2: a = Paraboloid2Mat; break;

	default:
		break;
	}
}