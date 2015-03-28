//=============================================================================
//                              GameApp
//
// Written by Evan Schipellite
//
// Holds all GameApp functionality
//=============================================================================
#ifndef GAMEAPP_H
#define GAMEAPP_H
//=============================================================================
#include "Camera.h"
#include "EditorState.h"
#include "PhysicsHandler.h"
#include "PlanetHandler.h"
#include "GL\glui.h"

class Skybox;
class Level;
//=============================================================================
class GameApp
{
private:
	Camera* mp_Camera;

	PhysicsHandler* mp_PhysicsHandler;
	Skybox* mp_Skybox;

	Level* mp_Level;

	static float ms_TimeStep;

	int m_FocusIndex;

public:
	GameApp();
	~GameApp();

	void Initialize();
	void Start();
	void CleanUp();
	void Update(float deltaTime, const EditorState* physicsState);
	void Draw();
	void Reset();

	void UpdateScreenSize(Vector3D screnSize);

	void HandleMouse(Vector3D mousePosition);
	void HandleKeyPressed(unsigned char key);
	void HandleKeyReleased(unsigned char key);
};
//=============================================================================
#endif // GAMEAPP_H

