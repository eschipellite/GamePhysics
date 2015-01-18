#include "stdafx.h"
#include "CppUnitTest.h"
#include "Matrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting_GamePhysics_EvanSchipellite
{
	TEST_CLASS(Test_Matrix)
	{
	public:
		
		TEST_METHOD(Test_SetValues)
		{
			float* valueArray1 = new float[6];
			valueArray1[0] = 1;
			valueArray1[1] = 2;
			valueArray1[2] = 3;
			valueArray1[3] = 4;
			valueArray1[4] = 5;
			valueArray1[5] = 6;
			Matrix matrix1 = Matrix(2, 3, valueArray1);

			Assert::AreEqual(1.0f, matrix1.Get(0, 0));
			Assert::AreEqual(2.0f, matrix1.Get(0, 1));
			Assert::AreEqual(3.0f, matrix1.Get(0, 2));
			Assert::AreEqual(4.0f, matrix1.Get(1, 0));
			Assert::AreEqual(5.0f, matrix1.Get(1, 1));
			Assert::AreEqual(6.0f, matrix1.Get(1, 2));
		}

		TEST_METHOD(Test_Multiplication)
		{
			float* valueArray1 = new float[6];
			valueArray1[0] = 1;
			valueArray1[1] = 2;
			valueArray1[2] = 3;
			valueArray1[3] = 4;
			valueArray1[4] = 5;
			valueArray1[5] = 6;
			Matrix matrix1 = Matrix(2, 3, valueArray1);

			float* valueArray2 = new float[6];
			valueArray2[0] = 7;
			valueArray2[1] = 8;
			valueArray2[2] = 9;
			valueArray2[3] = 10;
			valueArray2[4] = 11;
			valueArray2[5] = 12;
			Matrix matrix2 = Matrix(3, 2, valueArray2);

			float* resultArray = new float[4];
			resultArray[0] = 58;
			resultArray[1] = 64;
			resultArray[2] = 139;
			resultArray[3] = 154;
			Matrix resultMatrix = Matrix(2, 2, resultArray);

			Matrix testMatrix = matrix1 * matrix2;

			Assert::IsTrue(resultMatrix == testMatrix);
		}

		TEST_METHOD(Test_Addition)
		{
			float* valueArray1 = new float[4];
			valueArray1[0] = 1;
			valueArray1[1] = 2;
			valueArray1[2] = 3;
			valueArray1[3] = 4;
			Matrix matrix1 = Matrix(2, 2, valueArray1);

			float* valueArray2 = new float[4];
			valueArray2[0] = 7;
			valueArray2[1] = 8;
			valueArray2[2] = 9;
			valueArray2[3] = 10;
			Matrix matrix2 = Matrix(2, 2, valueArray2);

			float* resultArray = new float[4];
			resultArray[0] = 8;
			resultArray[1] = 10;
			resultArray[2] = 12;
			resultArray[3] = 14;
			Matrix resultMatrix = Matrix(2, 2, resultArray);

			Matrix added = matrix1 + matrix2;

			Assert::IsTrue(added == resultMatrix);
		}

		TEST_METHOD(Test_Subtraction)
		{
			float* valueArray1 = new float[4];
			valueArray1[0] = 1;
			valueArray1[1] = 2;
			valueArray1[2] = 3;
			valueArray1[3] = 4;
			Matrix matrix1 = Matrix(2, 2, valueArray1);

			float* valueArray2 = new float[4];
			valueArray2[0] = 7;
			valueArray2[1] = 8;
			valueArray2[2] = 9;
			valueArray2[3] = 10;
			Matrix matrix2 = Matrix(2, 2, valueArray2);

			float* resultArray = new float[4];
			resultArray[0] = -6;
			resultArray[1] = -6;
			resultArray[2] = -6;
			resultArray[3] = -6;
			Matrix resultMatrix = Matrix(2, 2, resultArray);

			Matrix added = matrix1 - matrix2;

			Assert::IsTrue(added == resultMatrix);
		}

	};
}