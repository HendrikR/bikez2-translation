#pragma once



//#include <windows.h>
//#include "resource.h"
#define D3D_OVERLOADS
/*#include <windowsx.h>
#include <mmsystem.h>
#include <ddraw.h>
#include <d3d.h>
#include <d3dx.h>
#include <dinput.h>
#include <dsound.h>*/
#include <stdio.h>
//#include "dsutil.h"
#include "pseudirectx.h"
#include "func.h"

// TODO: remove these after refactoring
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

/*
struct D3DDEVICE
{
// D3D Device info
	CHAR           strDesc[40];
	//GUID*          pDeviceGUID;
	D3DDEVICEDESC7 ddDeviceDesc;
	//BOOL           bHardware;
};

struct D3DDEVICEINFO
{
	CHAR           nimi[100];

	D3DDEVICE d3device[100];

	// DDraw Driver info
	GUID*          pDriverGUID;
	DDCAPS         ddDriverCaps;
	DDCAPS         ddHELCaps;

	// DDraw Mode Info
	DDSURFACEDESC2 ddsdMode;
	BOOL           bFullscreen;

	// For internal use (apps should not need these)
	GUID           guidDevice;
	GUID           guidDriver;
	DDSURFACEDESC2 ddsdModes[100];
	INT          dwNumModes;
	DWORD          dwCurrentMode;
	BOOL           bDesktopCompatible;
};

*/

struct charactertextures {//character textures
	int bodypart[4];
};

struct esine//object
{
	vvertex *triangle;
	INT vert;
};


struct objekt
{
	INT texture;//material
	INT texture2;//number of texture
	INT material;//skin 0, steel 1, cloth 2, sword 3
	D3DVECTOR upleft,downright;//size
	esine loota;//object box
	float x,y,z;
	float rx,ry,rz;

};

struct obj
{
	BOOL mirror;
	INT count;
	objekt *sisus;
	float x,y,z;
	float rx,ry,rz;
	float swordpointx,swordpointy,swordpointz;
	D3DXMATRIX sijainti;
};

struct Pictures//pictures
{
	obj *malli;
};

struct bodypartCoordinates//body part coordinates
{
	float x,y,z;
	float rx,ry,rz;
	float gox,goy,goz;//Does it fly
};

struct person
{
	int picture;//Picture in character
	float player_angle;//angle to player
	float distance;//distance from player
	float x,z,y;
	float x2,z2;//x and z were
	float direction;//direction
	float speed;//speed
	bool leg;//wich leg
	float lx,rx;//left and rigth leg
	int sektorix,sektoriz;//in wich sector it is *8000
	int jaosx,jaosz;//in wich section *400
	bool dying;//call for dying animation
	bool inactive;//character completely away
	bodypartCoordinates bodypart_coords[11];//bodypart_coordinates bodypart
	int weapon_idx;//wich weapon? -1=no weapon
	float gun_timer;//gun timer
	float energy;//energy
	int tactics;//What person does. 0=attacks 1=walks normally 2=escapes
	int walk_dir;//wich direction it is going 1=forward -1=backward
	float menoajastin;//timer for expense
	int movement_type;//0=own 1=passive 2=enemy
	bool visible;//visible or not.
	float height;//What size it is
	bool osuma[100];//has it collided with walls lately
};

struct missio
{
	int _type;//mission type (kill a character / go to place x)
	int subtype;//mission subtype (kill within a timelimit)
	int target_type;//target 0=character 1=coordinates 2=moped
	int target[100];//possible target (kill a character?)
	person asiakas[100];//taxi ride
	float targetx[100], targetz[100];//targets coordinates (go to place x?)
	float timer;//time
	int status;//0=not accomplished 1=accomplished 2=lost 3=there is no mission
	//int status2;//performed value on last frame
	int bounty;//bounty from the mission
	char briefing_short[100];//short briefing
	char briefing_long[800];//mission briefing
	int kohteita;//Ammount of similiar targets
};

struct missionReservoir//mission reservoir
{
	missio mission[20];
	int missions;//Number of mission in a level
};

