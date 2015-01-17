//=============================================================================
//                              GameApp
//
// Written by Evan Schipellite
//
// Holds all GameApp functionality
//=============================================================================
#ifndef GAMEAPP_H
#define GAMEAPP_H
//=============================================================================
class GameApp
{
public:
	GameApp();
	~GameApp();

	void Initialize();
	void CleanUp();
	void Update();
};
//=============================================================================
#endif // GAMEAPP_H

