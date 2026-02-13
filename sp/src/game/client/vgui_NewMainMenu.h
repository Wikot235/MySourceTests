#if !defined( VGUI_NEWMAINMENU_H )
#define VGUI_NEWMAINMENU_H
#ifdef _WIN32
#pragma once
#endif

class IMainMenu
{
public:
	virtual void		Create(vgui::VPANEL parent) = 0;
	virtual void		Destroy(void) = 0;
};

extern IMainMenu* mainmenu;

#endif