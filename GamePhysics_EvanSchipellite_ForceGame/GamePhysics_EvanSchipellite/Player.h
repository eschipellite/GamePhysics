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
public:
	Player();
	~Player();

	void Initialize(Vector3D initialPosition, std::string texture);
	void Draw();
};
//=============================================================================
#endif // PLAYER_H

