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
}

//-----------------------------------------------------------------------------
GameApp::~GameApp()
{
}

//-----------------------------------------------------------------------------
void GameApp::Initialize()
{
	mp_Camera->Initialize(Vector3D(-1, 1, 1));
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
}

//-----------------------------------------------------------------------------
void GameApp::Update()
{
	mp_Camera->Update();
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
