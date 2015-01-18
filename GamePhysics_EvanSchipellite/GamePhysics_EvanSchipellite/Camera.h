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

	float m_MouseSpeed;
	float m_CameraSpeed;
public:
	Camera();
	~Camera();

	void HandleKey(unsigned char key);
	void HandleMouse(Vector3D mousePosition);
	void Update();
};
//=============================================================================
#endif // CAMERA_H

