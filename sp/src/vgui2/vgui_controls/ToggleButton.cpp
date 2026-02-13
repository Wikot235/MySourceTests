//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#include <vgui/KeyCode.h>

#include <vgui_controls/ToggleButton.h>

#include <KeyValues.h>

// memdbgon must be the last include file in a .cpp file!!!
#include <tier0/memdbgon.h>

using namespace vgui;

DECLARE_BUILD_FACTORY_DEFAULT_TEXT( ToggleButton, ToggleButton );

//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
ToggleButton::ToggleButton(Panel *parent, const char *panelName, const char* text) : Button(parent, panelName, text)
{
	YesNoOnly = true;
	SetButtonActivationType(ACTIVATE_ONPRESSED);
}

void ToggleButton::SetYesNoOnly(bool state)
{
	YesNoOnly = state;
}

//-----------------------------------------------------------------------------
// Purpose: Turns double-click into normal click
//-----------------------------------------------------------------------------
void ToggleButton::OnMouseDoublePressed(MouseCode code)
{
	OnMousePressed(code);
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
Color ToggleButton::GetButtonFgColor()
{
	if (IsSelected())
	{
		// highlight the text when depressed
		return _selectedColor;
	}
	else
	{
		return BaseClass::GetButtonFgColor();
	}
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
bool ToggleButton::CanBeDefaultButton(void)
{
    return false;
}

//-----------------------------------------------------------------------------
// Purpose: Toggles the state of the button
//-----------------------------------------------------------------------------
void ToggleButton::DoClick()
{
	if (IsSelected())
	{
		if (!YesNoOnly)
			ForceDepressed(false);
		else
			SetText("Yes");
	}
	else if (!IsSelected())
	{
		if (!YesNoOnly)
			ForceDepressed(true);
		else
			SetText("No");
	}

	SetSelected(!IsSelected());
	FireActionSignal();

	// post a button toggled message
	KeyValues *msg = new KeyValues("ButtonToggled");
	msg->SetInt("state", (int)IsSelected());
	PostActionSignal(msg);
	
	Repaint();
}

void ToggleButton::OnThink()
{
	if (IsCursorOver())
		SetBgColor(Color(51, 51, 51, 255));
	else
		SetBgColor(Color(32, 32, 32, 255));
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void ToggleButton::ApplySchemeSettings(IScheme *pScheme)
{
	BaseClass::ApplySchemeSettings(pScheme);
	_selectedColor = GetSchemeColor("ToggleButton.SelectedTextColor", pScheme);
}

void ToggleButton::OnKeyCodePressed(KeyCode code)
{
    if (code != KEY_ENTER)
    {
        BaseClass::OnKeyCodePressed(code);
    }
}

