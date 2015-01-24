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
#include "PhysicsObject.h"
#include "FireworkLauncher.h"
//=============================================================================
class GameApp
{
private:
	Camera* mp_Camera;

	PhysicsObject* mp_PhysicsObject;
	FireworkLauncher* mp_FireworkLauncher;

public:
	GameApp();
	~GameApp();

	void Initialize();
	void Start();
	void CleanUp();
	void Update(int deltaTime, const EditorState* physicsState);
	void Draw();
	void Reset();

	void UpdateScreenSize(Vector3D screnSize);

	void HandleMouse(Vector3D mousePosition);
	void HandleKeyPressed(unsigned char key);
	void HandleKeyReleased(unsigned char key);
};
//=============================================================================
#endif // GAMEAPP_H

