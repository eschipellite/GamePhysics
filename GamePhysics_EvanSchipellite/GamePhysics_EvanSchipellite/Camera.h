//=============================================================================
//                              Camera
//
// Written by Evan Schipellite
//
// Handle translation, rotation, and calculations for viewing
//=============================================================================
#ifndef CAMERA_H
#define CAMERA_H
//=============================================================================
#include "Vector3D.h"
//=============================================================================
class Camera
{
private:
	Vector3D m_Position;
	Vector3D m_LastMousePosition;
	Vector3D m_Rotation;
	Vector3D m_ScreenSize;

	bool m_Move_Forward;
	bool m_Move_Backward;
	bool m_Move_Left;
	bool m_Move_Right;

	bool m_Move_Up;
	bool m_Move_Down;

	float m_MouseSpeed;
	float m_CameraSpeed;

private:
	void move();

public:
	Camera();
	~Camera();
	
	void CleanUp();
	void Initialize(Vector3D initialPosition = Vector3D(0, 0, 0));
	void Update();

	void UpdateScreenSize(Vector3D screenSize);

	void HandleKeyPressed(unsigned char key);
	void HandleKeyReleased(unsigned char key);
	void HandleMouse(Vector3D mousePosition);
};
//=============================================================================
#endif // CAMERA_H

