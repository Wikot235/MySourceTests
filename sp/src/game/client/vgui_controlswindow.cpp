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
#include "vgui_controlswindow.h"

#include <vgui_basepanel.h>

#include "ienginevgui.h"

#include "tier0/memdbgon.h"

using namespace vgui;

ControlsWindow::ControlsWindow(vgui::VPANEL parent) : BaseClass(NULL, "ControlsWindow")
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

	int sizeX = XRES2(700);
	int sizeY = XRES2(700);

	SetSize(sizeX, sizeY);
	MoveToCenterOfScreen();

	SetTitle("C O N T R O L S", true);

	m_pSensEntry = new vgui::TextEntry(this, "SensEntry");
	m_pSensEntry->SetSize(XRES2(75), YRES2(50));
	m_pSensEntry->SetBgColor(Color(32, 32, 32, 255));
	m_pSensEntry->SetPos(sizeX - XRES2(125), YRES2(115));
	m_pSensEntry->SetPaintBorderEnabled(0);
	m_pSensEntry->SetFont(AlteDinDynamic);

	m_pSensLabel = new vgui::Label(this, "SensLabel", "Mouse sensitivity");
	m_pSensLabel->SetFont(AlteDinDynamic);
	m_pSensLabel->SetSize(XRES2(300), YRES2(30));
	m_pSensLabel->SetPos(XRES2(50), YRES2(115 + 11));

	m_pSensSlider = new vgui::Slider(this, "SensSlider");
	m_pSensSlider->SetDragOnRepositionNob(true);
	m_pSensSlider->SetRange(1, 100);
	m_pSensSlider->SetSize(XRES2(250), YRES2(30));
	m_pSensSlider->SetPos(XRES2(300), YRES2(115 + 11));
	m_pSensSlider->SetPaintBorderEnabled(0);

	m_pInvertButton = new ToggleButton(this, "InvertButton", Checks(2));
	m_pInvertButton->SetYesNoOnly(true);
	m_pInvertButton->SetSize(XRES2(75), YRES2(50));
	m_pInvertButton->SetPos(sizeX - XRES2(125), YRES2(115 + 75));
	m_pInvertButton->SetPaintBorderEnabled(0);
	m_pInvertButton->SetFont(AlteDinDynamic);
	m_pInvertButton->SetContentAlignment(Label::a_center);
	m_pInvertButton->SetCommand("InvertMouseButton");

	m_pInvertLabel = new vgui::Label(this, "InvertLabel", "Invert Y axis");
	m_pInvertLabel->SetFont(AlteDinDynamic);
	m_pInvertLabel->SetSize(XRES2(300), YRES2(30));
	m_pInvertLabel->SetPos(XRES2(50), YRES2(115 + 10 + 75));

	m_pRawInputButton = new ToggleButton(this, "RawInputButton", Checks(3));
	m_pRawInputButton->SetYesNoOnly(true);
	m_pRawInputButton->SetSize(XRES2(75), YRES2(50));
	m_pRawInputButton->SetPos(sizeX - XRES2(125), YRES2(115 + 150));
	m_pRawInputButton->SetPaintBorderEnabled(0);
	m_pRawInputButton->SetFont(AlteDinDynamic);
	m_pRawInputButton->SetContentAlignment(Label::a_center);
	m_pRawInputButton->SetCommand("RawInputButton");

	m_pRawInputLabel = new vgui::Label(this, "InvertLabel", "Raw mouse input");
	m_pRawInputLabel->SetFont(AlteDinDynamic);
	m_pRawInputLabel->SetSize(XRES2(300), YRES2(30));
	m_pRawInputLabel->SetPos(XRES2(50), YRES2(115 + 10 + 150));

	m_pMouseFilterLabel = new vgui::Label(this, "FilterLabel", "Mouse Filter");
	m_pMouseFilterLabel->SetFont(AlteDinDynamic);
	m_pMouseFilterLabel->SetSize(XRES2(300), YRES2(30));
	m_pMouseFilterLabel->SetPos(XRES2(50), YRES2(115 + 10 + 225));

	m_pMouseFilter = new ToggleButton(this, "FilterButton", "No");
	m_pMouseFilter->SetYesNoOnly(true);
	m_pMouseFilter->SetSize(XRES2(75), YRES2(50));
	m_pMouseFilter->SetPos(sizeX - XRES2(125), YRES2(115 + 225));
	m_pMouseFilter->SetPaintBorderEnabled(0);
	m_pMouseFilter->SetFont(AlteDinDynamic);
	m_pMouseFilter->SetContentAlignment(Label::a_center);

	m_pBack = vgui::SETUP_PANEL(new vgui::Button(this, "CancelButton", "Back", this, "Back"));
	m_pBack->SetSize(XRES2(75), YRES2(50));
	m_pBack->MakeNewButton(true, Button::ButtonType::BUTTON_NORMALWINDOW);
	m_pBack->SetContentAlignment(vgui::Label::Alignment::a_center);
	m_pBack->SetFont(AlteDinDynamic);
	m_pBack->SetPaintBorderEnabled(false);
	m_pBack->SetPaintEnabled(true);
	m_pBack->SetPos(sizeX - XRES2(75) - XRES2(50), sizeY - YRES2(95));
	m_pBack->SetButtonActivationType(vgui::Button::ActivationType_t::ACTIVATE_ONRELEASED);

	Divider2 = vgui::SETUP_PANEL(new Panel(this));
	Divider2->SetSize(XRES2(372), YRES2(4));
	Divider2->SetPos(XRES2(180), YRES2(213));
	Divider2->SetBgColor(Color(75, 75, 75, 255));

	Divider3 = vgui::SETUP_PANEL(new Panel(this));
	Divider3->SetSize(XRES2(326), YRES2(4));
	Divider3->SetPos(XRES2(225), YRES2(288));
	Divider3->SetBgColor(Color(75, 75, 75, 255));

	MoveToFront();
}

