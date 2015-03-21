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
class PhysicsObject;
class Collectible;
class ContactGenerator;
//=============================================================================
class Level
{
private:
	Ground* mp_Ground;
	Player* mp_Player;

	std::vector<Collectible*> mp_CollectibleObjects;

	std::vector<ContactGenerator*> mp_ContactGenerators;

private:
	void drawCollectibles();
	void updateCollectibles(float deltaTime);
	void resetCollectibles();

	std::vector<ForceRegister> getCollectibleForceRegisters();
	std::vector<PhysicsObject*> getCollectibleCollisionObjects();

public:
	Level();
	~Level();

	void Initialize(Vector3D dimensions, std::string groundTexture, Vector3D playerPosition, std::string playerTexture, std::string collectibleTexture);
	void CleanUp();
	void Draw();
	void Update(float deltaTime);
	void Reset();

	std::vector<ForceRegister> GetForceRegisters();

	PhysicsObject* GetGround();
	std::vector<PhysicsObject*> GetCollisionObjects();

	std::vector<ContactGenerator*> GetContactGenerators();
};
//=============================================================================
#endif // LEVEL_H

