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
//=============================================================================
class GameApp
{
private:
	GLUI_StaticText* mp_PlanetName;
	GLUI_StaticText* mp_PlanetMass;
	GLUI_StaticText* mp_PlanetVelocity;
	GLUI_StaticText* mp_PlanetAcceleration;
	GLUI_StaticText* mp_TotalPlanetForce;
	Camera* mp_Camera;

	PhysicsHandler* mp_PhysicsHandler;
	PlanetHandler* mp_PlanetHandler;
	Skybox* mp_Skybox;

	static float ms_TimeStep;

	int m_FocusIndex;

private:
	void setFocus(unsigned char key);
	void focusPlanet(int index);
	std::string convertFloatToString(float value);
	std::string convertVector3DToString(Vector3D vector3D);
	void updateFocusPlanetUI();

public:
	GameApp();
	~GameApp();

	void Initialize();
	void SetTextReferences(GLUI_StaticText* planetName, GLUI_StaticText* planetMass, GLUI_StaticText* planetVelocity, GLUI_StaticText* planetAcceleration, GLUI_StaticText* totalPlanetForce);
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

