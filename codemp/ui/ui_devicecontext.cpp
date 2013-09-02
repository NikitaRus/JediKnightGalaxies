// This file gets shared between cgame and UI, similar to how BG files operate.
// We use this to define all of the virtual functions within the base device context.

#include "ui_devicecontext.h"

#pragma once

#ifdef CGAME

#define DCKEYCATCH			KEYCATCH_CGAME

#define DC_GetValue			CG_GetValue
#define DC_OwnerDrawVisible	CG_OwnerDrawVisible
#define DC_FeederCount		CG_FeederCount
#define DC_FeederSelection	CG_FeederSelection
#define DC_FeederItemText	CG_FeederItemText
#define DC_FeederItemImage	CG_FeederItemImage
#define DC_OwnerDrawWidth	CG_OwnerDrawWidth
#else

#define DCKEYCATCH			KEYCATCH_UI

#define DC_GetValue			UI_GetValue
#define DC_OwnerDrawVisible UI_OwnerDrawVisible
#define DC_FeederCount		UI_FeederCount
#define DC_FeederSelection	UI_FeederSelection
#define DC_FeederItemText	UI_FeederItemText
#define DC_FeederItemImage	UI_FeederItemImage
#define DC_OwnerDrawWidth	UI_OwnerDrawWidth

extern void UI_OwnerDraw(itemDef_t *item, float x, float y, float w, float h, float text_x, float text_y, int ownerDraw, 
		int ownerDrawFlags, int align, float special, float scale, vec4_t color, qhandle_t shader, int textStyle,int iMenuFont, int ownerDrawID);
extern bool UI_OwnerDrawHandleKey(int ownerDraw, int flags, float *special, int key, int ownerDrawID);
extern bool UI_DeferMenuScript ( char **args );
extern void UI_RunMenuScript(char **args);
#endif

extern float DC_GetValue( int ownerDraw );
extern bool DC_OwnerDrawVisible( int flags );
extern int DC_FeederCount( float feederVal );
extern bool DC_FeederSelection( float feederID, int index, itemDef_t *item );
extern const char *DC_FeederItemText(float feederID, int index, int column,
										 qhandle_t *handle1, qhandle_t *handle2, qhandle_t *handle3);
extern qhandle_t DC_FeederItemImage(float feederID, int index);
extern int DC_OwnerDrawWidth(int ownerDraw, float scale);

extern int MenuFontToHandle(int iMenuFont);

namespace DisplayContext
{
	float xscale = 0;
	float yscale = 0;
	float bias = 0;

	int frameTime = 0;
	int realTime = 0;
	
	glconfig_t glconfig = { 0 };

	qhandle_t whiteShader = 0;
	qhandle_t gradientImage = 0;
	qhandle_t cursor = 0;

	int cursorx = 0;
	int cursory = 0;

	float FPS = 0;

	cachedAssets_t Assets = { 0 };

	qhandle_t		(*RegisterShaderNoMip)( const char *p ) = NULL;
	void			(*SetColor)( const vec4_t v ) = NULL;
	void			(*DrawStretchPic)( float x, float y, float w, float h, float s1, float t1, float s2, float t2, qhandle_t hShader ) = NULL;
	qhandle_t		(*RegisterModel)( const char *p ) = NULL;
	void			(*ModelBounds)( qhandle_t model, vec3_t mins, vec3_t maxs ) = NULL;
	void			(*ClearScene)( void ) = NULL;
	void			(*AddRefEntityToScene)( const refEntity_t *re ) = NULL;
	void			(*RenderScene)( const refdef_t *fd ) = NULL;
	qhandle_t		(*RegisterFont)( const char *fontname ) = NULL;
	int				(*Font_StrLenPixels)( const char *text, const int iFontIndex, const float scale ) = NULL;
	int				(*Font_StrLenChars)( const char *text ) = NULL;
	int				(*Font_HeightPixels)( const int iFontIndex, const float scale ) = NULL;
	void			(*Font_DrawString)( int ox, int oy, const char *text, const float *rgba, const int setIndex, int iCharLimit, const float scale ) = NULL;
	bool			(*Language_IsAsian)( void ) = NULL;
	bool			(*Language_UsesSpaces)( void ) = NULL;
	unsigned int	(*AnyLanguage_ReadCharFromString)( const char *psText, int *piAdvanceCount, bool *pbIsTrailingPunctuation ) = NULL;
	void			(*GetCvarString)( const char *cvar, char *buffer, int bufsize ) = NULL;
	void			(*SetCvar)( const char *cvar, const char *value ) = NULL;
	void			(*StartLocalSound)( sfxHandle_t sfx, int channelNum ) = NULL;
	sfxHandle_t		(*RegisterSound)( const char *name ) = NULL;
	void			(*StartBackgroundTrack)( const char *intro, const char *loop, bool bReturnWithoutStarting ) = NULL;
	void			(*StopBackgroundTrack)( void ) = NULL;
	void			(*Error)( int level, const char *error, ... ) = NULL;
	void			(*Print)( const char *msg, ... ) = NULL;

