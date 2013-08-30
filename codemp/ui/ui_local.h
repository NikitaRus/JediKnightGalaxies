// Copyright (C) 1999-2000 Id Software, Inc.
//
#ifndef __UI_LOCAL_H__
#define __UI_LOCAL_H__

#include "qcommon/q_shared.h"
#include "rd-common/tr_types.h"
#include "ui_public.h"
#include "keycodes.h"
#include "../game/bg_public.h"
#include "ui_shared.h"

// global display context

extern vmCvar_t	ui_ffa_fraglimit;
extern vmCvar_t	ui_ffa_timelimit;

extern vmCvar_t ui_selectedModelIndex;

extern vmCvar_t	ui_team_fraglimit;
extern vmCvar_t	ui_team_timelimit;
extern vmCvar_t	ui_team_friendly;

extern vmCvar_t	ui_ctf_capturelimit;
extern vmCvar_t	ui_ctf_timelimit;
extern vmCvar_t	ui_ctf_friendly;

extern vmCvar_t	ui_arenasFile;
extern vmCvar_t	ui_botsFile;

extern vmCvar_t	ui_browserMaster;
extern vmCvar_t	ui_browserGameType;
extern vmCvar_t	ui_browserSortKey;
extern vmCvar_t	ui_browserShowFull;
extern vmCvar_t	ui_browserShowEmpty;

extern vmCvar_t	ui_drawCrosshair;
extern vmCvar_t	ui_drawCrosshairNames;
extern vmCvar_t	ui_marks;

extern vmCvar_t	ui_captureLimit;
extern vmCvar_t	ui_fragLimit;
extern vmCvar_t	ui_gameType;
extern vmCvar_t	ui_netGameType;
extern vmCvar_t	ui_actualNetGameType;
extern vmCvar_t	ui_joinGameType;
extern vmCvar_t	ui_netSource;
extern vmCvar_t	ui_serverFilterType;
extern vmCvar_t	ui_dedicated;
extern vmCvar_t	ui_opponentName;
extern vmCvar_t	ui_menuFiles;
extern vmCvar_t	ui_currentMap;
extern vmCvar_t	ui_currentNetMap;
extern vmCvar_t	ui_mapIndex;
extern vmCvar_t	ui_currentOpponent;
extern vmCvar_t	ui_selectedPlayer;
extern vmCvar_t	ui_selectedPlayerName;
extern vmCvar_t	ui_lastServerRefresh_0;
extern vmCvar_t	ui_lastServerRefresh_1;
extern vmCvar_t	ui_lastServerRefresh_2;
extern vmCvar_t	ui_lastServerRefresh_3;
extern vmCvar_t	ui_singlePlayerActive;
extern vmCvar_t	ui_scoreAccuracy;
extern vmCvar_t	ui_scoreImpressives;
extern vmCvar_t	ui_scoreExcellents;
extern vmCvar_t	ui_scoreDefends;
extern vmCvar_t	ui_scoreAssists;
extern vmCvar_t	ui_scoreGauntlets;
extern vmCvar_t	ui_scoreScore;
extern vmCvar_t	ui_scorePerfect;
extern vmCvar_t	ui_scoreTeam;
extern vmCvar_t	ui_scoreBase;
extern vmCvar_t	ui_scoreTimeBonus;
extern vmCvar_t	ui_scoreSkillBonus;
extern vmCvar_t	ui_scoreShutoutBonus;
extern vmCvar_t	ui_scoreTime;
extern vmCvar_t ui_serverStatusTimeOut;

extern vmCvar_t ui_bypassMainMenuLoad;

//
// ui_qmenu.c
//

#define RCOLUMN_OFFSET			( BIGCHAR_WIDTH )
#define LCOLUMN_OFFSET			(-BIGCHAR_WIDTH )

#define SLIDER_RANGE			10
#define	MAX_EDIT_LINE			256

#define MAX_MENUDEPTH			16 //Raz: was 8
//#define MAX_MENUITEMS			1024

#define MAX_FORCE_CONFIGS		128

//JAC: Moved from ui_main.c and ui_saber.c, also increased drastically
#define MAX_SABER_HILTS			256 //64

typedef struct _tag_menuframework
{
	int	cursor;
	int cursor_prev;

	int	nitems;
	void *items[MAX_MENUITEMS];

	void (*draw) (void);
	sfxHandle_t (*key) (int key);

	qboolean	wrapAround;
	qboolean	fullscreen;
	qboolean	showlogo;
} menuframework_s;

