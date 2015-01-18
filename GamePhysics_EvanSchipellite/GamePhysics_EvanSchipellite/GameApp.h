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
//=============================================================================
class GameApp
{
private:
	Camera* mp_Camera;

public:
	GameApp();
	~GameApp();

	void Initialize();
	void CleanUp();
	void Update();

	void UpdateScreenSize(Vector3D screnSize);

	void HandleMouse(Vector3D mousePosition);
	void HandleKeyPressed(unsigned char key);
	void HandleKeyReleased(unsigned char key);
};
//=============================================================================
#endif // GAMEAPP_H

