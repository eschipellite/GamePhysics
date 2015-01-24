//=============================================================================
//                              GameApp
//
// Written by Evan Schipellite
//
// Holds all GameApp functionality
//=============================================================================
#include "GameApp.h"
#include <iostream>

using namespace std;
//=============================================================================
GameApp::GameApp()
{
	mp_Camera = new Camera();
	mp_PhysicsObject = new PhysicsObject();
	mp_FireworkLauncher = new FireworkLauncher();
}

//-----------------------------------------------------------------------------
GameApp::~GameApp()
{
}

//-----------------------------------------------------------------------------
void GameApp::Initialize()
{
	mp_Camera->Initialize(Vector3D(0, 0, 0));

	mp_PhysicsObject->Initialize(.5f, Vector3D::Zero, Vector3D(.01f, 0, 0));

	mp_FireworkLauncher->Initialize(Vector3D::Zero, .05f, .01f, .02f, 5, 10, .4f, 3000, 3000, 3);
}

void GameApp::Start()
{
	mp_FireworkLauncher->Start();
}

//-----------------------------------------------------------------------------
void GameApp::CleanUp()
{
	if (mp_Camera != NULL)
	{
		mp_Camera->CleanUp();
	}
	delete mp_Camera;
	mp_Camera = nullptr;

	if (mp_PhysicsObject != NULL)
	{
		mp_PhysicsObject->CleanUp();
	}
	delete mp_PhysicsObject;
	mp_PhysicsObject = nullptr;

	if (mp_FireworkLauncher != NULL)
	{
		mp_FireworkLauncher->CleanUp();
	}
	delete mp_FireworkLauncher;
	mp_FireworkLauncher = nullptr;
}

//-----------------------------------------------------------------------------
void GameApp::Update(int deltaTime, const EditorState* physicsState)
{
	mp_Camera->Update();

	if (!physicsState->GetIsPaused())
	{
		mp_PhysicsObject->Update(deltaTime);

		mp_FireworkLauncher->Update(deltaTime);
	}
}

//-----------------------------------------------------------------------------
void GameApp::Draw()
{
	mp_PhysicsObject->Draw();

	mp_FireworkLauncher->Draw();
}

//-----------------------------------------------------------------------------
void GameApp::Reset()
{
	mp_PhysicsObject->Reset();

	mp_FireworkLauncher->Reset();
}

//-----------------------------------------------------------------------------
void GameApp::UpdateScreenSize(Vector3D screenSize)
{
	mp_Camera->UpdateScreenSize(screenSize);
}

//-----------------------------------------------------------------------------
void GameApp::HandleMouse(Vector3D mousePosition)
{
	mp_Camera->HandleMouse(mousePosition);
}

//-----------------------------------------------------------------------------
void GameApp::HandleKeyPressed(unsigned char key)
{
	mp_Camera->HandleKeyPressed(key);
}

//-----------------------------------------------------------------------------
void GameApp::HandleKeyReleased(unsigned char key)
{
	mp_Camera->HandleKeyReleased(key);
}
//=============================================================================