struct bikebase
{
	float smoke_timer;//Timer of exhaustgasses
	int numero;//player 1 or 2
	int ase[4];//Wich gun is where
	float gun_timer[4];//timer of guns
	bool enter,esc,up,down,left,right,one,two,three,four,space;//keys
	bool enter2,esc2,up2,down2,left2,right2,one2,two2,three2,four2,space2;//keys on last frame
	float x1,y1,z1;//front wheel coordinates
	float x2,y2,z2;//rear wheel
	float x3,y3,z3;//old front wheel coordinates
	float x4,y4,z4;//old rear wheel
	float x5,y5,z5;//front wheel front side
	float x6,y6,z6;//rear wheel rear side
	float etudirection;//front wheel direction
	float speed, direction;		//speed, direction
	float angle_yaw;//Rotation of wheels in angles
	float angle_pitch;//Angle of wheelie
	float angle_roll;//tilting of the bike
	float timesparks;//sparks doesnt appear too often
	int nearestcharacter;//Nearest character
	missio mission;//What mission is on
	missio mission_random;//random mission
	int missionumero;//What mission is given from the level
	int money;//ammount of money
	int mopona;//What kind of moped
	int sektorix,sektoriz;//In wich sector it is
	int target_character;//what character is aimed at -3=no-one
	float energy;//energy
	int level;//level of the given mission
	bool osuma[100];//has it collided with walls lately
	float directiontimer;//For artificial intelligence: how long it is gone to same direction
	float tacticstimer;//For artificial intelligence: tactic timer
	int tactics;//0=attack 1=escape
	bool visible;//Is in visible on the screen
	bool inactive;//get rid of moped
	float distance;//distance from player
	float player_angle;//angle to player
	bool has_muzzle_flare;//Muzzleflare
	bool korjaamolla,korjaamolla2;//Is it now at depot. Or has it been lately at depot
	D3DXMATRIX piippu;//where is the barrel of gun
	float walltimer;//How long its been since it hit wall
	float turntime;//how long its turned
	int left3;//have it turned left lately
	int right3;//have it turned right lately
	int up3;
	int down3;
};

struct dot
{
	float x1,y1,z1;//start point
	float x2,y2,z2;//end point
};

struct Line//route or a line
{
	int line_count;
	dot *point;
};

struct Route//routes
{
	int route_count;//line
	Line *route;
};

struct RouteGroup//route group
{
	int group_count;
	Route *routes;
};

struct bullet
{
	D3DXVECTOR3 place_old;//place old
	D3DXVECTOR3 place;//place
	D3DXVECTOR3 direction;//direction
	float q,w,e;//Angle of bullet
	int from_gun;//from gun
	bool remove;//delete
	float smoke_count;//How much time for making smoketrail
	int sektorix[2],sektoriz[2];//in wich sector it is
	//int jaosx,jaosz;//in wich section it is *800
	float timer;//time
	float speed;//bullet speed
	int from_moped;//whos bullet it is// positive=mopeds -1=character
	int from_character;//which character shot it (prevents suicides)
	float distance;//distance from the player
	int target;//-6667=no-one, negatives-1 are mopeds, positives are characters
};

struct weapon
{

	float smoke_size;//Size of smoke cloud
	float damage;//damage
	float dispersion;//dispersion
	int picture;//what does this gun look like?
	int bullet_picture;//bullet picture
	int decal_picture;//hole in wall -1 = empty
	int smoke_filled;//Is a hole in wall filled with smoke?
	int explosion_size;//Size of explosion
	float speed;//speed
	int rate_of_fire;//rate of fire
	float smoke_duration;//the smoke lasts
	float weight;//bullet weigth
	float smoke_count;//how often is smoke trail made?
	int num_bounces;//how many times it bounces from walls;
	bool homing;//is it homing
	int pdamage,pspeed,prate_of_fire,price,price2,pricehoming;//related to peddling //pdamage,pspeed,prateoffire,price,price2,pricesearch
	int bullets_per_shot;//how many bullets from one shot
	int _type;//gun type 0=pistol 1=machinegun 2=shotgun 3=rocketlauncher 4=no sound
};

struct smoke
{
	D3DXVECTOR3 place;//place
	int _type;//place
	float q,w,e;//smoke angle
	int picture;//subpicture 0 or 1
	float timer;//how much time
	float cos,sin,up;//for the angle
	float rotate;
	float size;//what size it is?
	float suurenee;//How much it grows
	bool inactive;//off
};

