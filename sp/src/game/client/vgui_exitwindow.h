#if !defined( VGUI_EXITWINDOW_H )
#define VGUI_EXITWINDOW_H
#ifdef _WIN32
#pragma once
#endif

#include "vgui_controls/Frame.h"

class ExitWindow : public vgui::Frame
{
	DECLARE_CLASS_SIMPLE(ExitWindow, vgui::Frame);

	ExitWindow(vgui::VPANEL parent);
	~ExitWindow();

protected:
	virtual void OnThink();
	virtual void OnCommand(const char* pcCommand);
	virtual void PaintBackground();

private:
	vgui::Button* m_pQuit;
	vgui::Button* m_pCancel;

	vgui::Label* m_pLabel;
};
#endif
