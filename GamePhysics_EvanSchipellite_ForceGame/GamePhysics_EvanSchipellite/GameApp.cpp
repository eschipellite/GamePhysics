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
void GameApp::updateText()
{
	std::string playerVelocity = convertVector3DToString(mp_Level->GetPlayer()->GetCurrentVelocity());
	std::string playerVelocityText = "Player Velocity: " + playerVelocity;
	mp_PlayerVelocityText->set_text(playerVelocityText.c_str());
	std::string objectsCollected = "Objects Collected: " + convertFloatToString((float)mp_Level->GetObjectsCollected());
	mp_ObjectsCollectedText->set_text(objectsCollected.c_str());
	std::string collisions = "Collisions: " + convertFloatToString((float)mp_PhysicsHandler->GetCollisions());
	mp_CollisionText->set_text(collisions.c_str());
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
	mp_Camera->SetFollowObject(mp_Level->GetPlayer(), 25);

	mp_Level->Initialize(Vector3D(60, 5, 60), "Content/Textures/Texture_Grass.jpg", Vector3D(0, 2, 0), "Content/Textures/Texture_Player.jpg", "Content/Textures/Texture_Collectible.jpg");

	mp_PhysicsHandler->AddToRegistry(mp_Level->GetForceRegisters());
	mp_PhysicsHandler->AddGround(mp_Level->GetGround());
	mp_PhysicsHandler->AddCollisionObjects(mp_Level->GetCollisionObjects());
	mp_PhysicsHandler->AddContactGenerators(mp_Level->GetContactGenerators());
	mp_PhysicsHandler->AddToRegistry(new BungeeForceGenerator(mp_Level->GetPlayer(), 5, 1), mp_Camera);
	mp_PhysicsHandler->AddCollisionObject(mp_Camera);
}

//-----------------------------------------------------------------------------
void GameApp::SetTextReferences(GLUI_StaticText* playerVelocityText, GLUI_StaticText* objectsCollectedText, GLUI_StaticText* collisionsText)
{
	mp_PlayerVelocityText = playerVelocityText;
	mp_ObjectsCollectedText = objectsCollectedText;
	mp_CollisionText = collisionsText;
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
			mp_Camera->Update(deltaTime);
			mp_PhysicsHandler->Update(deltaTime);
			mp_Level->Update(deltaTime);
			updateText();

			currentTime++;
		}
	}
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