typedef struct
{
	int type;
	const char *name;
	int	id;
	int x, y;
	int left;
	int	top;
	int	right;
	int	bottom;
	menuframework_s *parent;
	int menuPosition;
	unsigned flags;

	void (*callback)( void *self, int event );
	void (*statusbar)( void *self );
	void (*ownerdraw)( void *self );
} menucommon_s;

typedef struct {
	int		cursor;
	int		scroll;
	int		widthInChars;
	char	buffer[MAX_EDIT_LINE];
	int		maxchars;
} mfield_t;

typedef struct
{
	menucommon_s	generic;
	mfield_t		field;
} menufield_s;

typedef struct 
{
	menucommon_s generic;

	float minvalue;
	float maxvalue;
	float curvalue;

	float range;
} menuslider_s;

typedef struct
{
	menucommon_s generic;

	int	oldvalue;
	int curvalue;
	int	numitems;
	int	top;
		
	const char **itemnames;

	int width;
	int height;
	int	columns;
	int	seperation;
} menulist_s;

typedef struct
{
	menucommon_s generic;
} menuaction_s;

typedef struct
{
	menucommon_s generic;
	int curvalue;
} menuradiobutton_s;

typedef struct
{
	menucommon_s	generic;
	char*			focuspic;	
	char*			errorpic;
	qhandle_t		shader;
	qhandle_t		focusshader;
	int				width;
	int				height;
	float*			focuscolor;
} menubitmap_s;

typedef struct
{
	menucommon_s	generic;
	char*			string;
	int				style;
	float*			color;
} menutext_s;

extern void			Menu_Cache( void );
extern void			Menu_Focus( menucommon_s *m );
extern void			Menu_AddItem( menuframework_s *menu, void *item );
extern void			Menu_AdjustCursor( menuframework_s *menu, int dir );
extern void			Menu_Draw( menuframework_s *menu );
extern void			*Menu_ItemAtCursor( menuframework_s *m );
extern sfxHandle_t	Menu_ActivateItem( menuframework_s *s, menucommon_s* item );
extern void			Menu_SetCursor( menuframework_s *s, int cursor );
extern void			Menu_SetCursorToItem( menuframework_s *m, void* ptr );
extern sfxHandle_t	Menu_DefaultKey( menuframework_s *s, int key );
extern void			Bitmap_Init( menubitmap_s *b );
extern void			Bitmap_Draw( menubitmap_s *b );
extern void			ScrollList_Draw( menulist_s *l );
extern sfxHandle_t	ScrollList_Key( menulist_s *l, int key );
extern sfxHandle_t	menu_in_sound;
extern sfxHandle_t	menu_move_sound;
extern sfxHandle_t	menu_out_sound;
extern sfxHandle_t	menu_buzz_sound;
extern sfxHandle_t	menu_null_sound;
extern sfxHandle_t	weaponChangeSound;
extern vec4_t		menu_text_color;
extern vec4_t		menu_grayed_color;
extern vec4_t		menu_dark_color;
extern vec4_t		menu_highlight_color;
extern vec4_t		menu_red_color;
extern vec4_t		menu_black_color;
extern vec4_t		menu_dim_color;
extern vec4_t		color_black;
extern vec4_t		color_white;
extern vec4_t		color_yellow;
extern vec4_t		color_blue;
extern vec4_t		color_orange;
extern vec4_t		color_red;
extern vec4_t		color_dim;
extern vec4_t		name_color;
extern vec4_t		list_color;
extern vec4_t		listbar_color;
extern vec4_t		text_color_disabled; 
extern vec4_t		text_color_normal;
extern vec4_t		text_color_highlight;

//
// ui_main.c
//
qboolean UI_FeederSelection( float feederID, int index, itemDef_t *item );
void UI_Report();
void UI_Load();
void UI_LoadMenus(const char *menuFile, qboolean reset);
void _UI_SetActiveMenu( uiMenuCommand_t menu );
int UI_AdjustTimeByGame(int time);
void UI_LoadArenas(void);
extern void UI_DrawConnectScreen( qboolean overlay );
extern void UI_RegisterCvars( void );
extern void UI_UpdateCvars( void );

//
// ui_players.c
//

