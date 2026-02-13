#include "cbase.h"
#include "vgui_exitwindow.h"
using namespace vgui;
#include <vgui/IVGui.h>
#include "vgui_controls/Frame.h"
#include "vgui_controls/Button.h"
#include "vgui_controls/Label.h"
#include <vgui_WindowBackground.h>

ExitWindow::ExitWindow( vgui::VPANEL parent ) : BaseClass(NULL, "ExitWindow")
{
	
	//LoadControlSettings("resource/ui/ExitWindow.res");

	float sizeX = ( int )XRES2( 700 );
	float sizeY = ( int )YRES2( 400 );

	SetTitle("Q U I T   G A M E", true);
	SetSize( sizeX, sizeY );

	MakeNewFrame(true, FRAME_POPUPWINDOW);
	SetKeyBoardInputEnabled(true);
	SetMouseInputEnabled(true);
	SetProportional(false);
	SetTitleBarVisible(true);
	SetMinimizeButtonVisible(false);
	SetRoundedCorners(0);
	SetMaximizeButtonVisible(false);
	SetCloseButtonVisible(false);
	SetSizeable(false);
	SetMoveable(false);
	SetVisible(true);
	MoveToCenterOfScreen();

	//vgui::ivgui()->AddTickSignal(GetVPanel(), 100);

	m_pQuit = vgui::SETUP_PANEL(new vgui::Button(this, "QuitButton", "Yes", this, "quit"));
	m_pQuit->MakeNewButton( true, Button::ButtonType::BUTTON_NORMALWINDOW );
	m_pQuit->SetSize(XRES2(75), YRES2(50));
	m_pQuit->SetContentAlignment(vgui::Label::Alignment::a_center);
	m_pQuit->SetFont( AlteDinDynamic );
	m_pQuit->SetPaintBorderEnabled(false);
	m_pQuit->SetPaintEnabled(true);
	m_pQuit->SetPos(sizeX - XRES2(240), sizeY - YRES2(95));
	m_pQuit->SetButtonActivationType(vgui::Button::ActivationType_t::ACTIVATE_ONRELEASED);

	m_pCancel = vgui::SETUP_PANEL(new vgui::Button(this, "CancelButton", "No", this, "cancel"));
	m_pCancel->SetSize(XRES2(75), YRES2(50));
	m_pCancel->MakeNewButton(true, Button::ButtonType::BUTTON_NORMALWINDOW);
	m_pCancel->SetContentAlignment(vgui::Label::Alignment::a_center);
	m_pCancel->SetFont( AlteDinDynamic );
	m_pCancel->SetPaintBorderEnabled(false);
	m_pCancel->SetPaintEnabled(true);
	m_pCancel->SetPos(sizeX - XRES2(125), sizeY - YRES2(95));
	m_pCancel->SetButtonActivationType(vgui::Button::ActivationType_t::ACTIVATE_ONRELEASED);

	m_pLabel = vgui::SETUP_PANEL( new vgui::Label( this, "Label", "Are you sure you wan't to quit Project R?" ) );
	m_pLabel->SetSize( sizeX, YRES2(150));
	m_pLabel->SetContentAlignment( vgui::Label::Alignment::a_northwest );
	m_pLabel->SetFont( AlteDinDynamic );
	m_pLabel->SetPaintBorderEnabled( false );
	m_pLabel->SetPaintEnabled( true );
	m_pLabel->SetPos( 0, YRES2(110) );
	m_pLabel->SetTextInset( XRES2(50), 0 );

	MoveToFront();
}

ExitWindow::~ExitWindow()
{
	delete m_pQuit;
	delete m_pCancel;
	delete m_pLabel;
	delete this;
}

void ExitWindow::PaintBackground()
{
	SetBgColor(Color(40, 40, 40, 255));
	BaseClass::PaintBackground();
}

void ExitWindow::OnThink()
{
	BaseClass::OnThink();

	if ( m_bIsOepn )
		MoveToFront();
}

void ExitWindow::OnCommand(const char* pcCommand)
{
	BaseClass::OnCommand(pcCommand);
	
	if (!Q_stricmp(pcCommand, "quit"))
	{
		engine->ClientCmd("quit");
	}

	if (!Q_stricmp(pcCommand, "cancel"))
	{
		Close();
		backgroundwindow->Destroy();
	}
}
