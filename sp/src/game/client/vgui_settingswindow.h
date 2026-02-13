#include "cbase.h"

#include "vgui_NewMainMenu.h"
#include "vgui_exitwindow.h"

#include "vgui_controls/AnimationController.h"

#include "vgui_controls/Frame.h"
#include <vgui/ISurface.h>
#include <vgui/IVGui.h>
#include <vgui/IInput.h>

#include "vgui_controls/Button.h"
#include "vgui_controls/ImagePanel.h"
#include <vgui_basepanel.h>

#include "ienginevgui.h"

class SettingsWindow : public vgui::Frame
{
	DECLARE_CLASS_SIMPLE(SettingsWindow, vgui::Frame);

	SettingsWindow(vgui::VPANEL parent);
	~SettingsWindow();

public:
	void MsgFunc_ButtonToggled(bf_read& msg);

protected:
	virtual void OnThink();
	virtual void OnCommand(const char* pcCommand);
	virtual void PaintBackground();

	const char* Checks( int whatisit );

	void InitButtons();
	
private:

	//============== M A I N ===============//
	//										//
	vgui::Button* m_pGeneral;
	vgui::Button* m_pControls;
	vgui::Button* m_pGraphics;
	vgui::Button* m_pSounds;
	vgui::Button* m_pBack;
	//										//
	//======================================//

	float sizeX, sizeY;
};