/*struct monttu
  {
  D3DVECTOR position;
  float     u, v;

  };*/

struct light
{
	bool on;
	D3DLIGHT7 valo;	//light
	float timer;//how much timeleft
};




BOOL load(const char filename[200],obj *target,BOOL mirror,BOOL miekkakala);//load... swordfish
BOOL loadwall(const char filename[200],RouteGroup *target,BOOL mirror);//loadwall
BOOL loadtext();//loadtext
void init(void);
bool createscreen(void);
bool Render(void);
bool readpictures(void);//read pictures
void CleanUp(void);//destroys stuff
BOOL draw(obj *objects);
void removeobj(obj *target, int indeksi);//delete object
bool initkeyb(void);
bool deinitkeyb(void);
void readkeyb(void);//readkeyb
void aja(bikebase *moped);//driving mopeds
void initMopeds(void);//initializing mopeds
void calculateCollisions(void);//calculate collisions
void shoot(int target,int from_character,int from_moped, float timer,bikebase *moped, int weapon_idx,float placex,float placey,float placez,float directionx,float directiony,float directionz);//shooting //target, who, whos, time, bikebase, mopeds, as_a_weapon, placex,palcey,placez, directionx,directiony,directionz
void calculatebullets(void);//bullets fly
void fromsmoke(float size, float suurenee,bool rotate,float savukesto,float x,float y,float z,int _type,float q,float w,float e);//creates smoke
//void removebullet(int a);//inactivetaa luodin sarjasta
void calculatesmokes(void);//laskee savut
void SetupPixelFog(DWORD dwColor, DWORD dwMode);//fog
void SetupVertexFog(float fStart, float fEnd,DWORD dwColor, DWORD dwMode, BOOL fUseRange, FLOAT fDensity);//fog
void setLights(float x,float y,float z);//makes light
void removeLight(int a, int *b);//deletes light
void moveparts(int q);//moves parts to their places
BOOL drawfast(obj *objects);//draws faster
void calculatecharacters(void);//calculates movements of humans
//void removecharacter(int a);//deletes a character
void rendercharacters(void);//draws characters
//void rendertext(INT x, INT y, INT fontti,CHAR teksti[100],LPDIRECTDRAWSURFACE7 pinta,LPDIRECTDRAWSURFACE7 font1);
void rendertext(INT x, INT y, INT fontti,const char teksti[100]);
void render_game(void);//draws moped driving
void render_mission(void);//draws mission briefing
void create_mission(bikebase *moped,int missionumero);
void laskekoordinaatit(float *x,float *z);//gives x and z wich are not inside houses from the map.
void laskemissiot(bikebase *moped);//examines is a mission accomplished
void create_character(int q);//randomizes a character to field
void load_missions(void);//reads missions
void laskemoped(void);//calculate mopeds //for Artificial intelligence of mopeds
void create_mopo(int d);//randomizes a moped to field
void render_workshop(void);//draws a depot
void readkey_game(void);//read keys during game
void readsaves(void);//read saved games
void game_load(void);//loads a game
void game_save(void);//saves a game
void render_menu(void);//draws the menu
void game_new(void);//starts a new game
void cfg_save(void);//saves settings
void cfg_load(void);//loads settings
void sounds_start(void);//initialize voices
void playsound(int samplenumero,float volume,float placex,float placez);//plays a sound
void clearzbuffer(void);
void startApplication(HINSTANCE hInstance);




