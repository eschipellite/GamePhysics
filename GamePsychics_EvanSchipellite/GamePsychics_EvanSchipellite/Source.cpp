//=============================================================================
//                              Source
//
// Written by Evan Schipellite
//
// Source Contents for OpenGL
//=============================================================================
#include <iostream>
#include <Windows.h>
#include <GL/glut.h>
#include "GameApp.h"
using namespace std;
//=============================================================================
void initialize();
void cleanUp();
void idle();
void update();
void display();
//=============================================================================
const unsigned int FPS = 60;
const double MILLISECONDS = 1000.0;
const double FRAME_TIME = MILLISECONDS / FPS;
//=============================================================================
int g_StartTime;
int g_CurrentFrame;

GameApp* gp_GameApp;
//=============================================================================
int main(int argc, char** argv) 
{
	gp_GameApp = new GameApp();

	glutInit(&argc, argv);
	initialize();

	cleanUp();

	return 0;
}

//-----------------------------------------------------------------------------
void initialize()
{
	g_StartTime = glutGet(GLUT_ELAPSED_TIME);
	g_CurrentFrame = 0;

	glutInitWindowSize(720, 720);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("GamePsychics_EvanSchipellite");

	gp_GameApp->Initialize();
	
	atexit(cleanUp);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMainLoop();
}

//-----------------------------------------------------------------------------
void cleanUp()
{
	if (gp_GameApp != NULL)
	{
		gp_GameApp->CleanUp();
	}
	delete gp_GameApp;
	gp_GameApp = NULL;
}

//-----------------------------------------------------------------------------
void idle()
{
	double endFrameTime = g_StartTime + (g_CurrentFrame + 1) * FRAME_TIME;
	double endRenderingTime = glutGet(GLUT_ELAPSED_TIME);
	double idleTime = endFrameTime - endRenderingTime;

	if (idleTime < 0.0)
	{
		update();
	}
}

//-----------------------------------------------------------------------------
void update()
{
	gp_GameApp->Update();

	glutPostRedisplay();
	g_CurrentFrame++;
}

//-----------------------------------------------------------------------------
void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glRotatef(1, 0, 50, 0);
	glutWireCube(1);

	glFlush();
}
//=============================================================================