//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//
//=============================================================================//
//
// Health.cpp
//
// implementation of CHudHealth class
//
#include "cbase.h"
#include "hud.h"
#include "hud_macros.h"
#include "view.h"

#include "iclientmode.h"

#include <KeyValues.h>
#include <vgui/ISurface.h>
#include <vgui/ISystem.h>
#include <vgui_controls/AnimationController.h>

#include <vgui/ILocalize.h>

#include "hudelement.h"
#include "hud_numericdisplay.h"

#include "convar.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

using namespace vgui;

#define INIT_HEALTH -1

//-----------------------------------------------------------------------------
// Purpose: Health panel
//-----------------------------------------------------------------------------
class CHudHealth : public CHudElement, public CHudNumericDisplay
{
	DECLARE_CLASS_SIMPLE( CHudHealth, CHudNumericDisplay );

public:
	CHudHealth( const char *pElementName );
	virtual void Init( void );
	virtual void VidInit( void );
	virtual void Reset( void );
	virtual void OnThink();
	virtual void PaintBackground();
	void MsgFunc_Damage( bf_read &msg );

	float posX;
	float posY;
	float sizeX;
	float sizeY;

	Panel* m_pWhiteBar;

private:
	// old variables
	int		m_iHealth;
	
	int		m_bitsDamage;

};	

DECLARE_HUDELEMENT( CHudHealth );
DECLARE_HUD_MESSAGE( CHudHealth, Damage );

//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
CHudHealth::CHudHealth( const char *pElementName ) : CHudElement( pElementName ), CHudNumericDisplay(NULL, "HudHealth")
{
	SetHiddenBits( HIDEHUD_HEALTH | HIDEHUD_PLAYERDEAD | HIDEHUD_NEEDSUIT );
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CHudHealth::Init()
{
	HOOK_HUD_MESSAGE( CHudHealth, Damage );
	Reset();
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CHudHealth::Reset()
{
	m_iHealth		= INIT_HEALTH;
	m_bitsDamage	= 0;

	posX = ( int )XRES2( 50 );
	posY = ( int )YRES2( 950 );
	sizeX = ( int )XRES2( 233 );
	sizeY = ( int )YRES2( 96 );

	m_pWhiteBar = new Panel( this, "WhiteBar" );
	m_pWhiteBar->SetEnabled(1);
	m_pWhiteBar->SetVisible(1);
	//m_pWhiteBar->SetBgColor( GetFgColor() );

	m_pWhiteBar->SetRoundedCorners(0);
	m_pWhiteBar->SetSize( sizeX, YRES2(5) );
	m_pWhiteBar->SetPos( 0, sizeY - YRES2( 5 ) );


	SetProportional( false );
	SetEnabled( 1 );
	SetVisible( 1 );
	SetRoundedCorners( 0 );

	SetPos( posX, posY );
	SetSize( sizeX, sizeY );

	SetLabelText(L"A");
	SetTextPos( XRES2(29), YRES2(21) );
	SetDigitPos( XRES2(123), YRES2(7) );
	SetDisplayValue(m_iHealth);
}

void CHudHealth::PaintBackground()
{
	/*
	surface()->DrawSetColor( Color(255,255,255,255) );
	surface()->DrawFilledRect( 0, sizeY - YRES2( 5 ), sizeX, sizeY );
	*/
	//surface()->DrawSetColor( GetBgColor() );
	surface()->DrawSetColor( Color(0,0,0,255) );
	surface()->DrawFilledRectFade( 0, 0, sizeX, sizeY - YRES2( 5 ), 0, 255, 0 );
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CHudHealth::VidInit()
{
	Reset();
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CHudHealth::OnThink()
{
	m_pWhiteBar->SetBgColor( Color( 255, 255, 255, 255 ) );

	int newHealth = 0;
	C_BasePlayer *local = C_BasePlayer::GetLocalPlayer();
	if ( local )
	{
		// Never below zero
		newHealth = MAX( local->GetHealth(), 0 );
	}

	// Only update the fade if we've changed health
	if ( newHealth == m_iHealth )
	{
		return;
	}

	m_iHealth = newHealth;

	if ( m_iHealth >= 20 )
	{
		g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("HealthIncreasedAbove20");
	}
	else if ( m_iHealth > 0 )
	{
		g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("HealthIncreasedBelow20");
		g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("HealthLow");
	}

	SetDisplayValue(m_iHealth);
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CHudHealth::MsgFunc_Damage( bf_read &msg )
{

	int armor = msg.ReadByte();	// armor
	int damageTaken = msg.ReadByte();	// health
	long bitsDamage = msg.ReadLong(); // damage bits
	bitsDamage; // variable still sent but not used

	Vector vecFrom;

	vecFrom.x = msg.ReadBitCoord();
	vecFrom.y = msg.ReadBitCoord();
	vecFrom.z = msg.ReadBitCoord();

	// Actually took damage?
	if ( damageTaken > 0 || armor > 0 )
	{
		if ( damageTaken > 0 )
		{
			// start the animation
			g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("HealthDamageTaken");
		}
	}
}