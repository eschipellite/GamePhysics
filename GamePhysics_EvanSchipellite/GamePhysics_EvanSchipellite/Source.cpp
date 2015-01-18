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
void handleMouse(int x, int y);
void handleKeyboard(unsigned char key, int x, int y);
void display();
void reshape(int w, int h);
//=============================================================================
const unsigned int FPS = 60;
const double MILLISECONDS = 1000.0;
const double FRAME_TIME = MILLISECONDS / FPS;

const unsigned int KEY_ESCAPE = 27;
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

	float lightPosition[] = { 0.0, 0.0, -10.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//glutSetCursor(GLUT_CURSOR_NONE);

	gp_GameApp->Initialize();

	atexit(cleanUp);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutPassiveMotionFunc(handleMouse);
	glutKeyboardFunc(handleKeyboard);
	glutReshapeFunc(reshape);
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

	//SetCursorPos(GLUT_SCREEN_WIDTH, GLUT_SCREEN_HEIGHT);

	glutPostRedisplay();
	g_CurrentFrame++;
}

//-----------------------------------------------------------------------------
void handleMouse(int x, int y)
{
	gp_GameApp->HandleMouse(Vector3D((float)x, (float)y));
}

//-----------------------------------------------------------------------------
void handleKeyboard(unsigned char key, int x, int y)
{
	gp_GameApp->HandleKeyboard(key);

	if (key == KEY_ESCAPE)
	{
		exit(0);
	}
}

//-----------------------------------------------------------------------------
void display()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glRotatef(1, 0, .45f, .45f);
	
	glutSolidCube(.25);

	glutSwapBuffers();
}

//-----------------------------------------------------------------------------
void reshape(int w, int h) 
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.1f, 100.0);
	glMatrixMode(GL_MODELVIEW);

}
//=============================================================================