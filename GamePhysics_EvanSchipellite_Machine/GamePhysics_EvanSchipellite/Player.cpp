//=============================================================================
//                              Player
//
// Written by Evan Schipellite
//
// Contains Player Object and Player Values
//=============================================================================
#include "Player.h"
#include "GameApp.h"
//=============================================================================
Player::Player()
{
	m_Move_Forward = false;
	m_Move_Backward = false;
	m_Move_Left = false;
	m_Move_Right = false;
	m_Move_Up = false;
	m_CanJump = false;
}

//-----------------------------------------------------------------------------
Player::~Player()
{
}

//-----------------------------------------------------------------------------
void Player::checkInput()
{
	if (m_Move_Forward)
	{
		AddForce(Vector3D(0, 0, -m_Speed));
	}

	if (m_Move_Backward)
	{
		AddForce(Vector3D(0, 0, m_Speed));
	}

	if (m_Move_Left)
	{
		AddForce(Vector3D(-m_Speed, 0, 0));
	}

	if (m_Move_Right)
	{
		AddForce(Vector3D(m_Speed, 0, 0));
	}

	if (m_Move_Up && m_CanJump)
	{
		m_CanJump = false;
		AddForce(Vector3D(0, m_JumpSpeed, 0));
	}
}

//-----------------------------------------------------------------------------
void Player::Initialize(Vector3D initialPosition, std::string textureID, float speed, float jumpSpeed)
{
	PhysicsObject::Initialize(1, initialPosition, Vector3D(0, 0, 0), Vector3D::Zero, Vector3D::Zero, .9999f);

	loadTexture(textureID);

	m_Speed = speed;
	m_JumpSpeed = jumpSpeed;
}

//-----------------------------------------------------------------------------
void Player::Draw()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	gluQuadricTexture(m_Quad, m_Texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	gluQuadricDrawStyle(m_Quad, GLU_FILL);
	gluQuadricTexture(m_Quad, GL_TRUE);
	gluQuadricNormals(m_Quad, GLU_SMOOTH);

	glPushMatrix();
	glTranslatef(m_CurrentPosition.X, m_CurrentPosition.Y, m_CurrentPosition.Z);
	gluSphere(m_Quad, m_Radius, 36, 36);

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

//-----------------------------------------------------------------------------
void Player::Update(float deltaTime)
{
	checkInput();

	GameObject::Update(deltaTime);
}

//-----------------------------------------------------------------------------
void Player::Reset()
{
	GameObject::Reset();

	m_Move_Forward = false;
	m_Move_Backward = false;
	m_Move_Left = false;
	m_Move_Right = false;
	m_Move_Up = false;
	m_CanJump = false;
}

//-----------------------------------------------------------------------------
void Player::HandleKeyPressed(unsigned char key)
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
	case (32) :
		m_Move_Up = true;
		break;
	}
}

//-----------------------------------------------------------------------------
void Player::HandleKeyReleased(unsigned char key)
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
	case (32) :
		m_Move_Up = false;
		break;
	}
}

//-----------------------------------------------------------------------------
void Player::GroundCollision()
{
	m_CanJump = true;
}
//=============================================================================
