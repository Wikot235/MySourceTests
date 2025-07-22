
#include "cbase.h"
/*
#include "vgui_exitwindow.h"
using namespace vgui;
#include <vgui/IVGui.h>
#include "vgui_controls/Frame.h"
#include "vgui_controls/Button.h"
#include "vgui_controls/Label.h"
#include <vgui_WindowBackground.h>

class ExitWindow: public Frame
{
	DECLARE_CLASS_SIMPLE( ExitWindow, Frame );

	ExitWindow( vgui::VPANEL parent );
	~ExitWindow();

protected:
	virtual void OnThink();
	virtual void OnCommand( const char* pcCommand );
	virtual void PaintBackground();

private:
	vgui::Button* m_pQuit;
	vgui::Button* m_pCancel;

	vgui::Label* m_pLabel;
};

ExitWindow::ExitWindow( vgui::VPANEL parent ): BaseClass( NULL, "SettingsWindow" )
{

	SetTitle( "S E T T I N G S", true );

	MakeNewFrame( true, FRAME_POPUPWINDOW );
	SetKeyBoardInputEnabled( true );
	SetMouseInputEnabled( true );
	SetProportional( false );
	SetTitleBarVisible( true );
	SetMinimizeButtonVisible( false );
	SetRoundedCorners( 0 );
	SetMaximizeButtonVisible( false );
	SetCloseButtonVisible( false );
	SetSizeable( false );
	SetMoveable( false );
	SetVisible( true );
	MoveToCenterOfScreen();

	//vgui::ivgui()->AddTickSignal(GetVPanel(), 100);

	m_pQuit = vgui::SETUP_PANEL( new vgui::Button( this, "QuitButton", "Yes", this, "quit" ) );
	m_pQuit->SetSize( 75, 50 );
	m_pQuit->SetContentAlignment( vgui::Label::Alignment::a_center );
	m_pQuit->SetFont( AlteDinDynamic );
	m_pQuit->SetPaintBorderEnabled( false );
	m_pQuit->SetPaintEnabled( true );
	m_pQuit->SetPos( 460, 305 );
	m_pQuit->SetButtonActivationType( vgui::Button::ActivationType_t::ACTIVATE_ONRELEASED );

	m_pCancel = vgui::SETUP_PANEL( new vgui::Button( this, "CancelButton", "No", this, "cancel" ) );
	m_pCancel->SetSize( 75, 50 );
	m_pCancel->SetContentAlignment( vgui::Label::Alignment::a_center );
	m_pCancel->SetFont( AlteDinDynamic );
	m_pCancel->SetPaintBorderEnabled( false );
	m_pCancel->SetPaintEnabled( true );
	m_pCancel->SetPos( 575, 305 );
	m_pCancel->SetButtonActivationType( vgui::Button::ActivationType_t::ACTIVATE_ONRELEASED );

	m_pLabel = vgui::SETUP_PANEL( new vgui::Label( this, "Label", "Are you sure you wan't to quit Project R?" ) );
	m_pLabel->SetSize( 600, 150 );
	m_pLabel->SetContentAlignment( vgui::Label::Alignment::a_northwest );
	m_pLabel->SetFont( AlteDinDynamic );
	m_pLabel->SetPaintBorderEnabled( false );
	m_pLabel->SetPaintEnabled( true );
	m_pLabel->SetPos( 57, 110 );


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
	SetBgColor( Color( 40, 40, 40, 255 ) );
	BaseClass::PaintBackground();
}

void ExitWindow::OnThink()
{
	BaseClass::OnThink();

	if ( m_bIsOepn )
		MoveToFront();

	if ( m_pQuit->IsCursorOver() )
		m_pQuit->SetBgColor( Color( 51, 51, 51, 255 ) );
	else
		m_pQuit->SetBgColor( Color( 32, 32, 32, 255 ) );

	if ( m_pCancel->IsCursorOver() )
		m_pCancel->SetBgColor( Color( 51, 51, 51, 255 ) );
	else
		m_pCancel->SetBgColor( Color( 32, 32, 32, 255 ) );

}

void ExitWindow::OnCommand( const char* pcCommand )
{
	BaseClass::OnCommand( pcCommand );

	if ( !Q_stricmp( pcCommand, "quit" ) )
	{
		engine->ClientCmd( "quit" );
	}

	if ( !Q_stricmp( pcCommand, "cancel" ) )
	{
		Close();
		backgroundwindow->Destroy();
	}
}


class CExitWindowInterface: public IExitWindow
{
private:
	ExitWindow* ExitWindow_;
public:
	CExitWindowInterface()
	{
		ExitWindow_ = NULL;
	}
	void Create( vgui::VPANEL parent )
	{
		ExitWindow_ = new ExitWindow( parent );
	}
	void Destroy()
	{
		if ( ExitWindow_ )
		{
			ExitWindow_->SetParent( ( vgui::Panel* )NULL );
			delete ExitWindow_;
		}
	}
};
static CExitWindowInterface g_exitwindow;
IExitWindow* exitwindow = ( IExitWindow* )&g_exitwindow;
*/
