#include "Vector3D.h"
#include <cmath>

Vector3D::Vector3D()
{
	Vector3D::x = 0.0f;
	Vector3D::y = 0.0f;
	Vector3D::z = 0.0f;
	Vector3D::magnitude = 0.0f;
}

Vector3D::Vector3D(double x, double y, double z)
{
	Vector3D::magnitude = sqrt(pow(x,2) + pow(y, 2) + pow(z, 2));
	Vector3D::x = x;
	Vector3D::y = y;
	Vector3D::z = z;
}

Vector3D::Vector3D(double x, double y, double z, double magnitude)
{
	Vector3D::x = x;
	Vector3D::y = y;
	Vector3D::z = z;
	Vector3D::magnitude = magnitude;
}

void Vector3D::setVector(double x, double y, double z)
{
	Vector3D::magnitude = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	Vector3D::x = x;
	Vector3D::y = y;
	Vector3D::z = z;
}

void Vector3D::setVector(double x, double y, double z, double magnitude)
{
	Vector3D::x = x;
	Vector3D::y = y;
	Vector3D::z = z;
	Vector3D::magnitude = magnitude;
}

float Vector3D::getDotProduct(Vector3D vector2)
{
	return ((Vector3D::x * vector2.x) + (Vector3D::y * vector2.y) + (Vector3D::z * vector2.z));
}

Vector3D Vector3D::getDisplacementVector(Vector3D vector2)
{
	Vector3D displacementVector;

	displacementVector.x = vector2.x - Vector3D::x;
	displacementVector.y = vector2.y - Vector3D::y;
	displacementVector.z = vector2.z - Vector3D::z;
	displacementVector.magnitude = sqrt(pow(displacementVector.x, 2) + pow(displacementVector.y, 2) + pow(displacementVector.z, 2));

	return displacementVector;
}

void Vector3D::addVector(Vector3D vector2)
{
	Vector3D::x += vector2.x;
	Vector3D::y += vector2.y;
	Vector3D::z += vector2.z;
}

void Vector3D::multiplyVector(Vector3D vector2)
{
	Vector3D::x *= vector2.x;
	Vector3D::y *= vector2.y;
	Vector3D::z *= vector2.z;
}