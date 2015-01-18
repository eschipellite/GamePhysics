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
#include "GL/glui.h"

using namespace std;
//=============================================================================
void initialize();
void cleanUp();
void idle();
void update();
void handleMouse(int x, int y);
void handleKeyPressed(unsigned char key, int x, int y);
void handleKeyReleased(unsigned char key, int x, int y);
void handleMouseUI(int mouseButton, int state, int x, int y);
void display();
void reshape(int w, int h);
void updateScreenSize();

void eh_HandleUI(int buttonID);
//=============================================================================
const unsigned int FPS = 60;
const double MILLISECONDS = 1000.0;
const double FRAME_TIME = MILLISECONDS / FPS;

const unsigned int KEY_ESCAPE = 27;
const unsigned int KEY_SPACE = 32;

const Vector3D INITIAL_SCREEN_SIZE = Vector3D(720, 720);
const Vector3D INITIAL_WINDOW_POSITION = Vector3D(210, 30);

const unsigned int ID_PLAY = 0;
const unsigned int ID_PAUSE = 1;
const unsigned int ID_STOP = 2;
//=============================================================================
int g_StartTime;
int g_CurrentFrame;

int g_Angle;

bool g_FullScreen;
bool g_MouseActive;

Vector3D g_ScreenSize = INITIAL_SCREEN_SIZE;

int g_MainWindow;

GameApp* gp_GameApp;

GLUI* g_GluiSubWindow;
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
	g_MouseActive = false;

	glutInitWindowSize((int)INITIAL_SCREEN_SIZE.X, (int)INITIAL_SCREEN_SIZE.Y);
	glutInitWindowPosition((int)INITIAL_WINDOW_POSITION.X, (int)INITIAL_WINDOW_POSITION.Y);
	g_MainWindow =glutCreateWindow("GamePhysics_EvanSchipellite"); \

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
	GLUI_Master.set_glutIdleFunc(idle);
	GLUI_Master.set_glutMouseFunc(handleMouseUI);
	glutMotionFunc(handleMouse);
	glutPassiveMotionFunc(handleMouse);
	GLUI_Master.set_glutKeyboardFunc(handleKeyPressed);
	glutIgnoreKeyRepeat(1);
	glutKeyboardUpFunc(handleKeyReleased);
	GLUI_Master.set_glutReshapeFunc(reshape);

	g_GluiSubWindow = GLUI_Master.create_glui_subwindow(g_MainWindow, GLUI_SUBWINDOW_BOTTOM);
	g_GluiSubWindow->set_main_gfx_window(g_MainWindow);
	g_GluiSubWindow->add_button("Play", ID_PLAY, eh_HandleUI);
	g_GluiSubWindow->add_button("Pause", ID_PAUSE, eh_HandleUI);
	g_GluiSubWindow->add_button("Stop", ID_STOP, eh_HandleUI);

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
	glutSetWindow(g_MainWindow);

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

	if (!g_MouseActive)
	{
		SetCursorPos((int)(g_ScreenSize.X / 2.0f) + glutGet(GLUT_WINDOW_X), (int)(g_ScreenSize.Y / 2.0f) + glutGet(GLUT_WINDOW_Y));
	}
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
	if (!g_MouseActive)
	{
		gp_GameApp->HandleMouse(Vector3D((float)x, (float)y));
	}
}

//-----------------------------------------------------------------------------
void handleMouseUI(int mouseButton, int mouseState, int x, int y)
{

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

	if (key == KEY_SPACE)
	{
		if (!g_MouseActive)
		{	
			glutSetCursor(GLUT_CURSOR_INHERIT);
		}
		else
		{
			glutSetCursor(GLUT_CURSOR_NONE);
		}

		SetCursorPos((int)(g_ScreenSize.X / 2.0f) + glutGet(GLUT_WINDOW_X), (int)(g_ScreenSize.Y / 2.0f) + glutGet(GLUT_WINDOW_Y));
		g_MouseActive = !g_MouseActive;
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

//-----------------------------------------------------------------------------
void eh_HandleUI(int buttonUI)
{

}
//=============================================================================