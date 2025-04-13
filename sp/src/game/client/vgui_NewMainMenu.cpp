#include "cbase.h"

#include "vgui_NewMainMenu.h"
#include "vgui_exitwindow.h"
#include "vgui_WindowBackground.h"

#include "vgui_controls/AnimationController.h"

#include "vgui_controls/Frame.h"
#include <vgui/ISurface.h>
#include <vgui/IVGui.h>
#include <vgui/IInput.h>

#include "vgui_controls/Button.h"
#include "vgui_controls/ImagePanel.h"
#include <vgui_basepanel.h>

#include "ienginevgui.h"

#include "tier0/memdbgon.h"

using namespace vgui;

class CMainMenu : public vgui::Frame
{
public:

    DECLARE_CLASS_SIMPLE(CMainMenu, vgui::Frame);

    CMainMenu(vgui::VPANEL parent);
	~CMainMenu();

	//void InitializeButton(int x, int y, const char* ButtonName, const char* Text, const char* Command, vgui::Button*& ButtonPointer);

	virtual void OnThink();

	void IsMouseOver(vgui::Button* button);

	bool IsWindowOpen;

protected:
	virtual void OnCommand(const char* pcCommand);
	virtual void PaintBackground();
	//void InitializeButton(int x, int y, const char ButtonName, const char Text, const char Command, vgui::Button*& ButtonPointer);

private:
	VPANEL GameUIPanel = enginevgui->GetPanel(PANEL_GAMEUIDLL);

	vgui::Button* m_pExitButton;
	vgui::Button* m_pSettingsButton;
	vgui::Button* m_pLoadGameButton;
	vgui::Button* m_pBeginMissionButton;
};


CMainMenu::CMainMenu(vgui::VPANEL parent) : BaseClass(NULL, "NewMainMenu")
{
	SetParent(parent);

	LoadControlSettings("resource/ui/NewMainMenu.res");

	IsWindowOpen = false;

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
	SetPos(460, 500);
	SetSize(500, 300);

	vgui::ivgui()->AddTickSignal(GetVPanel(), 100);

	m_pBeginMissionButton = vgui::SETUP_PANEL(new vgui::Button(this, "BeginMission", "B E G I N   M I S S I O N", this, "beginmission"));
	m_pBeginMissionButton->SetSize(500, 45);
	m_pBeginMissionButton->SetTextInset(30, 0);
	m_pBeginMissionButton->SetFont(m_pHFontAlteDin);
	m_pBeginMissionButton->SetPaintBorderEnabled(false);
	m_pBeginMissionButton->SetPaintEnabled(true);
	m_pBeginMissionButton->SetPos(0, 255 - 65 * 3);
	m_pBeginMissionButton->SetButtonActivationType(vgui::Button::ActivationType_t::ACTIVATE_ONRELEASED);

	m_pLoadGameButton = vgui::SETUP_PANEL(new vgui::Button(this, "LoadButton", "L O A D   S A V E", this, "loadsave"));
	m_pLoadGameButton->SetSize(500, 45);
	m_pLoadGameButton->SetTextInset(30, 0);
	m_pLoadGameButton->SetFont(m_pHFontAlteDin);
	m_pLoadGameButton->SetPaintBorderEnabled(false);
	m_pLoadGameButton->SetPaintEnabled(true);
	m_pLoadGameButton->SetPos(0, 255 - 65 * 2);
	m_pLoadGameButton->SetButtonActivationType(vgui::Button::ActivationType_t::ACTIVATE_ONRELEASED);

	m_pSettingsButton = vgui::SETUP_PANEL(new vgui::Button(this, "SettingsButton", "S E T T I N G S", this, "settings"));
	m_pSettingsButton->SetSize(500, 45);
	m_pSettingsButton->SetTextInset(30, 0);
	m_pSettingsButton->SetFont(m_pHFontAlteDin);
	m_pSettingsButton->SetPaintBorderEnabled(false);
	m_pSettingsButton->SetPaintEnabled(true);
	m_pSettingsButton->SetPos(0, 255 - 65);
	m_pSettingsButton->SetButtonActivationType(vgui::Button::ActivationType_t::ACTIVATE_ONRELEASED);

	m_pExitButton = vgui::SETUP_PANEL(new vgui::Button(this, "ExitButton", "Q U I T", this, "quit"));
	m_pExitButton->SetSize(500, 45);
	m_pExitButton->SetTextInset(30, 0);
	m_pExitButton->SetFont(m_pHFontAlteDin);
	m_pExitButton->SetPaintBorderEnabled(false);
	m_pExitButton->SetPaintEnabled(true);
	m_pExitButton->SetPos(0, 255);
	m_pExitButton->SetButtonActivationType(vgui::Button::ActivationType_t::ACTIVATE_ONRELEASED);

}

CMainMenu::~CMainMenu()
{
	delete m_pBeginMissionButton;
	delete m_pLoadGameButton;
	delete m_pSettingsButton;
	delete m_pExitButton;
}

/*
void CMainMenu::InitializeButton(int x, int y, const char* ButtonName, const char* Text, const char* Command, vgui::Button*& ButtonPointer)
{
	ButtonPointer = new vgui::Button(this, ButtonName, ButtonName, this, Command);
	ButtonPointer->SetSize(500, 45);
	ButtonPointer->SetTextInset(30, 0);
	ButtonPointer->SetFont(m_pHFontAlteDin);
	ButtonPointer->SetPaintBorderEnabled(false);
	ButtonPointer->SetPaintEnabled(true);
	ButtonPointer->SetPos(x, y);
	ButtonPointer->SetButtonActivationType(vgui::Button::ACTIVATE_ONRELEASED);
}
*/

void CMainMenu::OnThink()
{
	BaseClass::OnThink();

	IsMouseOver(m_pExitButton);
	IsMouseOver(m_pSettingsButton);
	IsMouseOver(m_pLoadGameButton);
	IsMouseOver(m_pBeginMissionButton);

	//GetAnimationController()->RunAnimationCommand(this, "BgColor", Color(0, 0, 0, 0), 1.f, 2, AnimationController::INTERPOLATOR_LINEAR);

}

void CMainMenu::IsMouseOver(vgui::Button* button)
{
	if (button->IsCursorOver())

		button->SetBgColor(Color(0, 0, 0, 125));
	else
		button->SetBgColor(Color(0, 0, 0, 0));
}

void CMainMenu::OnCommand(const char* pcCommand)
{

	if (!Q_stricmp(pcCommand, "quit"))
	{
		backgroundwindow->Create(GameUIPanel);
		exitwindow->Create(GameUIPanel);
	}

	BaseClass::OnCommand(pcCommand);
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
