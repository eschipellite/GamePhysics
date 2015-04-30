/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update : April 30, 2015
* Filename : Matrix44f.h
*
*	Description :
*	This class defines a 4x4 matrix of floats.
*
*	Certification of Authenticity :
*I certify that this assignment is entirely my own work.
**********************************************************************/

#ifndef _MATRIX_44_H
#define _MATRIX_44_H

#include <string>
#include "Vector3D.h"

class Matrix44f
{
private:
	float mData[16];

public:
	const static Matrix44f identity;
	const static Matrix44f zero;	

public:
	Matrix44f();
	Matrix44f(float arrayList[16]);
	Matrix44f(float v00, float v01, float v02, float v03, float v10, float v11, float v12, float v13, float v20, float v21, float v22, float v23, float v30, float v31, float v32, float v33);
	Matrix44f(const Matrix44f &rhs);
	~Matrix44f();

	//basic math operator overloads
	const Matrix44f operator+(const Matrix44f& rhs) const;
	const Matrix44f operator-(const Matrix44f& rhs) const;
	const Matrix44f operator*(float mult) const;
	const Matrix44f operator*(const Matrix44f& rhs) const;
	Vector3D operator*(const Vector3D &vector) const;

	//assignment and math operators
	Matrix44f& operator = ( const Matrix44f& rhs );
	Matrix44f& operator += ( const Matrix44f& rhs );
	Matrix44f& operator -= ( const Matrix44f& rhs );
	Matrix44f& operator *= ( const Matrix44f& rhs );
	Matrix44f& operator *= ( float mult );

	//reference operators
	float operator[](int index) const; //get
	float& operator [](int index); //set

	//matrix functions
	Matrix44f Transpose() const;
	float Determinant() const;
	Vector3D Transform(const Vector3D &vector) const;
	Vector3D TransformInverse(const Vector3D &vector) const;
	Vector3D TransformDirection(const Vector3D &direction) const;
	Vector3D TransformInverseDirection(const Vector3D &direction) const;
	bool Inverse(Matrix44f &result) const;
	void Invert();

	//accessors
	Vector3D GetAxisVector(int i) const;

	//print operators
	friend std::ostream& Matrix44f::operator<<(std::ostream& stream, const Matrix44f& matrix);
	std::string ToString() const;
	void ToArray(float floatArray[16]);

	//special matricies to generate
	static void CreateTranslationMatrix(Matrix44f &result, const Vector3D &translation);
	static void CreateScaleMatrix(Matrix44f &result, const Vector3D &scale);
	static void CreateRotationMatrix(Matrix44f &result, const Vector3D &anglesRadians);
	static void CreateRotationMatrixFromAxis(Matrix44f &result, const Vector3D &axis, float rotationRadians);
	static void CreateRTSMatrix(Matrix44f &result, const Vector3D &translation, const Vector3D &anglesRadians, const Vector3D &scale);

private:
	//helper functions
	void SwapIndexValuesAt(int a, int b);
	float Determinant33(int v00, int v01, int v02, int v10, int v11, int v12, int v20, int v21, int v22)  const;

};

#endif