//=============================================================================
//                              Level
//
// Written by Evan Schipellite
//
// Manages physics objects within the level
//=============================================================================
#include "Level.h"
#include "Vector3D.h"
#include "Ground.h"
#include "Player.h"
#include <vector>
#include "PhysicsHandler.h"
//=============================================================================
Level::Level()
{
	mp_Ground = new Ground();
	mp_Player = new Player();
}

//-----------------------------------------------------------------------------
Level::~Level()
{
}

//-----------------------------------------------------------------------------
void Level::Initialize(Vector3D dimensions, std::string groundTexture, Vector3D playerPosition, std::string playerTexture)
{
	mp_Ground->Initialize(dimensions, 1, Vector3D::Zero, groundTexture);
	mp_Player->Initialize(playerPosition, playerTexture);
}

//-----------------------------------------------------------------------------
void Level::CleanUp()
{
	if (mp_Player != NULL)
	{
		mp_Player->CleanUp();
	}
	delete mp_Player;
	mp_Player = nullptr;

	if (mp_Ground != NULL)
	{
		mp_Ground->CleanUp();
	}
	delete mp_Ground;
	mp_Ground = nullptr;
}

//-----------------------------------------------------------------------------
void Level::Draw()
{
	mp_Ground->Draw();
	mp_Player->Draw();
}

//-----------------------------------------------------------------------------
void Level::Update(float deltaTime)
{
	mp_Ground->Update(deltaTime);
	mp_Player->Update(deltaTime);
}

//-----------------------------------------------------------------------------
void Level::Reset()
{
	mp_Ground->Reset();
	mp_Player->Reset();
}

//-----------------------------------------------------------------------------
std::vector<ForceRegister> Level::GetForceRegisters()
{
	std::vector<ForceRegister> forceRegisters;

	forceRegisters.push_back(ForceRegister(GeneratorType::EARTH_GRAVITY_GENERATOR, mp_Player));

	return forceRegisters;
}
//=============================================================================