	float			(*GetValue)( int ownerDraw ) = NULL;
	bool			(*OwnerDrawVisible)( int flags ) = NULL;
	int				(*GetFeederCount)( float feederID ) = NULL; // FIXME: should be int, not float...
	bool			(*FeederSelection)( float feederID, int index, itemDef_t *item ) = NULL;
	const char*		(*FeederItemText)( float feederID, int index, int column, qhandle_t *handle1, qhandle_t *handle2, qhandle_t *handle3 ) = NULL;
	qhandle_t		(*FeederItemImage)( float feederID, int index ) = NULL;
	int				(*OwnerDrawWidth)( int ownerDraw, float scale ) = NULL;

	void DrawHandlePic( float x, float y, float w, float h, qhandle_t asset )
	{
		float	s0;
		float	s1;
		float	t0;
		float	t1;

		if( w < 0 ) {	// flip about vertical
			w  = -w;
			s0 = 1;
			s1 = 0;
		}
		else {
			s0 = 0;
			s1 = 1;
		}

		if( h < 0 ) {	// flip about horizontal
			h  = -h;
			t0 = 1;
			t1 = 0;
		}
		else {
			t0 = 0;
			t1 = 1;
		}
	
		trap_R_DrawStretchPic( x, y, w, h, s0, t0, s1, t1, asset );
	}

	void DrawText( float x, float y, float scale, vec4_t color, const char *text, float adjust, int limit, int style, int iMenuFont )
	{
		int iStyleOR = 0;

		int iFontIndex = MenuFontToHandle(iMenuFont);
		//
		// kludge.. convert JK2 menu styles to SOF2 printstring ctrl codes...
		//	
		switch (style)
		{
		case  ITEM_TEXTSTYLE_NORMAL:			iStyleOR = 0;break;					// JK2 normal text
		case  ITEM_TEXTSTYLE_BLINK:				iStyleOR = (int)STYLE_BLINK;break;		// JK2 fast blinking
		case  ITEM_TEXTSTYLE_PULSE:				iStyleOR = (int)STYLE_BLINK;break;		// JK2 slow pulsing
		case  ITEM_TEXTSTYLE_SHADOWED:			iStyleOR = (int)STYLE_DROPSHADOW;break;	// JK2 drop shadow
		case  ITEM_TEXTSTYLE_OUTLINED:			iStyleOR = (int)STYLE_DROPSHADOW;break;	// JK2 drop shadow
		case  ITEM_TEXTSTYLE_OUTLINESHADOWED:	iStyleOR = (int)STYLE_DROPSHADOW;break;	// JK2 drop shadow
		case  ITEM_TEXTSTYLE_SHADOWEDMORE:		iStyleOR = (int)STYLE_DROPSHADOW;break;	// JK2 drop shadow
		}

		trap_R_Font_DrawString(	x,		// int ox
			y,		// int oy
			text,	// const char *text
			color,	// paletteRGBA_c c
			iStyleOR | iFontIndex,	// const int iFontHandle
			!limit?-1:limit,		// iCharLimit (-1 = none)
			scale	// const float scale = 1.0f
			);
	}

	int TextWidth( const char *text, float scale, int iMenuFont )
	{
		int iFontIndex = MenuFontToHandle(iMenuFont);
		// Remove colour codes before measuring as colour codes aren't drawn.
		char buffer[MAX_STRING_CHARS];
		Q_strncpyz (buffer, text, sizeof (buffer));
		Q_CleanStr (buffer);

		return trap_R_Font_StrLenPixels(buffer, iFontIndex, scale);
	}

	int TextHeight( const char *text, float scale, int iMenuFont )
	{
		int iFontIndex = MenuFontToHandle(iMenuFont);

		return trap_R_Font_HeightPixels(iFontIndex, scale);
	}

	void FillRect( float x, float y, float w, float h, const vec4_t color )
	{
		SetColor( color );

		DrawStretchPic( x, y, w, h, 0, 0, 0, 0, whiteShader );

		SetColor( NULL );
	}

	void DrawRect( float x, float y, float w, float h, float size, const vec4_t color )
	{
		SetColor( color );

		DrawTopBottom( x, y, w, h, size );
		DrawSides( x, y, w, h, size );

		SetColor( NULL );
	}

