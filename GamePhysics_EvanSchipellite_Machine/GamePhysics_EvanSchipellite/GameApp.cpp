//=============================================================================
//                              GameApp
//
// Written by Evan Schipellite
//
// Holds all GameApp functionality
//=============================================================================
#define _USE_MATH_DEFINES

#include "Skybox.h"
#include "GameApp.h"
#include <iostream>
#include <math.h>
#include <iomanip>
#include <sstream>
#include "Level.h"
#include "SpringForceGenerator.h"
#include "BungeeForceGenerator.h"
#include "ImageHandler.h"
//=============================================================================
float GameApp::ms_TimeStep = 1;
//=============================================================================
GameApp::GameApp()
{
	mp_Camera = new Camera();
	mp_PhysicsHandler = new PhysicsHandler();
	mp_Skybox = new Skybox();
	mp_Level = new Level();

	m_FocusIndex = -1;
}

//-----------------------------------------------------------------------------
GameApp::~GameApp()
{
	CleanUp();
}

//-----------------------------------------------------------------------------
std::string GameApp::convertFloatToString(float value)
{
	std::ostringstream out;
	out << std::setprecision(5) << value;
	return out.str();
}

//-----------------------------------------------------------------------------
std::string GameApp::convertVector3DToString(Vector3D vector3D)
{
	std::string x = convertFloatToString(vector3D.X);
	std::string y = convertFloatToString(vector3D.Y);
	std::string z = convertFloatToString(vector3D.Z);

	return "Vector3D(" + x + ", " + y + ", " + z + ")";
}

//-----------------------------------------------------------------------------
void GameApp::Initialize()
{
	mp_PhysicsHandler->Initialize();
	mp_Skybox->Initialize("Content/Skybox/Pond/Pond_Front.bmp", "Content/Skybox/Pond/Pond_Back.bmp", "Content/Skybox/Pond/Pond_Up.bmp", "Content/Skybox/Pond/Pond_Down.bmp",
		"Content/Skybox/Pond/Pond_Right.bmp", "Content/Skybox/Pond/Pond_Left.bmp");

	Vector3D centerPosition = Vector3D(0, 0, 0);
	Vector3D centerRotation = Vector3D(0, 0, 0);
	mp_Camera->Initialize(centerPosition, centerRotation);

	ImageHandler::GetInstance()->AddImage("Content/Textures/Texture_Grass.jpg", "Ground");
	ImageHandler::GetInstance()->AddImage("Content/Textures/Texture_Player.jpg", "Player");
	ImageHandler::GetInstance()->AddImage("Content/Textures/Texture_Collectible.jpg", "Collectible");

	mp_Level->Initialize(Vector3D(60, 5, 60), Vector3D(10, 2, 10), "Ground", "Player", "Collectible");

	mp_PhysicsHandler->AddToRegistry(mp_Level->GetForceRegisters());
	mp_PhysicsHandler->AddToRegistry(mp_Level->GetRigidForceRegisters());
	mp_PhysicsHandler->AddGround(mp_Level->GetGround());
	mp_PhysicsHandler->AddRigidBodies(mp_Level->GetRigidBodies());
	mp_PhysicsHandler->AddCollisionObjects(mp_Level->GetCollisionObjects());
	mp_PhysicsHandler->AddContactGenerators(mp_Level->GetContactGenerators());
}

//-----------------------------------------------------------------------------
void GameApp::Start()
{
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

	if (mp_PhysicsHandler != NULL)
	{
		mp_PhysicsHandler->CleanUp();
	}
	delete mp_PhysicsHandler;
	mp_PhysicsHandler = nullptr;

	if (mp_Skybox != NULL)
	{
		mp_Skybox->CleanUp();
	}
	delete mp_Skybox;
	mp_Skybox = nullptr;

	if (mp_Level != NULL)
	{
		mp_Level->CleanUp();
	}
	delete mp_Level;
	mp_Level = nullptr;
}

//-----------------------------------------------------------------------------
void GameApp::Update(float deltaTime, const EditorState* physicsState)
{
	if (!physicsState->GetIsPaused())
	{
		int currentTime = 0;

		while (currentTime < ms_TimeStep)
		{
			mp_PhysicsHandler->Update(deltaTime);
			mp_Level->Update(deltaTime);

			currentTime++;
		}
	}

	mp_Camera->Update(deltaTime);
}

//-----------------------------------------------------------------------------
void GameApp::Draw()
{
	mp_Skybox->Draw();
	mp_Level->Draw();
}

//-----------------------------------------------------------------------------
void GameApp::Reset()
{
	mp_PhysicsHandler->Reset();
	mp_Camera->Reset();
	mp_Level->Reset();

	mp_PhysicsHandler->AddGround(mp_Level->GetGround());
	mp_PhysicsHandler->AddContactGenerators(mp_Level->GetContactGenerators());
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
	mp_Level->HandleKeyPressed(key);
}

//-----------------------------------------------------------------------------
void GameApp::HandleKeyReleased(unsigned char key)
{
	mp_Camera->HandleKeyReleased(key);
	mp_Level->HandleKeyReleased(key);
}
//=============================================================================