ControlsWindow::~ControlsWindow()
{

}

void ControlsWindow::PaintBackground()
{
	SetBgColor(Color(40, 40, 40, 255));
	BaseClass::PaintBackground();
}

void ControlsWindow::OnThink()
{
	BaseClass::OnThink();
	if (m_bIsOepn)
		MoveToFront();
}

const char* ControlsWindow::Checks(int whatisit)
{
	switch (whatisit)
	{
	case 2:
		if (ConVarRef("m_pitch").GetFloat() < 0)
			//It's inverted
			return "Yes";
		else
			//It's not inverted
			return "No";

	case 3:
		if (ConVarRef("m_rawinput").GetFloat() == 1)
			return "Yes";
		else
			return "No";

	default:
		return "NDF";
	}
	
}

void ControlsWindow::OnCommand(const char* pcCommand)
{
	BaseClass::OnCommand(pcCommand);

	if (!Q_stricmp(pcCommand, "Back"))
	{
		Close();
		VPANEL GameUIPanel = enginevgui->GetPanel(PANEL_GAMEUIDLL);
		SettingsWindow* settingswindow = new SettingsWindow(GameUIPanel);
	}
	else if (!Q_stricmp(pcCommand, "InvertMouseButton"))
	{
		float YawNew = ConVarRef("m_pitch").GetFloat() * -1;
		char Buffer[32];
		snprintf(Buffer, sizeof(Buffer), "m_pitch %f", YawNew);

		engine->ClientCmd(Buffer);
	}
	else if (!Q_stricmp(pcCommand, "RawInputButton"))
	{
		int YawNew = ConVarRef("m_rawinput").GetInt() * -1;
		char Buffer[32];
		snprintf(Buffer, sizeof(Buffer), "m_rawinput %c", YawNew);

		engine->ClientCmd(Buffer);
	}
}
