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
void handleKeyPressed(unsigned char key, int x, int y);
void handleKeyReleased(unsigned char key, int x, int y);
void display();
void reshape(int w, int h);
void updateScreenSize();
//=============================================================================
const unsigned int FPS = 60;
const double MILLISECONDS = 1000.0;
const double FRAME_TIME = MILLISECONDS / FPS;

const unsigned int KEY_ESCAPE = 27;

const Vector3D INITIAL_SCREEN_SIZE = Vector3D(720, 720);
const Vector3D INITIAL_WINDOW_POSITION = Vector3D(210, 30);
//=============================================================================
int g_StartTime;
int g_CurrentFrame;

int g_Angle;

bool g_FullScreen;

Vector3D g_ScreenSize = INITIAL_SCREEN_SIZE;

GameApp* gp_GameApp;
//=============================================================================
int main(int argc, char** argv) 
{
	gp_GameApp = new GameApp();

	glutInit(&argc, argv);
	initialize();

	return 0;
}

//-----------------------------------------------------------------------------
void initialize()
{
	g_StartTime = glutGet(GLUT_ELAPSED_TIME);
	g_CurrentFrame = 0;
	g_Angle = 0;
	g_FullScreen = false;

	glutInitWindowSize((int)INITIAL_SCREEN_SIZE.X, (int)INITIAL_SCREEN_SIZE.Y);
	glutInitWindowPosition((int)INITIAL_WINDOW_POSITION.X, (int)INITIAL_WINDOW_POSITION.Y);
	glutCreateWindow("GamePhysics_EvanSchipellite");\

	float lightPosition[] = { 100.0, 100.0, 100.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glutSetCursor(GLUT_CURSOR_NONE);

	gp_GameApp->Initialize();
	updateScreenSize();

	atexit(cleanUp);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMotionFunc(handleMouse);
	glutPassiveMotionFunc(handleMouse);
	glutKeyboardFunc(handleKeyPressed);
	glutIgnoreKeyRepeat(1);
	glutKeyboardUpFunc(handleKeyReleased);
	glutReshapeFunc(reshape);

	SetCursorPos((int)(g_ScreenSize.X / 2.0f), (int)(g_ScreenSize.Y / 2.0f));

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
	g_Angle = (g_Angle + 1) % 360;

	gp_GameApp->Update();

	glutPostRedisplay();
	g_CurrentFrame++;

	SetCursorPos((int)(g_ScreenSize.X / 2.0f), (int)(g_ScreenSize.Y / 2.0f));
}

//--------------------------------------------------------------------------------
void updateScreenSize()
{
	RECT windowRect;
	HWND mainWindowHandle = FindWindow(NULL, "GamePhysics_EvanSchipellite");
	GetWindowRect(mainWindowHandle, &windowRect);

	g_ScreenSize.X = (float)glutGet(GLUT_WINDOW_WIDTH);
	g_ScreenSize.Y = (float)glutGet(GLUT_WINDOW_HEIGHT);
	gp_GameApp->UpdateScreenSize(Vector3D(g_ScreenSize.X, g_ScreenSize.Y, 0));
}

//-----------------------------------------------------------------------------
void handleMouse(int x, int y)
{
	gp_GameApp->HandleMouse(Vector3D((float)x + glutGet(GLUT_WINDOW_X), (float)y + glutGet(GLUT_WINDOW_Y)));
}

//-----------------------------------------------------------------------------
void handleKeyPressed(unsigned char key, int x, int y)
{
	gp_GameApp->HandleKeyPressed(key);

	if (key == KEY_ESCAPE)
	{
		exit(0);
	}

	if (key == 'f')
	{
		if (!g_FullScreen)
		{
			glutFullScreen();
		}
		else
		{
			glutReshapeWindow((int)INITIAL_SCREEN_SIZE.X, (int)INITIAL_SCREEN_SIZE.Y);
			glutPositionWindow((int)INITIAL_WINDOW_POSITION.X, (int)INITIAL_WINDOW_POSITION.X);
		}

		updateScreenSize();
		g_FullScreen = !g_FullScreen;
	}
}

//-----------------------------------------------------------------------------
void handleKeyReleased(unsigned char key, int x, int y)
{
	gp_GameApp->HandleKeyReleased(key);
}

//-----------------------------------------------------------------------------
void display()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glRotatef((float)g_Angle, 0, .45f, .45f);
	glutSolidCube(1);
	glPopMatrix();

	glutSwapBuffers();
}

//-----------------------------------------------------------------------------
void reshape(int w, int h) 
{
	updateScreenSize();

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.1f, 100.0);
	glMatrixMode(GL_MODELVIEW);

}
//=============================================================================