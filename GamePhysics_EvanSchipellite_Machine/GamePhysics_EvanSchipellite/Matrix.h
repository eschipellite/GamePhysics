//=============================================================================
//                              Matrix
//
// Written by Evan Schipellite
//
// Allows for Matrix calculations
//=============================================================================
#ifndef MATRIX_H
#define MATRIX_H
//=============================================================================
#include "Vector3D.h"
//=============================================================================
class Matrix
{
private:
	float* mp_Matrix;
	int m_NumRows;
	int m_NumColumns;
	int m_Size;

private:
	void initializeMatrix(int rows, int columns);

	Matrix combineMatrix(const Matrix&, bool shouldAdd) const;

public:
	Matrix();
	Matrix(const Matrix& rhs);
	Matrix(int length, bool identity);
	Matrix(int rows, int columns);
	Matrix(int rows, int columns, float* matrixArray);
	~Matrix();

	void Set(int row, int column, float value);
	void Set(int index, float value);
	float Get(int row, int column) const;
	float Get(int index) const;
	int GetNumRows() const { return m_NumRows; };
	int GetNumColumns() const { return m_NumColumns; };
	int GetSize() const { return m_Size; };

	bool IsSameSize(const Matrix&) const;

	Matrix operator+(const Matrix&) const;
	Matrix operator-(const Matrix&) const;
	Matrix operator*(const Matrix&) const;
	Matrix operator*(const float&) const;
	Vector3D operator*(const Vector3D&) const;
	bool operator==(const Matrix&) const;
	bool operator!=(const Matrix&) const;
	Matrix& operator=(const Matrix&);

	Matrix GetInverse() const;
	float GetDeterminant() const;
	Matrix GetTranspose() const;

	Vector3D Transform(const Vector3D &vector);
	Vector3D TransformInverse(const Vector3D &vector);
	Vector3D TransformTranspose(const Vector3D &vector);
	Vector3D GetAxisVector(unsigned int index) const;

	void SetSkewSymmetric(const Vector3D vector);
};
//=============================================================================
#endif // MATRIX_H

