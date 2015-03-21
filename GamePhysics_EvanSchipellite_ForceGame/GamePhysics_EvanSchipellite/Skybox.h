//=============================================================================
//                              Skybox
//
// Written by Evan Schipellite
//
// Renders the Skybox
//=============================================================================
#ifndef SKYBOX_H
#define SKYBOX_H
//=============================================================================
#include <Windows.h>
#include <GL\glew.h>
#include <vector>
#include <stdlib.h>
//=============================================================================
class Skybox
{
private:
	GLuint m_Texture_Front;
	GLuint m_Texture_Back;
	GLuint m_Texture_Top;
	GLuint m_Texture_Bottom;
	GLuint m_Texture_Right;
	GLuint m_Texture_Left;

private:
	void loadTexture(std::string texturePath, GLuint* texture);

public:
	Skybox();
	~Skybox();

	void Initialize(std::string frontPath, std::string backPath, std::string topPath, std::string bottomPath, std::string rightPath, std::string leftPath);
	void CleanUp();

	void Draw();
};
//=============================================================================
#endif // SKYBOX_H