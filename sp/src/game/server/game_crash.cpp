#include "cbase.h"
#ifdef _WIN32
#include <windows.h>
#endif

class CGameCrash : public CBaseEntity
{
	DECLARE_CLASS( CGameCrash, CBaseEntity );
	DECLARE_DATADESC();

private:
	void InputCrash( inputdata_t &inputdata );

#ifdef _WIN32
    char* m_szTitle;
#endif
	char* m_szMessage;
	int m_nType;
	//0 - crash without a window
	//1 - engine error crash
	//2 - message box crash
};


LINK_ENTITY_TO_CLASS( game_crash, CGameCrash );

BEGIN_DATADESC( CGameCrash )

	DEFINE_INPUTFUNC( FIELD_VOID, "Crash", InputCrash ),

    DEFINE_KEYFIELD( m_szTitle, FIELD_STRING, "title" ),
	DEFINE_KEYFIELD( m_szMessage, FIELD_STRING, "message" ),
	DEFINE_KEYFIELD( m_nType, FIELD_INTEGER, "type" ),

END_DATADESC()


void CGameCrash::InputCrash( inputdata_t& inputdata )
{
	switch ( m_nType )
	{
	case 0:
		engine->ClientCommand( UTIL_GetLocalPlayer()->edict(), "exit" );

	case 1:
		Error( "%s", m_szMessage );

	case 2:
#ifdef _WIN32
		engine->ClientCommand( UTIL_GetLocalPlayer()->edict(), "exit" );
		MessageBoxA( NULL, m_szMessage, m_szTitle, MB_OK );
#else
		Error( "%s", m_szMessage );
#endif
	}	
}
