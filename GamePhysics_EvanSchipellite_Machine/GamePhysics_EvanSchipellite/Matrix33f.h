/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update : April 30, 2015
* Filename : Matrix33f.h
*
*	Description :
*	This class defines a 3x3 matrix of floats.
*
*	Certification of Authenticity :
*I certify that this assignment is entirely my own work.
**********************************************************************/

#ifndef _MATRIX_33_H
#define _MATRIX_33_H

#include <ostream>
#include "Vector3D.h"

class Matrix33f
{
private:
	float mData[9];

public:
	const static Matrix33f identity;
	const static Matrix33f zero;	


public:
	Matrix33f();
	Matrix33f(float arrayList[9]);
	Matrix33f(float v00, float v01, float v02, float v10, float v11, float v12, float v20, float v21, float v22);
	Matrix33f(const Matrix33f &rhs);
	~Matrix33f();

	//basic math operator overloads
	const Matrix33f operator+(const Matrix33f& rhs) const;
	const Matrix33f operator-(const Matrix33f& rhs) const;
	const Matrix33f operator*(float mult) const;
	const Matrix33f operator*(const Matrix33f& rhs) const;
	Vector3D operator*(const Vector3D& vector) const;

	//assignment and math operators
	Matrix33f& operator = ( const Matrix33f& rhs );
	Matrix33f& operator += ( const Matrix33f& rhs );
	Matrix33f& operator -= ( const Matrix33f& rhs );
	Matrix33f& operator *= ( const Matrix33f& rhs );
	Matrix33f& operator *= ( float mult );

	//reference operators
	float operator[](int index) const; //get
	float& operator[](int index); //set

	//matrix functions
	Matrix33f Transpose() const;
	float Determinant() const;
	Matrix33f Inverse() const;
	void SetColumns(const Vector3D &first, const Vector3D &second, const Vector3D &third);
	void SetRows(const Vector3D &first, const Vector3D &second, const Vector3D &third);
	Vector3D Transform(const Vector3D &vector) const;
	Vector3D TransformTranspose(const Vector3D &vector) const;
	void SetInertiaTensorCoeffs(float ix, float iy, float iz, float ixy = 0.0f, float ixz = 0.0f, float iyz = 0.0f);
	void SetBlockInertiaTensor(const Vector3D &halfSizes, float mass);
	void SetSkewSymmetric(const Vector3D vector);
	void SetInverse(const Matrix33f &matrixToInvert);
	Vector3D GetAxisVector(int i) const;

	//static functions
	static Matrix33f Lerp(const Matrix33f& a, const Matrix33f& b, float lerpValue);
	
	//print operators
	friend std::ostream& Matrix33f::operator<<(std::ostream& stream, const Matrix33f& matrix);
	std::string ToString() const;
	void ToArray(float floatArray[9]);

private:
	//helper functions
	void SwapIndexValuesAt(int a, int b);

};

#endif