typedef struct {
	// model info
	qhandle_t		legsModel;
	qhandle_t		legsSkin;
	lerpFrame_t		legs;

	qhandle_t		torsoModel;
	qhandle_t		torsoSkin;
	lerpFrame_t		torso;

//	qhandle_t		headModel;
//	qhandle_t		headSkin;

	animation_t		animations[MAX_TOTALANIMATIONS];

	qhandle_t		weaponModel;
	qhandle_t		barrelModel;
	qhandle_t		flashModel;
	vec3_t			flashDlightColor;
	int				muzzleFlashTime;

	// currently in use drawing parms
	vec3_t			viewAngles;
	vec3_t			moveAngles;
	weapon_t		currentWeapon;
	int				legsAnim;
	int				torsoAnim;

	// animation vars
	weapon_t		weapon;
	weapon_t		lastWeapon;
	weapon_t		pendingWeapon;
	int				weaponTimer;
	int				pendingLegsAnim;
	int				torsoAnimationTimer;

	int				pendingTorsoAnim;
	int				legsAnimationTimer;

	qboolean		chat;
	qboolean		newModel;

	qboolean		barrelSpinning;
	float			barrelAngle;
	int				barrelTime;

	int				realWeapon;
} playerInfo_t;

//
// ui_atoms.c
//

// new ui stuff
#define UI_NUMFX 7
#define MAX_HEADS 64
#define MAX_ALIASES 64
#define MAX_HEADNAME  32
#define MAX_TEAMS 64
#define MAX_GAMETYPES 16
#define MAX_MAPS 512 //Raz: was 128
#define MAX_SPMAPS 16
#define PLAYERS_PER_TEAM 8//5
#define MAX_PINGREQUESTS		32

#define MAX_LISTBOXWIDTH		256 //59
#define UI_FONT_THRESHOLD		0.1
#define MAX_DISPLAY_SERVERS		2048
#define MAX_SERVERSTATUS_LINES	128
#define MAX_SERVERSTATUS_TEXT	4096 //1024
#define MAX_FOUNDPLAYER_SERVERS	16
#define TEAM_MEMBERS 8//5
#define GAMES_ALL			0
#define GAMES_FFA			1
#define GAMES_HOLOCRON		2
#define GAMES_TEAMPLAY		3
#define GAMES_TOURNEY		4
#define GAMES_CTF			5
#define MAPS_PER_TIER 3
#define MAX_TIERS 16
#define MAX_MODS 64

#define MAX_DEMOS 2048
#define MAX_MOVIES 2048
#define MAX_Q3PLAYERMODELS 1024
#define MAX_PLAYERMODELS 512

//JAC: Added
#define DEMO_DIRECTORY "demos"
#define DEMO_EXTENSION "dm_"
#define MAX_DEMOLIST (MAX_DEMOS * MAX_QPATH)

#define MAX_SCROLLTEXT_SIZE		4096
#define MAX_SCROLLTEXT_LINES		64

typedef struct {
	const char *name;
	const char *ai;
	const char *action;
} aliasInfo;

typedef struct {
  const char *teamName;
	const char *imageName;
	const char *teamMembers[TEAM_MEMBERS];
	int cinematic;
} teamInfo;

typedef struct {
  const char *gameType;
  int gtEnum;
} gameTypeInfo;

typedef struct {
  const char *mapName;
  const char *mapLoadName;
	const char *imageName;
	const char *opponentName;
	int teamMembers;
  int typeBits;
	int cinematic;
	int timeToBeat[MAX_GAMETYPES];
	qhandle_t levelShot;
	qboolean active;
} mapInfo;

typedef struct serverFilter_s {
	const char *description;
	const char *basedir;
} serverFilter_t;

typedef struct {
	char	adrstr[MAX_ADDRESSLENGTH];
	int		start;
} pinglist_t;


typedef struct serverStatus_s {
	pinglist_t pingList[MAX_PINGREQUESTS];
	int		numqueriedservers;
	int		currentping;
	int		nextpingtime;
	int		maxservers;
	int		refreshtime;
	int		numServers;
	int		sortKey;
	int		sortDir;
	int		lastCount;
	qboolean refreshActive;
	int		currentServer;
	int		displayServers[MAX_DISPLAY_SERVERS];
	int		numDisplayServers;
	int		numPlayersOnServers;
	int		nextDisplayRefresh;
	int		nextSortTime;
	qhandle_t currentServerPreview;
	int		currentServerCinematic;
	int		motdLen;
	int		motdWidth;
	int		motdPaintX;
	int		motdPaintX2;
	int		motdOffset;
	int		motdTime;
	char	motd[MAX_STRING_CHARS];
} serverStatus_t;


