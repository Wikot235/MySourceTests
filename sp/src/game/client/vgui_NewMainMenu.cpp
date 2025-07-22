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

class CMainMenu: public Frame
{
public:

	DECLARE_CLASS_SIMPLE( CMainMenu, Frame );

	CMainMenu( VPANEL parent );
	~CMainMenu();

	void InitializeButton( int order, const char* ButtonName, const char* Text, const char* Command, Button*& ButtonPointer );

	virtual void OnThink();

	void IsMouseOver( Button* button );

	bool IsWindowOpen;

protected:
	virtual void OnCommand( const char* pcCommand );
	virtual void PaintBackground();

private:
	VPANEL GameUIPanel = enginevgui->GetPanel( PANEL_GAMEUIDLL );

	vgui::Button* m_pBeginMissionButton;
	vgui::Button* m_pLoadGameButton;
	vgui::Button* m_pSettingsButton;
	vgui::Button* m_pExitButton;

	vgui::Button* m_pResumeButton;
	vgui::Button* m_pDisconnectButton;

	vgui::ImagePanel* m_pLogoPanel;

	bool IsInGame;
};


CMainMenu::CMainMenu( vgui::VPANEL parent ): BaseClass( NULL, "NewMainMenu" )
{
	SetParent( parent );

	IsWindowOpen = false;

	SetKeyBoardInputEnabled( true );
	SetMouseInputEnabled( true );

	SetProportional( false );
	SetTitleBarVisible( false );
	SetMinimizeButtonVisible( false );

	SetRoundedCorners( 0 );
	SetMaximizeButtonVisible( false );
	SetCloseButtonVisible( false );

	SetSizeable( false );
	SetMoveable( false );
	SetVisible( true );

	SetPos( XRES2(100), YRES2(0) );
	SetSize( ScreenWidth(), ScreenHeight() );

	m_pLogoPanel = SETUP_PANEL( new ImagePanel( this, "LogoPanel" ) );
	m_pLogoPanel->SetImage( "D:\\Program Files\\Steam\\steamapps\\sourcemods\\ProjectR\\materials\\vgui\\ProjRLogo.vtf" );
	m_pLogoPanel->SetPos( XRES2(100), YRES2(500) );

	C_BasePlayer* pPlayer = C_BasePlayer::GetLocalPlayer();

	if ( pPlayer )
	{
		InitializeButton( 1, "ResumeGame", "R E S U M E   G A M E", "resumegame", m_pResumeButton );
		InitializeButton( 2, "LoadButton", "L O A D   S A V E", "loadsave", m_pLoadGameButton );
		InitializeButton( 3, "SettingsButton", "S E T T I N G S", "settings", m_pSettingsButton );
		InitializeButton( 4, "DisconnectButton", "B A C K   T O   M A I N   M E N U ", "disconnect", m_pDisconnectButton );
		InitializeButton( 5, "ExitButton", "Q U I T", "quit", m_pExitButton );
		IsInGame = true;
	}
	else
	{
		InitializeButton( 1, "BeginMission", "B E G I N   M I S S I O N", "beginmission", m_pBeginMissionButton );
		InitializeButton( 2, "LoadButton", "L O A D   S A V E", "loadsave", m_pLoadGameButton );
		InitializeButton( 3, "SettingsButton", "S E T T I N G S", "settings", m_pSettingsButton );
		InitializeButton( 4, "ExitButton", "Q U I T", "quit", m_pExitButton );
		IsInGame = false;
	}
}

CMainMenu::~CMainMenu()
{

}


void CMainMenu::InitializeButton( int order, const char* ButtonName, const char* Text, const char* Command, vgui::Button*& ButtonPointer )
{
	ButtonPointer = vgui::SETUP_PANEL( new vgui::Button( this, ButtonName, Text, this, Command ) );
	ButtonPointer->MakeNewButton( true, vgui::Button::ButtonType::BUTTON_MAINMENU );
	ButtonPointer->SetSize( XRES2(500), YRES2(45) );
	ButtonPointer->SetTextInset( XRES2(30), 0 );
	ButtonPointer->SetFont( AlteDinDynamic );
	ButtonPointer->SetPaintBorderEnabled( false );
	ButtonPointer->SetPaintEnabled( true );
	ButtonPointer->SetPos( 0, YRES2((45 + (65 * order) ) + 500) );
	ButtonPointer->SetButtonActivationType( vgui::Button::ActivationType_t::ACTIVATE_ONRELEASED );
	ButtonPointer->SetArmedSound( "MainMenu\\ClickSmall.wav" );
}

void CMainMenu::OnThink()
{
	BaseClass::OnThink();
}

/*
void CMainMenu::IsMouseOver( vgui::Button* button )
{
	if ( button->IsCursorOver() )

		button->SetBgColor( Color( 0, 0, 0, 125 ) );
	else
		button->SetBgColor( Color( 0, 0, 0, 0 ) );
}
*/

void CMainMenu::OnCommand( const char* pcCommand )
{
	if ( !Q_stricmp( pcCommand, "beginmission" ) )
	{
		//engine->ClientCmd( "gamemenucommand opennewgamedialog" );
		engine->ClientCmd( "map testmap01" );
	}
	else if ( !Q_stricmp( pcCommand, "loadsave" ) )
	{
		engine->ClientCmd( "gamemenucommand openloadgamedialog" );
	}
	else if ( !Q_stricmp( pcCommand, "settings" ) )
	{
		engine->ClientCmd( "gamemenucommand openoptionsdialog" );
	}
	else if ( !Q_stricmp( pcCommand, "disconnect" ) )
	{
		engine->ClientCmd( "gamemenucommand disconnect" );
	}
	else if ( !Q_stricmp( pcCommand, "resumegame" ) )
	{
		engine->ClientCmd( "gamemenucommand resumegame" );
	}
	else if ( !Q_stricmp( pcCommand, "quit" ) )
	{
		backgroundwindow->Create( GameUIPanel );
		exitwindow->Create( GameUIPanel );
	}

	BaseClass::OnCommand( pcCommand );
}

void CMainMenu::PaintBackground()
{
	SetBgColor( Color( 0, 0, 0, 0 ) );
	BaseClass::PaintBackground();
}


class CMainMenuInterface: public IMainMenu
{
private:
	CMainMenu* MainMenu;
public:
	CMainMenuInterface()
	{
		MainMenu = NULL;
	}
	void Create( vgui::VPANEL parent )
	{
		MainMenu = new CMainMenu( parent );
	}
	void Destroy()
	{
		if ( MainMenu )
		{
			MainMenu->SetParent( ( vgui::Panel* )NULL );
			delete MainMenu;
		}
	}
};
static CMainMenuInterface g_MainMenu;
IMainMenu* mainmenu = ( IMainMenu* )&g_MainMenu;
