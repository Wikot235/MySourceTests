#include "cbase.h"
#include "vgui_WindowBackground.h"
#include <vgui/IVGui.h>
#include <vgui_controls/Frame.h>

using namespace vgui;

WindowBackground::WindowBackground(vgui::VPANEL parent) : BaseClass(NULL, "WindowBackground")
{
	SetParent(parent);
	SetKeyBoardInputEnabled(false);
	SetMouseInputEnabled(true);
	SetProportional(false);
	SetTitleBarVisible(false);
	SetMinimizeButtonVisible(false);
	SetRoundedCorners(0);
	SetMaximizeButtonVisible(false);
	SetCloseButtonVisible(false);
	SetSizeable(false);
	SetMoveable(false);
	SetVisible(true);

	SetPos(0, 0);
	SetSize(ScreenWidth(), ScreenHeight());
}

void WindowBackground::PaintBackground()
{
	SetBgColor(Color(0, 0, 0, 125));
	BaseClass::PaintBackground();
}

void WindowBackground::OnThink()
{
	BaseClass::OnThink();
}

void WindowBackground::OnCommand(const char* pcCommand)
{
	BaseClass::OnCommand(pcCommand);
}


class CWindowBackgroundInterface : public IWindowBackground
{
private:
	WindowBackground* WindowBackground_;
public:
	CWindowBackgroundInterface()
	{
		WindowBackground_ = NULL;
	}
	void Create(vgui::VPANEL parent)
	{
		WindowBackground_ = new WindowBackground(parent);
	}
	void Destroy()
	{
		if (WindowBackground_)
		{
			WindowBackground_->SetParent((vgui::Panel*)NULL);
			delete WindowBackground_;
		}
	}
};
static CWindowBackgroundInterface g_windowbackground;
IWindowBackground* backgroundwindow = (IWindowBackground*)&g_windowbackground;
