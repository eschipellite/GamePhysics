//=============================================================================
//                              Vector3D
//
// Written by Evan Schipellite
//
// Vector storage and information
//=============================================================================
#ifndef VECTOR3D_H
#define VECTOR3D_H
//=============================================================================
class Vector3D
{
public:
	float X;
	float Y;
	float Z;

public:
	Vector3D();
	Vector3D(float x, float y, float z);
	~Vector3D();

	Vector3D operator*(const float&) const;
	Vector3D operator/(const float&) const;

	Vector3D operator+(const Vector3D&) const;
	Vector3D operator-(const Vector3D&) const;
	
	float operatordot(const Vector3D&) const;
	Vector3D operatorcross(const Vector3D&) const;
	
	bool operator==(const Vector3D&) const;
	bool operator!=(const Vector3D&) const;

	float Magnitude();
	float MagnitudeSquared();

	void Normalize();
	Vector3D Normalized();
};
//=============================================================================
#endif // VECTOR3D_H

