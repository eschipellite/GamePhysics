//=============================================================================
//                              Test_Vector3D
//
// Written by Evan Schipellite
//=============================================================================
#include "stdafx.h"
#include "CppUnitTest.h"
#include "Vector3D.h"
#include <iostream>
//=============================================================================
using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//=============================================================================
namespace UnitTesting_GamePhysics_EvanSchipellite
{
	TEST_CLASS(Test_Vector3D)
	{
	public:

		//-----------------------------------------------------------------------------
		TEST_METHOD(Vector_TestEqual)
		{
			Vector3D vector3D1 = Vector3D(1, 2, 3);
			Vector3D vector3D2 = Vector3D(1, 2, 3);

			Assert::IsTrue(vector3D1 == vector3D2);
		}

		//-----------------------------------------------------------------------------
		TEST_METHOD(Vector_TestNotEqual)
		{
			Vector3D vector3D1 = Vector3D(1, 1, 1);
			Vector3D vector3D2 = Vector3D(2, 2, 2);

			Assert::IsTrue(vector3D1 != vector3D2);
		}

		//-----------------------------------------------------------------------------
		TEST_METHOD(Vector_TestNormalized)
		{
			Vector3D vector3D1 = Vector3D(2, 0, 0);
			vector3D1.Normalize();

			Assert::IsTrue(vector3D1 == Vector3D(1, 0, 0));
		}

		//-----------------------------------------------------------------------------
		TEST_METHOD(Vector_TestMultiply)
		{
			Vector3D vector3D1 = Vector3D(1, 1, 1);
			vector3D1 = vector3D1 * 2;

			Assert::IsTrue(vector3D1 == Vector3D(2, 2, 2));
		}

		//-----------------------------------------------------------------------------
		TEST_METHOD(Vector_TestDivide)
		{
			Vector3D vector3D1 = Vector3D(2, 2, 2);
			vector3D1 = vector3D1 / 2;

			Assert::IsTrue(vector3D1 == Vector3D(1, 1, 1));
		}

		//-----------------------------------------------------------------------------
		TEST_METHOD(Vector_TestAddAndSubtract)
		{
			Vector3D vector3D1 = Vector3D(1, 1, 1);
			vector3D1 = vector3D1 + Vector3D(1, 1, 1);

			Assert::IsTrue(vector3D1 == Vector3D(2, 2, 2));

			vector3D1 = vector3D1 - Vector3D(2, 2, 2);

			Assert::IsTrue(vector3D1 == Vector3D(0, 0, 0));
		}

		//-----------------------------------------------------------------------------
		TEST_METHOD(Vector_TestDot)
		{
			Vector3D vector3D1 = Vector3D(1, 1, 1);
			float dot = vector3D1.Dot(Vector3D(2, 2, 2));

			Assert::AreEqual(dot, 6.0f);
		}

		//-----------------------------------------------------------------------------
		TEST_METHOD(Vector_TestCross)
		{
			Vector3D vector3D1 = Vector3D(3, -3, 1);
			Vector3D vector3D2 = Vector3D(-12, 12, -4);

			Vector3D crossVector = vector3D1.Cross(vector3D2);

			Assert::IsTrue(crossVector == Vector3D(0, 0, 0));
		}
	};
}
//=============================================================================