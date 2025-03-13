#include "cbase.h"
#include "vgui_NewMainMenu.h"

#include "vgui_controls/Frame.h"
#include <vgui/ISurface.h>
#include <vgui/IVGui.h>
#include <vgui/IInput.h>

#include "vgui_controls/Button.h"
#include "vgui_controls/ImagePanel.h"
#include <vgui_basepanel.h>

#include "tier0/memdbgon.h"


using namespace vgui;

//CMainMenu class: Tutorial example class
class CMainMenu : public vgui::Frame
{
public:

    DECLARE_CLASS_SIMPLE(CMainMenu, vgui::Frame);

    CMainMenu(vgui::VPANEL parent);
    ~CMainMenu() {};

	virtual void OnThink();

protected:
	virtual void OnCommand(const char* pcCommand);
	virtual void PaintBackground();

private:
	vgui::Button* m_pExitButton;
	vgui::Panel* m_pExitBg;
	vgui::RichText* m_pExitText;



	vgui::HFont m_pHFontAlteDin;
};



CMainMenu::CMainMenu(vgui::VPANEL parent) : BaseClass(NULL, "NewMainMenu")
{
	SetParent(parent);

	vgui::HScheme scheme = vgui::scheme()->LoadSchemeFromFile("resource/SourceScheme.res", "SourceScheme");

	SetScheme(scheme);

	m_pHFontAlteDin = vgui::scheme()->GetIScheme(scheme)->GetFont("AlteDin1451");

	LoadControlSettings("resource/ui/NewMainMenu.res");

	SetKeyBoardInputEnabled(true);
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

	vgui::ivgui()->AddTickSignal(GetVPanel(), 100);
	
	m_pExitBg = vgui::SETUP_PANEL(new vgui::Panel(this, "ExitBg"));
	m_pExitBg->SetSize(500, 45);
	m_pExitBg->SetPaintEnabled(true);
	m_pExitBg->SetBgColor(Color(0, 0, 0, 0));
	m_pExitBg->SetPos(0, 0);

	m_pExitButton = vgui::SETUP_PANEL(new vgui::Button(this, "ExitButton", "E X I T"));
	m_pExitButton->SetSize(500, 45);
	m_pExitButton->SetTextInset(30, 0);
	m_pExitButton->SetFont(m_pHFontAlteDin);
	m_pExitButton->SetPaintBorderEnabled(false);
	m_pExitButton->SetPaintEnabled(true);
	m_pExitButton->SetPos(0, 0);
	m_pExitButton->SetBlink(false);
	m_pExitButton->ForceDepressed(false);
	//m_pExitButton->SetButtonActivationType(vgui::Button::ActivationType_t::ACTIVATE_ONRELEASED);

	m_pExitButton->SetCommand("quit");
	m_pExitButton->OnCommand("quit");

	//m_pExitText = new RichText(this, "RichText");

}

void CMainMenu::OnThink()
{
	BaseClass::OnThink();

	//int Cursor_x, Cursor_y;
	//vgui::input()->GetCursorPos(Cursor_x, Cursor_y);

	if (m_pExitButton->IsCursorOver())
		m_pExitBg->SetBgColor(Color(0, 0, 0, 125));
	else
		m_pExitBg->SetBgColor(Color(0, 0, 0, 0));
}

void CMainMenu::OnCommand(const char* pcCommand)
{

	if (pcCommand == "quit")
	{
		engine->ClientCmd("quit");
		engine->ServerCmd("quit");
	}
	else
	{
		BaseClass::OnCommand(pcCommand);
	}
}

void CMainMenu::PaintBackground()
{
	SetBgColor(Color(0, 0, 0, 0));
	BaseClass::PaintBackground();
}



class CMainMenuInterface : public IMainMenu
{
private:
	CMainMenu* MainMenu;
public:
	CMainMenuInterface()
	{
		MainMenu = NULL;
	}
	void Create(vgui::VPANEL parent)
	{
		MainMenu = new CMainMenu(parent);
	}
	void Destroy()
	{
		if (MainMenu)
		{
			MainMenu->SetParent((vgui::Panel*)NULL);
			delete MainMenu;
		}
	}
};
static CMainMenuInterface g_MainMenu;
IMainMenu* mainmenu = (IMainMenu*)&g_MainMenu;
