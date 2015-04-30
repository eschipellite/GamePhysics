/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update : April 30, 2015
* Filename : Matrix33f.cpp
*
*	Description :
*	This class defines a 3x3 matrix of floats.
*
*	Certification of Authenticity :
*I certify that this assignment is entirely my own work.
**********************************************************************/

#include "Matrix33f.h"
#include <sstream>

//constant matricies
const Matrix33f Matrix33f::identity = Matrix33f(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
const Matrix33f Matrix33f::zero = Matrix33f(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

//constructors
Matrix33f::Matrix33f()
{
	mData[0] = 1.0f; mData[1] = 0.0f; mData[2] = 0.0f;
	mData[3] = 0.0f; mData[4] = 1.0f; mData[5] = 0.0f;
	mData[6] = 0.0f; mData[7] = 0.0f; mData[8] = 1.0f;
}
Matrix33f::Matrix33f(float v00, float v01, float v02, float v10, float v11, float v12, float v20, float v21, float v22)
{
	mData[0] = v00; mData[1] = v01; mData[2] = v02;
	mData[3] = v10; mData[4] = v11; mData[5] = v12;
	mData[6] = v20; mData[7] = v21; mData[8] = v22;
}
Matrix33f::Matrix33f(const Matrix33f &rhs)
{
	*this = rhs;
}

Matrix33f::~Matrix33f()
{

}

//basic math operator overloads
const Matrix33f Matrix33f::operator+(const Matrix33f& rhs) const
{
	return Matrix33f(
		mData[0] + rhs.mData[0], mData[1] + rhs.mData[1], mData[2] + rhs.mData[2],
		mData[3] + rhs.mData[3], mData[4] + rhs.mData[4], mData[5] + rhs.mData[5],
		mData[6] + rhs.mData[6], mData[7] + rhs.mData[7], mData[8] + rhs.mData[8]);
}
const Matrix33f Matrix33f::operator-(const Matrix33f& rhs) const
{
	return Matrix33f(
		mData[0] - rhs.mData[0], mData[1] - rhs.mData[1], mData[2] - rhs.mData[2],
		mData[3] - rhs.mData[3], mData[4] - rhs.mData[4], mData[5] - rhs.mData[5],
		mData[6] - rhs.mData[6], mData[7] - rhs.mData[7], mData[8] - rhs.mData[8]);
}
const Matrix33f Matrix33f::operator*(float mult) const
{
	return Matrix33f(
		mData[0] * mult, mData[1] * mult, mData[2] * mult,
		mData[3] * mult, mData[4] * mult, mData[5] * mult,
		mData[6] * mult, mData[7] * mult, mData[8] * mult);
}
const Matrix33f Matrix33f::operator*(const Matrix33f& rhs) const
{
	/*
	a11xb11 + a12xb21 + a13xb31,	a11xb12 + a12xb22 + a13xb32,	a11xb13 + a12xb23 + a13xb33
	a21xb11 + a22xb21 + a23xb31,	a21xb12 + a22xb22 + a23xb32,	a21xb13 + a22xb23 + a23xb33
	a31xb11 + a32xb21 + a33xb31,	a31xb12 + a32xb22 + a33xb32,	a31xb13 + a32xb23 + a33xb33
	*/

	return Matrix33f(
		mData[0] * rhs.mData[0] + mData[1] * rhs.mData[3] + mData[2] * rhs.mData[6],
		mData[0] * rhs.mData[1] + mData[1] * rhs.mData[4] + mData[2] * rhs.mData[7],
		mData[0] * rhs.mData[2] + mData[1] * rhs.mData[5] + mData[2] * rhs.mData[8],
		mData[3] * rhs.mData[0] + mData[4] * rhs.mData[3] + mData[5] * rhs.mData[6],
		mData[3] * rhs.mData[1] + mData[4] * rhs.mData[4] + mData[5] * rhs.mData[7],
		mData[3] * rhs.mData[2] + mData[4] * rhs.mData[5] + mData[5] * rhs.mData[8],
		mData[6] * rhs.mData[0] + mData[7] * rhs.mData[3] + mData[8] * rhs.mData[6],
		mData[6] * rhs.mData[1] + mData[7] * rhs.mData[4] + mData[8] * rhs.mData[7],
		mData[6] * rhs.mData[2] + mData[7] * rhs.mData[5] + mData[8] * rhs.mData[8]);
}
Vector3D Matrix33f::operator*(const Vector3D &vector) const
{
	return Vector3D(
		vector.X * mData[0] + vector.Y * mData[1] + vector.Z * mData[2],
		vector.X * mData[3] + vector.Y * mData[4] + vector.Z * mData[5],
		vector.X * mData[6] + vector.Y * mData[7] + vector.Z * mData[8]);
}

//assignment and math operators
Matrix33f& Matrix33f::operator = ( const Matrix33f& rhs )
{
	mData[0] = rhs.mData[0]; mData[1] = rhs.mData[1]; mData[2] = rhs.mData[2];
	mData[3] = rhs.mData[3]; mData[4] = rhs.mData[4]; mData[5] = rhs.mData[5];
	mData[6] = rhs.mData[6]; mData[7] = rhs.mData[7]; mData[8] = rhs.mData[8];
	return (*this);
}
Matrix33f& Matrix33f::operator += ( const Matrix33f& rhs )
{
	mData[0] += rhs.mData[0]; mData[1] += rhs.mData[1]; mData[2] += rhs.mData[2];
	mData[3] += rhs.mData[3]; mData[4] += rhs.mData[4]; mData[5] += rhs.mData[5];
	mData[6] += rhs.mData[6]; mData[7] += rhs.mData[7]; mData[8] += rhs.mData[8];
	return (*this);
}
Matrix33f& Matrix33f::operator -= ( const Matrix33f& rhs )
{
	mData[0] -= rhs.mData[0]; mData[1] -= rhs.mData[1]; mData[2] -= rhs.mData[2];
	mData[3] -= rhs.mData[3]; mData[4] -= rhs.mData[4]; mData[5] -= rhs.mData[5];
	mData[6] -= rhs.mData[6]; mData[7] -= rhs.mData[7]; mData[8] -= rhs.mData[8];
	return (*this);
}
Matrix33f& Matrix33f::operator *= ( const Matrix33f& rhs )
{
	(*this) = (*this) * rhs;
	return (*this);
}
Matrix33f& Matrix33f::operator *= ( float mult )
{
	(*this) = (*this) * mult;
	return (*this);
}

//reference operators
float Matrix33f::operator[](int index) const
{
	return mData[index];
}
float& Matrix33f::operator[](int index)
{
	return mData[index];
}

//matrix functions
Matrix33f Matrix33f::Transpose() const
{
	return Matrix33f(mData[0], mData[3], mData[6], mData[1], mData[4], mData[7], mData[2], mData[5], mData[8]);
}
float Matrix33f::Determinant() const
{
	return 
		(mData[0] * mData[4] * mData[8]) + (mData[1] * mData[5] * mData[6]) + (mData[2] * mData[3] * mData[7]) -
		(mData[6] * mData[4] * mData[2]) - (mData[7] * mData[5] * mData[0]) - (mData[8] * mData[3] * mData[1]); 
}
Matrix33f Matrix33f::Inverse() const
{
	Matrix33f mat = Matrix33f();
	mat.SetInverse(*this);
	return mat;
}
void Matrix33f::SetColumns(const Vector3D &first, const Vector3D &second, const Vector3D &third)
{
	mData[0] = first.X; mData[1] = second.X; mData[2] = third.X;
	mData[3] = first.Y; mData[4] = second.Y; mData[5] = third.Y;
	mData[6] = first.Z; mData[7] = second.Z; mData[8] = third.Z;  
}
void Matrix33f::SetRows(const Vector3D &first, const Vector3D &second, const Vector3D &third)
{
	mData[0] = first.X; mData[1] = first.Y; mData[2] = first.Z;
	mData[3] = second.X; mData[4] = second.Y; mData[5] = second.Z;
	mData[6] = third.X; mData[7] = third.Y; mData[8] = third.Z;
}
Vector3D Matrix33f::TransformTranspose(const Vector3D &vector) const
{
	return Vector3D(
		vector.X * mData[0] + vector.Y * mData[3] + vector.Z * mData[6],
		vector.X * mData[1] + vector.Y * mData[4] + vector.Z * mData[7],
		vector.X * mData[2] + vector.Y * mData[5] + vector.Z * mData[8]);
}
Vector3D Matrix33f::Transform(const Vector3D &vector) const
{
	return (*this) * vector;
}
Matrix33f Matrix33f::Lerp(const Matrix33f& a, const Matrix33f& b, float lerpValue)
{
	return Matrix33f(
		a.mData[0] * (1.0f - lerpValue) + b.mData[0] * lerpValue,
		a.mData[1] * (1.0f - lerpValue) + b.mData[1] * lerpValue,
		a.mData[2] * (1.0f - lerpValue) + b.mData[2] * lerpValue,
		a.mData[3] * (1.0f - lerpValue) + b.mData[3] * lerpValue,
		a.mData[4] * (1.0f - lerpValue) + b.mData[4] * lerpValue,
		a.mData[5] * (1.0f - lerpValue) + b.mData[5] * lerpValue,
		a.mData[6] * (1.0f - lerpValue) + b.mData[6] * lerpValue,
		a.mData[7] * (1.0f - lerpValue) + b.mData[7] * lerpValue,
		a.mData[8] * (1.0f - lerpValue) + b.mData[8] * lerpValue);
}
void Matrix33f::SetInertiaTensorCoeffs(float ix, float iy, float iz, float ixy, float ixz, float iyz)
{
	mData[0] = ix;
	mData[1] = mData[3] = -ixy;
	mData[2] = mData[6] = -ixz;
	mData[4] = iy;
	mData[5] = mData[7] = -iyz;
	mData[8] = iz;
}
void Matrix33f::SetBlockInertiaTensor(const Vector3D &halfSizes, float mass)
{
	//halfSizes.componentProduct(halfSizes);
	//Vector3f squares = Vector3f::CrossProduct(halfSizes, halfSizes);
	//squares.Power(2.0f);
	Vector3D squares = halfSizes * halfSizes;

	SetInertiaTensorCoeffs(0.3f * mass * (squares.Y + squares.Z), 0.3f * mass * (squares.X + squares.Z), 0.3f * mass * (squares.X + squares.Y));
}
void Matrix33f::SetSkewSymmetric(const Vector3D vector)
{
	mData[0] = 0.0f;
	mData[1] = -vector.Z;
	mData[2] = vector.Y;
	mData[3] = vector.Z;
	mData[4] = 0.0f;
	mData[5] = -vector.X;
	mData[6] = -vector.Y;
	mData[7] = vector.X;
	mData[8] = 0.0f;
}
void Matrix33f::SetInverse(const Matrix33f &matrix)
{
	float t4 = matrix.mData[0] * matrix.mData[4];
    float t6 = matrix.mData[0] * matrix.mData[5];
    float t8 = matrix.mData[1] * matrix.mData[3];
    float t10 = matrix.mData[2] * matrix.mData[3];
    float t12 = matrix.mData[1] * matrix.mData[6];
    float t14 = matrix.mData[2] * matrix.mData[6];

    // Calculate the determinant
    float t16 = (t4 * matrix.mData[8] - t6*matrix.mData[7] - t8 * matrix.mData[8]+
                t10 * matrix.mData[7] + t12*matrix.mData[5] - t14 * matrix.mData[4]);

    // Make sure the determinant is non-zero.
    if (t16 == (float)0.0f)
	{
		return;
	}
    float t17 = 1.0f / t16;

    this->mData[0] = (matrix.mData[4] * matrix.mData[8]-matrix.mData[5] * matrix.mData[7])*t17;
    this->mData[1] = -(matrix.mData[1] * matrix.mData[8]-matrix.mData[2] * matrix.mData[7])*t17;
    this->mData[2] = (matrix.mData[1] * matrix.mData[5]-matrix.mData[2] * matrix.mData[4])*t17;
    this->mData[3] = -(matrix.mData[3] * matrix.mData[8]-matrix.mData[5] * matrix.mData[6])*t17;
    this->mData[4] = (matrix.mData[0] * matrix.mData[8]-t14)*t17;
    this->mData[5] = -(t6-t10)*t17;
    this->mData[6] = (matrix.mData[3] * matrix.mData[7]-matrix.mData[4] * matrix.mData[6])*t17;
    this->mData[7] = -(matrix.mData[0] * matrix.mData[7]-t12)*t17;
    this->mData[8] = (t4-t8)*t17;
}

//accessors
Vector3D Matrix33f::GetAxisVector(int i) const
{
	return Vector3D(mData[i], mData[i + 3], mData[i + 6]);
}

//helper functions
void Matrix33f::SwapIndexValuesAt(int a, int b)
{
	float tmp = mData[a];
	mData[a] = mData[b];
	mData[b] = tmp;
}

//stream operators
std::ostream& operator<<(std::ostream& stream, const Matrix33f& matrix)
{
	stream << "[" 
		<< matrix.mData[0] << ", " << matrix.mData[1] << ", " << matrix.mData[2] << "; "
		<< matrix.mData[3] << ", " << matrix.mData[4] << ", " << matrix.mData[5] << "; "
		<< matrix.mData[6] << ", " << matrix.mData[7] << ", " << matrix.mData[8] << 
		"]";

	return stream;
}
std::string Matrix33f::ToString() const
{
	std::ostringstream ss;
	ss << (*this);
	return ss.str();
}
void Matrix33f::ToArray(float floatArray[9])
{
	floatArray[0] = mData[0]; floatArray[1] = mData[1]; floatArray[2] = mData[2];
	floatArray[3] = mData[3]; floatArray[4] = mData[4]; floatArray[5] = mData[5];
	floatArray[6] = mData[6]; floatArray[7] = mData[7]; floatArray[8] = mData[8];
}