//=============================================================================
//                              EditorState
//
// Written by Evan Schipellite
//
// Holds application information to be sent to the GameApp each update
//=============================================================================
#ifndef EDITORSTATE_H
#define EDITORSTATE_H
//=============================================================================
class EditorState
{
public:
	bool m_IsPaused;
	bool m_IsFullScreen;
	bool m_IsMouseActive;
public:
	EditorState();
	~EditorState();

	void SetIsPaused(bool isPaused);
	bool GetIsPaused() const;
	void SetIsFullScreen(bool isFullScreen);
	bool GetIsFullScreen() const;
	void SetIsMouseActive(bool isMouseActive);
	bool GetIsMouseActive() const;
};
//=============================================================================
#endif // EDITORSTATE_H

