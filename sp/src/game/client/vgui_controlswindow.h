#if !defined( VGUI_CONTROLSWINDOW_H )
#define VGUI_CONTROLSWINDOW_H
#ifdef _WIN32
#pragma once
#endif

#include "vgui_controls/Frame.h"

class ControlsWindow : public vgui::Frame
{
	DECLARE_CLASS_SIMPLE(ControlsWindow, vgui::Frame);

	ControlsWindow(vgui::VPANEL parent);
	~ControlsWindow();

protected:
	virtual void OnThink();
	virtual void OnCommand(const char* pcCommand);
	virtual void PaintBackground();

	const char* Checks(int whatisit);

private:

	vgui::Label* m_pMouseFilterLabel;
	vgui::ToggleButton* m_pMouseFilter;

	vgui::ToggleButton* m_pMouseAccel;
	vgui::Label* m_pMouseAccelLabel;
	vgui::Slider* m_pMouseAccelSlider;

	vgui::TextEntry* m_pSensEntry;
	vgui::Label* m_pSensLabel;
	vgui::Slider* m_pSensSlider;

	vgui::ToggleButton* m_pInvertButton;
	vgui::Label* m_pInvertLabel;

	vgui::ToggleButton* m_pRawInputButton;
	vgui::Label* m_pRawInputLabel;

	vgui::Button* m_pBack;

	vgui::Panel* Divider1;
	vgui::Panel* Divider2;
	vgui::Panel* Divider3;
	vgui::Panel* Divider4;
	vgui::Panel* Divider5;
	vgui::Panel* Divider6;

	vgui::Button* m_pQuit;
	vgui::Button* m_pCancel;

	vgui::Label* m_pLabel;
};
#endif