typedef struct {
	char		adrstr[MAX_ADDRESSLENGTH];
	char		name[MAX_ADDRESSLENGTH];
	int			startTime;
	int			serverNum;
	qboolean	valid;
} pendingServer_t;

typedef struct {
	int num;
	pendingServer_t server[MAX_SERVERSTATUSREQUESTS];
} pendingServerStatus_t;

typedef struct {
	char address[MAX_ADDRESSLENGTH];
	char *lines[MAX_SERVERSTATUS_LINES][4];
	char text[MAX_SERVERSTATUS_TEXT];
	char pings[MAX_CLIENTS * 3];
	int numLines;
} serverStatusInfo_t;

typedef struct {
	const char *modName;
	const char *modDescr;
} modInfo_t;

typedef struct {
	char		Name[64];
	int			SkinHeadCount;
	char		SkinHeadNames[MAX_PLAYERMODELS][16];
	int			SkinTorsoCount;
	char		SkinTorsoNames[MAX_PLAYERMODELS][16];
	int			SkinLegCount;
	char		SkinLegNames[MAX_PLAYERMODELS][16];
	char		ColorShader[MAX_PLAYERMODELS][64];
	int			ColorCount;
	char		ColorActionText[MAX_PLAYERMODELS][128];
} playerSpeciesInfo_t;

typedef struct {
	qboolean demoAvailable;
	
	int characterCount;
	int botIndex;

	int aliasCount;
	aliasInfo aliasList[MAX_ALIASES];

	int teamCount;
	teamInfo teamList[MAX_TEAMS];

	int numGameTypes;
	gameTypeInfo gameTypes[MAX_GAMETYPES];

	int numJoinGameTypes;
	gameTypeInfo joinGameTypes[MAX_GAMETYPES];

	int redBlue;
	int playerCount;
	int myTeamCount;
	int teamIndex;
	int playerRefresh;
	int playerIndex;
	int playerNumber; 
	qboolean teamLeader;
	char playerNames[MAX_CLIENTS][MAX_NETNAME];
	char teamNames[MAX_CLIENTS][MAX_NETNAME];
	int teamClientNums[MAX_CLIENTS];

	int playerIndexes[MAX_CLIENTS]; //so we can vote-kick by index

	int mapCount;
	mapInfo mapList[MAX_MAPS];

	int skillIndex;

	modInfo_t modList[MAX_MODS];
	int modCount;
	int modIndex;

	char demoList[MAX_DEMOS][MAX_QPATH];
	int demoCount;
	int demoIndex;
	int loadedDemos;

	const char *movieList[MAX_MOVIES];
	int movieCount;
	int movieIndex;
	int previewMovie;

	char scrolltext[MAX_SCROLLTEXT_SIZE];
	const char *scrolltextLine[MAX_SCROLLTEXT_LINES];
	int scrolltextLineCount;

	serverStatus_t serverStatus;

	// for the showing the status of a server
	char serverStatusAddress[MAX_ADDRESSLENGTH];
	serverStatusInfo_t serverStatusInfo;
	int nextServerStatusRefresh;

	// to retrieve the status of server to find a player
	pendingServerStatus_t pendingServerStatus;
	char findPlayerName[MAX_STRING_CHARS];
	char foundPlayerServerAddresses[MAX_FOUNDPLAYER_SERVERS][MAX_ADDRESSLENGTH];
	char foundPlayerServerNames[MAX_FOUNDPLAYER_SERVERS][MAX_ADDRESSLENGTH];
	int currentFoundPlayerServer;
	int numFoundPlayerServers;
	int nextFindPlayerRefresh;

	int currentCrosshair;

	int				q3HeadCount;
	char			q3HeadNames[MAX_Q3PLAYERMODELS][64];
	qhandle_t		q3HeadIcons[MAX_Q3PLAYERMODELS];
	int				q3SelectedHead;

	int effectsColor;

	qboolean inGameLoad;

	int					playerSpeciesCount;
	playerSpeciesInfo_t	playerSpecies[MAX_PLAYERMODELS];
	int					playerSpeciesIndex;

	short		movesTitleIndex;
	const char	*movesBaseAnim;
	int			moveAnimTime;

	int			languageCount;
	int			languageCountIndex;

	int			hideCursor;
}	uiInfo_t;

extern uiInfo_t uiInfo;


