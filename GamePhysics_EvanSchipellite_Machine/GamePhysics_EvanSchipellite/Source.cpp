//=============================================================================
//                              Source
//
// Written by Evan Schipellite
//
// Source Contents for OpenGL
//=============================================================================
#include <iostream>
#include <Windows.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include "GameApp.h"
#include "GL/glui.h"
#include "EditorState.h"
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include "GlutTime.h"

using namespace std;
//=============================================================================
void initialize();
void start();
void cleanUp();
void idle();
void update(float deltaTime);
void handleMouse(int x, int y);
void handleKeyPressed(unsigned char key, int x, int y);
void handleKeyReleased(unsigned char key, int x, int y);
void handleMouseUI(int mouseButton, int state, int x, int y);
void display();
void reshape(int w, int h);
void updateScreenSize();
void reset();
void play();
void pause();
void stop();

void eh_HandleUI(int buttonID);
//=============================================================================
const unsigned int KEY_ESCAPE = 27;
const unsigned int KEY_ENTER = 13;

const Vector3D INITIAL_SCREEN_SIZE = Vector3D(720, 720);
const Vector3D INITIAL_WINDOW_POSITION = Vector3D(210, 30);

const unsigned int ID_PLAY = 0;
const unsigned int ID_PAUSE = 1;
const unsigned int ID_STOP = 2;
//=============================================================================
int g_CurrentFrame;
int g_TimeBase;

Vector3D g_ScreenSize = INITIAL_SCREEN_SIZE;

int g_MainWindow;

GameApp* gp_GameApp;
EditorState* gp_EditorState;

GLUI* g_GluiSubWindow;
GLUI_StaticText* g_StaticText;
GLUI_StaticText* g_FPSText;

GlutTime* gp_GlutTime;
//=============================================================================
int main(int argc, char** argv) 
{
	gp_GameApp = new GameApp();
	gp_EditorState = new EditorState();

	glutInit(&argc, argv);
	initialize();

	return 0;
}

//-----------------------------------------------------------------------------
void initialize()
{
	srand(static_cast<unsigned int>(time(NULL)));

	g_TimeBase = glutGet(GLUT_ELAPSED_TIME);
	g_CurrentFrame = 0;

	gp_GlutTime = new GlutTime();
	gp_GlutTime->Init();

	glutInitWindowSize((int)INITIAL_SCREEN_SIZE.X, (int)INITIAL_SCREEN_SIZE.Y);
	glutInitWindowPosition((int)INITIAL_WINDOW_POSITION.X, (int)INITIAL_WINDOW_POSITION.Y);
	g_MainWindow =glutCreateWindow("GamePhysics_EvanSchipellite");

	glewInit();

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
	glutKeyboardFunc(handleKeyPressed);
	glutKeyboardUpFunc(handleKeyReleased);
	GLUI_Master.set_glutReshapeFunc(reshape);

	g_GluiSubWindow = GLUI_Master.create_glui_subwindow(g_MainWindow, GLUI_SUBWINDOW_BOTTOM);
	g_GluiSubWindow->set_main_gfx_window(g_MainWindow);
	g_GluiSubWindow->add_button("Play", ID_PLAY, eh_HandleUI);
	g_GluiSubWindow->add_button("Pause", ID_PAUSE, eh_HandleUI);
	g_GluiSubWindow->add_button("Reset", ID_STOP, eh_HandleUI);
	g_StaticText = g_GluiSubWindow->add_statictext("Playing");
	g_StaticText->set_alignment(GLUI_ALIGN_RIGHT);
	g_GluiSubWindow->add_column();
	g_FPSText = g_GluiSubWindow->add_statictext("FPS: 0");

	SetCursorPos((int)(g_ScreenSize.X / 2.0f), (int)(g_ScreenSize.Y / 2.0f));

	start();

	glutSetWindow(g_MainWindow);
	glutMainLoop();
}

//-----------------------------------------------------------------------------
void start()
{
	gp_GameApp->Start();
	stop();
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
	int time = glutGet(GLUT_ELAPSED_TIME);

	if (gp_GlutTime->UpdateTime())
	{
		g_CurrentFrame++;
		update(gp_GlutTime->GetDeltaTime());
		gp_GlutTime->IncrementFrame();
	}

	if (time - g_TimeBase > 1000)
	{
		std::ostringstream out;
		out << "FPS: " << g_CurrentFrame;
		std::string fpsString = out.str();
		g_FPSText->set_text(fpsString.c_str());
		g_TimeBase = time;
		g_CurrentFrame = 0;
	}
}

//-----------------------------------------------------------------------------
void update(float deltaTime)
{
	gp_GameApp->Update(deltaTime, gp_EditorState);

	glutPostRedisplay();

	if (!gp_EditorState->GetIsMouseActive())
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
	if (!gp_EditorState->GetIsMouseActive())
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
		if (!gp_EditorState->GetIsFullScreen())
		{
			glutFullScreen();
		}
		else
		{
			glutReshapeWindow((int)INITIAL_SCREEN_SIZE.X, (int)INITIAL_SCREEN_SIZE.Y);
			glutPositionWindow((int)INITIAL_WINDOW_POSITION.X, (int)INITIAL_WINDOW_POSITION.X);
		}

		updateScreenSize();
		gp_EditorState->SetIsFullScreen(!gp_EditorState->GetIsFullScreen());
	}

	if (key == KEY_ENTER)
	{
		if (!gp_EditorState->GetIsMouseActive())
		{	
			glutSetCursor(GLUT_CURSOR_INHERIT);
		}
		else
		{
			glutSetCursor(GLUT_CURSOR_NONE);
		}

		SetCursorPos((int)(g_ScreenSize.X / 2.0f) + glutGet(GLUT_WINDOW_X), (int)(g_ScreenSize.Y / 2.0f) + glutGet(GLUT_WINDOW_Y));
		gp_EditorState->SetIsMouseActive(!gp_EditorState->GetIsMouseActive());
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

	gp_GameApp->Draw();

	glutSwapBuffers();
}

//-----------------------------------------------------------------------------
void reshape(int w, int h) 
{
	updateScreenSize();

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.1f, 150.0);
	glMatrixMode(GL_MODELVIEW);
}

//-----------------------------------------------------------------------------
void eh_HandleUI(int buttonUI)
{
	switch (buttonUI)
	{
	case ID_PLAY:
		play();
		break;
	case ID_PAUSE:
		pause();
		break;
	case ID_STOP:
		stop();
		break;
	}
}

//-----------------------------------------------------------------------------
void reset()
{
	gp_GameApp->Reset();
}

//-----------------------------------------------------------------------------
void play()
{
	gp_EditorState->SetIsPaused(false);
	g_StaticText->set_text("Playing");
}

//-----------------------------------------------------------------------------
void pause()
{
	gp_EditorState->SetIsPaused(true);
	g_StaticText->set_text("Paused");
}

//-----------------------------------------------------------------------------
void stop()
{
	gp_EditorState->SetIsPaused(true);
	g_StaticText->set_text("Stopped");
	reset();
}
//=============================================================================