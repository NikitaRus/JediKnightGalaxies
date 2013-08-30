#ifndef UI_DEVICECONTEXT_H
#define UI_DEVICECONTEXT_H

#include "ui_shared.h"
#ifdef CGAME
#include "cgame/cg_local.h"
#else
#include "ui_local.h"
#endif

namespace DisplayContext
{
	float xscale;
	float yscale;
	float bias;

	int frameTime;
	int realTime;

	glconfig_t glconfig;

	qhandle_t whiteShader;
	qhandle_t gradientImage;
	qhandle_t cursor;

	int cursorx;
	int cursory;

	float FPS;

	cachedAssets_t Assets;

	// Pointers to stuff
	qhandle_t		(*RegisterShaderNoMip)( const char *p );
	void			(*SetColor)( const vec4_t v );
	void			(*DrawStretchPic)( float x, float y, float w, float h, float s1, float t1, float s2, float t2, qhandle_t hShader );
	qhandle_t		(*RegisterModel)( const char *p );
	void			(*ModelBounds)( qhandle_t model, vec3_t mins, vec3_t maxs );
	void			(*ClearScene)( void );
	void			(*AddRefEntityToScene)( const refEntity_t *re );
	void			(*RenderScene)( const refdef_t *fd );
	qhandle_t		(*RegisterFont)( const char *fontname );
	int				(*Font_StrLenPixels)( const char *text, const int iFontIndex, const float scale );
	int				(*Font_StrLenChars)( const char *text );
	int				(*Font_HeightPixels)( const int iFontIndex, const float scale );
	void			(*Font_DrawString)( int ox, int oy, const char *text, const float *rgba, const int setIndex, int iCharLimit, const float scale );
	bool			(*Language_IsAsian)( void );
	bool			(*Language_UsesSpaces)( void );
	unsigned int	(*AnyLanguage_ReadCharFromString)( const char *psText, int *piAdvanceCount, bool *pbIsTrailingPunctuation );
	void			(*GetCvarString)( const char *cvar, char *buffer, int bufsize );
	void			(*SetCvar)( const char *cvar, const char *value );
	void			(*StartLocalSound)( sfxHandle_t sfx, int channelNum );
	sfxHandle_t		(*RegisterSound)( const char *name );
	void			(*StartBackgroundTrack)( const char *intro, const char *loop, bool bReturnWithoutStarting );
	void			(*StopBackgroundTrack)( void );
	void			(*Error)( int level, const char *error, ... );
	void			(*Print)( const char *msg, ... );

	float			(*GetValue)( int ownerDraw );
	bool			(*OwnerDrawVisible)( int flags );
	int				(*GetFeederCount)( float feederID ); // FIXME: should be int, not float...
	bool			(*FeederSelection)( float feederID, int index, itemDef_t *item );
	const char*		(*FeederItemText)( float feederID, int index, int column, qhandle_t *handle1, qhandle_t *handle2, qhandle_t *handle3 );
	qhandle_t		(*FeederItemImage)( float feederID, int index );
	int				(*OwnerDrawWidth)( int ownerDraw, float scale );

	// Virtuals, we direct these to the trap calls on cgame/ui (no... these aren't virtuals in namespaces)
	void			DrawHandlePic( float x, float y, float w, float h, qhandle_t asset );
	void			DrawText( float x, float y, float scale, vec4_t color, const char *text, float adjust, int limit, int style, int iMenuFont );
	int				TextWidth( const char *text, float scale, int iMenuFont );
	int				TextHeight( const char *text, float scale, int iMenuFont );
	void			FillRect( float x, float y, float w, float h, const vec4_t color );
	void			DrawRect( float x, float y, float w, float h, float size, const vec4_t color );
	void			DrawSides( float x, float y, float w, float h, float size );
	void			DrawTopBottom( float x, float y, float w, float h, float size );

	float		GetCvarValue( const char *cvar );
	
	void			OwnerDrawItem( itemDef_t *item, float x, float y, float w, float h, float text_x, float text_y, int ownerDraw, int ownerDrawFlags, 
		int align, float special, float scale, vec4_t color, qhandle_t shader, int textStyle,int iMenuFont, int ownerDrawID );
	bool			OwnerDrawHandleKey( int ownerDraw, int flags, float *special, int key, int ownerDrawID );
	void			RunScript( char **p );
	bool			DeferScript( char **p );
	void			GetTeamColor( vec4_t *color );
	
	void			DrawTextWithCursor( float x, float y, float scale, vec4_t color, const char *text, int cursorPos, char cursor, int limit, int style, int iFontIndex );
	void			SetOverstrikeMode( bool b );
	bool			GetOverstrikeMode( void );
	
	void			KeyNumToStringBuf( int keynum, char *buf, int buflen );
	void			GetBindingBuf( int keynum, char *buf, int buflen );
	void			SetBinding( int keynum, const char *binding );
	
	void			ExecuteText( int exec_when, const char *text );

	void			Pause( bool b );

	int PlayCinematic(const char *name, float x, float y, float w, float h);
	void StopCinematic(int handle);
	void DrawCinematic(int handle, float x, float y, float w, float h);
	void RunCinematicFrame(int handle);

	void RegisterCallbacks();
	void SetTime( int newRealTime );
};

#endif