extern void			UI_Init( void );
extern void			UI_Shutdown( void );
extern void			UI_KeyEvent( int key );
extern void			UI_MouseEvent( int dx, int dy );
extern void			UI_Refresh( int realtime );
extern qboolean		UI_ConsoleCommand( int realTime );
extern float		UI_ClampCvar( float min, float max, float value );
extern void			UI_DrawNamedPic( float x, float y, float width, float height, const char *picname );
extern void			UI_DrawHandlePic( float x, float y, float w, float h, qhandle_t hShader ); 
extern void			UI_FillRect( float x, float y, float width, float height, const float *color );
extern void			UI_DrawRect( float x, float y, float width, float height, const float *color );
extern void     UI_DrawTopBottom(float x, float y, float w, float h);
extern void     UI_DrawSides(float x, float y, float w, float h);
extern void			UI_UpdateScreen( void );
extern void			UI_SetColor( const float *rgba );
extern void			UI_LerpColor(vec4_t a, vec4_t b, vec4_t c, float t);
extern void			UI_DrawBannerString( int x, int y, const char* str, int style, vec4_t color );
extern float		UI_ProportionalSizeScale( int style );
extern void			UI_DrawProportionalString( int x, int y, const char* str, int style, vec4_t color, int font );
extern int			UI_ProportionalStringWidth( const char* str );
extern void			UI_DrawString( int x, int y, const char* str, int style, vec4_t color );
extern void			UI_DrawChar( int x, int y, int ch, int style, vec4_t color );
extern qboolean 	UI_CursorInRect (int x, int y, int width, int height);
extern void			UI_DrawTextBox (int x, int y, int width, int lines);
extern qboolean		UI_IsFullscreen( void );
extern void			UI_SetActiveMenu( uiMenuCommand_t menu );
extern void			UI_PushMenu ( menuframework_s *menu );
extern void			UI_PopMenu (void);
extern void			UI_ForceMenuOff (void);
extern char			*UI_Argv( int arg );
extern char			*UI_Cvar_VariableString( const char *var_name );
extern void			UI_Refresh( int time );
extern void			UI_KeyEvent( int key );

//
// ui_syscalls.c
//

