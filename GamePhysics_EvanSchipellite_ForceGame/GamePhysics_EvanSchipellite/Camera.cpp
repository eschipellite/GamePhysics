//=============================================================================
//                              Camera
//
// Written by Evan Schipellite
//
// Handle translation, rotation, and calculations for viewing
//=============================================================================
#define _USE_MATH_DEFINES

#include "Camera.h"
#include "GL\glut.h"
#include <math.h>
#include "PhysicsObject.h"
//=============================================================================
Camera::Camera()
{
	m_Position = Vector3D();
	m_LastMousePosition = Vector3D();
	m_Rotation = Vector3D();
	m_ScreenSize = Vector3D();

	m_InitialPosition = Vector3D();
	m_InitialRotation = Vector3D();
	
	m_Move_Forward = false;
	m_Move_Backward = false;
	m_Move_Left = false;
	m_Move_Right = false;

	m_Move_Up = false;
	m_Move_Down = false;

	m_MouseSpeed = 1.0f / 10.0f;
	m_CameraSpeed = 3.0f / 10.0f;

	m_DistanceFromFollowObject = 0;
}

//-----------------------------------------------------------------------------
Camera::~Camera()
{
}

//-----------------------------------------------------------------------------
void Camera::freeMove()
{
	Vector3D radianRotation = Vector3D((float)(m_Rotation.X / 180 * M_PI), (float)(m_Rotation.Y / 180 * M_PI));

	if (m_Move_Forward && !m_Move_Backward)
	{
		m_Position.X += float(sin(radianRotation.Y)) * m_CameraSpeed;
		m_Position.Y -= float(sin(radianRotation.X)) * m_CameraSpeed;
		m_Position.Z -= float(cos(radianRotation.Y)) * m_CameraSpeed;
	}
	else if (m_Move_Backward && !m_Move_Forward)
	{
		m_Position.X -= float(sin(radianRotation.Y)) * m_CameraSpeed;
		m_Position.Y += float(sin(radianRotation.X)) * m_CameraSpeed;
		m_Position.Z += float(cos(radianRotation.Y)) * m_CameraSpeed;
	}

	if (m_Move_Left && !m_Move_Right)
	{
		m_Position.X -= float(cos(radianRotation.Y)) * m_CameraSpeed;
		m_Position.Z -= float(sin(radianRotation.Y)) * m_CameraSpeed;
	}
	else if (m_Move_Right && !m_Move_Left)
	{
		m_Position.X += float(cos(radianRotation.Y)) * m_CameraSpeed;
		m_Position.Z += float(sin(radianRotation.Y)) * m_CameraSpeed;
	}

	if (m_Move_Up && !m_Move_Down)
	{
		m_Position.Y -= float(sin(radianRotation.X)) * m_CameraSpeed;
	}
	else if (m_Move_Down && !m_Move_Up)
	{
		m_Position.Y += float(sin(radianRotation.X)) * m_CameraSpeed;
	}
}

//-----------------------------------------------------------------------------
void Camera::followMove()
{
	if (mp_FollowObject)
	{
		m_Position = m_CurrentPosition;
		m_Rotation = Vector3D(90.0f, 0, 0);
		m_Position.Y = mp_FollowObject->GetPosition().Y + m_DistanceFromFollowObject;
	}
}

//-----------------------------------------------------------------------------
void Camera::CleanUp()
{

}

//-----------------------------------------------------------------------------
void Camera::Initialize(Vector3D initialPosition, Vector3D initialRotation)
{
	m_InitialPosition = initialPosition;
	m_Position = m_InitialPosition;

	m_InitialRotation = initialRotation;
	m_Rotation = m_InitialRotation;

	m_LastMousePosition = Vector3D(142, 300); // Center of window

	PhysicsObject::Initialize(1, initialPosition, Vector3D::Zero, Vector3D::Zero, Vector3D::Zero, .99f);
}

//-----------------------------------------------------------------------------
void Camera::Update(float deltaTime)
{
	PhysicsObject::Update(deltaTime);

	if (m_ShouldFollowObject)
	{
		followMove();
	}
	else
	{
		freeMove();
	}

	glLoadIdentity();
	glRotatef(m_Rotation.X, 1.0, 0.0, 0.0);
	glRotatef(m_Rotation.Y, 0.0, 1.0, 0.0);
	glTranslated(-m_Position.X, -m_Position.Y, -m_Position.Z);

	m_LastMousePosition = Vector3D((float)(int)((m_ScreenSize.X / 2.0f)), (float)(int)((m_ScreenSize.Y / 2.0f)));
}

//-----------------------------------------------------------------------------
void Camera::Reset()
{
	m_Position = m_InitialPosition;
	m_Rotation = m_InitialRotation;

	PhysicsObject::Reset();
}

//-----------------------------------------------------------------------------
void Camera::UpdateScreenSize(Vector3D screenSize)
{
	m_ScreenSize = screenSize;
}

//-----------------------------------------------------------------------------
void Camera::HandleKeyPressed(unsigned char key)
{
	switch (key)
	{
	case ('w') :
		m_Move_Forward = true;
		break;
	case ('s') :
		m_Move_Backward = true;
		break;
	case ('d') :
		m_Move_Right = true;
		break;
	case ('a') :
		m_Move_Left = true;
		break;
	case ('q') :
		m_Move_Up = true;
		break;
	case ('e') :
		m_Move_Down = true;
		break;
	case ('`') :
		Reset();
		break;
	}
}

//-----------------------------------------------------------------------------
void Camera::HandleKeyReleased(unsigned char key)
{
	switch (key)
	{
	case ('w') :
		m_Move_Forward = false;
		break;
	case ('s') :
		m_Move_Backward = false;
		break;
	case ('d') :
		m_Move_Right = false;
		break;
	case ('a') :
		m_Move_Left = false;
		break;
	case ('q') :
		m_Move_Up = false;
		break;
	case ('e') :
		m_Move_Down = false;
		break;
	}
}

//-----------------------------------------------------------------------------
void Camera::HandleMouse(Vector3D mousePosition)
{
	Vector3D difference = mousePosition - m_LastMousePosition;
	m_LastMousePosition = mousePosition;
	m_Rotation.X = m_Rotation.X + difference.Y * m_MouseSpeed;
	m_Rotation.Y = m_Rotation.Y + difference.X * m_MouseSpeed;
}

//-----------------------------------------------------------------------------
void Camera::SetFollowObject(PhysicsObject* followObject, float distanceFromFollowObject)
{
	mp_FollowObject = followObject;
	m_DistanceFromFollowObject = distanceFromFollowObject;
	ToggleShouldFollow(true);
}

//-----------------------------------------------------------------------------
void Camera::ToggleShouldFollow(bool toggle)
{
	m_ShouldFollowObject = toggle;
}
//=============================================================================
