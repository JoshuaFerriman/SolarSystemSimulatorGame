#ifndef CLASS_VECTOR3D_H
#define CLASS_VECTOR3D_H

class Vector3D
{

public:
	double x;
	double y;
	double z;
	double magnitude;

public:
	Vector3D();
	Vector3D(double x, double y, double z);
	Vector3D(double x, double y, double z, double magnitude);

	void setVector(double x, double y, double z);
	void setVector(double x, double y, double z, double magnitude);

	void multiplyVector(Vector3D vector2);
	Vector3D multiplyVectors(Vector3D vector1, Vector3D vector2);
	void addVector(Vector3D vector2);
	Vector3D addVectors(Vector3D vector1, Vector3D vector2);
	float getDotProduct(Vector3D vector2);
	Vector3D getDisplacementVector(Vector3D vector2);
};

#endif
