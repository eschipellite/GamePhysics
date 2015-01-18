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
	Matrix(const Matrix&);
	Matrix(int length, bool identity);
	Matrix(int rows, int columns);
	Matrix(int rows, int columns, float* matrixArray);
	~Matrix();

	void Set(int row, int column, float value);
	float Get(int row, int column) const;
	int GetNumRows() const { return m_NumRows; };
	int GetNumColumns() const { return m_NumColumns; };
	int GetSize() const { return m_Size; };

	bool IsSameSize(const Matrix&) const;

	Matrix operator+(const Matrix&) const;
	Matrix operator-(const Matrix&) const;
	Matrix operator*(const Matrix&) const;
	Matrix operator*(const float&) const;
	Matrix operator*(const Vector3D&) const;
	bool operator==(const Matrix&) const;
	bool operator!=(const Matrix&) const;
	Matrix& operator=(const Matrix&);
};
//=============================================================================
#endif // MATRIX_H

