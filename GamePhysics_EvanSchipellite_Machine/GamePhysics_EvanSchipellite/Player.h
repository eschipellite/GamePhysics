//=============================================================================
//                              Player
//
// Written by Evan Schipellite
//
// Contains Player Object and Player Values
//=============================================================================
#ifndef PLAYER_H
#define PLAYER_H
//=============================================================================
#include "GameObject.h"
//=============================================================================
class Player :
	public GameObject
{
private:
	bool m_Move_Forward;
	bool m_Move_Backward;
	bool m_Move_Left;
	bool m_Move_Right;
	bool m_Move_Up;
	bool m_CanJump;

	float m_Speed;
	float m_JumpSpeed;

private:
	void checkInput();

public:
	Player();
	~Player();

	void Initialize(Vector3D initialPosition, std::string textureID, float speed = 10, float jumpSpeed = 10);
	void Draw();
	void Update(float deltaTime);
	void Reset();

	void HandleKeyPressed(unsigned char key);
	void HandleKeyReleased(unsigned char key);

	void GroundCollision();
};
//=============================================================================
#endif // PLAYER_H

