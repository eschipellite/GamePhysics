//=============================================================================
//                              Test_PhysicsObject
//
// Written by Evan Schipellite
//=============================================================================
#include "stdafx.h"
#include "CppUnitTest.h"
#include "PhysicsObject.h"
//=============================================================================
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//=============================================================================
namespace UnitTesting_GamePhysics_EvanSchipellite
{
	TEST_CLASS(Test_PhysicsObject)
	{
	public:
		
		//-----------------------------------------------------------------------------
		TEST_METHOD(Test_EulerIntergration)
		{
			PhysicsObject* physicsObject = new PhysicsObject();
			physicsObject->Initialize(1.0f, 1.0f, Vector3D(0, 0, 0), Vector3D(1, 0, 0));

			Vector3D startPosition = Vector3D(0, 0, 0);
			Assert::IsTrue(startPosition == physicsObject->GetPosition());

			physicsObject->Update(1);
			Vector3D newPosition = Vector3D(1, 0, 0);
			Assert::IsTrue(newPosition == physicsObject->GetPosition());

			PhysicsObject* physicsObjectTwo = new PhysicsObject();
			physicsObjectTwo->Initialize(1.0f, 1.0f, Vector3D(0, 0, 0), Vector3D(0, 0, 0));

			Vector3D newVelocity = Vector3D(1, 0, 0);
			physicsObjectTwo->AddForce(Vector3D(1, 0, 0));
			physicsObjectTwo->Update(1);
			Assert::IsTrue(newVelocity == physicsObjectTwo->GetCurrentVelocity());
		}

	};
}
//=============================================================================