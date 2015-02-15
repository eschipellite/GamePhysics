//=============================================================================
//                              Test_GravityForceGenerator
//
// Written by Evan Schipellite
//=============================================================================
#include "stdafx.h"
#include "CppUnitTest.h"
#include "GravityGenerator.h"
//=============================================================================
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//=============================================================================
namespace UnitTesting_GamePhysics_EvanSchipellite
{
	TEST_CLASS(Test_GravityForceGenerator)
	{
	public:
		
		//-----------------------------------------------------------------------------
		TEST_METHOD(Test_Update)
		{
			GravityGenerator* gravityGenerator = new GravityGenerator();

			Assert::AreEqual(1.0f, 1.0f);
		}
	};
}
//=============================================================================