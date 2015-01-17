//=============================================================================
//                              Matrix
//
// Written by Evan Schipellite
//
// Allows for Matrix calculations
//=============================================================================
#include "Matrix.h"
#include "Vector3D.h"
//=============================================================================
Matrix::Matrix()
: Matrix(2, true)
{
}

//-----------------------------------------------------------------------------
Matrix::Matrix(int length, bool identity)
: Matrix(length, length)
{
	if (identity)
	{
		for (int row = 0; row < m_NumRows; row++)
		{
			mp_Matrix[row * m_NumRows + row] = 1;
		}
	}
}

//-----------------------------------------------------------------------------
Matrix::Matrix(int rows, int columns)
{
	initializeMatrix(rows, columns);

	for (int i = 0; i < m_Size; i++)
	{
		mp_Matrix[i] = 0;
	}
}

//-----------------------------------------------------------------------------
Matrix::Matrix(int rows, int columns, float* matrixArray)
{
	initializeMatrix(rows, columns);

	for (int i = 0; i < m_Size; i++)
	{
		mp_Matrix[i] = matrixArray[i];
	}
}

//-----------------------------------------------------------------------------
Matrix::~Matrix()
{
}

//-----------------------------------------------------------------------------
void Matrix::initializeMatrix(int rows, int columns)
{
	m_NumRows = rows;
	m_NumColumns = columns;
	m_Size = m_NumRows * m_NumColumns;
	mp_Matrix = new float[m_Size];
}

//-----------------------------------------------------------------------------
Matrix Matrix::combineMatrix(const Matrix& rhs, bool shouldAdd) const
{
	int direction = 1;

	if (!shouldAdd)
	{
		direction = -1;
	}

	if (!IsSameSize(rhs))
	{
		return *this;
	}

	Matrix returnMatrix = Matrix(m_NumRows, m_NumColumns);

	for (int row = 0; row < m_NumRows; row++)
	{
		for (int col = 0; col < m_NumColumns; col++)
		{
			returnMatrix.Set(row, col, Get(row, col) + rhs.Get(row, col) * direction);
		}
	}

	return returnMatrix;
}

//-----------------------------------------------------------------------------
void Matrix::Set(int row, int column, float value)
{
	mp_Matrix[row * m_NumColumns + column] = value;
}

//-----------------------------------------------------------------------------
float Matrix::Get(int row, int column) const
{
	return mp_Matrix[row * m_NumColumns + column];
}

//-----------------------------------------------------------------------------
bool Matrix::IsSameSize(const Matrix& rhs) const
{
	return m_NumRows == rhs.GetNumRows() && m_NumColumns == rhs.GetNumColumns();
}

//-----------------------------------------------------------------------------
Matrix Matrix::operator+(const Matrix& rhs) const
{
	return combineMatrix(rhs, true);
}

//-----------------------------------------------------------------------------
Matrix Matrix::operator-(const Matrix& rhs) const
{
	return combineMatrix(rhs, false);
}

//-----------------------------------------------------------------------------
Matrix Matrix::operator*(const Matrix& rhs) const
{
	if (m_NumColumns != rhs.GetNumRows())
	{
		return *this;
	}

	Matrix returnMatrix = Matrix(m_NumRows, rhs.GetNumColumns());

	for (int i = 0; i < returnMatrix.GetNumColumns(); i++)
	{
		for (int j = 0; j < returnMatrix.GetNumRows(); j++)
		{
			float value = 0;

			for (int k = 0; k < m_NumRows; k++)
			{
				value += Get(i, k) * rhs.Get(k, j);
			}

			returnMatrix.Set(i, j, value);
		}
	}

	return returnMatrix;
}

//-----------------------------------------------------------------------------
Matrix Matrix::operator*(const float& rhs) const
{
	float* tempArray = new float[m_Size];

	for (int i = 0; i < m_Size; i++)
	{
		tempArray[i] = mp_Matrix[i] * rhs;
	}

	return Matrix(m_NumRows, m_NumColumns, tempArray);
}

//-----------------------------------------------------------------------------
Matrix Matrix::operator*(const Vector3D& rhs) const
{
	float* tempArray = new float[3];
	tempArray[0] = rhs.X;
	tempArray[1] = rhs.Y;
	tempArray[2] = rhs.Z;

	Matrix vectorMatrix = Matrix(3, 1, tempArray);

	return (*this * vectorMatrix);
}
//=============================================================================
