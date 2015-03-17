//=============================================================================
//                              Test_GravityForceGenerator
//
// Written by Evan Schipellite
//=============================================================================
#include "stdafx.h"
#include "CppUnitTest.h"
#include "GravityGenerator.h"
#include "PhysicsObject.h"
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

			PhysicsObject* objectOne = new PhysicsObject();
			objectOne->Initialize(1, Vector3D(1, 0, 0));
			PhysicsObject* objectTwo = new PhysicsObject();
			objectTwo->Initialize(1, Vector3D(0, 0, 0));

			gravityGenerator->UpdateForce(objectOne, objectTwo);

			Vector3D objectOneForce = objectOne->GetCurrentTotalForce();
			Vector3D objectTwoForce = objectTwo->GetCurrentTotalForce();
			objectOneForce *= -1;

			Assert::IsTrue(objectOneForce == objectOneForce);
		}
	};
}
//=============================================================================