//game content objects
const float maxvisible =25000.0f;
int mapsx,mapsz;//ammount of maps
const int MAX_BULLETS=1000;//400//maximium ammount of bullets
const int MAX_SMOKES=4000;//400//maximium ammount of smokes
const int MAX_LIGHTS=10;//maximium ammount of lights
const int MAX_CHARACTERS=1000;//maximium ammount of characters
D3DVECTOR center_point[MAX_SMOKES]; //centerpoint[maximium ammount of smokes]
DWORD visible[MAX_SMOKES];
float radius[MAX_SMOKES];
pvertex triangles[MAX_SMOKES*12];//triangles
pvertex bullet_trace[MAX_BULLETS*2];//bullet trace
bikebase moped[1000];//mopeds
int num_mopeds;//ammount of mopeds
int headquarter_posx,headquarter_posz;//coordinates of headquarters
RouteGroup wallgroup[2];//walls
int num_wallgroups;//ammount of wall groups
bullet bullet[MAX_BULLETS];//bullets
weapon ase[20];//guns
smoke smokes[MAX_SMOKES];//smokes
int maps[200][200];
person character[MAX_CHARACTERS];//person character[maximium ammount of characters]
D3DVECTOR center_pointcharacter[MAX_CHARACTERS];//center point character
DWORD visiblecharacter[MAX_CHARACTERS];//visible character
float radiuscharacter[MAX_CHARACTERS];//radius character
D3DVECTOR center_pointmap[1000];//centerpoint character
DWORD visiblemap[1000];
float radiusmap[1000];
//float speedoli;
int gamephase,gamephase_old;//gamephase, gamepahse_was
int gamephase2,gamephase2_old;//gamephase2, gamepahse_was2
light lights[MAX_LIGHTS];
bool mapmode,mapmode2;//0 =normal 1=from above
float kamerax1,kameray1,kameraz1;//camera from
float kamerax2,kameray2,kameraz2;//camera to
charactertextures charactertexture[10];//charactertextures
missionReservoir missionlevel[10];//mission reservoir
char missioninfo[21][800];//mission briefing
int mission_is_read;//is briefing readed
float gamespeed;//game speed
int repair_cost;//price of repairs
char m_filenames[10][256];//file names of saved files
int letters_in_file_names[10];//how many letters are in file names
bool loadable[10];//is it able to load
int savegame_slot;//wich save is selected
bool is_saved;//is game saved
int keytimer;//keyboard timer
int letters_in_name;//how many letters in name
char savefilename[256];//name of save
float cursor_timer;//cursor timer
int menu_selection;//what is selected in menu
int menuja[10];//how many selections are possible
bool options[10];//options
int game_difficulty;//game difficulty level
bool is_selected;//selected //while setting keys
float quake;//makes game quake for short time


//sounds
int SAMPLE_NUMBER;//number of samples
LPDIRECTSOUND        lpDS;
//LPDIRECTSOUNDBUFFER pDSB;
HSNDOBJ voices[25];
bool SOUNDS_ON;//is sound engine initialized
bool SOUNDS_LOADED;//are samples loaded
WORD			DLLversion;
float soundtimer[25];//samples are not played every millisecond

//objects
Pictures mallit[11];

//input
LPDIRECTINPUT8        g_lpDI;
LPDIRECTINPUTDEVICE8  g_lpDIDevice;
LPDIRECTINPUTDEVICE8  g_pMouse;
DIMOUSESTATE		  mousestate;
DIMOUSESTATE		  mousestate2;
char  buffer[256], buffer2[256];
float mousex, mousey;
float plusmiinus;// tempfloat adjustable by keyboard
int key[20];//game input keys
bool pressed,pressed2;//is any key pressed


int characters;//ammount of characters in a level
int smoke_count;//ammount of smokes in a level
int bullet_count;//ammount of bullets in the air
LPDIRECT3DDEVICE7 m_pDevice;
LPDIRECT3D7 m_pD3D;
LPDIRECTDRAWSURFACE7 taka;
LPDIRECTDRAWSURFACE7 m_pPrimary;
LPDIRECTDRAW7 m_pDD;
LPDIRECTDRAWSURFACE7 zbuffer;//zbuffer
D3DMATRIX m_World, m_View, m_Projection;
int enumerationint1,enumerationint2;//enumbering ints
int SCREEN_WIDTH;
int SCREEN_HEIGHT;
int SCREEN_BITS;
int screenmode;
//D3DDEVICEINFO info;
DWORD m_LastTime;
bool is_quitting;//are we quiting?
int material_count;//ammount of materials
D3DMATERIAL7 *mat;
ID3DXMatrixStack *matrices;
LONG bug1,bug2,bug3;
float elapsed,elapsed2;
float elapsed3[100];
D3DDEVICEDESC7 desc3d;
float dx,dx2,dy,dz;//camera
float camx,camy,camz;//camera
LPDIRECTDRAWSURFACE7
	*background		//background
	//,cube
	//,
	//,font1
	,*pictures;//pictures
