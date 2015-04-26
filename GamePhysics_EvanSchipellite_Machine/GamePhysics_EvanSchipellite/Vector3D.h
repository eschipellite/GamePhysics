//=============================================================================
//                              Vector3D
//
// Written by Evan Schipellite
//
// Vector storage and information for (x, y, z)
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
	static const Vector3D Zero;
	static const Vector3D Up;

public:
	Vector3D();
	Vector3D(const Vector3D&);
	Vector3D(float x, float y, float z = 0);
	~Vector3D();
	
	void operator*=(const Vector3D&);
	Vector3D operator*(const Vector3D&) const;
	Vector3D operator*(const float&) const;
	void operator*=(const float&);
	Vector3D operator/(const float&) const;
	void operator/=(const float&);

	Vector3D operator+(const Vector3D&) const;
	Vector3D operator-(const Vector3D&) const;
	void operator+=(const Vector3D&);
	void operator-=(const Vector3D&);
	
	float Dot(const Vector3D&) const;
	Vector3D Cross(const Vector3D&) const;
	
	bool operator==(const Vector3D&) const;
	bool operator!=(const Vector3D&) const;

	float Magnitude() const;
	float MagnitudeSquared() const;

	void Normalize();
	Vector3D Normalized();

	float GetDistanceSquared(Vector3D rhs);
	float GetDistance(Vector3D rhs);

	void SetIndex(int index, float value);
	float GetIndex(int index) const;
};
//=============================================================================
#endif // VECTOR3D_H

