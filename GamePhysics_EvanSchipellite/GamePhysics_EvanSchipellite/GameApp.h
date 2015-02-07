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
//=============================================================================
class GameApp
{
private:
	Camera* mp_Camera;

	PhysicsHandler* mp_PhysicsHandler;
	PlanetHandler* mp_PlanetHandler;

	static float ms_TimeStep;

private:
	void setFocus(unsigned char key);

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