	void DrawSides( float x, float y, float w, float h, float size )
	{
		size /= xscale;

		DrawStretchPic( x, y, size, h, 0, 0, 0, 0, whiteShader );
		DrawStretchPic( x + w - size, y, size, h, 0, 0, 0, 0, whiteShader );
	}

	void DrawTopBottom( float x, float y, float w, float h, float size )
	{
		size /= yscale;

		DrawStretchPic( x+size, y, w-size*2, size, 0, 0, 0, 0, whiteShader );
		DrawStretchPic( x+size, y + h - size, w-size*2, size, 0, 0, 0, 0, whiteShader );
	}

	void OwnerDrawItem( itemDef_t *item, float x, float y, float w, float h, 
		float text_x, float text_y, int ownerDraw, int ownerDrawFlags, int align, float special, float scale, vec4_t color, 
		qhandle_t shader, int textStyle,int iMenuFont, int ownerDrawID )
	{
	#ifdef CGAME // fixme use _CGAME
		return;	// Not used.
	#else
		UI_OwnerDraw( item, x, y, w, h, text_x, text_y, ownerDraw, ownerDrawFlags, align, special, scale, color, shader, textStyle, iMenuFont, ownerDrawID );
	#endif
	}

	bool OwnerDrawHandleKey( int ownerDraw, int flags, float *special, int key, int ownerDrawID )
	{
	#ifdef CGAME // fixme use _CGAME
		return false; // Not used.
	#else
		return UI_OwnerDrawHandleKey( ownerDraw, flags, special, key, ownerDrawID );
	#endif
	}

	void RunScript( char **p )
	{
	#ifdef UI_EXPORTS // fixme use _UI
		UI_RunMenuScript( p );
	#endif
	}

	bool DeferScript( char **p )
	{
	#ifdef CGAME // fixme use _CGAME
		return false;
	#else
		return UI_DeferMenuScript(p);
	#endif
	}

	void GetTeamColor( vec4_t *color )
	{
	#ifdef CGAME // fixme use _CGAME
		playerState_t *ps = &cg.snap->ps;
		if (ps->persistant[PERS_TEAM] == TEAM_RED) {
			(*color)[0] = 1.0f;
			(*color)[3] = 0.25f;
			(*color)[1] = (*color)[2] = 0.0f;
		} else if (ps->persistant[PERS_TEAM] == TEAM_BLUE) {
			(*color)[0] = (*color)[1] = 0.0f;
			(*color)[2] = 1.0f;
			(*color)[3] = 0.25f;
		} else {
			(*color)[0] = (*color)[2] = 0.0f;
			(*color)[1] = 0.17f;
			(*color)[3] = 0.25f;
		}
	#endif
	}

	float GetCvarValue( const char *cvar )
	{
	#ifndef CGAME // fixme use _CGAME
		return trap_Cvar_VariableValue( cvar );
	#else
		char buff[128];
		memset(buff, 0, sizeof(buff));
		trap_Cvar_VariableStringBuffer(cvar, buff, sizeof(buff));
		return atof(buff);
	#endif
	}

	void DrawTextWithCursor( float x, float y, float scale, vec4_t color, 
		const char *text, int cursorPos, char cursor, int limit, int style, int iFontIndex )
	{
		DrawText( x, y, scale, color, text, 0, limit, style, iFontIndex );

		char sTemp[1024];
		int iCopyCount = limit ? min( (signed)strlen( text ), limit ) : (signed)strlen( text );
		iCopyCount = min( iCopyCount, cursorPos );
		iCopyCount = min( iCopyCount, sizeof( sTemp ) );

		// copy text into temp buffer for pixel measure...
		//
		Q_strncpyz( sTemp, text, iCopyCount );

		int iFont = MenuFontToHandle( iFontIndex );	
		int iNextXpos  = trap_R_Font_StrLenPixels(sTemp, iFont, scale );

		DrawText( x, y, scale, color, va("%c", cursor), 0, limit, style|ITEM_TEXTSTYLE_BLINK, iFontIndex );
	}

	void SetOverstrikeMode( bool b )
	{
	#ifndef CGAME // fixme use _CGAME
		trap_Key_SetOverstrikeMode( b );
	#endif
	}

	bool GetOverstrikeMode( void )
	{
	#ifdef CGAME // fixme use _CGAME
		return false;
	#else
		return trap_Key_GetOverstrikeMode();
	#endif
	}

