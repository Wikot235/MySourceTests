#include "cbase.h"

#include "vgui_WindowBackground.h"

#include "vgui_controls/AnimationController.h"

#include "vgui_controls/Frame.h"
#include <vgui/ISurface.h>
#include <vgui/IVGui.h>
#include <vgui/IInput.h>

#include "vgui_controls/Button.h"
#include "vgui_controls/ImagePanel.h"
#include "vgui_controls/TextEntry.h"
#include "vgui_controls/ToggleButton.h"
#include "vgui_controls/Divider.h"
#include "vgui_controls/Slider.h"

#include "vgui_settingswindow.h"
#include <vgui_controlswindow.h>

#include <vgui_basepanel.h>

#include "ienginevgui.h"

#include "tier0/memdbgon.h"

using namespace vgui;

SettingsWindow::SettingsWindow(vgui::VPANEL parent) : BaseClass(NULL, "SettingsWindow")
{
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

	//vgui::ivgui()->AddTickSignal(GetVPanel(), 100);

	InitButtons();

	MoveToFront();
}

SettingsWindow::~SettingsWindow()
{
	delete m_pGeneral;
	delete m_pControls;
	delete m_pGraphics;
	delete m_pSounds;

	delete m_pBack;
	delete this;
}

void SettingsWindow::PaintBackground()
{
	SetBgColor(Color(40, 40, 40, 255));
	BaseClass::PaintBackground();
}

void SettingsWindow::InitButtons()
{
	SetTitle("S E T T I N G S", true);

	sizeX = (int)XRES2(700);
	sizeY = (int)YRES2(525);

	SetSize(sizeX, sizeY);
	MoveToCenterOfScreen();

	m_pGeneral = vgui::SETUP_PANEL(new vgui::Button(this, "General", "General", this, "General"));
	m_pGeneral->MakeNewButton(true, Button::ButtonType::BUTTON_NORMALWINDOW);
	m_pGeneral->SetSize(sizeX - XRES2(100), YRES2(50));
	m_pGeneral->SetTextInset(XRES2(30), 0);
	m_pGeneral->SetContentAlignment(vgui::Label::Alignment::a_west);
	m_pGeneral->SetFont(AlteDinDynamic);
	m_pGeneral->SetPaintBorderEnabled(false);
	m_pGeneral->SetPaintEnabled(true);
	m_pGeneral->SetPos(XRES2(50), YRES2(110));
	m_pGeneral->SetButtonActivationType(vgui::Button::ActivationType_t::ACTIVATE_ONRELEASED);

	m_pControls = vgui::SETUP_PANEL(new vgui::Button(this, "Controls", "Controls", this, "Controls"));
	m_pControls->MakeNewButton(true, Button::ButtonType::BUTTON_NORMALWINDOW);
	m_pControls->SetSize(sizeX - XRES2(100), YRES2(50));
	m_pControls->SetTextInset(XRES2(30), 0);
	m_pControls->SetContentAlignment(vgui::Label::Alignment::a_west);
	m_pControls->SetFont(AlteDinDynamic);
	m_pControls->SetPaintBorderEnabled(false);
	m_pControls->SetPaintEnabled(true);
	m_pControls->SetPos(XRES2(50), YRES2(110 + 75));
	m_pControls->SetButtonActivationType(vgui::Button::ActivationType_t::ACTIVATE_ONRELEASED);

	m_pGraphics = vgui::SETUP_PANEL(new vgui::Button(this, "Graphics", "Graphics", this, "Graphics"));
	m_pGraphics->MakeNewButton(true, Button::ButtonType::BUTTON_NORMALWINDOW);
	m_pGraphics->SetSize(sizeX - XRES2(100), YRES2(50));
	m_pGraphics->SetTextInset(XRES2(30), 0);
	m_pGraphics->SetContentAlignment(vgui::Label::Alignment::a_west);
	m_pGraphics->SetFont(AlteDinDynamic);
	m_pGraphics->SetPaintBorderEnabled(false);
	m_pGraphics->SetPaintEnabled(true);
	m_pGraphics->SetPos(XRES2(50), YRES2(110 + 150));
	m_pGraphics->SetButtonActivationType(vgui::Button::ActivationType_t::ACTIVATE_ONRELEASED);

	m_pSounds = vgui::SETUP_PANEL(new vgui::Button(this, "Sounds", "Sounds", this, "Sounds"));
	m_pSounds->MakeNewButton(true, Button::ButtonType::BUTTON_NORMALWINDOW);
	m_pSounds->SetSize(sizeX - XRES2(100), YRES2(50));
	m_pSounds->SetTextInset(XRES2(30), 0);
	m_pSounds->SetContentAlignment(vgui::Label::Alignment::a_west);
	m_pSounds->SetFont(AlteDinDynamic);
	m_pSounds->SetPaintBorderEnabled(false);
	m_pSounds->SetPaintEnabled(true);
	m_pSounds->SetPos(XRES2(50), YRES2(110 + 225));
	m_pSounds->SetButtonActivationType(vgui::Button::ActivationType_t::ACTIVATE_ONRELEASED);

	m_pBack = vgui::SETUP_PANEL(new vgui::Button(this, "CancelButton", "Back", this, "Back"));
	m_pBack->SetSize(XRES2(75), YRES2(50));
	m_pBack->MakeNewButton(true, Button::ButtonType::BUTTON_NORMALWINDOW);
	m_pBack->SetContentAlignment(vgui::Label::Alignment::a_center);
	m_pBack->SetFont(AlteDinDynamic);
	m_pBack->SetPaintBorderEnabled(false);
	m_pBack->SetPaintEnabled(true);
	m_pBack->SetPos(sizeX - XRES2(75) - XRES2(50), sizeY - YRES2(95));
	m_pBack->SetButtonActivationType(vgui::Button::ActivationType_t::ACTIVATE_ONRELEASED);
}

void SettingsWindow::OnThink()
{
	BaseClass::OnThink();

	if ( m_bIsOepn )
		MoveToFront();
}

void SettingsWindow::OnCommand(const char* pcCommand)
{
	BaseClass::OnCommand(pcCommand);

	if (!Q_stricmp(pcCommand, "General"))
	{
		Close();
	}

	VPANEL GameUIPanel = enginevgui->GetPanel( PANEL_GAMEUIDLL );

	if (!Q_stricmp(pcCommand, "Controls"))
	{
		Close();
		ControlsWindow* controlswindow = new ControlsWindow(GameUIPanel);
	}

	if (!Q_stricmp(pcCommand, "Back"))
	{
		Close();
		backgroundwindow->Destroy();
	}

}
