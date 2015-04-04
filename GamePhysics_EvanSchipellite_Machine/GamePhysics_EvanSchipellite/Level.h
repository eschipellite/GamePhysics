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

class ForceGenerator;
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

	std::vector<ForceGenerator*> mp_ForceGenerators;
	std::vector<ContactGenerator*> mp_ContactGenerators;

	std::string m_CollectibleTexture;

private:
	void createLevel();
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

	PhysicsObject* GetGround();
	PhysicsObject* GetPlayer();
	std::vector<PhysicsObject*> GetCollisionObjects();

	std::vector<ForceRegister> GetForceRegisters();
	std::vector<ContactGenerator*> GetContactGenerators();

	void HandleKeyPressed(unsigned char key);
	void HandleKeyReleased(unsigned char key);

	int GetObjectsCollected();
};
//=============================================================================
#endif // LEVEL_H

