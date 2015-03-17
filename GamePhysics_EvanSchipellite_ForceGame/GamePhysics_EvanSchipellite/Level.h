//=============================================================================
//                              Level
//
// Written by Evan Schipellite
//
// Manages physics objects within the level
//=============================================================================
#ifndef LEVEL_H
#define LEVEL_H
//=============================================================================
#include <iostream>
#include <vector>

class Ground;
class Player;
class Vector3D;
class ForceRegister;
//=============================================================================
class Level
{
private:
	Ground* mp_Ground;
	Player* mp_Player;

public:
	Level();
	~Level();

	void Initialize(Vector3D dimensions, std::string groundTexture, Vector3D playerPosition, std::string playerTexture);
	void CleanUp();
	void Draw();
	void Update(float deltaTime);
	void Reset();

	std::vector<ForceRegister> GetForceRegisters();
};
//=============================================================================
#endif // LEVEL_H