void			trap_Print( const char *string );
void			trap_Error( const char *string );
int				trap_Milliseconds( void );
void			trap_Cvar_Register( vmCvar_t *vmCvar, const char *varName, const char *defaultValue, int flags );
void			trap_Cvar_Update( vmCvar_t *vmCvar );
void			trap_Cvar_Set( const char *var_name, const char *value );
float			trap_Cvar_VariableValue( const char *var_name );
void			trap_Cvar_VariableStringBuffer( const char *var_name, char *buffer, int bufsize );
void			trap_Cvar_SetValue( const char *var_name, float value );
void			trap_Cvar_Reset( const char *name );
void			trap_Cvar_Create( const char *var_name, const char *var_value, int flags );
void			trap_Cvar_InfoStringBuffer( int bit, char *buffer, int bufsize );
int				trap_Argc( void );
void			trap_Argv( int n, char *buffer, int bufferLength );
void			trap_Cmd_ExecuteText( int exec_when, const char *text );	// don't use EXEC_NOW!
int				trap_FS_FOpenFile( const char *qpath, fileHandle_t *f, fsMode_t mode );
void			trap_FS_Read( void *buffer, int len, fileHandle_t f );
void			trap_FS_Write( const void *buffer, int len, fileHandle_t f );
void			trap_FS_FCloseFile( fileHandle_t f );
int				trap_FS_GetFileList(  const char *path, const char *extension, char *listbuf, int bufsize );
qhandle_t		trap_R_RegisterModel( const char *name );
qhandle_t		trap_R_RegisterSkin( const char *name );
qhandle_t		trap_R_RegisterShaderNoMip( const char *name );
void			trap_R_ShaderNameFromIndex(char *name, int index);
void			trap_R_ClearScene( void );
void			trap_R_AddRefEntityToScene( const refEntity_t *re );
void			trap_R_AddPolyToScene( qhandle_t hShader , int numVerts, const polyVert_t *verts );
void			trap_R_AddLightToScene( const vec3_t org, float intensity, float r, float g, float b );
void			trap_R_RenderScene( const refdef_t *fd );
void			trap_R_SetColor( const float *rgba );
void			trap_R_DrawStretchPic( float x, float y, float w, float h, float s1, float t1, float s2, float t2, qhandle_t hShader );
void			trap_R_ModelBounds( clipHandle_t model, vec3_t mins, vec3_t maxs );
void			trap_UpdateScreen( void );
int				trap_CM_LerpTag( orientation_t *tag, clipHandle_t mod, int startFrame, int endFrame, float frac, const char *tagName );
void			trap_S_StartLocalSound( sfxHandle_t sfx, int channelNum );
sfxHandle_t		trap_S_RegisterSound( const char *sample );
void			trap_Key_KeynumToStringBuf( int keynum, char *buf, int buflen );
void			trap_Key_GetBindingBuf( int keynum, char *buf, int buflen );
void			trap_Key_SetBinding( int keynum, const char *binding );
qboolean		trap_Key_IsDown( int keynum );
qboolean		trap_Key_GetOverstrikeMode( void );
void			trap_Key_SetOverstrikeMode( qboolean state );
void			trap_Key_ClearStates( void );
int				trap_Key_GetCatcher( void );
void			trap_Key_SetCatcher( int catcher );
void			trap_GetClipboardData( char *buf, int bufsize );
void			trap_GetClientState( uiClientState_t *state );
void			trap_GetGlconfig( glconfig_t *glconfig );
int				trap_GetConfigString( int index, char* buff, int buffsize );
int				trap_LAN_GetServerCount( int source );
void			trap_LAN_GetServerAddressString( int source, int n, char *buf, int buflen );
void			trap_LAN_GetServerInfo( int source, int n, char *buf, int buflen );
int				trap_LAN_GetServerPing( int source, int n );
int				trap_LAN_GetPingQueueCount( void );
void			trap_LAN_ClearPing( int n );
void			trap_LAN_GetPing( int n, char *buf, int buflen, int *pingtime );
void			trap_LAN_GetPingInfo( int n, char *buf, int buflen );
void			trap_LAN_LoadCachedServers();
void			trap_LAN_SaveCachedServers();
void			trap_LAN_MarkServerVisible(int source, int n, qboolean visible);
int				trap_LAN_ServerIsVisible( int source, int n);
qboolean		trap_LAN_UpdateVisiblePings( int source );
int				trap_LAN_AddServer(int source, const char *name, const char *addr);
void			trap_LAN_RemoveServer(int source, const char *addr);
void			trap_LAN_ResetPings(int n);
int				trap_LAN_ServerStatus( const char *serverAddress, char *serverStatus, int maxLen );
int				trap_LAN_CompareServers( int source, int sortKey, int sortDir, int s1, int s2 );
int				trap_MemoryRemaining( void );
qhandle_t		trap_R_RegisterFont( const char *name );
int				trap_R_Font_StrLenPixels(const char *text, const int iFontIndex, const float scale);
int				trap_R_Font_StrLenChars(const char *text);
int				trap_R_Font_HeightPixels(const int iFontIndex, const float scale);
void			trap_R_Font_DrawString(int ox, int oy, const char *text, const float *rgba, const int setIndex, int iCharLimit, const float scale);
qboolean		trap_Language_IsAsian(void);
qboolean		trap_Language_UsesSpaces(void);
unsigned		trap_AnyLanguage_ReadCharFromString( const char *psText, int *piAdvanceCount, qboolean *pbIsTrailingPunctuation/* = NULL*/ );
void			trap_S_StopBackgroundTrack( void );
void			trap_S_StartBackgroundTrack( const char *intro, const char *loop, qboolean bReturnWithoutStarting);
int				trap_CIN_PlayCinematic( const char *arg0, int xpos, int ypos, int width, int height, int bits);
e_status		trap_CIN_StopCinematic(int handle);
e_status		trap_CIN_RunCinematic (int handle);
void			trap_CIN_DrawCinematic (int handle);
void			trap_CIN_SetExtents (int handle, int x, int y, int w, int h);
int				trap_RealTime(qtime_t *qtime);
void			trap_R_RemapShader( const char *oldShader, const char *newShader, const char *timeOffset );

// crossover
void			trap_Syscall_UI( void );
void			trap_Syscall_CG( void );

//
// ui_gameinfo.c
//

char *UI_GetBotInfoByNumber( int num );
char *UI_GetBotInfoByName( const char *name );
int UI_GetNumBots( void );
void UI_LoadBots( void );
char *UI_GetBotNameByNumber( int num );

void UI_InitGameinfo( void );

//
// JKG - ui_servercmds.c
//
qboolean UI_ServerCommand( const char *cmd_string );



#endif
