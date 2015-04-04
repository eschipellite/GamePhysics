//=============================================================================
//                              EditorState
//
// Written by Evan Schipellite
//
// Holds application information to be sent to the GameApp each update
//=============================================================================
#include "EditorState.h"
//=============================================================================
EditorState::EditorState()
{
	m_IsPaused = false;
	m_IsFullScreen = false;
	m_IsMouseActive = false;
}

//-----------------------------------------------------------------------------
EditorState::~EditorState()
{
}

//-----------------------------------------------------------------------------
void EditorState::SetIsPaused(bool isPaused)
{
	m_IsPaused = isPaused;
}

//-----------------------------------------------------------------------------
bool EditorState::GetIsPaused() const
{
	return m_IsPaused;
}

//-----------------------------------------------------------------------------
void EditorState::SetIsFullScreen(bool isFullScreen)
{
	m_IsFullScreen = isFullScreen;
}

//-----------------------------------------------------------------------------
bool EditorState::GetIsFullScreen() const
{
	return m_IsFullScreen;
}

//-----------------------------------------------------------------------------
void EditorState::SetIsMouseActive(bool isMouseActive)
{
	m_IsMouseActive = isMouseActive;
}

//-----------------------------------------------------------------------------
bool EditorState::GetIsMouseActive() const
{
	return m_IsMouseActive;
}
//=============================================================================
