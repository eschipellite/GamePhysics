//=============================================================================
//                              Quaternion
//
// Written by Evan Schipellite
//
// Allows Quaternion rotations
//=============================================================================
#ifndef QUATERNION_H
#define QUATERNION_H
//=============================================================================
class Vector3D;
//=============================================================================
class Quaternion
{
public:
	float R;
	float I;
	float J;
	float K;
public:
	Quaternion();
	Quaternion(float r, float i, float j, float k);
	Quaternion(Vector3D rhs);
	Quaternion(const Quaternion&);
	~Quaternion();

	void Normalize();

	Quaternion operator*(const Quaternion&);
	void operator*=(const Quaternion&);

	void RotateByVector(const Vector3D& rhs);
	void AddScaledVector(const Vector3D& rhs, float scale);
};
//=============================================================================
#endif // QUATERNION_H