	void KeyNumToStringBuf( int keynum, char *buf, int buflen )
	{
	#ifndef CGAME // fixme use _CGAME
		trap_Key_KeynumToStringBuf( keynum, buf, buflen );
	#endif
	// this should probably set the buffer to empty as else because no more func pointer
	}

	void GetBindingBuf( int keynum, char *buf, int buflen )
	{
	#ifndef CGAME // fixme use _CGAME
		trap_Key_GetBindingBuf( keynum, buf, buflen );
	#endif
	// this should probably set the buffer to empty as else because no more func pointer
	}

	void SetBinding( int keynum, const char *binding )
	{
	#ifndef CGAME // fixme use _CGAME
		trap_Key_SetBinding( keynum, binding );
	#endif
	}

	void ExecuteText( int exec_when, const char *text )
	{
	#ifndef CGAME // fixme use _CGAME
		trap_Cmd_ExecuteText( exec_when, text );
	#endif
	}

	void Pause( bool b )
	{
		if (b) {
			// pause the game and set the keycatcher
			trap_Cvar_Set( "cl_paused", "1" );
			trap_Key_SetCatcher( DCKEYCATCH );
		} else {
			// unpause the game and clear the keycatcher
			trap_Key_SetCatcher( trap_Key_GetCatcher() & ~DCKEYCATCH );
	#ifndef CGAME // fixme use _CGAME
			trap_Key_ClearStates();
	#endif
			trap_Cvar_Set( "cl_paused", "0" );
		}
	}

	int PlayCinematic( const char *name, float x, float y, float w, float h )
	{
		return trap_CIN_PlayCinematic(name, x, y, w, h, CIN_loop);
	}

	void StopCinematic( int handle )
	{
		trap_CIN_StopCinematic(handle);
	}

	void DrawCinematic( int handle, float x, float y, float w, float h )
	{
		trap_CIN_SetExtents(handle, x, y, w, h);
		trap_CIN_DrawCinematic(handle);
	}

	void RunCinematicFrame( int handle )
	{
		trap_CIN_RunCinematic( handle );
	}

	void SetTime( int newRealTime )
	{
		frameTime = newRealTime - realTime;
		realTime = newRealTime;
	}

	void RegisterCallbacks()
	{
		RegisterShaderNoMip = trap_R_RegisterShaderNoMip;
		SetColor = trap_R_SetColor;
		DrawStretchPic = trap_R_DrawStretchPic;
		RegisterModel = trap_R_RegisterModel;
		ModelBounds = trap_R_ModelBounds;
		ClearScene = trap_R_ClearScene;
		AddRefEntityToScene = trap_R_AddRefEntityToScene;
		RenderScene = trap_R_RenderScene;
		RegisterFont = trap_R_RegisterFont;
		Font_StrLenPixels = trap_R_Font_StrLenPixels;
		Font_StrLenChars = trap_R_Font_StrLenChars;
		Font_HeightPixels = trap_R_Font_HeightPixels;
		Font_DrawString = trap_R_Font_DrawString;
		Language_IsAsian = trap_Language_IsAsian;
		Language_UsesSpaces = trap_Language_UsesSpaces;
		AnyLanguage_ReadCharFromString = trap_AnyLanguage_ReadCharFromString;
		GetCvarString = trap_Cvar_VariableStringBuffer;
		SetCvar = trap_Cvar_Set;
		StartLocalSound = trap_S_StartLocalSound;
		RegisterSound = trap_S_RegisterSound;
		StartBackgroundTrack = trap_S_StartBackgroundTrack;
		StopBackgroundTrack = trap_S_StopBackgroundTrack;
		Error = Com_Error;
		Print = Com_Printf;

		// And now we get to the func pointers which vary based on cgame/ui...
		GetValue = DC_GetValue;
		OwnerDrawVisible = DC_OwnerDrawVisible;
		GetFeederCount = DC_FeederCount;
		FeederSelection = DC_FeederSelection;
		FeederItemText = DC_FeederItemText;
		FeederItemImage = DC_FeederItemImage;
		OwnerDrawWidth = DC_OwnerDrawWidth;

		trap_GetGlconfig( &glconfig );
		yscale = glconfig.vidHeight * (1.0/SCREEN_HEIGHT);
		xscale = glconfig.vidWidth * (1.0/SCREEN_WIDTH);
		bias = 0.5 * ( glconfig.vidWidth - ( glconfig.vidHeight * (SCREEN_WIDTH/SCREEN_HEIGHT) ) );


		whiteShader = trap_R_RegisterShaderNoMip( "white" );
		cursor = trap_R_RegisterShaderNoMip( "menu/art/3_cursor2" );

		realTime = 0;
	}
}