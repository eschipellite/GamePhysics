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
Matrix::Matrix(const Matrix& rhs)
{
	m_NumRows = rhs.GetNumRows();
	m_NumColumns = rhs.GetNumColumns();
	m_Size = m_NumRows * m_NumColumns;
	mp_Matrix = new float[m_Size];

	for (int i = 0; i < m_Size; i++)
	{
		mp_Matrix[i] = rhs.mp_Matrix[i];
	}
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
	delete [] mp_Matrix;
	mp_Matrix = nullptr;
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
void Matrix::Set(int index, float value)
{
	mp_Matrix[index] = value;
}

//-----------------------------------------------------------------------------
float Matrix::Get(int row, int column) const
{
	return mp_Matrix[row * m_NumColumns + column];
}

//-----------------------------------------------------------------------------
float Matrix::Get(int index) const
{
	return mp_Matrix[index];
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

	for (int i = 0; i < m_NumRows; i++)
	{
		for (int j = 0; j < returnMatrix.GetNumColumns(); j++)
		{
			float value = 0;

			for (int k = 0; k < m_NumColumns; k++)
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
Vector3D Matrix::operator*(const Vector3D& rhs) const
{
	float* tempArray = new float[3];
	tempArray[0] = rhs.X;
	tempArray[1] = rhs.Y;
	tempArray[2] = rhs.Z;

	Matrix vectorMatrix = Matrix(3, 1, tempArray);
	vectorMatrix = *this * vectorMatrix;

	return Vector3D(vectorMatrix.Get(0), vectorMatrix.Get(1), vectorMatrix.Get(2));
}

//-----------------------------------------------------------------------------
bool Matrix::operator==(const Matrix& rhs) const
{
	if (!IsSameSize(rhs))
	{
		return false;
	}

	for (int row = 0; row < m_NumRows; row++)
	{
		for (int col = 0; col < m_NumColumns; col++)
		{
			if (Get(row, col) != rhs.Get(row, col))
			{
				return false;
			}
		}
	}

	return true;
}

//-----------------------------------------------------------------------------
bool Matrix::operator!=(const Matrix& rhs) const
{
	return !(*this == rhs);
}

//-----------------------------------------------------------------------------
Matrix& Matrix::operator=(const Matrix& rhs)
{
	m_NumRows = rhs.GetNumRows();
	m_NumColumns = rhs.GetNumColumns();
	m_Size = m_NumRows * m_NumColumns;
	mp_Matrix = new float[m_Size];

	for (int i = 0; i < m_Size; i++)
	{
		mp_Matrix[i] = rhs.mp_Matrix[i];
	}

	return *this;
}

//http://www.sanfoundry.com/cpp-program-finds-inverse-graph-matrix/
//-----------------------------------------------------------------------------
// Assistance from Robert Bethune
Matrix Matrix::GetInverse() const
{
	Matrix inverse = *this;
	if (inverse.GetDeterminant() != 0)
	{
		int n = inverse.GetNumRows();
		int i, j, k;
		float d;
		for (int i = 1; i <= n; i++)
		{
			for (j = 1; j <= 2 * n; j++)
			{
				if (j == (i + n))
				{
					inverse.Set(i, j, 1);
				}
			}
		}
		for (i = n; i > 1; i--)
		{
			if (inverse.Get(i - 1, 1) < inverse.Get(i, 1))
			{
				for (j = 1; j <= n * 2; j++)
				{
					d = inverse.Get(i, j);
					inverse.Set(i, j, inverse.Get(i - 1, j));
					inverse.Set(i - 1, j, d);
				}
			}
		}
		for (i = 1; i <= n; i++)
		{
			for (j = 1; j <= n * 2; j++)
			{
				if (j != i)
				{
					d = inverse.Get(j, i) / inverse.Get(i, i);
					for (k = 1; k <= n * 2; k++)
					{
						inverse.Set(j, k, inverse.Get(j, k) - (inverse.Get(i, k) * d));
					}
				}
			}
		}
		for (i = 1; i <= n; i++)
		{
			d = inverse.Get(i, i);
			for (j = 1; j <= n * 2; j++)
			{
				inverse.Set(i, j, inverse.Get(i, j) / d);
			}
		}
		return inverse;
	}

	return Matrix(inverse.GetNumRows(), inverse.GetNumColumns());
}

//--------------------------------------------------------------------------------------------
// Assistance from Robert Bethune
float Matrix::GetDeterminant() const
{
	float ratio, det;
	Matrix m = *this;
	if (m_NumRows == m_NumColumns)
	{
		for (int i = 0; i < m_NumRows; i++)
		{
			for (int j = 0; j < m_NumColumns; j++)
			{
				if (j > i)
				{
					ratio = m.Get(j, i) / m.Get(i, i);

					for (int k = 0; k < m_NumRows; k++)
					{
						m.Set(j, k, (m.Get(j, k) - (ratio*m.Get(i, k))));
					}
				}
			}
		}
		det = 1;
		for (int i = 0; i < m_NumRows; i++)
		{
			det *= m.Get(i, i);
		}
		return det;
	}
	else
	{
		return 0;
	}
}

//--------------------------------------------------------------------------------------------
Vector3D Matrix::Transform(const Vector3D &vector)
{
	return (*this) * vector;
}

//--------------------------------------------------------------------------------------------
Vector3D Matrix::GetAxisVector(unsigned int index) const
{
	return Vector3D(mp_Matrix[index], mp_Matrix[index + 4], mp_Matrix[index + 8]);
}
//=============================================================================
