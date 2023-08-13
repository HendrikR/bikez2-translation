// bikez2.cpp : Defines the entry point for the application.
//

#include "bikez2.h"
#include "pseudirectx.h"
#include <iostream>

int numpictures=6;

const int objnum0=6; //obj1 - bike
const int objnum1=8; //map0
const int objnum2=18; //obj2 - bullets
const int objnum3=11; //character0 (character0)
const int objnum4=11; //character1
const int objnum5=11; //character2
const int objnum6=3; //obj3 - bike2
const int objnum7=11; //character3
const int objnum8=11; //character4
const int objnum9=3; //obj4 - bike3
const int objnum10=11; //character5


#define RELEASE(x) if (x) {x->Release(); x=NULL;}
#define sqr(x)				((x)*(x))
static const float pi = 3.1415926535897932384626433832795f;

// Global Variables:
HINSTANCE hInst;								// current instance
HWND hWnd;
LPD3DXCONTEXT dxctx;             // Direct3DX context handle.

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

int sub(int test){
	int age = 33;
	return age*test;

}


//BOOL loadwall(char nimi[200],RouteGroup *target,BOOL mirror);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hInstNULL, LPSTR lpszCmdLine, int nCmdShow){
	startApplication(hInstance);
        return 0;
}

int main(int argc, char** argv) {
        WinMain(0, 0, argv[0], 1);
        return 0;
}

void startApplication(HINSTANCE hInstance)
{
 	// TODO: Place code here.
	MSG msg;

	// Initialize global strings
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, 1))
	{
		return;
	}

	init();

        BOOL bGotMsg;
	m_LastTime = GetTickCount(); //reset timer
	bool g_bReady=true;
	bool g_bActive=true;
	PeekMessage( &msg, NULL, 0U, 0U, PM_NOREMOVE );
	while( msg.type != SDL_QUIT )
	{
                // Use PeekMessage() if the app is active, so we can use idle time to
                // render the scene. Else, use GetMessage() to avoid eating CPU time.
                if( g_bActive )
                        bGotMsg = PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE );
                else
                        bGotMsg = GetMessage( &msg, NULL, 0U, 0U );
		if( bGotMsg )
                {
			TranslateMessage( &msg );
                        DispatchMessage( &msg );
                }
		else
		{
                        // Render a frame during idle time (no messages are waiting)
                        if( g_bActive && g_bReady )
			{


				readkeyb();
				if(!is_quitting)
				{
					Render();
					dxctx->UpdateFrame(0);

				}
				else{
					break;
				}
			}
                }
	}

}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style		= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon		= LoadIcon(hInstance, (LPCTSTR)IDI_ICON1);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	//wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName	= (LPCSTR)"bikez2";
	wcex.lpszClassName	= "bikez2";
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_ICON1);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
        hInst = hInstance; // Store instance handle in our global variable

        hWnd=CreateWindow(
                        "bikez2",
                        "bikez2",
                        WS_POPUPWINDOW|WS_VISIBLE,
                        CW_USEDEFAULT,
                        0,
                        1026,
                        770,
                        NULL,
                        NULL,
                        hInstance,
                        NULL);

        if (!hWnd)
        {
                return FALSE;
        }

        ShowWindow(hWnd, nCmdShow);
        return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//int wmId, wmEvent;
	//PAINTSTRUCT ps;
	//HDC hdc;

	switch (message)
	{
        case WM_ACTIVATE:
        {
                if (g_pMouse)
                {
                        g_pMouse->Acquire();
                }
                if (g_lpDIDevice)
                {
                        g_lpDIDevice->Acquire();
                }
        }
        break;
        case WM_CHAR:	//read keys for input name
        {
                if(gamephase==4)
                        if(gamephase2==3)
				if(keytimer<0){
					keytimer=25;
					bug1=bug1+1;

                                        switch (wParam) {
                                        case 0x0A:break;  // linefeed
                                        case 0x1B:break;  // escape
                                        case 0x09:break;  // tab
                                        case 0x0D:break;  // carriage return

                                        case 0x08:  // backspace
                                                letters_in_name=letters_in_name-1;
                                                if(letters_in_name<0)letters_in_name=0;
                                                savefilename[letters_in_name]=0;
                                                break;

                                        default:
                                                char che=(char)wParam;
                                                savefilename[letters_in_name]=che;
                                                letters_in_name=letters_in_name+1;
                                                if(letters_in_name>49)letters_in_name=49;
                                        }
				}
        }
        break;
        case WM_DESTROY:
                CleanUp();
                PostQuitMessage(0);
                break;

        default:
                return DefWindowProc(hWnd, message, wParam, lParam);
        }
        return 0;
}
/*
// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
switch (message)
{
case WM_INITDIALOG:
return TRUE;

case WM_COMMAND:
if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
{
EndDialog(hDlg, LOWORD(wParam));
return TRUE;
}
break;
}
return FALSE;
}
*/

void SetupPixelFog(DWORD dwColor, DWORD dwMode)
{
        float fStart = maxvisible-5000,    // for linear mode
                fEnd   = maxvisible,
                fDensity = 0.66f;  // for exponential modes

	fStart=0.5f;
	fEnd=1.0f;
        // Enable fog blending.
        m_pDevice->SetRenderState(D3DRENDERSTATE_FOGENABLE, TRUE);

        // Set the fog color.
        m_pDevice->SetRenderState(D3DRENDERSTATE_FOGCOLOR, dwColor);

        // Set fog parameters.
        if(D3DFOG_LINEAR == dwMode)
        {
                m_pDevice->SetRenderState(D3DRENDERSTATE_FOGTABLEMODE, dwMode);
                m_pDevice->SetRenderState(D3DRENDERSTATE_FOGSTART, *(DWORD *)(&fStart));
                m_pDevice->SetRenderState(D3DRENDERSTATE_FOGEND,   *(DWORD *)(&fEnd));
        }
        else
        {
                m_pDevice->SetRenderState(D3DRENDERSTATE_FOGTABLEMODE, dwMode);
                m_pDevice->SetRenderState(D3DRENDERSTATE_FOGDENSITY, *(DWORD *)(&fDensity));
        }

}

void SetupVertexFog(float fStart, float fEnd, DWORD dwColor, DWORD dwMode, BOOL fUseRange, FLOAT fDensity)
{




        // Enable fog blending.
        m_pDevice->SetRenderState(D3DRENDERSTATE_FOGENABLE, TRUE);

        // Set the fog color.
        m_pDevice->SetRenderState(D3DRENDERSTATE_FOGCOLOR, dwColor);

        // Set fog parameters.
        if(D3DFOG_LINEAR == dwMode)
        {
                m_pDevice->SetRenderState(D3DRENDERSTATE_FOGVERTEXMODE, dwMode);
                m_pDevice->SetRenderState(D3DRENDERSTATE_FOGSTART, *(DWORD *)(&fStart));
                m_pDevice->SetRenderState(D3DRENDERSTATE_FOGEND,   *(DWORD *)(&fEnd));
        }
        else
        {
                m_pDevice->SetRenderState(D3DRENDERSTATE_FOGSTART, *(DWORD *)(&fStart));
                m_pDevice->SetRenderState(D3DRENDERSTATE_FOGEND,   *(DWORD *)(&fEnd));
		m_pDevice->SetRenderState(D3DRENDERSTATE_FOGVERTEXMODE, dwMode);
                m_pDevice->SetRenderState(D3DRENDERSTATE_FOGDENSITY, *(LPDWORD)(&fDensity));
        }

        // Enable range-based fog if desired (only supported for vertex fog).
        // For this example, it is assumed that fUseRange is set to a nonzero value
        // only if the driver exposes the D3DPRASTERCAPS_FOGRANGE capability.
        //
        // Note: this is slightly more performance intensive
        //       than non-range-based fog.
        if(fUseRange)
                m_pDevice->SetRenderState(
                                D3DRENDERSTATE_RANGEFOGENABLE,
                                TRUE);
}


//Program initialization
void init()
{
	int q;
	RECT rcSource, rcDest;

	bool osuma=false;
	keytimer=0;

	//randomgenerator(i didnt find command for this)
	for (q=0; q<(int)GetTickCount()/100; q++){
		rand();
	}

	SOUNDS_ON=true;
	SOUNDS_LOADED=false;


	//initialize 3d
	D3DXInitialize();
	ShowCursor(false);
	SetCursor(NULL);
	LoadCursor(NULL, IDC_ARROW);
	initkeyb();
	createscreen();
	readpictures();
	cfg_load();
	//background image
	m_pDevice->Clear( 0, NULL, D3DCLEAR_TARGET, 0xFFFFFFFF, 0, 0 );
	rcSource.top = 0;
	rcSource.left = 0;
	rcSource.bottom = 132;
	rcSource.right = 351;
	rcDest.top = (int)((SCREEN_HEIGHT-132)/2);
	rcDest.left = (int)((SCREEN_WIDTH-351)/2);
	rcDest.bottom = rcDest.top+132;
	rcDest.right = rcDest.left+351;
	/*if(rcDest.top<0)rcDest.top=0;
          if(rcDest.left<0)rcDest.left=0;
          if(rcDest.bottom>SCREEN_HEIGHT)rcDest.bottom=SCREEN_HEIGHT;
          if(rcDest.right>SCREEN_WIDTH)rcDest.right=SCREEN_WIDTH;*/

	taka->Blt(&rcDest, pictures[5], &rcSource,DDBLT_WAIT  ,NULL);
	dxctx->UpdateFrame(0);

	plusmiinus=0;

        std::cout << "initializing 3D parameters" << std::endl;
        // Initialize and set the matrices
	m_World = IdentityMatrix();
	m_View = ViewMatrix(D3DVECTOR(0,0,0), D3DVECTOR(0,0,1), D3DVECTOR(0,1,0), 0);

	//m_Projection = ProjectionMatrix(50.0f, 12000.0f, (float)(80*pi/180)); // 60 vision field
	m_Projection = ProjectionMatrix(100.0f, maxvisible, (float)(80*pi/180)); // 60 vision field
	m_pDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &m_World);
	m_pDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &m_View);
	m_pDevice->SetTransform(D3DTRANSFORMSTATE_PROJECTION, &m_Projection);

	// Set the render states
	//m_pDevice->SetRenderState(D3DRENDERSTATE_ANTIALIAS,D3DANTIALIAS_SORTDEPENDENT );//ota DDSCAPS2_HINTANTIALIASING inactive jos inactivetat

	//sumut
	if((desc3d.dpcTriCaps.dwRasterCaps&D3DPRASTERCAPS_FOGVERTEX)&&(!(desc3d.dpcTriCaps.dwRasterCaps&D3DPRASTERCAPS_FOGRANGE)))
		SetupVertexFog(maxvisible-5000,maxvisible,0x004C4C4C, D3DFOG_LINEAR  , FALSE, 0);//sumu
	if((desc3d.dpcTriCaps.dwRasterCaps&D3DPRASTERCAPS_FOGVERTEX)&&(desc3d.dpcTriCaps.dwRasterCaps&D3DPRASTERCAPS_FOGRANGE))
		SetupVertexFog(maxvisible-5000,maxvisible,0x004C4C4C, D3DFOG_LINEAR  , TRUE, 0);//sumu
	/*if(desc3d.dpcTriCaps.dwRasterCaps&D3DPRASTERCAPS_FOGTABLE)
          SetupPixelFog(0x004C4C4C, D3DFOG_LINEAR);*/


	m_pDevice->SetRenderState(D3DRENDERSTATE_TEXTUREPERSPECTIVE,TRUE);
	m_pDevice->SetRenderState(D3DRENDERSTATE_ZENABLE,TRUE);
	m_pDevice->SetRenderState(D3DRENDERSTATE_SHADEMODE,D3DSHADE_GOURAUD);
	m_pDevice->SetRenderState(D3DRENDERSTATE_CULLMODE,D3DCULL_CCW);//D3DCULL_CCW
	m_pDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE,TRUE);


	//m_pDevice->SetTextureStageState(0,D3DTSS_MAGFILTER, D3DTFG_LINEAR);
	//m_pDevice->SetTextureStageState(0,D3DTSS_MINFILTER, D3DTFN_LINEAR);

	//first linear filter
	if(desc3d.dpcTriCaps.dwTextureFilterCaps&D3DPTFILTERCAPS_MAGFLINEAR)
		m_pDevice->SetTextureStageState(0,D3DTSS_MAGFILTER, D3DTFG_LINEAR);
	if(desc3d.dpcTriCaps.dwTextureFilterCaps&D3DPTFILTERCAPS_MINFLINEAR)
		m_pDevice->SetTextureStageState(0,D3DTSS_MINFILTER, D3DTFG_LINEAR);

	//then anistropic filter
	if(desc3d.dpcTriCaps.dwTextureFilterCaps&D3DPTFILTERCAPS_MAGFANISOTROPIC)
		m_pDevice->SetTextureStageState(0,D3DTSS_MAGFILTER, D3DTFG_ANISOTROPIC);
	if(desc3d.dpcTriCaps.dwTextureFilterCaps&D3DPTFILTERCAPS_MINFANISOTROPIC)
		m_pDevice->SetTextureStageState(0,D3DTSS_MINFILTER, D3DTFN_ANISOTROPIC);


	m_pDevice->SetTextureStageState(0,D3DTSS_MAXANISOTROPY,2);


	m_pDevice->SetTextureStageState(0,D3DTSS_ADDRESS,D3DTADDRESS_MIRROR);

	m_pDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS,
                        D3DTTFF_COUNT2 //| D3DTTFF_PROJECTED
                );

	m_pDevice->SetRenderState( D3DRENDERSTATE_LIGHTING,TRUE);

	//set mouse center
	mousex=(float)(SCREEN_WIDTH/2);
	mousey=(float)(SCREEN_HEIGHT/2);

	//load missions
	load_missions();

	//load textures
	loadtext();
	DDCOLORKEY color;
	color.dwColorSpaceHighValue=0x000000;//CLR_INVALID is top corner
	color.dwColorSpaceLowValue=0x000000;
	//color.dwColorSpaceHighValue=CLR_INVALID;//CLR_INVALID is top corner
	//color.dwColorSpaceLowValue=CLR_INVALID;

	background[15]->SetColorKey(DDCKEY_SRCBLT,&color);

	//load objects //remember to add mallit[n]
        std::cout << "loading objects" << std::endl;
	mallit[0].malli= new obj[objnum0];
	mallit[1].malli= new obj[objnum1];
	mallit[2].malli= new obj[objnum2];
	mallit[3].malli= new obj[objnum3];
	mallit[4].malli= new obj[objnum4];
	mallit[5].malli= new obj[objnum5];
	mallit[6].malli= new obj[objnum6];
	mallit[7].malli= new obj[objnum7];
	mallit[8].malli= new obj[objnum8];
	mallit[9].malli= new obj[objnum9];
	mallit[10].malli= new obj[objnum10];
	load("models/obj1.3dw",	mallit[0].malli,	false,	false);
	load("models/map0.3dw",	mallit[1].malli,	false,	false);
	load("models/obj2.3dw",	mallit[2].malli,	false,	false);
	load("models/ukko0.3dw",	mallit[3].malli,	false,	false);
	load("models/ukko1.3dw",	mallit[4].malli,	false,	false);
	load("models/ukko2.3dw",	mallit[5].malli,	false,	false);
	load("models/obj3.3dw",	mallit[6].malli,	false,	false);
	load("models/ukko3.3dw",	mallit[7].malli,	false,	false);
	load("models/ukko4.3dw",	mallit[8].malli,	false,	false);
	load("models/obj4.3dw",	mallit[9].malli,	false,	false);
	load("models/ukko5.3dw",	mallit[10].malli,	false,	false);

/*
  moveparts(3);//moves character0 pieces to their places
  moveparts(4);//moves character1 pieces to their places
  moveparts(5);//moves character1 pieces to their places
*/


	//initialize matrix
	ZeroMemory(&matrices, sizeof(matrices));
	D3DXCreateMatrixStack(  0, &matrices);

	//load walls
        std::cout << "loading walls" << std::endl;
	num_wallgroups=2;//remember to add it to the header
	loadwall("models/wall0.3dw",&wallgroup[0],false);//walls of maps(or levels)
	loadwall("models/wall1.3dw",&wallgroup[1],false);//moped

	is_selected=false;
	menu_selection=1;
	menuja[0]=4;
	menuja[1]=13;
	menuja[2]=13;
	menuja[3]=13;
	menuja[4]=13;
	menuja[5]=4;
	menuja[6]=13;

	//character textures
	charactertexture[0].bodypart[0]=10;//torso
	charactertexture[0].bodypart[1]=11;//legs
	charactertexture[0].bodypart[2]=12;//hand
	charactertexture[0].bodypart[3]=14;//face

	charactertexture[1].bodypart[0]=28;//torso
	charactertexture[1].bodypart[1]=28;//legs
	charactertexture[1].bodypart[2]=28;//hand
	charactertexture[1].bodypart[3]=29;//face

	charactertexture[2].bodypart[0]=49;//torso
	charactertexture[2].bodypart[1]=51;//legs
	charactertexture[2].bodypart[2]=50;//hand
	charactertexture[2].bodypart[3]=48;//face

	charactertexture[3].bodypart[0]=53;//torso
	charactertexture[3].bodypart[1]=55;//legs
	charactertexture[3].bodypart[2]=54;//hand
	charactertexture[3].bodypart[3]=52;//face

	charactertexture[4].bodypart[0]=57;//torso
	charactertexture[4].bodypart[1]=59;//legs
	charactertexture[4].bodypart[2]=58;//hand
	charactertexture[4].bodypart[3]=56;//face

	sounds_start();


	//weapons
	//weapons could be loaded from a file.
        std::cout << "initializing weapons" << std::endl;
	q=0;
	ase[q].picture=0;//machine gun
	ase[q].speed=70;
	ase[q].dispersion=0.2f;
	ase[q].rate_of_fire=30;
	ase[q].decal_picture=0;
	ase[q].bullet_picture=0;
	ase[q].smoke_filled=0;
	ase[q].smoke_duration=5000;
	ase[q].weight=0.00001f;
	ase[q].explosion_size=0;
	ase[q].smoke_count=0;
	ase[q].num_bounces=3;
	ase[q].damage=0.4f;
	ase[q].homing=false;
	ase[q].smoke_size=1.0f;
	ase[q].pdamage=1;
	ase[q].pspeed=5;
	ase[q].prate_of_fire=9;
	ase[q].bullets_per_shot=1;
	ase[q]._type=4;


	q=1;
	ase[q].picture=1;//homing missile
	ase[q].speed=3.7f;
	ase[q].dispersion=0.01f;
	ase[q].rate_of_fire=1000;
	ase[q].decal_picture=1;
	ase[q].bullet_picture=1;
	ase[q].smoke_filled=2;
	ase[q].smoke_duration=1000;
	ase[q].weight=0.0f;
	ase[q].explosion_size=3;
	ase[q].smoke_count=10;
	ase[q].num_bounces=0;
	ase[q].damage=8;
	ase[q].homing=true;
	ase[q].smoke_size=1.0f;
	ase[q].pdamage=10;
	ase[q].pspeed=1;
	ase[q].prate_of_fire=2;
	ase[q].bullets_per_shot=1;
	ase[q]._type=4;

	q=2;
	ase[q].picture=0;//bounce and explode
	ase[q].speed=666;//speed=random
	ase[q].dispersion=0.1f;
	ase[q].rate_of_fire=1;
	ase[q].decal_picture=-1;
	ase[q].bullet_picture=2;
	ase[q].smoke_filled=0;
	ase[q].smoke_duration=5000;
	ase[q].weight=0.01f;
	ase[q].explosion_size=0;
	ase[q].smoke_count=0;
	ase[q].num_bounces=0;
	ase[q].damage=1;
	ase[q].homing=false;
	ase[q].pdamage=2;
	ase[q].pspeed=2;
	ase[q].prate_of_fire=2;
	ase[q].bullets_per_shot=1;
	ase[q]._type=4;

	q=3;
	ase[q].picture=1;//spark
	ase[q].speed=3;
	ase[q].dispersion=0.1f;
	ase[q].rate_of_fire=1;
	ase[q].decal_picture=-1;
	ase[q].bullet_picture=2;
	ase[q].smoke_filled=0;
	ase[q].smoke_duration=5000;
	ase[q].weight=0.01f;
	ase[q].explosion_size=0;
	ase[q].smoke_count=0;
	ase[q].num_bounces=0;
	ase[q].damage=0;
	ase[q].homing=false;
	ase[q].pdamage=2;
	ase[q].pspeed=2;
	ase[q].prate_of_fire=2;
	ase[q].bullets_per_shot=1;
	ase[q]._type=4;

	q=4;
	ase[q].picture=1;//blood
	ase[q].speed=2;
	ase[q].dispersion=0.4f;
	ase[q].rate_of_fire=1;
	ase[q].decal_picture=-1;
	ase[q].bullet_picture=3;
	ase[q].smoke_filled=0;
	ase[q].smoke_duration=5000;
	ase[q].weight=0.01f;
	ase[q].explosion_size=0;
	ase[q].smoke_count=0;
	ase[q].num_bounces=0;
	ase[q].damage=0;
	ase[q].homing=false;
	ase[q].pdamage=2;
	ase[q].pspeed=2;
	ase[q].prate_of_fire=2;
	ase[q].bullets_per_shot=1;
	ase[q]._type=4;

	q=5;
	ase[q].picture=0;//pistole
	ase[q].speed=50;
	ase[q].dispersion=0.2f;
	ase[q].rate_of_fire=500;
	ase[q].decal_picture=0;
	ase[q].bullet_picture=0;
	ase[q].smoke_filled=0;
	ase[q].smoke_duration=5000;
	ase[q].weight=0.00001f;
	ase[q].explosion_size=0;
	ase[q].smoke_count=0;
	ase[q].num_bounces=2;
	ase[q].damage=2.1f;
	ase[q].homing=false;
	ase[q].pdamage=2;
	ase[q].pspeed=2;
	ase[q].prate_of_fire=2;
	ase[q].bullets_per_shot=1;
	ase[q]._type=4;
/*
  q=6;
  ase[q].picture=0;//mopedweapon0 // mopo ase0
  ase[q].speed=45;
  ase[q].dispersion=0.2f;
  ase[q].rate_of_fire=711;
  ase[q].decal_picture=0;
  ase[q].bullet_picture=0;
  ase[q].smoke_filled=0;
  ase[q].smoke_duration=5000;
  ase[q].weight=0.00001f;
  ase[q].explosion_size=0;
  ase[q].smoke_count=0;
  ase[q].num_bounces=2;
  ase[q].damage=0.1f;
  ase[q].homing=false;
  ase[q].pdamage=2;
  ase[q].pspeed=2;
  ase[q].prate_of_fire=2;

  q=7;
  ase[q].picture=0;//mopedweapon1 // mopo ase1
  ase[q].speed=45;
  ase[q].dispersion=0.2f;
  ase[q].rate_of_fire=711;
  ase[q].decal_picture=0;
  ase[q].bullet_picture=0;
  ase[q].smoke_filled=0;
  ase[q].smoke_duration=5000;
  ase[q].weight=0.00001f;
  ase[q].explosion_size=0;
  ase[q].smoke_count=0;
  ase[q].num_bounces=2;
  ase[q].damage=0.1f;
  ase[q].homing=false;
  ase[q].pdamage=2;
  ase[q].pspeed=2;
  ase[q].prate_of_fire=2;

  q=8;
  ase[q].picture=0;//mopedweapon2 // mopo ase2
  ase[q].speed=45;
  ase[q].dispersion=0.2f;
  ase[q].rate_of_fire=711;
  ase[q].decal_picture=0;
  ase[q].bullet_picture=0;
  ase[q].smoke_filled=0;
  ase[q].smoke_duration=5000;
  ase[q].weight=0.00001f;
  ase[q].explosion_size=0;
  ase[q].smoke_count=0;
  ase[q].num_bounces=2;
  ase[q].damage=0.1f;
  ase[q].homing=false;
  ase[q].pdamage=2;
  ase[q].pspeed=2;
  ase[q].prate_of_fire=2;

  q=9;
  ase[q].picture=0;//mopedweapon3 // mopo ase3
  ase[q].speed=45;
  ase[q].dispersion=0.2f;
  ase[q].rate_of_fire=711;
  ase[q].decal_picture=0;
  ase[q].bullet_picture=0;
  ase[q].smoke_filled=0;
  ase[q].smoke_duration=5000;
  ase[q].weight=0.00001f;
  ase[q].explosion_size=0;
  ase[q].smoke_count=0;
  ase[q].num_bounces=2;
  ase[q].damage=0.1f;
  ase[q].homing=false;
  ase[q].pdamage=2;
  ase[q].pspeed=2;
  ase[q].prate_of_fire=2;
*/
	q=10;
	ase[q].picture=0;//police gun 0 pistole
	ase[q].speed=70;
	ase[q].dispersion=0.2f;
	ase[q].rate_of_fire=711;
	ase[q].decal_picture=0;
	ase[q].bullet_picture=0;
	ase[q].smoke_filled=0;
	ase[q].smoke_duration=5000;
	ase[q].weight=0.00001f;
	ase[q].explosion_size=0;
	ase[q].smoke_count=0;
	ase[q].num_bounces=5;
	ase[q].damage=5.5f;
	ase[q].homing=false;
	ase[q].smoke_size=1.0f;
	ase[q].bullets_per_shot=1;
	ase[q].pdamage=3;
	ase[q].pspeed=2;
	ase[q].prate_of_fire=2;
	ase[q]._type=4;

	q=11;
	ase[q].picture=0;//police gun 1 machinegun
	ase[q].speed=70;
	ase[q].dispersion=0.2f;
	ase[q].rate_of_fire=30;
	ase[q].decal_picture=0;
	ase[q].bullet_picture=0;
	ase[q].smoke_filled=0;
	ase[q].smoke_duration=5000;
	ase[q].weight=0.00001f;
	ase[q].explosion_size=0;
	ase[q].smoke_count=0;
	ase[q].num_bounces=3;
	ase[q].damage=0.8f;
	ase[q].homing=false;
	ase[q].smoke_size=1.0f;
	ase[q].bullets_per_shot=1;
	ase[q].pdamage=2;
	ase[q].pspeed=5;
	ase[q].prate_of_fire=9;
	ase[q]._type=4;

	q=12;
	ase[q].picture=0;//police gun 2 missile
	ase[q].speed=3.7f;
	ase[q].dispersion=0.01f;
	ase[q].rate_of_fire=2000;
	ase[q].decal_picture=1;
	ase[q].bullet_picture=1;
	ase[q].smoke_filled=2;
	ase[q].smoke_duration=1000;
	ase[q].weight=0.0f;
	ase[q].explosion_size=3;
	ase[q].smoke_count=10;
	ase[q].num_bounces=0;
	ase[q].damage=10;
	ase[q].homing=true;
	ase[q].smoke_size=1.0f;
	ase[q].bullets_per_shot=1;
	ase[q].pdamage=10;
	ase[q].pspeed=1;
	ase[q].prate_of_fire=1;
	ase[q]._type=4;

	gamephase2=0;
	gamephase=4;
	elapsed=15;
	for (q=0; q<100; q++){
		elapsed3[q]=15;
	}
	setLights(0,0,0);
	setLights(0,0,0);


}

void moveparts(int q)
{
//int q;
	//for (q=0; q<1; q++){

	//head
	character[q].bodypart_coords[2].x=0;
	character[q].bodypart_coords[2].y=37.1f;
	character[q].bodypart_coords[2].z=0;

	//torso
	character[q].bodypart_coords[1].x=0;
	character[q].bodypart_coords[1].y=0;
	character[q].bodypart_coords[1].z=0;

	//butt
	character[q].bodypart_coords[0].x=0;
	character[q].bodypart_coords[0].y=0;
	character[q].bodypart_coords[0].z=0;

	//upper leg
	character[q].bodypart_coords[5].x=-0.8f;
	character[q].bodypart_coords[5].y=-3.9f;
	character[q].bodypart_coords[5].z=-6.7f;
	character[q].bodypart_coords[9].x=-0.8f;
	character[q].bodypart_coords[9].y=-3.9f;
	character[q].bodypart_coords[9].z=6.7f;

	//lower leg
	character[q].bodypart_coords[6].x= 3.2f -character[q].bodypart_coords[5].x;
	character[q].bodypart_coords[6].y=-26.5f-character[q].bodypart_coords[5].y;
	character[q].bodypart_coords[6].z=-8.0f-character[q].bodypart_coords[5].z;
	character[q].bodypart_coords[10].x= 3.2f -character[q].bodypart_coords[9].x;
	character[q].bodypart_coords[10].y=-26.5f-character[q].bodypart_coords[9].y;
	character[q].bodypart_coords[10].z=8.0f-character[q].bodypart_coords[9].z;


	//upper arm
	character[q].bodypart_coords[3].x=-1.7f;
	character[q].bodypart_coords[3].y=30.15f;
	character[q].bodypart_coords[3].z=-14.7f;
	character[q].bodypart_coords[8].x=-1.7f;
	character[q].bodypart_coords[8].y=30.15f;
	character[q].bodypart_coords[8].z=14.7f;


	//lower arm
	character[q].bodypart_coords[4].x=-3.26f -character[q].bodypart_coords[3].x;
	character[q].bodypart_coords[4].y=16.3f -character[q].bodypart_coords[3].y;
	character[q].bodypart_coords[4].z=-16.8f-character[q].bodypart_coords[3].z;
	character[q].bodypart_coords[7].x=-3.27f -character[q].bodypart_coords[8].x;
	character[q].bodypart_coords[7].y=16.3f -character[q].bodypart_coords[8].y;
	character[q].bodypart_coords[7].z=16.8f-character[q].bodypart_coords[8].z;


/*
//head
mallit[q].malli[2].x=0;
mallit[q].malli[2].y=37.1f;
mallit[q].malli[2].z=0;

//torso
mallit[q].malli[1].x=0;
mallit[q].malli[1].y=0;
mallit[q].malli[1].z=0;

//butt
mallit[q].malli[0].x=0;
mallit[q].malli[0].y=0;
mallit[q].malli[0].z=0;

//upper leg
mallit[q].malli[5].x=-0.8f;
mallit[q].malli[5].y=-3.9f;
mallit[q].malli[5].z=-6.7f;
mallit[q].malli[9].x=-0.8f;
mallit[q].malli[9].y=-3.9f;
mallit[q].malli[9].z=6.7f;

//lower leg
mallit[q].malli[6].x= 3.2f -mallit[q].malli[5].x;
mallit[q].malli[6].y=-26.5f-mallit[q].malli[5].y;
mallit[q].malli[6].z=-8.0f-mallit[q].malli[5].z;
mallit[q].malli[10].x= 3.2f -mallit[q].malli[9].x;
mallit[q].malli[10].y=-26.5f-mallit[q].malli[9].y;
mallit[q].malli[10].z=8.0f-mallit[q].malli[9].z;


//upper arm
mallit[q].malli[3].x=-1.7f;
mallit[q].malli[3].y=30.15f;
mallit[q].malli[3].z=-14.7f;
mallit[q].malli[8].x=-1.7f;
mallit[q].malli[8].y=30.15f;
mallit[q].malli[8].z=14.7f;


//lower arm
mallit[q].malli[4].x=-3.26f -mallit[q].malli[3].x;
mallit[q].malli[4].y=16.3f -mallit[q].malli[3].y;
mallit[q].malli[4].z=-16.8f-mallit[q].malli[3].z;
mallit[q].malli[7].x=-3.27f -mallit[q].malli[8].x;
mallit[q].malli[7].y=16.3f -mallit[q].malli[8].y;
mallit[q].malli[7].z=16.8f-mallit[q].malli[8].z;
*/
	/*

	//hand
	mallit[q].malli[5].x=+1.1f-mallit[q].malli[4].x;
	mallit[q].malli[5].y=-3.2f-mallit[q].malli[4].y;
	mallit[q].malli[5].z=15.2f-mallit[q].malli[4].z;
	mallit[q].malli[10].x=+3.4f;//+2.8424f;
	mallit[q].malli[10].y=-11.7593f -(41.2814f-20.8306f);
	mallit[q].malli[10].z=-0.7f;*/


}

void initMopeds(void)//initialize mopeds
{
	int d,a;

	d=0;
	moped[d].etudirection=0;
	moped[d].ase[0]=6;
	moped[d].ase[1]=7;
	moped[d].ase[2]=8;
	moped[d].ase[3]=9;
	moped[d].timesparks=-1;
	moped[d].mission.status=3;
	moped[d].mopona=1;
	moped[d].numero=d;
	moped[d].energy=100;
	moped[d].level=0;
	moped[d].direction=pi*0.25f;
	moped[d].x1=(float)(headquarter_posz*8000+2450);
	moped[d].z1=(float)(headquarter_posx*8000+2200);
	moped[d].x2=moped[d].x1+sinf(moped[d].direction)*70;
	moped[d].z2=moped[d].z1+cosf(moped[d].direction)*70;
	moped[d].speed=0.00f;
	moped[d].sektorix=(int)moped[d].x1/8000;
	moped[d].sektoriz=(int)moped[d].z1/8000;
	moped[d].inactive=false;
	for (a=0; a<100; a++)moped[d].osuma[a]=false;
	moped[d].directiontimer=0;
	moped[d].visible=true;
	moped[d].x3=moped[d].x1;
	moped[d].z3=moped[d].z1;
	moped[d].x4=moped[d].x2;
	moped[d].z4=moped[d].z2;
	moped[d].money=50;


	for (d=1; d<num_mopeds; d++){
		create_mopo(d);
	}

}

BOOL loadwall(const char *nimi,RouteGroup *target,BOOL mirror)
{
	FILE *fil;
	CHAR row[300];
	fil = fopen(nimi,"rt");
	int b,a,c;
	FLOAT groupx,groupy,groupz;

	FLOAT x[2000];
	FLOAT y[2000];
	FLOAT z[2000];

//add mirror properties to both ways


	fgets(row,sizeof(row),fil);//ammount of groups
	target->group_count=atoi(row);
	target->routes=new Route[target->group_count];

	for (b=0; b<target->group_count; b++)
	{
		//location of group
		fgets(row,sizeof(row),fil);
		groupx=(float)atof(row);
		fgets(row,sizeof(row),fil);
		groupy=(float)atof(row);
		fgets(row,sizeof(row),fil);
		groupz=(float)atof(row);

		fgets(row,sizeof(row),fil);//ammount of buildings
		target->routes[b].route_count=atoi(row);
		target->routes[b].route=new Line[target->routes[b].route_count];
		for (a=0; a<target->routes[b].route_count; a++)
		{
			fgets(row,sizeof(row),fil);//ammount of lines in a building
			target->routes[b].route[a].line_count=atoi(row);
			target->routes[b].route[a].point=new dot[target->routes[b].route[a].line_count];
			for (c=0; c<target->routes[b].route[a].line_count; c++)//read points
			{
				x[c]=(float)atof(fgets(row,sizeof(row),fil))-groupx;//x
				y[c]=(float)atof(fgets(row,sizeof(row),fil))-groupy;//y
				z[c]=(float)atof(fgets(row,sizeof(row),fil))-groupz;//z
			}
			for (c=0; c<target->routes[b].route[a].line_count-1; c++)//making lines to every except the last one. (NOTE -1)
			{
				target->routes[b].route[a].point[c].x1=x[c];
				target->routes[b].route[a].point[c].y1=y[c];
				target->routes[b].route[a].point[c].z1=z[c];
				target->routes[b].route[a].point[c].x2=x[c+1];
				target->routes[b].route[a].point[c].y2=y[c+1];
				target->routes[b].route[a].point[c].z2=z[c+1];
			}
			c=target->routes[b].route[a].line_count-1;//last line
			target->routes[b].route[a].point[c].x1=x[c];
			target->routes[b].route[a].point[c].y1=y[c];
			target->routes[b].route[a].point[c].z1=z[c];
			target->routes[b].route[a].point[c].x2=x[0];
			target->routes[b].route[a].point[c].y2=y[0];
			target->routes[b].route[a].point[c].z2=z[0];
		}
	}

	fclose(fil);

	return true;
}

BOOL load(const char filename[200],obj *target,BOOL mirror,BOOL miekkakala)
{
	FILE *fil;
	CHAR row[300];
	//INT faces;
	INT kolme,kolmi;
	FLOAT x[2000];
	FLOAT y[2000];
	FLOAT z[2000];
	FLOAT x1[2000];
	FLOAT y1[2000];
	FLOAT z1[2000];
	FLOAT u[2000];
	FLOAT v[2000];
	FLOAT w[2000];

	INT peili;
	if (mirror) peili=-1; else peili=1;

	FLOAT groupx,groupy,groupz;
	//float g[3];
	//CHAR picturet[300];//pictures

	INT sivu0[2000];
	INT sivu1[2000];
	INT sivu2[2000];
	INT sivu20[2000];
	INT sivu21[2000];
	INT sivu22[2000];
	D3DVECTOR p1;
	D3DVECTOR vNormal;
	INT cur=0;
	INT cura=0;
	//int lootia;//boxes
	//INT kolmion;//triangle's

	INT i,j,b,a,q,faces;
	fil = fopen(filename,"rt");


	//target = new objekt[lootia];


	fgets(row,sizeof(row),fil);
	j=atoi(row);
	//lataaapu(j,&target); //load help(j,&target);
	//*target	= new obj[j];


	for (b=0; b<j; b++)
	{
		fgets(row,sizeof(row),fil);
		a=atoi(row);

		fgets(row,sizeof(row),fil);
		groupx=(float)atof(row);
		fgets(row,sizeof(row),fil);
		groupy=(float)atof(row);
		fgets(row,sizeof(row),fil);
		groupz=(float)atof(row);

//At this point we load the tip of the sword.

		if (miekkakala)//swordfish
		{
			fgets(row,sizeof(row),fil);
			target[b].swordpointx=(float)atof(row)-groupx;
			fgets(row,sizeof(row),fil);
			target[b].swordpointy=(float)atof(row)-groupy;
			fgets(row,sizeof(row),fil);
			target[b].swordpointz=(float)atof(row)-groupz;
		}

		target[b].mirror=mirror;
		target[b].sisus = new objekt[a];
		target[b].count = a;

		for (q=0; q<a; q++)
		{
                	fgets(row,sizeof(row),fil);//666666
			fgets(row,sizeof(row),fil);//materials
			target[b].sisus[q].material=atoi(row);
			fgets(row,sizeof(row),fil);//materials second time

			{
				fgets(row,sizeof(row),fil);
                                //new(INT faces=atoi(row));
				kolme=atoi(row);
				fgets(row,sizeof(row),fil);
				faces=atoi(row);
				//D3DVERTEX triangle[faces*3];
				//FLOAT new( x[kolme]);
				//x=new(FLOAT[kolme]);
				target[b].sisus[q].loota.triangle = new vvertex[faces*3];
				target[b].sisus[q].loota.vert = faces*3;

				target[b].sisus[q].upleft.x=0;
				target[b].sisus[q].upleft.y=0;
				target[b].sisus[q].upleft.z=0;

				target[b].sisus[q].downright.x=0;
				target[b].sisus[q].downright.y=0;
				target[b].sisus[q].downright.z=0;

				for (i=0; i<kolme; i++)
				{
					fgets(row,sizeof(row),fil);
					x[i]=(((float)atof(row))-groupx);
					fgets(row,sizeof(row),fil);
					y[i]=(((float)atof(row))-groupy);
					fgets(row,sizeof(row),fil);
					z[i]=(((float)atof(row))-groupz)*peili;

					//dimensions
					if(x[i]<target[b].sisus[q].upleft.x) target[b].sisus[q].upleft.x=x[i];
					if(y[i]<target[b].sisus[q].upleft.y) target[b].sisus[q].upleft.y=y[i];
					if(z[i]<target[b].sisus[q].upleft.z) target[b].sisus[q].upleft.z=z[i];
					if(x[i]>target[b].sisus[q].downright.x) target[b].sisus[q].downright.x=x[i];
					if(y[i]>target[b].sisus[q].downright.y) target[b].sisus[q].downright.y=y[i];
					if(z[i]>target[b].sisus[q].downright.z) target[b].sisus[q].downright.z=z[i];
				}

				for (i=0; i<faces; i++)
				{
					fgets(row,sizeof(row),fil);
					sivu0[i]=atoi(row);
					fgets(row,sizeof(row),fil);
					sivu1[i]=atoi(row);
					fgets(row,sizeof(row),fil);
					sivu2[i]=atoi(row);
				}

				fgets(row,sizeof(row),fil);
				kolmi=atoi(row);

				for (i=0; i<kolmi; i++)
				{
					fgets(row,sizeof(row),fil);
					u[i]=(float)atof(row);
					fgets(row,sizeof(row),fil);
					v[i]=1.0f-(float)atof(row);
					fgets(row,sizeof(row),fil);
					w[i]=(float)atof(row);
				}

				fgets(row,sizeof(row),fil);
				kolmi=atoi(row);
				for (i=0; i<kolmi; i++)
				{
					fgets(row,sizeof(row),fil);
					sivu20[i]=atoi(row);
					fgets(row,sizeof(row),fil);
					sivu21[i]=atoi(row);
					fgets(row,sizeof(row),fil);
					sivu22[i]=atoi(row);
				}
				for (i=0; i<(3*faces); i++)
				{
					fgets(row,sizeof(row),fil);
					x1[i]=((float)atof(row));
					fgets(row,sizeof(row),fil);
					y1[i]=((float)atof(row));
					fgets(row,sizeof(row),fil);
					z1[i]=((float)atof(row))*peili;
				}

				for (i=0; i<faces; i++)
				{
					p1.x=x[sivu0[i]];
					p1.y=y[sivu0[i]];
					p1.z=z[sivu0[i]];
					vNormal.x=x1[sivu0[i]];
					vNormal.y=y1[sivu0[i]];
					vNormal.z=z1[sivu0[i]];
					target[b].sisus[q].loota.triangle[i*3+0].position=		p1;
					target[b].sisus[q].loota.triangle[i*3+0].normal=		vNormal;
					target[b].sisus[q].loota.triangle[i*3+0].u=			u[sivu20[i]];//w[sivu20[i]];//side
					target[b].sisus[q].loota.triangle[i*3+0].v=			v[sivu20[i]];//w[sivu20[i]];



					p1.x=x[sivu1[i]];
					p1.y=y[sivu1[i]];
					p1.z=z[sivu1[i]];
					vNormal.x=x1[sivu1[i]];
					vNormal.y=y1[sivu1[i]];
					vNormal.z=z1[sivu1[i]];
					target[b].sisus[q].loota.triangle[i*3+1].position=		p1;
					target[b].sisus[q].loota.triangle[i*3+1].normal=		vNormal;
					target[b].sisus[q].loota.triangle[i*3+1].u=			u[sivu21[i]];//w[sivu21[i]];
					target[b].sisus[q].loota.triangle[i*3+1].v=			v[sivu21[i]];//w[sivu21[i]];



					p1.x=x[sivu2[i]];
					p1.y=y[sivu2[i]];
					p1.z=z[sivu2[i]];
					vNormal.x=x1[sivu2[i]];
					vNormal.y=y1[sivu2[i]];
					vNormal.z=z1[sivu2[i]];
					target[b].sisus[q].loota.triangle[i*3+2].position=		p1;
					target[b].sisus[q].loota.triangle[i*3+2].normal=		vNormal;
					target[b].sisus[q].loota.triangle[i*3+2].u=			u[sivu22[i]];//w[sivu22[i]];
					target[b].sisus[q].loota.triangle[i*3+2].v=			v[sivu22[i]];//w[sivu22[i]];


				}


				fgets(row,sizeof(row),fil);
				target[b].sisus[q].texture=atoi(row);
				target[b].sisus[q].texture2=atoi(row);
				target[b].sisus[q].x=0.0f;
				target[b].sisus[q].y=0.0f;
				target[b].sisus[q].z=0.0f;
				target[b].x=0.0f;
				target[b].y=0.0f;
				target[b].z=0.0f;
				target[b].rx=0.0f;
				target[b].ry=0.0f;
				target[b].rz=0.0f;
			}
		}
	}


	fclose(fil);

	return true;

}



BOOL loadtext()
{
        std::cout << "loading textures" << std::endl;

	FILE *fil;
	CHAR row[300];
	CHAR rows[13];
	CHAR texturefilename[100];
	DWORD x=100;
	DWORD y=100;
	DWORD mipmaps=D3DX_DEFAULT;
	DWORD mipmapping=D3DX_DEFAULT;
	int q;
	fil = fopen("models/mat.3dw","rt");

	fgets(row,sizeof(row),fil);
	material_count=atoi(row);
	mat = new D3DMATERIAL7[material_count];
	background = new LPDIRECTDRAWSURFACE7[material_count];
	bool filter[300];//to filter or not to filter

	for (q=0; q<material_count; q++)
		filter[q]=false;
/*
//audience is not filtered
filter[49]=true;
filter[50]=true;
*/

	/*for (q=material_count; q<material_count+40; q++)
          {

          D3DXCreateTexture(
          m_pDevice,
          NULL,
          &x,
          &y,
          NULL,
          NULL,
          &background[q],
          NULL
          );

          }*/

	for (q=0; q<material_count; q++)
	{
		ZeroMemory( &background[q], sizeof(background[q]) );
		ZeroMemory( &mat[q], sizeof(mat[q]) );

		// Set the RGBA for ambient reflection.
		fgets(row,sizeof(row),fil);
		mat[q].dcvAmbient.r = (D3DVALUE)atof(row);
		fgets(row,sizeof(row),fil);
		mat[q].dcvAmbient.g = (D3DVALUE)atof(row);
		fgets(row,sizeof(row),fil);
		mat[q].dcvAmbient.b = (D3DVALUE)atof(row);
		mat[q].dcvAmbient.a = (D3DVALUE)1.0;

		// Set the RGBA for diffuse reflection.
		fgets(row,sizeof(row),fil);
		mat[q].dcvDiffuse.r = (D3DVALUE)atof(row);
		fgets(row,sizeof(row),fil);
		mat[q].dcvDiffuse.g = (D3DVALUE)atof(row);
		fgets(row,sizeof(row),fil);
		mat[q].dcvDiffuse.b = (D3DVALUE)atof(row);
		mat[q].dcvDiffuse.a = (D3DVALUE)1.0;

		// Set the color and sharpness of specular highlights.
		fgets(row,sizeof(row),fil);
		mat[q].dcvSpecular.r = (D3DVALUE)atof(row);
		fgets(row,sizeof(row),fil);
		mat[q].dcvSpecular.g = (D3DVALUE)atof(row);
		fgets(row,sizeof(row),fil);
		mat[q].dcvSpecular.b = (D3DVALUE)atof(row);
		mat[q].dcvSpecular.a =1;
		mat[q].dvPower = 50;

		fgets(rows,sizeof(rows),fil);
		fgets(row,sizeof(row),fil);

		//itoa(savegame_slot,temprow,10);//(saveplace, templine, 10)
		strcpy(texturefilename,"textures/");
		strcat(texturefilename,rows);

		//if(atoi(row)==155)




		//if(atoi(row)==255)

		//background[q]=loadPicture(m_pDD,rows,true);//background[q]loadpicture

		D3DX_SURFACEFORMAT pixel;

		if(SCREEN_BITS==32)pixel=D3DX_SF_UNKNOWN; //32
		if(SCREEN_BITS==24)pixel=D3DX_SF_UNKNOWN; //24
		if(SCREEN_BITS==16)pixel=D3DX_SF_UNKNOWN;//16
		/*if(SCREEN_BITS==32)pixel=D3DX_SF_A8R8G8B8 ; //32
                  if(SCREEN_BITS==24)pixel=D3DX_SF_R8G8B8; //24
                  if(SCREEN_BITS==16)pixel=D3DX_SF_R5G6B5; //16*/

		//D3DXCheckTextureRequirements(m_pDevice,NULL,0,0,&pixel);


		//background[q]=loadTexture(screenmode,info,&m_pDevice,m_pDD,texturefilename,true);//background[q]=loadtexture(screenmode,info,&m_pDevice,m_pDD,texturename,true);
		/*
                  D3DXLoadTextureFromFile(
                  m_pDevice,
                  background[q],                       // destination
                  D3DX_DEFAULT ,               // all mip levels
                  texturefilename,		//texturefilename		        // source
                  NULL,                       // entire source
                  NULL,                       // entire destination
                  D3DX_FT_LINEAR );
                */

		if(filter[q])
                        D3DXCreateTextureFromFile(
                                        m_pDevice,
                                        NULL,
                                        0,
                                        0,
                                        &pixel,
                                        0,
                                        &background[q],
                                        NULL,
                                        texturefilename,
                                        D3DX_FT_POINT    //D3DX_FT_DEFAULT
                                );
		else
                        D3DXCreateTextureFromFile(
                                        m_pDevice,
                                        &mipmapping,
                                        0,
                                        0,
                                        &pixel,
                                        0,
                                        &background[q],
                                        &mipmaps,
                                        texturefilename,
                                        D3DX_FT_DEFAULT
                                );


	}

	fclose(fil);


	return TRUE;
}

static HRESULT WINAPI EnumZBufferCallback( DDPIXELFORMAT* pddpf, VOID* pddpfDesired )
{
        // For this tutorial, we are only interested in z-buffers, so ignore any
        // other formats (e.g. DDPF_STENCILBUFFER) that get enumerated. An app
        // could also check the depth of the z-buffer (16-bit, etc,) and make a
        // choice based on that, as well. For this tutorial, we'll take the first
        // one we get.
        if( pddpf->dwFlags == DDPF_ZBUFFER )
                if( pddpf->dwZBufferBitDepth >=16)
                {
                        memcpy( pddpfDesired, pddpf, sizeof(DDPIXELFORMAT) );

                        // Return with D3DENUMRET_CANCEL to end the search.
                        return D3DENUMRET_CANCEL;
                }

        // Return with D3DENUMRET_OK to continue the search.
        return D3DENUMRET_OK;
}


bool createscreen(void){
        std::cout << "creating screen" << std::endl;
	SCREEN_WIDTH=1024;
	SCREEN_HEIGHT=768;
	SCREEN_BITS=32;

	int fs=0;
	D3DXCreateContext(
                        D3DX_DEFAULT,
                        D3DX_CONTEXT_FULLSCREEN*fs,  //windowed = 0
                        hWnd,
                        1024,
                        768,
                        &dxctx);
	/*D3DXCreateContextEx(D3DX_DEFAULT,
          D3DX_CONTEXT_FULLSCREEN*fs,  //windowed = 0
          hWnd,
          hWnd,
          24,
          0,
          8,
          0,
          1,
          1024,
          768,
          0,
          &dxctx);*/
	m_pDD=dxctx->GetDD();
	m_pDevice=dxctx->GetD3DDevice();
	//taka=dxctx->GetBackBuffer(0);
	m_pDevice->GetRenderTarget(&taka);

	//memset(&m_pViewport, 0, sizeof(D3DVIEWPORT7));
	D3DVIEWPORT7 m_pViewport;
	m_pViewport.dwX = 0;
        m_pViewport.dwY = 0;
	m_pViewport.dwWidth  = SCREEN_WIDTH;
        m_pViewport.dwHeight = SCREEN_HEIGHT;
	m_pViewport.dvMinZ = 0.0f;
        m_pViewport.dvMaxZ = 1.0f;



        m_pDevice->SetViewport( &m_pViewport );
        //!= D3D_OK)
	//return FALSE;
	m_pDevice->GetCaps(&desc3d);
	//desc3d=infot[driver].d3device[device].ddDeviceDesc;
	//info=infot[driver];
	return true;

}

void readkeyb(void)
{
        #define KEYDOWN(name,key) (name[key] & 0x80)
	int q;
	int down;//which key is pressed

        HRESULT  hr;

	D3DXVECTOR3 intersect;
	//int kolmio;//,sisus,q; //==> triangle;//,interrior,q;

	long thistime = GetTickCount();
	elapsed2=0;
	elapsed3[30]=(float)(thistime - m_LastTime);
	for (q=0; q<30; q++){
		elapsed3[q]=elapsed3[q+1];
		elapsed2=elapsed2+elapsed3[q];
	}
	elapsed=elapsed2/30;
	m_LastTime = thistime;
/*
  elapsed2=elapsed;
  elapsed = (float)((thistime - m_LastTime)+elapsed+elapsed2)/3;
  m_LastTime = thistime;*/

	mousestate2=mousestate;
	hr = g_pMouse->GetDeviceState(sizeof(mousestate),&mousestate);
	if FAILED(hr)
                 {
                         return;
                 }


	mousex= mousex + (mousestate.lX+mousestate2.lX)*SCREEN_WIDTH/1024;
	mousey= mousey + (mousestate.lY+mousestate2.lY)*SCREEN_HEIGHT/768;

	//mousex= mousex + mousestate.lX*2;
	//mousey= mousey + mousestate.lY*2;

	if (mousex<0) mousex=0;
	if (mousex>SCREEN_WIDTH) mousex=(float)SCREEN_WIDTH-1;
	if (mousey<0) mousey=0;
	if (mousey>SCREEN_HEIGHT) mousey=(float)SCREEN_HEIGHT-1;

	pressed2=pressed;
	pressed=false;
	for (q=0; q<256; q++){buffer2[q]=buffer[q];}


	hr = g_lpDIDevice->GetDeviceState(sizeof(buffer),(LPVOID)&buffer);
        if FAILED(hr)
                 {
                         // If it failed, the device has probably been lost.
                         // We should check for (hr == DIERR_INPUTLOST)
                         // and attempt to reacquire it here.
                         return;
                 }
	for (q=0; q<256; q++){if((buffer[q]& 0x80)!=0){pressed=true;down=q;}}
	if((mousestate.rgbButtons[0])||(mousestate.rgbButtons[1]))pressed=true;

	//plusmiinus //plusminus
	if (KEYDOWN(buffer, DIK_SUBTRACT))
		plusmiinus=plusmiinus-0.001f*elapsed*gamespeed;
	if (KEYDOWN(buffer, DIK_ADD))
		plusmiinus=plusmiinus+0.001f*elapsed*gamespeed;




	if((!pressed&&!pressed2)&&(gamephase!=0))return;

	switch (gamephase)
	{
	case 0:{//game
                readkey_game();
                break;
        }
	case 1:{//mission assigment
                //accept mission
                if (!KEYDOWN(buffer,  DIK_RETURN )&&KEYDOWN(buffer2,  DIK_RETURN)){
                        if(mission_is_read==1){
                                gamephase=0;//back to riding
                                SndObjPlay(voices[1], DSBPLAY_LOOPING,options[1]&&SOUNDS_LOADED);
                                moped[0].mission=moped[0].mission_random;
                                //a dude comes aboard
                                if(moped[0].mission._type==1)
                                        character[moped->nearestcharacter].inactive=true;
                        }
                        mission_is_read=1;//introduction is readed
                }
                break;
        }
	case 2:{//workshop
                //pressing esc means escape.
                if ((!KEYDOWN(buffer,  DIK_ESCAPE )&&KEYDOWN(buffer2,  DIK_ESCAPE))||(!KEYDOWN(buffer,  DIK_F9 )&&KEYDOWN(buffer2,  DIK_F9)))
                {
                        gamephase2=0;
                        gamephase=0;
                        SndObjPlay(voices[1], DSBPLAY_LOOPING,options[1]&&SOUNDS_LOADED);
                }
                break;
        }
	case 3:
		break;
	case 4:{
		//pressing esc means escape.
		if ((!KEYDOWN(buffer,  DIK_ESCAPE )&&KEYDOWN(buffer2,  DIK_ESCAPE))||(!KEYDOWN(buffer,  DIK_F9 )&&KEYDOWN(buffer2,  DIK_F9))){
			if(gamephase2==0)
				SendMessage( hWnd, WM_CLOSE, 0, 0 );
			else {
				//if it came to load from workshop
				if((gamephase2==1)||(gamephase2==2)){
					if(gamephase_old==2){
                                                gamephase2=0;
                                                gamephase=2;
					}
					if(gamephase_old==4){
                                                gamephase2=0;
                                                gamephase=4;
					}
				}
				else if(gamephase2==3)
					gamephase2=2;
				else{
					gamephase2=0;
					gamephase=4;
				}

			}
		}
		//down
                if(gamephase2!=3)
			if (!KEYDOWN(buffer,  DIK_DOWN )&&KEYDOWN(buffer2,  DIK_DOWN)){
				menu_selection=menu_selection+1;
				if(menu_selection>=menuja[gamephase2])menu_selection=0;
				SndObjPlay(voices[0], 0, options[1]&&SOUNDS_LOADED);
			}
		//up
                if(gamephase2!=3)
			if (!KEYDOWN(buffer,  DIK_UP )&&KEYDOWN(buffer2,  DIK_UP)){
				menu_selection=menu_selection-1;
				if(menu_selection<0)menu_selection=menuja[gamephase2]-1;
				SndObjPlay(voices[0], 0, options[1]&&SOUNDS_LOADED);
			}

		//changching keys
                if(gamephase2==6)
			if((menu_selection<12)&&(menu_selection>0)&&(pressed)&&(is_selected))
			{
				key[menu_selection]=down;
				is_selected=false;
				SndObjPlay(voices[0], 0, options[1]&&SOUNDS_LOADED);
				cfg_save();
			}

		//selection pressed
                if (((mousestate2.rgbButtons[0])&&(!mousestate.rgbButtons[0]))||(!KEYDOWN(buffer,  DIK_RETURN )&&KEYDOWN(buffer2,  DIK_RETURN))){
                        //loading a game
                        if(gamephase2==1)
				if((menu_selection<11)&&(menu_selection>0))
				{
					savegame_slot=menu_selection-1;
					game_load();
					SndObjPlay(voices[0], 0, options[1]&&SOUNDS_LOADED);
					break;
				}
                        //selecting a load
                        if(gamephase2==2)
				if((menu_selection<11)&&(menu_selection>0))
				{
					savegame_slot=menu_selection-1;
					gamephase2=3;
					letters_in_name=letters_in_file_names[savegame_slot];
					strcpy(savefilename,"                                                 ");
					strcpy(savefilename,m_filenames[savegame_slot]);
					if(!loadable[savegame_slot]){
						letters_in_name=0;
						strcpy(savefilename,"                                                 ");
					}
					SndObjPlay(voices[0], 0, options[1]&&SOUNDS_LOADED);
					break;
				}
                        //saving a game
                        if(gamephase2==3)
				if((menu_selection<11)&&(menu_selection>0))
				{
					savegame_slot=menu_selection-1;
					game_save();
					if(gamephase_old==2){
						gamephase2=0;
						gamephase=2;
					}
					if(gamephase_old==4){
						gamephase2=0;
						gamephase=4;
					}
					readsaves();
					SndObjPlay(voices[0], 0, options[1]&&SOUNDS_LOADED);
					break;
				}
                        //changching settings
                        if(gamephase2==4)
				if((menu_selection<10)&&(menu_selection>0))
				{
					if(options[menu_selection])options[menu_selection]=false;
					else options[menu_selection]=true;
					options[2]=false;//music permanently off
					cfg_save();
					SndObjPlay(voices[0], 0, options[1]&&SOUNDS_LOADED);
				}

                        //changching keys //select a key
                        if(gamephase2==6)
				if((menu_selection<12)&&(menu_selection>0))
				{
					is_selected=true;
					SndObjPlay(voices[0], 0, options[1]&&SOUNDS_LOADED);
				}


                        switch (menu_selection){
                        case 0:
                                if(gamephase2==0){//new game
                                        gamephase2=5;
                                        SndObjPlay(voices[0], 0, options[1]&&SOUNDS_LOADED);
                                        break;
                                }
                                if(gamephase2==5){//difficulty level
                                        game_difficulty=0;
                                        SndObjPlay(voices[0], 0, options[1]&&SOUNDS_LOADED);
                                        game_new();
                                }
                                break;
                        case 1:
                                if(gamephase2==0){//load
                                        readsaves(); gamephase2=1; gamephase_old=4;
                                        SndObjPlay(voices[0], 0, options[1]&&SOUNDS_LOADED);
                                }
                                if(gamephase2==5){//difficulty level
                                        game_difficulty=1;
                                        SndObjPlay(voices[0], 0, options[1]&&SOUNDS_LOADED);
                                        game_new();
                                }
                                break;
                        case 2:
                                if(gamephase2==0){//options
                                        gamephase2=4;
                                        SndObjPlay(voices[0], 0, options[1]&&SOUNDS_LOADED);
                                }
                                if(gamephase2==5){//difficulty level
                                        game_difficulty=2;
                                        SndObjPlay(voices[0], 0, options[1]&&SOUNDS_LOADED);
                                        game_new();
                                }
                                break;
                        case 3:
                                if(gamephase2==0){//exit
                                        SendMessage( hWnd, WM_CLOSE, 0, 0 );
                                        //SndObjPlay(voices[0], 0, options[1]&&SOUNDS_LOADED);
                                }
                                if(gamephase2==5){//Back
                                        gamephase2=0;
                                        SndObjPlay(voices[0], 0, options[1]&&SOUNDS_LOADED);
                                }
                                break;
                        case 11:
                                if(gamephase2==4){//set keys
                                        gamephase2=6;
                                        is_selected=false;//key not selected
                                        SndObjPlay(voices[0], 0, options[1]&&SOUNDS_LOADED);
                                }
                                break;
                        case 12:
                                if((gamephase2==1)||(gamephase2==2)){//back
                                        //if it came to load from workshop
                                        if(gamephase_old==2){
                                                gamephase2=0;
                                                gamephase=2;
                                        }
                                        //if it came to load from menu
                                        if(gamephase_old==4){
                                                gamephase2=0;
                                                gamephase=4;
                                        }
                                        SndObjPlay(voices[0], 0, options[1]&&SOUNDS_LOADED);
                                }
                                if(gamephase2==3){
                                        gamephase2=2;
                                        SndObjPlay(voices[0], 0, options[1]&&SOUNDS_LOADED);
                                }
                                if(gamephase2==4){
                                        gamephase2=0;
                                        SndObjPlay(voices[0], 0, options[1]&&SOUNDS_LOADED);
                                }
                                if(gamephase2==6){
                                        gamephase2=4;
                                        SndObjPlay(voices[0], 0, options[1]&&SOUNDS_LOADED);
                                }
                                break;

                        }
                }

        }
                break;

	}
}

void calculatesmokes(void)//calculate smokes
{
	int a;
	float smoke_speed=0.1f;
	float rotatespeed=0.001f;

	for (a=0; a<MAX_SMOKES; a++){
		if(smokes[a].inactive)continue;
		smokes[a].timer=smokes[a].timer-elapsed*gamespeed;

		//A smoke disappears if it is too small
		smokes[a].size=smokes[a].size+smokes[a].suurenee*elapsed*gamespeed;
		if(smokes[a].size<=0) {smokes[a].timer=-1;}

		/*if(smokes[a].timer<0){   //if(smoke[a].time<0)
                  for (q=a; q<smoke_count; q++){
                  smokes[q]=smokes[q+1];//smoke
                  }
                  smoke_count=smoke_count-1;//smokes
                  }*/
		if(smokes[a].timer<0){
			smokes[a].inactive=true;
			continue;
		}

		//smoke[a].w=smokes[a].w+rotatespeed*smokes[a].rotate*elapsed*gamespeed;//smokes are rolling

		//smoke[a].size=smokes[a].size+0.0001f*elapsed*gamespeed;

		//smokes fly
		if(smokes[a].up!=0){
			//	camx,camy,camz)
			/*smokes[a].q=-atan2f(-kamerax2+kamerax1,-kameraz2+kameraz1);
                          smokes[a].w=0;
                          smokes[a].e=-atan2f(-kameray2+kameray1,((-kameraz2+kameraz1+0.1f)*(-kamerax2+kamerax1+0.1f)));
			*/
			smokes[a].place.x=smokes[a].place.x+smokes[a].cos*elapsed*gamespeed*smoke_speed;
			smokes[a].place.y=smokes[a].place.y+smokes[a].up*elapsed*gamespeed*smoke_speed;
			smokes[a].place.z=smokes[a].place.z+smokes[a].sin*elapsed*gamespeed*smoke_speed;
		}

	}
}

void fromsmoke(float size, float suurenee,bool rotate,float smoke_duration,float x,float y,float z,int _type,float q,float w,float e)//does smokes and explosion
{
	int a,b;
	/*if(smoke_count>=MAX_SMOKES)//Remove a smokes if there are too many
          {
          for (a=randInt(0,smoke_count); a<smoke_count; a++){
          smokes[a]=smokes[a+1];
          }
          smoke_count=smoke_count-1;//smokes
          }*/
	//deciding wich bullet is replaced with a new one
        a=0;
        b=0;
  alku1:
        a=randInt(0,MAX_SMOKES);
        b=b+1;
        if(b>MAX_SMOKES)smokes[a].inactive=true;
        if(!smokes[a].inactive)goto alku1;

	smokes[a].inactive=false;
	smokes[a].place.x=x;
	smokes[a].place.y=y;
	smokes[a].place.z=z;
	smokes[a]._type=_type;
	smokes[a].size=size+randDouble(-0.2f,0.2f);
	if(size<0.1f)size=0.1f;

	//picture for cloud smoke is randomly selected from to pictures.
	if(_type==2)
                smokes[a].picture=randInt(0,2);

	smokes[a].q=q;
	smokes[a].w=w;
	smokes[a].e=e;
	smokes[a].suurenee=suurenee;


	smokes[a].timer=randDouble(0,smoke_duration);
	smokes[a].cos=(float)cos(smokes[a].q);
	smokes[a].sin=(float)sin(smokes[a].q);
	smokes[a].up=0;
	if(rotate)
	{
		smokes[a].rotate=randDouble(-pi,pi);
		smokes[a].up=(float)sin(smokes[a].w);
	}
	else smokes[a].rotate=0;

}

void calculatebullets(void)//calculates bullets
{
	int j,a,q,q2,d;
	D3DXVECTOR3 skaalattu;
	float height,kuljettumatka;
	int pommeja=1;//ammount of explosions

	RECT r1;

	bool osuma;
	float osumax,osumaz,wallkulma,osumax2,osumaz2;
	float osuix,osuiz;
	int sektoreita,w[2],b,c;
	int wallhits;
	int negaatio;
	float dq,temp1;
	//int mapx,mapz;

	for (a=0; a<MAX_BULLETS; a++){

		if(bullet[a].remove)continue;

		//time
		if(bullet[a].timer<-1)bullet[a].remove=true;
		if(bullet[a].timer!=-1)bullet[a].timer=bullet[a].timer-elapsed*gamespeed*0.999f;
		if(a>9){//Bullets at the beginning are for mopeds to run over people
			bullet[a].place_old=bullet[a].place;//save old place for collisions
			bullet[a].direction.y=bullet[a].direction.y-ase[bullet[a].from_gun].weight*elapsed*gamespeed;//bullet falls down
			D3DXVec3Scale(&skaalattu,&bullet[a].direction,elapsed*gamespeed);//liikkuu * elapsed*gamespeed //moves*elapsed*gamespeed
			D3DXVec3Add(&bullet[a].place,&bullet[a].place,&skaalattu);
			bullet[a].distance=sqrtf(sqr(bullet[a].place.x-moped[0].x1)+sqr(bullet[a].place.z-moped[0].z1));
			if(bullet[a].distance>20000){bullet[a].remove=true;continue;}
			if((bullet[a].place.x<0)||(bullet[a].place.z<0)||(bullet[a].place.x>mapsx*8000)||(bullet[a].place.z>mapsz*8000)){bullet[a].remove=true;continue;}
		}
		bullet[a].sektorix[0]=(int)bullet[a].place.x/8000;
		bullet[a].sektoriz[0]=(int)bullet[a].place.z/8000;
		bullet[a].sektorix[1]=(int)bullet[a].place_old.x/8000;
		bullet[a].sektoriz[1]=(int)bullet[a].place_old.z/8000;
		/*bullet[a].jaosx=(int)bullet[a].place.x/800;
                  bullet[a].jaosz=(int)bullet[a].place.z/800;*/
		w[1]=maps[bullet[a].sektoriz[1]][bullet[a].sektorix[1]];//define mapsquare 1
		w[0]=maps[bullet[a].sektoriz[0]][bullet[a].sektorix[0]];//define mapsquare 2
		sektoreita=1;
		if(bullet[a].sektorix[0]!=bullet[a].sektorix[1])sektoreita=2;
		if(bullet[a].sektoriz[0]!=bullet[a].sektoriz[1])sektoreita=2;


		//homing // seeking target
		if((ase[bullet[a].from_gun].homing)&&(bullet[a].target!=-6667)){
			if(bullet[a].target<=-1){
				//dq=-atan2f(moped[-bullet[a].target-1].z1-bullet[a].place.z,moped[-bullet[a].target-1].x1-bullet[a].place.x);
				dq=-atan2f(bullet[a].place.z-moped[-bullet[a].target-1].z1,bullet[a].place.x-moped[-bullet[a].target-1].x1)+pi;
				//dq=atan2f(moped[d].z1-moped[0].z1,moped[d].x1-moped[0].x1)+pi;
				bullet[a].e=bullet[a].e+atan2f(moped[-bullet[a].target-1].y1-bullet[a].place.y,(moped[-bullet[a].target-1].x1-bullet[a].place.x)*(moped[-bullet[a].target-1].z1-bullet[a].place.z));
			}
			if(bullet[a].target>=0){
				//dq=-atan2f(character[bullet[a].target].z-bullet[a].place.z,character[bullet[a].target].x-bullet[a].place.x);
				dq=-atan2f(bullet[a].place.z-character[bullet[a].target].z,bullet[a].place.x-character[bullet[a].target].x)+pi;
				//dq=atan2f(moped[d].z1-moped[0].z1,moped[d].x1-moped[0].x1)+pi;
				bullet[a].e=bullet[a].e+atan2f(70-bullet[a].place.y,(character[bullet[a].target].x-bullet[a].place.x)*(character[bullet[a].target].z-bullet[a].place.z));
			}
/*

  if(bullet[a].q<0)bullet[a].q=bullet[a].q+pi*2;
  if(bullet[a].q>2*pi)bullet[a].q=bullet[a].q-pi*2;

  temp1=bullet[a].q;
  if(temp1-dq>pi)temp1=temp1-pi*2;
  if(dq-temp1>pi)dq=dq-pi*2;

  negaatio=1;
  if (dq<temp1)
  negaatio=-1;*/

                        if(bullet[a].q>pi*2)bullet[a].q=bullet[a].q-pi*2;
                        if(bullet[a].q<0)bullet[a].q=bullet[a].q+pi*2;
                        if(dq>pi*2)dq=dq-pi*2;
                        if(dq<0)dq=dq+pi*2;
                        //does it turn left or rigth
                        negaatio=1;
                        temp1=(float)fabs(dq-bullet[a].q);
                        if(temp1>pi*2-temp1)
                        {
                                negaatio=-1;
                        }

                        bullet[a].q=bullet[a].q+negaatio*(dq-bullet[a].q)*elapsed*gamespeed*3*0.001f;


			bullet[a].direction.x=(float)cos(-bullet[a].q)*bullet[a].speed;
			bullet[a].direction.z=(float)sin(-bullet[a].q)*bullet[a].speed;
			bullet[a].direction.y=(float)sin(bullet[a].e)*bullet[a].speed;
		}



		//smoketrail
		if(ase[bullet[a].from_gun].smoke_count>0)//if there is any smoke
                        bullet[a].smoke_count=bullet[a].smoke_count+elapsed*gamespeed;
		while(bullet[a].smoke_count>0){
			bullet[a].smoke_count=bullet[a].smoke_count-ase[bullet[a].from_gun].smoke_count;
			fromsmoke(ase[bullet[a].from_gun].smoke_size, 0.0f,true,100,bullet[a].place.x,bullet[a].place.y,bullet[a].place.z,ase[bullet[a].from_gun].smoke_filled,randDouble(-bullet[a].q+pi-pi/2,-bullet[a].q+pi+pi/2),(float)fabs(randDouble(0,pi)),randDouble(0,2*pi));
		}


		//there is no point about calculating collisions if a bullet is harmless
		if(ase[bullet[a].from_gun].damage<=0){if(bullet[a].place.y<0)bullet[a].remove=true; continue;}

		//go thruogh all the sectors that a bullet visits
		for (j=0; j<sektoreita; j++){

			//bullet's retangle
			r1.left=(long)bullet[a].place_old.x-bullet[a].sektorix[j]*8000;
			r1.top=(long)bullet[a].place_old.z-bullet[a].sektoriz[j]*8000;
			r1.right=(long)bullet[a].place.x-bullet[a].sektorix[j]*8000;
			r1.bottom=(long)bullet[a].place.z-bullet[a].sektoriz[j]*8000;

			if(bullet[a].place_old.x>bullet[a].place.x){
				r1.right=(long)bullet[a].place_old.x-bullet[a].sektorix[j]*8000;
				r1.left=(long)bullet[a].place.x-bullet[a].sektorix[j]*8000;
			}
			if(bullet[a].place_old.z>bullet[a].place.z){
				r1.bottom=(long)bullet[a].place_old.z-bullet[a].sektoriz[j]*8000;

				r1.top=(long)bullet[a].place.z-bullet[a].sektoriz[j]*8000;
			}


                        //does it hit characters
                        if(bullet[a].distance<13000)//is the bullet too far away
                        {

                                for (q=0; q<characters; q++){
                                        if(bullet[a].place_old.y>(130*character[q].height))continue;//if not too high
                                        if(character[q].sektorix!=bullet[a].sektorix[j])continue;//sector check
                                        if(character[q].sektoriz!=bullet[a].sektoriz[j])continue;//sector check
                                        if(bullet[a].from_character==q)continue;//characters cannot shoot them selves
                                        if(character[q].distance>10000)continue;//there is no point about calculating if a character is too far
                                        if(character[q].dying)continue;//continue if it already has hit
                                        if(character[q].inactive)continue;//continue if it already has hit

                                        if(sqrtf(sqr(bullet[a].place.x-character[q].x)+sqr(bullet[a].place.z-character[q].z))>bullet[a].speed*elapsed*gamespeed+100)
                                        {continue;}

                                        if(!linecollidesline(&osuma,&osumax,&osumaz,bullet[a].place_old.x-bullet[a].sektorix[j]*8000,bullet[a].place_old.z-bullet[a].sektoriz[j]*8000,bullet[a].place.x-bullet[a].sektorix[j]*8000,bullet[a].place.z-bullet[a].sektoriz[j]*8000,character[q].x-character[q].sektorix*8000-40,character[q].z-character[q].sektoriz*8000-40,character[q].x-character[q].sektorix*8000+40,character[q].z-character[q].sektoriz*8000+40))continue;
                                        if(linecollidesline(&osuma,&osumax,&osumaz,bullet[a].place_old.x-bullet[a].sektorix[j]*8000,bullet[a].place_old.z-bullet[a].sektoriz[j]*8000,bullet[a].place.x-bullet[a].sektorix[j]*8000,bullet[a].place.z-bullet[a].sektoriz[j]*8000,character[q].x-character[q].sektorix*8000+40,character[q].z-character[q].sektoriz*8000+40,character[q].x-character[q].sektorix*8000-40,character[q].z-character[q].sektoriz*8000-40))
                                        {
                                                kuljettumatka=(float)sqrtf(sqr(osumax+bullet[a].sektorix[j]*8000-bullet[a].place_old.x)+sqr(osumaz+bullet[a].sektoriz[j]*8000-bullet[a].place_old.z))/(bullet[a].speed*elapsed*gamespeed);
                                                height=bullet[a].place_old.y+kuljettumatka*(bullet[a].place.y-bullet[a].place_old.y);

                                                //a passive character may change tacktic if he is being shot
                                                if(bullet[a].from_moped==0)//bullet is not players
                                                        if(character[q].movement_type==1){
                                                                //character escapes if it doesnt have a gun
                                                                if(character[q].weapon_idx==-1)character[q].tactics=2;
                                                                //character attacks if it has a gun
                                                                if(character[q].weapon_idx!=-1)character[q].tactics=0;
                                                        }

                                                //reducing energy and removing bullet
                                                character[q].energy=character[q].energy-ase[bullet[a].from_gun].damage;
                                                bullet[a].remove=true;

                                                //blood
                                                //if(ase[bullet[a].from_gun].num_bounces!=0){
						for (q2=0; q2<50; q2++){
							shoot(-6667,-1,bullet[a].from_moped,randDouble(0,250),moped,4,osumax+bullet[a].sektorix[j]*8000,height,osumaz+bullet[a].sektoriz[j]*8000,bullet[a].q,bullet[a].w,bullet[a].e);
						}
                                                //}

                                                //character dies
                                                if(character[q].energy<0){
                                                        character[q].dying=true;
                                                        //payment for player
                                                        if(bullet[a].from_moped==0)//bullet is player's
                                                                moped[bullet[a].from_moped].money=moped[bullet[a].from_moped].money+1;
                                                        //bodyparts fly
                                                        for (q2=0; q2<11; q2++){
                                                                character[q].bodypart_coords[q2].gox=(float)randDouble(-0.3f,0.3f);
                                                                character[q].bodypart_coords[q2].goy=(float)randDouble(-0.3f,0.3f);
                                                                character[q].bodypart_coords[q2].goz=(float)randDouble(-0.3f,0.3f);

                                                        }
                                                }

                                                //smoke to air
                                                if(ase[bullet[a].from_gun].smoke_filled!=0)
                                                        for (q2=0; q2<3; q2++){
                                                                fromsmoke(ase[bullet[a].from_gun].smoke_size, 0.001f,true,ase[bullet[a].from_gun].smoke_duration+1000,osumax+bullet[a].sektorix[j]*8000,bullet[a].place.y,osumaz+bullet[a].sektoriz[j]*8000,ase[bullet[a].from_gun].smoke_filled,randDouble(-bullet[a].q+pi-pi/2,-bullet[a].q+pi+pi/2),(float)fabs(randDouble(0,pi)),randDouble(0,2*pi));
                                                        }
                                                //explosion
                                                if(ase[bullet[a].from_gun].explosion_size!=0){
                                                        for (q2=0; q2<ase[bullet[a].from_gun].explosion_size*30; q2++){
                                                                shoot(-6667,-1,bullet[a].from_moped,randDouble(100,300),moped,2,osumax+bullet[a].sektorix[j]*8000,bullet[a].place.y,osumaz+bullet[a].sektoriz[j]*8000,randDouble(-pi,pi),randDouble(-pi,pi),randDouble(-pi,pi));
                                                        }
                                                        for (q2=0; q2<pommeja; q2++){
                                                                fromsmoke(ase[bullet[a].from_gun].smoke_size, 0.004f*ase[bullet[a].from_gun].explosion_size,true,ase[bullet[a].from_gun].smoke_duration,osumax+bullet[a].sektorix[j]*8000,bullet[a].place.y,osumaz+bullet[a].sektoriz[j]*8000,3,0,0,0);
                                                        }
                                                        quake=10000/bullet[a].distance;
                                                        playsound(8,2,osumax+bullet[a].sektorix[j]*8000,osumaz+bullet[a].sektoriz[j]*8000);
                                                }
                                                //sound
                                                if(ase[bullet[a].from_gun].explosion_size==0){
                                                        if(ase[bullet[a].from_gun]._type!=4)
                                                                playsound(randInt(13,18),1,osumax+bullet[a].sektorix[j]*8000,osumaz+bullet[a].sektoriz[j]*8000);
                                                }

                                        }
                                }
                        }

                        //does it hit a bike
                        for (d=0; d<num_mopeds; d++) {
                                if(a<10)continue;
                                if(moped[d].inactive)continue;
                                if(moped[d].sektorix!=bullet[a].sektorix[j])continue;//sector check
                                if(moped[d].sektoriz!=bullet[a].sektoriz[j])continue;//sector check

                                if(bullet[a].from_moped!=d) {//is not player's
                                        //if it is too close
                                        if(sqrtf(sqr(moped[d].x1-bullet[a].place.x)+sqr(moped[d].z1-bullet[a].place.z))<60) {
                                                //reducing energy

                                                moped[d].energy=moped[d].energy-ase[bullet[a].from_gun].damage;
                                                //bounce
                                                if(ase[bullet[a].from_gun].num_bounces!=0){
                                                        for (q2=0; q2<ase[bullet[a].from_gun].num_bounces; q2++){
                                                                shoot(-6667,-1,bullet[a].from_moped,randDouble(0,50),moped,3,moped[d].x1,70,moped[d].z1,randDouble(-pi,pi),randDouble(-pi,pi),randDouble(-pi,pi));
                                                        }
                                                }
                                                //smoke to air
                                                if(ase[bullet[a].from_gun].smoke_filled!=0) {
                                                        for (q=0; q<3; q++){
                                                                fromsmoke(ase[bullet[a].from_gun].smoke_size, 0.001f,true,ase[bullet[a].from_gun].smoke_duration+1000,moped[d].x1,70,moped[d].z1,ase[bullet[a].from_gun].smoke_filled,randDouble(-bullet[a].q+pi-pi/2,-bullet[a].q+pi+pi/2),(float)fabs(randDouble(0,pi)),randDouble(0,2*pi));
                                                        }
                                                }
                                                //explosion
                                                if(ase[bullet[a].from_gun].explosion_size!=0){
                                                        for (q2=0; q2<ase[bullet[a].from_gun].explosion_size*30; q2++){
                                                                shoot(-6667,-1,bullet[a].from_moped,randDouble(100,300),moped,3,moped[d].x1,70,moped[d].z1,randDouble(-pi,pi),randDouble(-pi,pi),randDouble(-pi,pi));
                                                        }
                                                        for (q2=0; q2<pommeja; q2++){
                                                                fromsmoke(ase[bullet[a].from_gun].smoke_size, 0.004f*ase[bullet[a].from_gun].explosion_size,true,ase[bullet[a].from_gun].smoke_duration,moped[d].x1,70,moped[d].z1,3,0,0,0);
                                                        }
                                                        quake=10000/bullet[a].distance;
                                                        playsound(8,2,osumax+bullet[a].sektorix[j]*8000,osumaz+bullet[a].sektoriz[j]*8000);
                                                }
                                                //sound
                                                if(ase[bullet[a].from_gun].explosion_size==0){
                                                        if(ase[bullet[a].from_gun]._type!=4)
                                                                playsound(randInt(9,13),1,osumax+bullet[a].sektorix[j]*8000,osumaz+bullet[a].sektoriz[j]*8000);
                                                }
                                                //removing bullet
                                                bullet[a].remove=true;
                                        }

                                        //does it collide with lines
                                        if(linecollidesline(&osuma,&osuix,&osuiz,bullet[a].place_old.x-bullet[a].sektorix[j]*8000,bullet[a].place_old.z-bullet[a].sektoriz[j]*8000,bullet[a].place.x-bullet[a].sektorix[j]*8000,bullet[a].place.z-bullet[a].sektoriz[j]*8000,	moped[d].x6-bullet[a].sektorix[j]*8000,moped[d].z6-bullet[a].sektoriz[j]*8000,moped[d].x5-bullet[a].sektorix[j]*8000,moped[d].z5-bullet[a].sektoriz[j]*8000))

                                        {
                                                kuljettumatka=(float)sqrtf(sqr(osuix+bullet[a].sektorix[j]*8000-bullet[a].place_old.x)+sqr(osuiz+bullet[a].sektoriz[j]*8000-bullet[a].place_old.z))/(bullet[a].speed*elapsed*gamespeed);
                                                height=bullet[a].place_old.y+kuljettumatka*(bullet[a].place.y-bullet[a].place_old.y);
                                                float xa,za;
                                                xa=sqrtf(sqr(osuix-moped[d].x6+bullet[a].sektorix[j]*8000)+sqr(osuiz-moped[d].z6+bullet[a].sektoriz[j]*8000));
                                                za=height;

                                                wallhits=0;
                                                //is it inside a sidepicture
                                                for (b=0; b<wallgroup[1].routes[0].route_count; b++){
                                                        for (c=0; c<wallgroup[1].routes[0].route[b].line_count; c++){
                                                                if(linecollidesline(&osuma,&osumax,&osumaz,xa,za,xa+1000,za+1000,	wallgroup[1].routes[0].route[b].point[c].x1,wallgroup[1].routes[0].route[b].point[c].z1,wallgroup[1].routes[0].route[b].point[c].x2,wallgroup[1].routes[0].route[b].point[c].z2))
                                                                        wallhits=wallhits+1;
                                                        }
                                                }
                                                if((float)wallhits/2*1000!=((int)(wallhits/2))*1000){
                                                        //reduce energy
                                                        moped[d].energy=moped[d].energy-ase[bullet[a].from_gun].damage;
                                                        //bounce
                                                        if(ase[bullet[a].from_gun].num_bounces!=0){
                                                                for (q2=0; q2<ase[bullet[a].from_gun].num_bounces; q2++){
                                                                        shoot(-6667,-1,bullet[a].from_moped,randDouble(0,50),moped,3,osuix+bullet[a].sektorix[j]*8000,height,osuiz+bullet[a].sektoriz[j]*8000,randDouble(-pi,pi),randDouble(-pi,pi),randDouble(-pi,pi));
                                                                }
                                                        }
                                                        //smoke to air
                                                        if(ase[bullet[a].from_gun].smoke_filled!=0){
                                                                for (q=0; q<3; q++){
                                                                        fromsmoke(ase[bullet[a].from_gun].smoke_size, 0.001f,true,ase[bullet[a].from_gun].smoke_duration+1000,osuix+bullet[a].sektorix[j]*8000,height,osuiz+bullet[a].sektoriz[j]*8000,ase[bullet[a].from_gun].smoke_filled,randDouble(-bullet[a].q+pi-pi/2,-bullet[a].q+pi+pi/2),(float)fabs(randDouble(0,pi)),randDouble(0,2*pi));
                                                                }
                                                        }
                                                        //explosion
                                                        if(ase[bullet[a].from_gun].explosion_size!=0){
                                                                for (q2=0; q2<ase[bullet[a].from_gun].explosion_size*30; q2++){
                                                                        shoot(-6667,-1,bullet[a].from_moped,randDouble(100,300),moped,3,osuix+bullet[a].sektorix[j]*8000,height,osuiz+bullet[a].sektoriz[j]*8000,randDouble(-pi,pi),randDouble(-pi,pi),randDouble(-pi,pi));
                                                                }
                                                                for (q2=0; q2<pommeja; q2++){
                                                                        fromsmoke(ase[bullet[a].from_gun].smoke_size, 0.004f*ase[bullet[a].from_gun].explosion_size,true,ase[bullet[a].from_gun].smoke_duration,osuix+bullet[a].sektorix[j]*8000,height,osuiz+bullet[a].sektoriz[j]*8000,3,0,0,0);
                                                                }
                                                                quake=10000/bullet[a].distance;
                                                                playsound(8,2,osumax+bullet[a].sektorix[j]*8000,osumaz+bullet[a].sektoriz[j]*8000);
                                                        }
                                                        //sound
                                                        if(ase[bullet[a].from_gun].explosion_size==0){
                                                                if(ase[bullet[a].from_gun]._type!=4)
                                                                        playsound(randInt(9,13),1,osumax+bullet[a].sektorix[j]*8000,osumaz+bullet[a].sektoriz[j]*8000);
                                                        }
                                                        //removing bullet
                                                        bullet[a].remove=true;
                                                }
                                        }
                                }

                                //}
                                /*
                                  matrices->LoadIdentity();
                                  matrices->TranslateLocal(moped->x6+xa,0+za,moped->z6);
                                  matrices->ScaleLocal(0.2f,0.2f,0.2f);
                                  drawfast(&mallit[2].malli[5]);

                                  matrices->LoadIdentity();
                                  matrices->TranslateLocal(moped->x5,0,moped->z5);
                                  matrices->ScaleLocal(0.2f,0.2f,0.2f);
                                  drawfast(&mallit[2].malli[5]);

                                  matrices->LoadIdentity();
                                  matrices->TranslateLocal(moped->x6,0,moped->z6);
                                  matrices->ScaleLocal(0.2f,0.2f,0.2f);
                                  drawfast(&mallit[2].malli[5]);

                                  pvertex bullet_trace[MAX_BULLETS*2];
                                  q=6;
                                  for (b=0; b<wallgroup[1].routes[0].route_count; b++){
                                  for (c=0; c<wallgroup[1].routes[0].route[b].line_count; c++){
                                  q=q+1;
                                  matrices->LoadIdentity();
                                  matrices->TranslateLocal(moped->x6,0,moped->z6);
                                  bullet_trace[c*2].position.x=wallgroup[1].routes[0].route[b].point[c].x1;
                                  bullet_trace[c*2].position.y=wallgroup[1].routes[0].route[b].point[c].z1;
                                  bullet_trace[c*2].position.z=0;

                                  bullet_trace[c*2+1].position.x=wallgroup[1].routes[0].route[b].point[c].x2;
                                  bullet_trace[c*2+1].position.y=wallgroup[1].routes[0].route[b].point[c].z2;
                                  bullet_trace[c*2+1].position.z=0;

                                  bullet_trace[c*2].u=0;
                                  bullet_trace[c*2].v=0.16f;
                                  bullet_trace[c*2+1].u=1;
                                  bullet_trace[c*2+1].v=0.16f;
                                  }

                                  m_pDevice->SetMaterial( &mat[30] );
                                  m_pDevice->SetTexture( 0, background[30] );
                                  m_pDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, *matrices->GetTop());
                                  m_pDevice->DrawPrimitive(D3DPT_LINELIST  ,
                                  D3DFVF_XYZ |D3DFVF_TEX1|D3DFVF_TEXCOORDSIZE2(0) ,bullet_trace,q,NULL);

                                  }
                                */
                        }



                        //does it hit a wall
                        for (b=0; b<wallgroup[0].routes[w[j]].route_count; b++){
                                for (c=0; c<wallgroup[0].routes[w[j]].route[b].line_count; c++){

                                        if(linecollidesline(&osuma,&osumax,&osumaz,bullet[a].place_old.x-bullet[a].sektorix[j]*8000,bullet[a].place_old.z-bullet[a].sektoriz[j]*8000,bullet[a].place.x-bullet[a].sektorix[j]*8000,bullet[a].place.z-bullet[a].sektoriz[j]*8000,	wallgroup[0].routes[w[j]].route[b].point[c].x1,wallgroup[0].routes[w[j]].route[b].point[c].z1,wallgroup[0].routes[w[j]].route[b].point[c].x2,wallgroup[0].routes[w[j]].route[b].point[c].z2))
                                        {
                                                wallkulma=-atan2f(wallgroup[0].routes[w[j]].route[b].point[c].z2-wallgroup[0].routes[w[j]].route[b].point[c].z1,wallgroup[0].routes[w[j]].route[b].point[c].x2-wallgroup[0].routes[w[j]].route[b].point[c].x1);
                                                osumax2=osumax+cosf(-bullet[a].q+pi+pi)*-100;
                                                osumaz2=osumaz+sinf(-bullet[a].q+pi+pi)*-100;
                                                //prosentual distance that the bullet has travelled before collision.
                                                kuljettumatka=(float)sqrtf(sqr(osumax+bullet[a].sektorix[j]*8000-bullet[a].place_old.x)+sqr(osumaz+bullet[a].sektoriz[j]*8000-bullet[a].place_old.z))/(bullet[a].speed*elapsed*gamespeed);
                                                height=bullet[a].place_old.y+kuljettumatka*(bullet[a].place.y-bullet[a].place_old.y);


                                                //bullet hole
                                                if(ase[bullet[a].from_gun].decal_picture>-1)
                                                        fromsmoke(ase[bullet[a].from_gun].smoke_size, 0,false,40000,osumax+bullet[a].sektorix[j]*8000,height,osumaz+bullet[a].sektoriz[j]*8000,ase[bullet[a].from_gun].decal_picture,-wallkulma,randDouble(0,2*pi),0);
                                                //smoke to air
                                                if(ase[bullet[a].from_gun].smoke_filled!=0)
                                                        for (q=0; q<3; q++){
                                                                fromsmoke(ase[bullet[a].from_gun].smoke_size, 0.001f,true,ase[bullet[a].from_gun].smoke_duration+1000,osumax2+bullet[a].sektorix[j]*8000,height,osumaz2+bullet[a].sektoriz[j]*8000,ase[bullet[a].from_gun].smoke_filled,randDouble(-bullet[a].q+pi-pi/2,-bullet[a].q+pi+pi/2),(float)fabs(randDouble(0,pi)),randDouble(0,2*pi));
                                                        }
                                                //explosion
                                                if(ase[bullet[a].from_gun].explosion_size!=0){
                                                        for (q2=0; q2<ase[bullet[a].from_gun].explosion_size*30; q2++){
                                                                shoot(-6667,-1,bullet[a].from_moped,randDouble(100,300),moped,2,osumax+bullet[a].sektorix[j]*8000,height,osumaz+bullet[a].sektoriz[j]*8000,randDouble(-pi,pi),randDouble(-pi,pi),randDouble(-pi,pi));
                                                        }
                                                        for (q2=0; q2<pommeja; q2++){
                                                                fromsmoke(ase[bullet[a].from_gun].smoke_size, 0.004f*ase[bullet[a].from_gun].explosion_size,true,ase[bullet[a].from_gun].smoke_duration,osumax+bullet[a].sektorix[j]*8000,height,osumaz+bullet[a].sektoriz[j]*8000,3,0,0,0);
                                                        }
                                                        quake=10000/bullet[a].distance;
                                                        playsound(8,2,osumax+bullet[a].sektorix[j]*8000,osumaz+bullet[a].sektoriz[j]*8000);
                                                }
                                                //bounce
                                                if(ase[bullet[a].from_gun].num_bounces>0){
                                                        for (q2=0; q2<ase[bullet[a].from_gun].num_bounces; q2++){
                                                                shoot(-6667,-1,bullet[a].from_moped,randDouble(0,50),moped,3,osumax+bullet[a].sektorix[j]*8000,height,osumaz+bullet[a].sektoriz[j]*8000,randDouble(-pi,pi),randDouble(-pi,pi),randDouble(-pi,pi));
                                                        }
                                                }
                                                //sound
                                                if(ase[bullet[a].from_gun].explosion_size==0){
                                                        if(ase[bullet[a].from_gun]._type!=4)
                                                                playsound(randInt(9,13),1,osumax+bullet[a].sektorix[j]*8000,osumaz+bullet[a].sektoriz[j]*8000);
                                                }



                                                //light
                                                //	setLights(osumax2+bullet[a].sektorix*8000,bullet[a].place.y,osumaz2+bullet[a].sektoriz*8000);


                                                bullet[a].remove=true;
                                        }
                                }
                        }



                        if(bullet[a].place.y<0)//bullet hits the ground
                        {
                                //smoke to air
                                if(ase[bullet[a].from_gun].smoke_filled!=0)
                                        for (q=0; q<3; q++){
                                                osumax=osumax+cosf(-bullet[a].q+pi+pi)*-100;
                                                osumaz=osumaz+sinf(-bullet[a].q+pi+pi)*-100;
                                                fromsmoke(ase[bullet[a].from_gun].smoke_size, 0.001f,true,ase[bullet[a].from_gun].smoke_duration,bullet[a].place.x,0,bullet[a].place.z,ase[bullet[a].from_gun].smoke_filled,randDouble(-bullet[a].q+pi-pi/2,-bullet[a].q+pi+pi/2),(float)fabs(randDouble(0,pi)),randDouble(0,2*pi));
                                        }
                                //explosion
                                if(ase[bullet[a].from_gun].explosion_size!=0){
                                        for (q2=0; q2<ase[bullet[a].from_gun].explosion_size*30; q2++){
						shoot(-6667,-1,bullet[a].from_moped,randDouble(100,300),moped,2,bullet[a].place.x,bullet[a].place.y,bullet[a].place.z,randDouble(-pi,pi),randDouble(-pi,pi),randDouble(-pi,pi));
                                        }
                                        for (q2=0; q2<pommeja; q2++){
                                                fromsmoke(ase[bullet[a].from_gun].smoke_size, 0.004f*ase[bullet[a].from_gun].explosion_size,true,ase[bullet[a].from_gun].smoke_duration,bullet[a].place.x,0,bullet[a].place.z,3,0,0,0);
                                        }
                                        quake=10000/bullet[a].distance;
                                        playsound(8,2,bullet[a].place.x,bullet[a].place.z);
                                }
                                //sound
                                if(ase[bullet[a].from_gun].explosion_size==0){
                                        if(ase[bullet[a].from_gun]._type!=4)
						playsound(randInt(9,13),1,bullet[a].place.x,bullet[a].place.z);
                                }

                                bullet[a].remove=true;
                        }
		}//j ends

		if(bullet[a].place.y>2500)bullet[a].remove=true;

	}

}

void setLights(float x,float y,float z)
{

	int q;
	for (q=0; q<MAX_LIGHTS; q++) if(lights[q].on==false) break;//searching for free lightbulb (lights = lightbulb)
        if(q>=MAX_LIGHTS)q=randInt(0,MAX_LIGHTS);//if there is no free light bulbs


        lights[q].on=true;
        lights[q].valo.dltType = D3DLIGHT_POINT;
        lights[q].valo.dcvDiffuse.r = 1.0f;
        lights[q].valo.dcvDiffuse.g = 1.0f;
        lights[q].valo.dcvDiffuse.b = 1.0f;
        lights[q].valo.dcvAmbient.r = 1.0f;
        lights[q].valo.dcvAmbient.g = 1.0f;
        lights[q].valo.dcvAmbient.b = 1.0f;
        lights[q].valo.dcvSpecular.r = 1.0f;
        lights[q].valo.dcvSpecular.g = 1.0f;
        lights[q].valo.dcvSpecular.b = 1.0f;
        lights[q].valo.dvDirection=D3DVECTOR(1.0f);
        lights[q].valo.dvPosition.x = x;
        lights[q].valo.dvPosition.y = y;
        lights[q].valo.dvPosition.z = z;
        lights[q].valo.dvAttenuation0 = 0.5f;
        lights[q].valo.dvAttenuation1=0.0f;
        lights[q].valo.dvAttenuation2=0.0f;
        lights[q].valo.dvRange = 500;

        m_pDevice->SetLight(q, &lights[q].valo);
        m_pDevice->LightEnable(q, TRUE);
}


void shoot(int target,int from_character, int from_moped,float timer,bikebase *moped, int weapon_idx,float placex,float placey,float placez,float directionx,float directiony,float directionz)//shooting
{
	int a,b,q;
	int d=-1;
	float rekyyli;

	if(placex==0.0){//shooting from a bike
		while(moped->gun_timer[weapon_idx]>=0){
			moped->gun_timer[weapon_idx]=moped->gun_timer[weapon_idx]-ase[moped->ase[weapon_idx]].rate_of_fire;
			for (q=0; q<ase[moped->ase[weapon_idx]].bullets_per_shot; q++){
                                //deciding wich bullet is replaced with a new one
                                a=10;
                                b=0;
                          alku1:
                                a=randInt(10,MAX_BULLETS);
                                b=b+1;
                                if(b>MAX_BULLETS)bullet[a].remove=true;
                                if(!bullet[a].remove)goto alku1;

                                d=a;
                                //recoil
                                rekyyli=((ase[moped->ase[weapon_idx]].pdamage+ase[moped->ase[weapon_idx]].pspeed)/ase[moped->ase[weapon_idx]].prate_of_fire)*0.05f;
                                moped->speed=moped->speed-rekyyli;
                                if(moped->speed<-1.5f)moped->speed=-1.5f;


                                moped->has_muzzle_flare=true;
                                bullet[a].remove=false;
                                bullet[a].from_moped=from_moped;
                                bullet[a].from_gun=moped->ase[weapon_idx];
                                bullet[a].smoke_count=ase[moped->ase[weapon_idx]].smoke_count;
                                /*bullet[a].place.x=moped->x1+cosf(moped->direction)*15*moped->speed;
                                  bullet[a].place.y=moped->y1+70;
                                  bullet[a].place.z=moped->z1+sinf(moped->direction)*15*moped->speed;*/
                                bullet[a].place.x=moped->piippu[3][0];
                                bullet[a].place.y=moped->piippu[3][1];
                                bullet[a].place.z=moped->piippu[3][2];

                                bullet[a].place_old=bullet[a].place;
                                bullet[a].q=-moped->direction;//-mopeds->frontdirection;
                                bullet[a].w=moped->angle_roll;
                                bullet[a].e=moped->angle_pitch;
                                bullet[a].timer=timer;
                                bullet[a].from_character=from_character;
                                //player is target if it is a AI-player's
                                if(from_moped>0)bullet[a].target=-1;
                                else bullet[a].target=target;

                                //bullet speed
                                if(ase[moped->ase[weapon_idx]].speed==666)
                                        bullet[a].speed=randDouble(1.5f,3.5f);
				else bullet[a].speed=ase[moped->ase[weapon_idx]].speed;


                                //speed=random
                                if(ase[moped->ase[weapon_idx]].speed==666)
                                {
                                        bullet[a].direction.x=(float)cos(-bullet[a].q)*bullet[a].speed+randDouble(-ase[moped->ase[weapon_idx]].dispersion,ase[moped->ase[weapon_idx]].dispersion);
                                        bullet[a].direction.z=(float)sin(-bullet[a].q)*bullet[a].speed+randDouble(-ase[moped->ase[weapon_idx]].dispersion,ase[moped->ase[weapon_idx]].dispersion);
                                        bullet[a].direction.y=(float)sin(bullet[a].e)*bullet[a].speed+randDouble(-ase[moped->ase[weapon_idx]].dispersion,ase[moped->ase[weapon_idx]].dispersion);
                                }
                                //moving normally
                                else
                                {
                                        bullet[a].direction.x=(float)cos(-bullet[a].q)*bullet[a].speed+randDouble(-ase[moped->ase[weapon_idx]].dispersion,ase[moped->ase[weapon_idx]].dispersion);
                                        bullet[a].direction.z=(float)sin(-bullet[a].q)*bullet[a].speed+randDouble(-ase[moped->ase[weapon_idx]].dispersion,ase[moped->ase[weapon_idx]].dispersion);
                                        bullet[a].direction.y=(float)sin(bullet[a].e)*bullet[a].speed+randDouble(-ase[moped->ase[weapon_idx]].dispersion,ase[moped->ase[weapon_idx]].dispersion);
                                }
			}

		}
	}

	else{//shot from else where
		for (q=0; q<ase[weapon_idx].bullets_per_shot; q++){
			//deciding wich bullet is replaced with a new one

			a=10;
			b=0;
                  alku2:
                        a=randInt(10,MAX_BULLETS);
                        b=b+1;
                        if(b>MAX_BULLETS)bullet[a].remove=true;
                        if(!bullet[a].remove)goto alku2;
                        d=a;

                        //moped->gun_timer[weapon_idx]=moped->gun_timer[weapon_idx]-ase[moped->ase[weapon_idx]].rate_of_fire;
                        bullet[a].remove=false;
                        bullet[a].from_moped=from_moped;
                        bullet[a].from_gun=weapon_idx;
                        bullet[a].smoke_count=ase[weapon_idx].smoke_count;
                        bullet[a].place.x=placex;
                        bullet[a].place.y=placey;
                        bullet[a].place.z=placez;
                        bullet[a].place_old=bullet[a].place;
                        bullet[a].q=directionx;
                        bullet[a].w=directiony;
                        bullet[a].e=directionz;
                        bullet[a].timer=timer;
                        bullet[a].from_character=from_character;
                        bullet[a].target=target;

                        //bullet speed
                        if((ase[weapon_idx].speed==666))
                                bullet[a].speed=randDouble(1.5f,3.5f);
			else bullet[a].speed=ase[weapon_idx].speed;

			//voices
			if(ase[bullet[a].from_gun]._type==0)playsound(2,1,bullet[a].place.x,bullet[a].place.z);
			if(ase[bullet[a].from_gun]._type==1)playsound(5,1,bullet[a].place.x,bullet[a].place.z);
			if(ase[bullet[a].from_gun]._type==2)playsound(4,1,bullet[a].place.x,bullet[a].place.z);
			if(ase[bullet[a].from_gun]._type==3)playsound(3,1,bullet[a].place.x,bullet[a].place.z);


			//speed=random
			if(ase[weapon_idx].speed==666)
			{
                                bullet[a].direction.x=(float)cos(-bullet[a].q)*bullet[a].speed+randDouble(-ase[weapon_idx].dispersion,ase[weapon_idx].dispersion);
                                bullet[a].direction.z=(float)sin(-bullet[a].q)*bullet[a].speed+randDouble(-ase[weapon_idx].dispersion,ase[weapon_idx].dispersion);
                                bullet[a].direction.y=(float)sin(bullet[a].e)*bullet[a].speed+randDouble(-ase[weapon_idx].dispersion,ase[weapon_idx].dispersion);
			}
			//moves normally
			else
			{
                                bullet[a].direction.x=(float)cos(-bullet[a].q)*bullet[a].speed+randDouble(-ase[weapon_idx].dispersion,ase[weapon_idx].dispersion);
                                bullet[a].direction.z=(float)sin(-bullet[a].q)*bullet[a].speed+randDouble(-ase[weapon_idx].dispersion,ase[weapon_idx].dispersion);
                                bullet[a].direction.y=(float)sin(bullet[a].e)*bullet[a].speed+randDouble(-ase[weapon_idx].dispersion,ase[weapon_idx].dispersion);
			}
		}
	}


        //äänet //a= vähän epävarma
	if(d>=0){
                if(ase[bullet[d].from_gun]._type==0)playsound(2,1,bullet[d].place.x,bullet[d].place.z);
                if(ase[bullet[d].from_gun]._type==1)playsound(5,1,bullet[d].place.x,bullet[d].place.z);
                if(ase[bullet[d].from_gun]._type==2)playsound(4,1,bullet[d].place.x,bullet[d].place.z);
                if(ase[bullet[d].from_gun]._type==3)playsound(3,1,bullet[d].place.x,bullet[d].place.z);
	}


}

void aja(bikebase *moped)
{
	int q,temp1;
	float temp2;
	float kerroin;
	float tuulenvastus;

	//computers drive slower
	//if(moped->numero==0)
        tuulenvastus=0.2f;
	//else tuulenvastus=0.2f;

	if(moped->left||moped->right)
		tuulenvastus=0.24f;


	/*
          float speednyt = moped->speed*elapsed;
          float speed=0;

          moped->nopeutena[50]=(float)(speednyt - speedoli);
          for (q=0; q<50; q++){
          moped->nopeutena[q]=moped->nopeutena[q+1];
          speed=speed+moped->nopeutena[q];
          }
          speed=speed/50;
          speedoli = speednyt;

          moped->speed=moped->speed*elapsed;
        */



	if(!moped->left&&!moped->right)moped->turntime=0;
	else moped->turntime=moped->turntime+elapsed*gamespeed;

	// choosing targetted character
	moped->target_character=-6667;
	for (q=0; q<characters; q++){
		if(character[q].inactive)continue;
		if(character[q].dying)continue;
		//accepted angle is 0.075f
		if(fabs(fabs(character[q].player_angle)-fabs(moped->direction))<0.08f)//if angle is right
		{
			if(moped->target_character==-6667){moped->target_character=q;continue;}
			if(fabs(fabs(character[moped->target_character].player_angle)-fabs(moped->direction))<0.075f)//if last angle is rigth
			{
				if(character[q].distance<character[moped->target_character].distance)//if last angle is farther
                                        moped->target_character=q;
			}
			else moped->target_character=q;
		}
	}
	// choosing targetted moped
	temp1=-6667;
	for (q=0; q<num_mopeds; q++){
		if(q==moped->numero)continue;
		if(moped[q].inactive)continue;
		//accepted angle is 0.075f
		if(fabs(fabs(moped[q].player_angle)-fabs(moped->direction))<0.1f)//is angle is rigth
		{
			if(temp1==-6667){temp1=q;continue;}
			if(fabs(fabs(moped[temp1].player_angle)-fabs(moped->direction))<0.075f)//if last angle is rigth
			{
				if(moped[q].distance<moped[temp1].distance)//if last angle is farther
                                        temp1=q;
			}
			else temp1=q;
		}
	}

	//if there is moped front. shoot it instead
	if(temp1!=-6667) moped->target_character=-temp1-1;

        moped->x3=moped->x1;
        moped->y3=moped->y1;
        moped->z3=moped->z1;
        moped->x4=moped->x2;
        moped->y4=moped->y2;
        moped->z4=moped->z2;


	if(moped->timesparks>=0)moped->timesparks=moped->timesparks-elapsed*gamespeed;
	if(moped->gun_timer[0]<0)moped->gun_timer[0]=moped->gun_timer[0]+elapsed*gamespeed;
	if(moped->gun_timer[1]<0)moped->gun_timer[1]=moped->gun_timer[1]+elapsed*gamespeed;
	if(moped->gun_timer[2]<0)moped->gun_timer[2]=moped->gun_timer[2]+elapsed*gamespeed;
	if(moped->gun_timer[3]<0)moped->gun_timer[3]=moped->gun_timer[3]+elapsed*gamespeed;



	if((moped->enter==false) & (moped->enter2==true))
	{
		//asking for a mission
		if(moped->mission.status!=0)//there is no mission
                        if(moped->nearestcharacter>-1)
                                if(character[moped->nearestcharacter].movement_type==0)
                                        if(!character[moped->nearestcharacter].dying)
                                                if(fabs(moped->speed)<0.7f){
                                                        create_mission(moped,-1);
                                                        gamephase=1;
                                                        SndObjStop(voices[1]);
                                                }
	}

	if(moped->up)//throttle
	{
		moped->angle_pitch=moped->angle_pitch+2*0.4f*0.001f*elapsed*gamespeed;
		moped->speed=moped->speed+(0.002f-sqr(moped->speed)*tuulenvastus/1000)*elapsed*gamespeed;
	}
	else if(moped->down)//brake
	{
		if(moped->angle_pitch>0)
			moped->angle_pitch=moped->angle_pitch-2*0.3f*0.001f*elapsed*gamespeed;
		if(moped->speed>0)//while braking
                        moped->speed=moped->speed-(0.002f+sqr(moped->speed)*tuulenvastus/1000)*elapsed*gamespeed;
		else//while reverse
                        moped->speed=moped->speed-(0.0005f-sqr(moped->speed)*tuulenvastus/1000)*elapsed*gamespeed;
	}
	if((!moped->down)&&(!moped->up))//no throtle or brake
	{
		if(moped->speed>0)
			moped->speed=moped->speed-(sqr(moped->speed)*tuulenvastus/1000)*elapsed*gamespeed;
		else
			moped->speed=moped->speed+(sqr(moped->speed)*tuulenvastus/1000)*elapsed*gamespeed;
	}

	//tilting bike
	moped->angle_roll=moped->etudirection*sqr(moped->speed);

	//pop a wheelie
	//if(moped->angle_pitch>0) //if(mopeds->wheelie angle>0)
        moped->angle_pitch=moped->angle_pitch-(float)fabs((moped->speed*0.4f+0.2f)*0.001f*elapsed*gamespeed);
	if(moped->angle_pitch>pi/4)moped->angle_pitch=pi/4;
	if(moped->angle_pitch<0) moped->angle_pitch=0;

	//if(moped->angle_pitch>0.5f)	//if(mopeds->wheelie angle>0.5f)
	//if(randInt((int)(moped->angle_pitch*elapsed),10)==9)


	//mopeds release smoke
	moped->smoke_timer=moped->smoke_timer+elapsed*gamespeed*(moped->angle_pitch+0.1f);
	while(moped->smoke_timer>=0){
                moped->smoke_timer=moped->smoke_timer-4.0f;
                fromsmoke(1.0f,-0.01f,true,randDouble(200,400),moped->x2+randDouble(-10,10)-cosf(moped->direction)*15,randDouble(0,30),moped->z2+randDouble(-10,10)-sinf(moped->direction)*15,4,randDouble(0,2*pi),0,randDouble(0,2*pi));
	}

	//turning front wheel
	temp2=moped->speed;
	if(temp2==0)temp2=0.01f;
	float maksimi=(0.5f)/(float)fabs(temp2*3.0f);
	if (maksimi>pi/4)maksimi=pi/4;

	//the longer it is pressed the faster it turns
	float turnrate;
	turnrate=moped->turntime*moped->turntime*0.666f*0.0001f;
	if(turnrate>1)turnrate=1;

	if(moped->left)
	{
		moped->etudirection=moped->etudirection+turnrate*maksimi/0.2f/1000*elapsed*gamespeed;
	}
	else if(moped->right)
	{
		moped->etudirection=moped->etudirection-turnrate*maksimi/0.2f/1000*elapsed*gamespeed;
	}
	else
	{
		moped->etudirection=moped->etudirection-moped->etudirection*0.004f*elapsed*gamespeed;
	}
	if(moped->etudirection<0)
                if(moped->etudirection<=-maksimi)moped->etudirection=-maksimi;
	if(moped->etudirection>0)
                if(moped->etudirection>=maksimi)moped->etudirection=maksimi;

	float liike=elapsed*gamespeed*(moped->speed);


	//fromt wheel moves
	moped->x1=moped->x1+(float)cos(moped->direction+moped->etudirection)*liike;
	moped->z1=moped->z1+(float)sin(moped->direction+moped->etudirection)*liike;
	//handbrake
	if(moped->space){
		if(moped->angle_pitch>0)
			moped->angle_pitch=moped->angle_pitch-2*0.3f*0.001f*elapsed*gamespeed;
		if(moped->speed>0)//while braking
			moped->speed=moped->speed-(0.001f+sqr(moped->speed)*tuulenvastus/1000)*elapsed*gamespeed;
		else//while reverse
                        moped->speed=moped->speed+(0.002f+sqr(moped->speed)*tuulenvastus/1000)*elapsed*gamespeed;
		//stops completely if riding slowly
		if(fabs(moped->speed)<(0.002f+sqr(moped->speed)*tuulenvastus/1000)*elapsed*gamespeed)
			moped->speed=0;
		else moped->direction=moped->direction+moped->etudirection*-0.7f;
	}
	//rear wheel moves
	moped->x2=moped->x2+cosf(moped->direction)*liike;
	moped->z2=moped->z2+sinf(moped->direction)*liike;
	//calculate direction
	moped->direction=atan2f(moped->z1-moped->z2,moped->x1-moped->x2);
	if (moped->direction<0)moped->direction=moped->direction+2*pi;
	if (moped->direction>2*pi)moped->direction=moped->direction-2*pi;
	if(sqrtf(sqr(moped->z1-moped->z2)+sqr(moped->x1-moped->x2))!=70)
	{
		kerroin=sqrtf(sqr(70)/(sqr(moped->z1-moped->z2)+sqr(moped->x1-moped->x2)));
		moped->x2=(moped->x2-moped->x1)*kerroin+moped->x1;
		moped->z2=(moped->z2-moped->z1)*kerroin+moped->z1;
	}
	//roll wheels
        //how much it has moved
        float matka=sqrtf((float)sqr(cos(moped->direction)*elapsed*gamespeed*moped->speed)+(float)sqr(sin(moped->direction)*elapsed*gamespeed*moped->speed));

        if (moped->speed<0)
                moped->angle_yaw=moped->angle_yaw+(matka*2*pi)/(2*pi*20);
        else
                moped->angle_yaw=moped->angle_yaw-(matka*2*pi)/(2*pi*20);

	//moped->x1=moped->x1+moped->speed*elapsed*gamespeed;
	//front wheel front side
	moped->x5=moped->x1+cosf(moped->direction)*70.0f;
	moped->y5=0;
	moped->z5=moped->z1+sinf(moped->direction)*70.0f;
	//rear wheel rear side
	moped->x6=moped->x2-cosf(moped->direction)*25.0f;
	moped->y6=0;
	moped->z6=moped->z2-sinf(moped->direction)*25.0f;


	moped->has_muzzle_flare=false;
	//shooting
	if(moped->one)
		shoot(moped->target_character,-1,moped->numero,-1,moped,0, 0, 0, 0, 0, 0, 0);
	if(moped->two)
		shoot(moped->target_character,-1,moped->numero,-1,moped,1, 0, 0, 0, 0, 0, 0);
	if(moped->three)
		shoot(moped->target_character,-1,moped->numero,-1,moped,2, 0, 0, 0, 0, 0, 0);
	if(moped->four)
		shoot(moped->target_character,-1,moped->numero,-1,moped,3, 0, 0, 0, 0, 0, 0);


	//sectors
	moped->sektorix=(int)moped->x1/8000;
	moped->sektoriz=(int)moped->z1/8000;

	//there is a bullet under a moped
	bullet[moped->numero].remove=false;
	bullet[moped->numero].from_gun=5;
	bullet[moped->numero].from_moped=moped->numero;
	bullet[moped->numero].timer=-1;
	bullet[moped->numero].place.x=moped->x5;
	bullet[moped->numero].place.y=50;
	bullet[moped->numero].place.z=moped->z5;
	bullet[moped->numero].place_old.x=moped->x3;
	bullet[moped->numero].place_old.y=50;
	bullet[moped->numero].place_old.z=moped->z3;



}

bool Render(void)
{
	m_pDevice->BeginScene();

	switch (gamephase)
	{
	case 0:{
		clearzbuffer();
		render_game();
		break;
        }
	case 1:{

		clearzbuffer();
		render_mission();
		break;
        }
	case 2:{
		render_workshop();
		break;
        }
	case 3:
		break;
	case 4:{
		clearzbuffer();
		if(keytimer>-10*elapsed)keytimer=keytimer-(int)elapsed;
		render_menu();
		break;
        }
	}

	if(options[1]&&SOUNDS_LOADED){
		int q;
		for (q=0; q<25; q++){
			soundtimer[q]=soundtimer[q]+elapsed*gamespeed;
		}
	}



	if(plusmiinus!=0){
		CHAR t[100];
		rendertext(10,10,0,"debug mode:");

		ltoa(bug1,t,10);
		rendertext(10,25,0,t);

		ltoa(bug2,t,10);
		rendertext(10,40,0,t);

		ltoa(bug3,t,10);
		rendertext(10,55,0,t);

		ltoa((long)(plusmiinus*1000),t,10);
		rendertext(10,70,0,t);

		ltoa((long)(1000/elapsed),t,10);
		rendertext(10,85,0,t);
	}



	m_pDevice->EndScene();
	return true;
}

void calculateCollisions(void)//collisions
{
	bool osuma,osuma2;
	float osumax,osumaz;
	float wallkulma;
	float temp1;
	int a,b,c,d;
	int q;
	bool osuu;
	bool turned;
	int wallhits;
	int wallhits2;
	int mapx,mapz,b2,c2;
	float kx,kz;

	for (d=0; d<num_mopeds; d++){
                if(moped[d].inactive)continue;
		osuma=false;
		osuu=false;

                mapx=moped[d].sektorix;
                mapz=moped[d].sektoriz;

                //}
		//}
                for (q=99; q>0; q--){
                        moped[d].osuma[q]=moped[d].osuma[q-1];
                }
		kx=moped[d].x3;
		kz=moped[d].z3;
                if(fabs(moped[d].speed)<1.6f){
                        kx=moped[d].x2;
                        kz=moped[d].z2;
                }

                moped[d].osuma[0]=false;
                //collisions with walls
                //for (a=0; a<wallgroup[0].group_count; a++){
                a=maps[mapz][mapx];
		for (b=0; b<wallgroup[0].routes[a].route_count; b++){
			for (c=0; c<wallgroup[0].routes[a].route[b].line_count; c++){
				if(linecollidesline(&osuma,&osumax,&osumaz,moped[d].x1-mapx*8000,moped[d].z1-mapz*8000,kx-mapx*8000,kz-mapz*8000,	wallgroup[0].routes[a].route[b].point[c].x1,wallgroup[0].routes[a].route[b].point[c].z1,wallgroup[0].routes[a].route[b].point[c].x2,wallgroup[0].routes[a].route[b].point[c].z2))
					//||(linecollidesline(&osuma,&osumax,&osumaz,mtempx1-mapx*8000,mtempz1-mapz*8000,mtempx2-mapx*8000,mtempz2-mapz*8000,	wallgroup[0].routes[a].route[b].point[c].x1,wallgroup[0].routes[a].route[b].point[c].z1,wallgroup[0].routes[a].route[b].point[c].x2,wallgroup[0].routes[a].route[b].point[c].z2)))
				{
					//moped[d].speed=-moped[d].speed/3;

					moped[d].osuma[0]=true;
					//sparks
                                        if(moped[d].timesparks<0){
                                                for (q=0; q<70; q++){
                                                        shoot(-6667,-1,2,randDouble(100,200),moped,3,osumax+mapx*8000+randDouble(-20,20),50+randDouble(-20,20),osumaz+mapz*8000+randDouble(-20,20),randDouble(-pi,pi),randDouble(-pi,pi),randDouble(-pi,pi));
                                                }
						moped[d].timesparks=moped[d].timesparks+randDouble(100,500);
                                        }
					playsound(randInt(6,8),(float)fabs(moped[d].speed/3.2f),moped[d].x1,moped[d].z1);

					moped[d].x1=moped[d].x3;
					moped[d].y1=moped[d].y3;
					moped[d].z1=moped[d].z3;
					moped[d].x2=moped[d].x4;
					moped[d].y2=moped[d].y4;
					moped[d].z2=moped[d].z4;

					wallkulma=atan2f(wallgroup[0].routes[a].route[b].point[c].z2-wallgroup[0].routes[a].route[b].point[c].z1,wallgroup[0].routes[a].route[b].point[c].x2-wallgroup[0].routes[a].route[b].point[c].x1);

					if (wallkulma<0)wallkulma=wallkulma+2*pi;

					//rotate wall if angle between it and moped is >90 degrees
					turned=false;
					temp1=(float)fabs(wallkulma-moped[d].direction);
					if(temp1>pi)temp1=2*pi-temp1;
					if(temp1>=2*pi)temp1=temp1-2*pi;
					temp1=(float)fabs(temp1);
					if(temp1>pi/2)
					{
						wallkulma=wallkulma-pi;
						turned=true;
					}

					//calculate angle between moped and wall
					temp1=(float)fabs(wallkulma-moped[d].direction);
					if(temp1>pi)temp1=2*pi-temp1;
					if(temp1>=2*pi)temp1=temp1-2*pi;
					temp1=(float)fabs(temp1);



					moped[d].etudirection=0;


					//to same direction as wall
					if(temp1<pi*0.47f){
						if(moped[d].speed>0){
                                                        moped[d].x1=moped[d].x2+(float)cos(wallkulma)*70;
                                                        moped[d].z1=moped[d].z2+(float)sin(wallkulma)*70;
						}
						else{
                                                        moped[d].x2=moped[d].x1-(float)cos(wallkulma)*70;
                                                        moped[d].z2=moped[d].z1-(float)sin(wallkulma)*70;
						}

						//re check
						for (b2=0; b2<wallgroup[0].routes[a].route_count; b2++){
                                                        for (c2=0; c2<wallgroup[0].routes[a].route[b2].line_count; c2++){
                                                                if(linecollidesline(&osuma2,&osumax,&osumaz,moped[d].x1-mapx*8000,moped[d].z1-mapz*8000,kx-mapx*8000,kz-mapz*8000,	wallgroup[0].routes[a].route[b2].point[c2].x1,wallgroup[0].routes[a].route[b2].point[c2].z1,wallgroup[0].routes[a].route[b2].point[c2].x2,wallgroup[0].routes[a].route[b2].point[c2].z2))
                                                                {
                                                                        moped[d].x1=moped[d].x3;
                                                                        moped[d].y1=moped[d].y3;
                                                                        moped[d].z1=moped[d].z3;
                                                                        moped[d].x2=moped[d].x4;
                                                                        moped[d].y2=moped[d].y4;
                                                                        moped[d].z2=moped[d].z4;
                                                                        moped[d].speed=-moped[d].speed/3;
                                                                        moped[d].angle_pitch=0;
                                                                }
                                                        }
						}

					}
					//backwards from wall
					else{
						moped[d].speed=-moped[d].speed/3;
						moped[d].angle_pitch=0;
					}

				}


				if(osuma)break;
			}
			if(osuma)break;
                        //	}
                        //if(osuma)break;
                }





                //is it inside a house
                wallhits=0;
                wallhits2=0;
                a=maps[mapz][mapx];
                for (b=0; b<wallgroup[0].routes[a].route_count; b++){
			for (c=0; c<wallgroup[0].routes[a].route[b].line_count; c++){
				if(linecollidesline(&osuma,&osumax,&osumaz,moped[d].x1-mapx*8000,moped[d].z1-mapz*8000,moped[d].x1-mapx*8000+80000,moped[d].z1-mapz*8000+80000,	wallgroup[0].routes[a].route[b].point[c].x1,wallgroup[0].routes[a].route[b].point[c].z1,wallgroup[0].routes[a].route[b].point[c].x2,wallgroup[0].routes[a].route[b].point[c].z2))
					wallhits=wallhits+1;
				if(linecollidesline(&osuma,&osumax,&osumaz,moped[d].x2-mapx*8000,moped[d].z2-mapz*8000,moped[d].x2-mapx*8000+80000,moped[d].z2-mapz*8000+80000,	wallgroup[0].routes[a].route[b].point[c].x1,wallgroup[0].routes[a].route[b].point[c].z1,wallgroup[0].routes[a].route[b].point[c].x2,wallgroup[0].routes[a].route[b].point[c].z2))
					wallhits2=wallhits2+1;
			}
                }
                /*if((float)wallhits/2*1000!=((int)(wallhits/2))*1000)
                  osuu=true;
                  if((float)wallhits2/2*1000!=((int)(wallhits2/2))*1000)
                  osuu=true;*/
                if(((float)wallhits/2*1000!=((int)(wallhits/2))*1000)&((float)wallhits2/2*1000!=((int)(wallhits2/2))*1000))
                        osuu=true;


                //return old coordinates if it hits
                if(osuu){

                        moped[d].osuma[0]=true;

                        //return coordinates
                        moped[d].x1=moped[d].x3;
                        moped[d].y1=moped[d].y3;
                        moped[d].z1=moped[d].z3;
                        moped[d].x2=moped[d].x4;
                        moped[d].y2=moped[d].y4;
                        moped[d].z2=moped[d].z4;
                }



        }


}

bool readpictures(void)
{
        std::cout << "loading pictures" << std::endl;

	DDCOLORKEY color;
	int q;
	pictures	=	new LPDIRECTDRAWSURFACE7[numpictures];
/*
  font1=loadPicture(m_pDD,"textures/abc.bmp",false);
  color.dwColorSpaceHighValue=0xFFFFFF;
  color.dwColorSpaceLowValue=0xFFFFFF;
  font1->SetColorKey(DDCKEY_SRCBLT,&color);
*/

	char row[256], temprow[256];

	for (q=0; q<numpictures; q++){

                strcpy(row,"textures/pic");
                itoa(q,temprow,10);
                strcat(row,temprow);
                strcat(row,".bmp");

                pictures[q]=loadPicture(m_pDD, row,false);
                color.dwColorSpaceHighValue=0x000000;
                color.dwColorSpaceLowValue=0x000000;
                pictures[q]->SetColorKey(DDCKEY_SRCBLT,&color);
	}

	return true;

}

bool initkeyb(void)
{
        std::cout << "initializing keyboard" << std::endl;
	HRESULT hr;
	// Create the DirectInput object.
        hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION,
                        IID_IDirectInput8, &g_lpDI, NULL);
        if FAILED(hr) return FALSE;

	//näpiskä //this is some weird slang word. seriously wtf, wille!?
	//keyboard,
	// Retrieve a pointer to an IDirectInputDevice7 interface
	hr = g_lpDI->CreateDevice(GUID_SysKeyboard,
			&g_lpDIDevice,NULL);
	if FAILED(hr)
                 {
                         deinitkeyb();
                         return FALSE;
                 }
	// Now that you have an IDirectInputDevice7 interface, get
	// it ready to use.
	// Set the data format using the predefined keyboard data
	// format provided by the DirectInput object for keyboards.
	hr = g_lpDIDevice->SetDataFormat(&g_lpDIDevice);
	if FAILED(hr)
                 {
                         deinitkeyb();
                         return FALSE;
                 }
	// Set the cooperative level
	hr = g_lpDIDevice->SetCooperativeLevel(hWnd,
                        DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if FAILED(hr)
                 {
                         deinitkeyb();
                         return FALSE;
                 }
	// Get access to the input device.
	hr = g_lpDIDevice->Acquire();
	if FAILED(hr)
                 {
                         deinitkeyb();
                         return FALSE;
                 }



	//mouse
	hr = g_lpDI->CreateDevice(GUID_SysMouse, &g_pMouse, NULL);
	if (FAILED(hr))
        {
                deinitkeyb();
                return FALSE;
        }
	hr = g_pMouse->SetDataFormat(&g_pMouse);
	if (FAILED(hr))
        {
                deinitkeyb();
                return FALSE;
        }
	hr = g_pMouse->SetCooperativeLevel(hWnd,DISCL_EXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(hr))
        {
                deinitkeyb();
                return FALSE;
        }

	hr = g_pMouse->Acquire();
	if (FAILED(hr))
        {
                deinitkeyb();
                return FALSE;
        }

        return TRUE;


}

bool deinitkeyb(void)
{

	if (g_lpDI)
	{
		if (g_lpDIDevice)
		{

                        //Always unacquire device before calling Release().

                        g_lpDIDevice->Unacquire();
                        g_lpDIDevice->Release();
                        g_lpDIDevice = NULL;
		}
		g_lpDI->Release();
		g_lpDI = NULL;

		if (g_pMouse)
		{

                        //Always unacquire device before calling Release().

                        g_pMouse->Unacquire();
                        g_pMouse->Release();
                        g_pMouse = NULL;
		}
	}



	return true;
}


void removeobj(obj *target, int indeksi)
{
	for (int a=0; a<indeksi; a++)
	{
                for (int q=0; q<target[a].count; q++)
                        delete(target[a].sisus[q].loota.triangle);
                delete(target[a].sisus);
	}
	delete(target);

}

void CleanUp(void)
{

	int q;

	is_quitting=true;
	deinitkeyb();

	//removing walls
	for (int c=0; c<num_wallgroups; c++){
		for (int a=0; a<wallgroup[c].group_count; a++)
		{
			for (int b=0; b<wallgroup[c].routes[a].route_count; b++)
			{
                                delete(wallgroup[c].routes[a].route[b].point);
			}
			delete(wallgroup[c].routes[a].route);
		}
		delete(wallgroup[c].routes);
	}


	removeobj(mallit[0].malli,	objnum0	);
	removeobj(mallit[1].malli,	objnum1	);
	removeobj(mallit[2].malli,	objnum2	);
	removeobj(mallit[3].malli,	objnum3	);
	removeobj(mallit[4].malli,	objnum4	);
	removeobj(mallit[5].malli,	objnum5	);
	removeobj(mallit[6].malli,	objnum6	);
	removeobj(mallit[7].malli,	objnum7	);
	removeobj(mallit[8].malli,	objnum8	);
	removeobj(mallit[9].malli,	objnum9	);
	removeobj(mallit[10].malli,	objnum10);

	delete(background);
	//RELEASE(font1);
	for (q=0; q<numpictures; q++)	RELEASE(pictures[q]);

	//delete(lights);
	delete(mat);

	D3DXUninitialize();

	RELEASE(m_pDevice);
	RELEASE(m_pDD);

	RELEASE(taka);
	RELEASE(zbuffer);

	if(SOUNDS_LOADED){
                for (q=0; q<SAMPLE_NUMBER; q++)
                        SndObjDestroy(voices[q]);
	}

	if(lpDS)lpDS->Release();
}



BOOL draw(obj *tavara)
{

/*
  matrices->TranslateLocal(tavara->x,tavara->y,tavara->z); //matrices = matrix
  matrices->RotateYawPitchRollLocal(tavara->rx,tavara->ry,tavara->rz);
*/
	//matrices->TranslateLocal(tavara->x,tavara->y,tavara->z);
	m_pDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, *matrices->GetTop());
	tavara->sijainti=*matrices->GetTop();
	if (tavara->mirror) m_pDevice->SetRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_CW);
	else m_pDevice->SetRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_CCW);
/*
  m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,TRUE);
  // Set the source blend state.
  m_pDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND,
  D3DBLEND_ONE);
// Set the destination blend state.
m_pDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND,
D3DBLEND_SRCCOLOR );
*/
	for (INT q=0; q<tavara->count; q++)
	{
		//make reflektions //if steel// (or sword)
		/*if((tavara->sisus[q].material==1)||(tavara->sisus[q].matsku==3))
                  m_pDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE,TRUE);*/
		//else
		//m_pDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE,TRUE);


		//matrices->Push();
		//matrices->TranslateLocal(tavara->sisus[q].x,tavara->sisus[q].y,tavara->sisus[q].z);
		//matrices->TranslateLocal(tavara->sisus[q].x,tavara->sisus[q].y,tavara->sisus[q].z);
		//m_pDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, *matrices->GetTop());
		m_pDevice->SetMaterial( &mat[tavara->sisus[q].texture] );
		m_pDevice->SetTexture( 0, background[tavara->sisus[q].texture2] );

		m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST  ,
                                D3DFVF_XYZ  | D3DFVF_NORMAL | D3DFVF_TEX1|D3DFVF_TEXCOORDSIZE2(0)//|D3DFVF_TEXCOORDSIZE1(1)
                                ,(LPVOID)tavara->sisus[q].loota.triangle,tavara->sisus[q].loota.vert,NULL);
		//matrices->Pop();
	}
	//m_pDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE,FALSE);
	//m_pDevice->SetTexture( 0, NULL);//tarvitaanko tätä?
	return true;

}


BOOL drawfast(obj *tavara)
{


	m_pDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, *matrices->GetTop());
	//tavara->sijainti=*matrices->GetTop();
	//if (tavara->mirror) m_pDevice->SetRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_CW);
	//else m_pDevice->SetRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_CCW);

	for (INT q=0; q<tavara->count; q++)
	{
		//make reflektions //if steel// (or sword)
		//if((tavara->sisus[q].material==1)||(tavara->sisus[q].matsku==3))
		//m_pDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE,TRUE);
		//else
		//m_pDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE,TRUE);


		//matrices->Push();
		//matrices->TranslateLocal(tavara->sisus[q].x,tavara->sisus[q].y,tavara->sisus[q].z);
		if(quake>0){
			matrices->TranslateLocal(randDouble(-quake,quake),randDouble(-quake,quake),randDouble(-quake,quake));
			m_pDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, *matrices->GetTop());
		}

		m_pDevice->SetMaterial( &mat[tavara->sisus[q].texture] );
		m_pDevice->SetTexture( 0, background[tavara->sisus[q].texture2] );

		m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST  ,
                                D3DFVF_XYZ  | D3DFVF_NORMAL | D3DFVF_TEX1|D3DFVF_TEXCOORDSIZE2(0)//|D3DFVF_TEXCOORDSIZE1(1)
                                ,(LPVOID)tavara->sisus[q].loota.triangle,tavara->sisus[q].loota.vert,NULL);
		//matrices->Pop();

		/*m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST  ,
                  D3DFVF_XYZ  | D3DFVF_NORMAL | D3DFVF_TEX1|D3DFVF_TEXCOORDSIZE2(0)//|D3DFVF_TEXCOORDSIZE1(1)
                  ,(LPVOID)tavara->sisus[q].loota.triangle,tavara->sisus[q].loota.vert,NULL);		*/
	}
	//m_pDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE,FALSE);
	//m_pDevice->SetTexture( 0, NULL);//tarvitaanko tätä?
	return true;

}

void calculatecharacters(void) //calculatecharacters
{
	int q,mapx,mapz,wallhits;
	int a,b,c;
	bool osuma;
	float osumax,osumaz;
	float cos,sin;
	float MOTION_SPEED=0.1f;
	int inactiveko;
	int osumia;
	moped[0].nearestcharacter=-1;

	for (q=0; q<characters; q++)
	{

		//randomize new character if one is dead
		if(character[q].inactive){
			create_character(q);
		}

		for (a=99; a>0; a--){
			character[q].osuma[a]=character[q].osuma[a-1];
		}

		character[q].x2=character[q].x;
		character[q].z2=character[q].z;

		/*//A character will be executed if it too near to edge
                  if(character[q].sektorix==0) character[q].dying=true;
                  if(character[q].sektorix==mapsx-1) character[q].dying=true;
                  if(character[q].sektoriz==0) character[q].dying=true;
                  if(character[q].sektoriz==mapsz-1) character[q].dying=true;*/

		//A character will be executed if it too near to edge
		if(character[q].sektorix==-1) character[q].dying=true;
		if(character[q].sektorix==mapsx) character[q].dying=true;
		if(character[q].sektoriz==-1) character[q].dying=true;
		if(character[q].sektoriz==mapsz) character[q].dying=true;

		//legs dont swing if speed is 0
		if(character[q].speed==0){
			character[q].lx=0;
			character[q].rx=0;
		}

		/*mapx=(int)character[q].x/8000;
                  mapz=(int)character[q].z/8000;
                  w=maps[mapz][mapx];*/



		//distance from moped
		character[q].distance=sqrtf(sqr(character[q].x-moped[0].x1)+sqr(character[q].z-moped[0].z1));

		//is it nearest
		if((character[q].distance<300)&&(character[q].movement_type==0))
                        //if(character[q].weapon_idx==-1)
			if(moped[0].nearestcharacter==-1)
				moped[0].nearestcharacter=q;
			else if(character[q].distance>character[moped[0].nearestcharacter].distance)
				moped[0].nearestcharacter=q;


		if(character[q].dying){
			character[q].speed=0;//doesnt move if dead
			inactiveko=0;
			for (a=0; a<11; a++){
				if(character[q].bodypart_coords[a].y<-100)
					inactiveko=inactiveko+1;
				character[q].bodypart_coords[a].goy=character[q].bodypart_coords[a].goy-elapsed*gamespeed*0.25f/1000;
				character[q].bodypart_coords[a].x=character[q].bodypart_coords[a].x+character[q].bodypart_coords[a].gox*elapsed*gamespeed;
				character[q].bodypart_coords[a].y=character[q].bodypart_coords[a].y+character[q].bodypart_coords[a].goy*elapsed*gamespeed;
				character[q].bodypart_coords[a].z=character[q].bodypart_coords[a].z+character[q].bodypart_coords[a].goz*elapsed*gamespeed;
			}
			if(inactiveko==11)character[q].inactive=true;
		}
		if(character[q].distance<15000){
                        if(character[q].dying)continue;


                        cos=cosf(character[q].direction);
                        sin=sinf(character[q].direction);

                        character[q].player_angle=atan2f(moped[0].z1-character[q].z,moped[0].x1-character[q].x)+pi;



                        /*
                          matrices->Push();q=3;//left upper arm
                          matrices->Push();q=4;//left lower arm
                          matrices->TranslateLocal(character[a].bodypart_coords[q].x,character[a].bodypart_coords[q].y,character[a].bodypart_coords[q].z);
                          matrices->RotateYawPitchRollLocal(character[a].bodypart_coords[q].rx,character[a].bodypart_coords[q].ry,character[a].bodypart_coords[q].rz);

                          matrices->Push();q=8;//rigth upper arm
                          matrices->Push();q=7;//rigth lower arm*/

			//reset arms
			character[q].bodypart_coords[8].rz=0;
			character[q].bodypart_coords[3].rz=0;
			character[q].bodypart_coords[7].rz=0;
			character[q].bodypart_coords[4].rz=0;


                        //walks
                        if(character[q].tactics==1){

                                //arms are swinging
                                character[q].bodypart_coords[8].rz=(character[q].lx*1.2f+0.24f)*character[q].speed*10;//lift upper arm (rigth)
                                character[q].bodypart_coords[3].rz=(character[q].rx*1.2f+0.24f)*character[q].speed*10;//lift upper arm (left)
                                character[q].bodypart_coords[7].rz=(character[q].rx*-0.55f)*character[q].speed*10;//lift lower arm (rigth)
                                character[q].bodypart_coords[4].rz=(character[q].lx*-0.55f)*character[q].speed*10;//lift lower arm (left)

                        }

                        //escapes
                        if(character[q].tactics==2){

                                //arms are swinging
                                character[q].bodypart_coords[8].rz=(character[q].lx*1.2f+0.24f)*character[q].speed*10;//lift upper arm (rigth)
                                character[q].bodypart_coords[3].rz=(character[q].rx*1.2f+0.24f)*character[q].speed*10;//lift upper arm (left)
                                character[q].bodypart_coords[7].rz=(character[q].rx*-0.55f)*character[q].speed*10;//lift lower arm (rigth)
                                character[q].bodypart_coords[4].rz=(character[q].lx*-0.55f)*character[q].speed*10;//lift lower arm (left)

                                character[q].direction=character[q].player_angle;
                                if(character[q].distance<1000)character[q].speed=0.2f;
                        }

                        //attack
                        if(character[q].tactics==0){
                                character[q].menoajastin=character[q].menoajastin-elapsed*gamespeed;
                                if(character[q].distance<5000)
                                {
                                        character[q].direction=atan2f(moped[0].z1-sinf(moped[0].direction)*randDouble(30,moped[0].speed*30+30)-character[q].z,moped[0].x1-cosf(moped[0].direction)*randDouble(30,moped[0].speed*30+30)-character[q].x);
                                        character[q].bodypart_coords[8].rz=1.5f;
                                        character[q].bodypart_coords[3].rz=1.5f;
                                        character[q].bodypart_coords[8].rx=0.4f;
                                        character[q].bodypart_coords[3].rx=-0.4f;
                                        //doesnt go too close
                                        if(character[q].distance<200) character[q].speed=0.0f;
                                        if(character[q].distance>800) character[q].speed=0.2f;

                                }

                                if(character[q].menoajastin<0)
                                {
                                        character[q].menoajastin=character[q].menoajastin+2000;
                                        character[q].walk_dir=1;

                                        if(character[q].distance<1000){
                                                if(randInt(0,2)==0)
                                                        character[q].walk_dir=-1;
                                        }
                                }
                                if(character[q].distance<200){
                                        character[q].menoajastin=2000;
                                        character[q].walk_dir=-1;
                                }

                                if(character[q].walk_dir==1)
                                        character[q].speed=0.2f;
                                if(character[q].walk_dir==-1)
                                        character[q].speed=-0.2f;

                                //character shoots
                                if(character[q].gun_timer<0)character[q].gun_timer=character[q].gun_timer+elapsed*gamespeed;
                                //if((character[q].distance<1000)|(randInt(0,(int)(elapsed*gamespeed*300))==0)){
                                if(randInt(0,(int)(elapsed*gamespeed*character[q].distance*character[q].distance*ase[character[q].weapon_idx].rate_of_fire*0.02f*0.000001f+1))<=1){
                                        if(character[q].dying!=true)
                                                if(character[q].weapon_idx!=-1){
                                                        while(character[q].gun_timer>=0){
                                                                character[q].gun_timer=character[q].gun_timer-ase[character[q].weapon_idx].rate_of_fire;
                                                                shoot(-1,q,-1,-1,moped,character[q].weapon_idx,character[q].x+cos*33,92*character[q].height,character[q].z+sin*33,-character[q].direction,randDouble(-0.03f,0.03f),randDouble(-0.03f,0.03f));
                                                                //shoot(q,2,-1,moped,character[q].weapon_idx,character[q].x+cos*33,85,character[q].z+sin*33,-character[q].direction,0,0); //shoot
                                                        }
                                                }
                                }
                        }



                        character[q].sektorix=(int)character[q].x/8000;
                        character[q].sektoriz=(int)character[q].z/8000;
                        character[q].jaosx=(int)character[q].x/800;
                        character[q].jaosz=(int)character[q].z/800;


                        //move forward
                        if((character[q].speed!=0))//||(character[q].kulku==-1))
                        {

                                character[q].bodypart_coords[9].rz=(character[q].rx*1.2f+0.24f)*character[q].speed*10;//lift upper leg (rigth)
                                character[q].bodypart_coords[5].rz=(character[q].lx*1.2f+0.24f)*character[q].speed*10;//lift upper leg (left)
                                character[q].bodypart_coords[10].rz=(character[q].rx*-0.2f-0.15f)*character[q].speed*10;//lift lower leg (rigth)
                                character[q].bodypart_coords[6].rz=(character[q].lx*-0.2f-0.15f)*character[q].speed*10;//lift lower leg (left)




                                //does it collide with walls
                                mapx=character[q].sektorix;
                                mapz=character[q].sektoriz;
                                a=maps[mapz][mapx];
                                wallhits=0;
                                for (b=0; b<wallgroup[0].routes[a].route_count; b++){
					for (c=0; c<wallgroup[0].routes[a].route[b].line_count; c++){
						if(linecollidesline(&osuma,&osumax,&osumaz,character[q].x+cos*100*character[q].walk_dir-mapx*8000,character[q].z+sin*100*character[q].walk_dir-mapz*8000,character[q].x+cos*100*character[q].walk_dir+8000-mapx*8000,character[q].z+sin*100*character[q].walk_dir-mapz*8000,	wallgroup[0].routes[a].route[b].point[c].x1,wallgroup[0].routes[a].route[b].point[c].z1,wallgroup[0].routes[a].route[b].point[c].x2,wallgroup[0].routes[a].route[b].point[c].z2))
							wallhits=wallhits+1;
					}
                                }
                                character[q].osuma[0]=false;
                                if((float)wallhits/2*1000!=((int)(wallhits/2))*1000){
                                        character[q].rx=0;
                                        character[q].lx=0;
                                        character[q].bodypart_coords[9].rz=0;
                                        character[q].bodypart_coords[5].rz=0;
                                        character[q].bodypart_coords[10].rz=0;
                                        character[q].bodypart_coords[6].rz=0;
                                        character[q].speed=0;
                                        character[q].x=character[q].x2;
                                        character[q].z=character[q].z2;
                                        character[q].osuma[0]=true;
                                }



                                //legs are swingin
                                if(character[q].speed!=0){
					if (character[q].leg){
                                                character[q].lx=character[q].lx-MOTION_SPEED*0.015f*elapsed*gamespeed;
                                                if (character[q].lx<-0.6f)
                                                {character[q].leg=false;
                                                        /*q=randInt(0,3);
                                                          if(q==1)svolume(voices[14+q],(int)-distance ,SOUNDS_ON);
                                                          else svolume(voices[14+q],0 ,SOUNDS_ON);
                                                          SndObjPlay(voices[14+q], 0, SOUNDS_ON);*/
                                                }
                                                if (character[q].rx<= 0.20f)	character[q].rx=character[q].rx+MOTION_SPEED*0.015f*elapsed*gamespeed;
					}

					else{
                                                character[q].rx=character[q].rx-MOTION_SPEED*0.015f*elapsed*gamespeed;
                                                if (character[q].rx<-0.6f)
                                                {character[q].leg=true;
                                                        /*q=randInt(0,3);
                                                          if(q==1)svolume(voices[14+q],(int)-distance ,SOUNDS_ON);
                                                          else svolume(voices[14+q],0 ,SOUNDS_ON);
                                                          SndObjPlay(voices[14+q], 0, SOUNDS_ON);*/
                                                }
                                                if (character[q].lx<= 0.20f)	character[q].lx=character[q].lx+MOTION_SPEED*0.015f*elapsed*gamespeed;
					}
                                }

                                /*if (distance<100) character[q].kulku=-1;//is not allowed to go too close

                                  character[q].ux=character[q].ux+(float)cos(character[q].kulma)*elapsed*gamespeed*UKON_SPEED*character[q].kulku;
                                  character[q].uz=character[q].uz+(float)sin(character[q].kulma)*elapsed*gamespeed*UKON_SPEED*character[q].kulku;
                                */

                                character[q].x=character[q].x+cos*character[q].speed*elapsed*gamespeed;
                                character[q].z=character[q].z+sin*character[q].speed*elapsed*gamespeed;
                        }
                        if(character[q].speed==0)
                        {


                                BOOL eteen=false;
                                if(character[q].leg) if (character[q].lx< 0.10f)	{character[q].lx=character[q].lx+MOTION_SPEED*0.02f*elapsed*gamespeed;eteen=true;}
                                if(!character[q].leg) if (character[q].rx< 0.10f)	{character[q].rx=character[q].rx+MOTION_SPEED*0.02f*elapsed*gamespeed;eteen=true;}

                                //deciding new direction
                                if((character[q].tactics!=0)&&(!character[q].visible)){
                                        character[q].direction=randDouble(-pi,pi);
                                        //does it collide with walls
                                        cos=cosf(character[q].direction);
                                        sin=sinf(character[q].direction);
                                        mapx=character[q].sektorix;
                                        mapz=character[q].sektoriz;
                                        a=maps[mapz][mapx];
                                        wallhits=0;
                                        for (b=0; b<wallgroup[0].routes[a].route_count; b++){
                                                for (c=0; c<wallgroup[0].routes[a].route[b].line_count; c++){
                                                        if(linecollidesline(&osuma,&osumax,&osumaz,character[q].x+cos*100-mapx*8000,character[q].z+sin*100-mapz*8000,character[q].x+cos*100+8000-mapx*8000,character[q].z+sin*100-mapz*8000,	wallgroup[0].routes[a].route[b].point[c].x1,wallgroup[0].routes[a].route[b].point[c].z1,wallgroup[0].routes[a].route[b].point[c].x2,wallgroup[0].routes[a].route[b].point[c].z2))
                                                                wallhits=wallhits+1;
                                                }
                                        }
                                        if((float)wallhits/2*1000==((int)(wallhits/2))*1000){
                                                character[q].speed=randDouble(0.05f,0.1f);
                                        }
                                }
                                /*
                                  if (eteen)
                                  {
                                  character[q].ux=character[q].ux+(float)cos(character[q].kulma)*elapsed*gamespeed*UKON_SPEED*character[q].edkulku;
                                  character[q].uz=character[q].uz+(float)sin(character[q].kulma)*elapsed*gamespeed*UKON_SPEED*character[q].edkulku;
                                  }
                                */
                        }

                }

		osumia=0;
		//if can get out of the wall
		for (a=0; a<100; a++){
			if(character[q].osuma[a])
                                osumia=osumia+1;
		}
		if((osumia>40)&&(character[q].visible==false)){
                        for (a=0; a<100; a++){
                                character[q].osuma[a]=false;
                        }

                        laskekoordinaatit(&character[q].x,&character[q].z);
		}




	}

}

void rendercharacters(void){
	int q,a,d;




	//rendering humans -characters (character)

	for (q=0; q<characters; q++)
	{
		if(character[q].inactive)continue;
		radiuscharacter[q]=50.01f;
		center_pointcharacter[q].x=character[q].x;
		center_pointcharacter[q].y=50;
		center_pointcharacter[q].z=character[q].z;
	}


	matrices->LoadIdentity();
	m_pDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, *matrices->GetTop());
	m_pDevice->ComputeSphereVisibility(center_pointcharacter,radiuscharacter,characters,0,visiblecharacter);//remember SetTransform



	int pictureaja;

	for (a=0; a<characters; a++)
	{
		if(character[a].inactive)continue;
                character[a].visible=true;
		if((visiblecharacter[a] &D3DSTATUS_CLIPINTERSECTIONALL   ) ){character[a].visible=false; continue;}


		if(character[a].distance>8000)continue;//no point to render if too far away

		//if(character[a].distance>2000)
		if(character[a].distance>2000)
                        pictureaja=4;
		else pictureaja=character[a].picture;
		if(character[a].dying)pictureaja=5;


		//from farther away all characters look ugly
		if(!mapmode){
			if(character[a].distance>3100)continue;
			pictureaja=4;
		}

		//selecting textures
		switch (character[a].picture)
                {
                case 3:{
                        d=0;
                        break;
                }
                        /*case 5:{
                          d=1;
                          break;
                          }*/
                case 7:{
                        d=2;
                        break;
                }
                case 8:{
                        d=3;
                        break;
                }
                case 10:{
                        d=4;
                        break;
                }
                }
		if(pictureaja==5) d=1;

/*
  charactertexture[d].bodypart[0]=10;//torso
  charactertexture[d].bodypart[1]=11;//legs
  charactertexture[d].bodypart[2]=12;//arm
  charactertexture[d].bodypart[3]=14;//face
*/
		//5;left upper leg
		//6;left lower leg
		//9;right upper leg
		//10;right lower leg




		if(!character[a].dying){
			m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,TRUE);
			m_pDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE    );
			m_pDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_SRCALPHA    );


			//render mission mark
			if(moped[0].mission.status!=0)
                                if(moped[0].nearestcharacter==a)
                                        if(character[moped[0].nearestcharacter].movement_type==0)
                                                //if(!character[moped[0].nearestcharacter].dying)
                                                if(fabs(moped[0].speed)<0.7f){
                                                        matrices->LoadIdentity();
                                                        matrices->TranslateLocal(character[a].x,1,character[a].z);
                                                        matrices->RotateYawPitchRollLocal(0,0,pi/2);
                                                        drawfast(&mallit[2].malli[6]);
                                                }



			//render balls if viewed from above
			if(!mapmode){
				matrices->LoadIdentity();
				matrices->TranslateLocal(character[a].x,1,character[a].z);
				matrices->RotateYawPitchRollLocal(0,0,pi/2);
				if(character[a].movement_type==0)drawfast(&mallit[2].malli[13]);
				if(character[a].movement_type==1)drawfast(&mallit[2].malli[11]);
				if(character[a].movement_type==2)drawfast(&mallit[2].malli[14]);
			}
			m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,FALSE);

		}

		matrices->LoadIdentity();
		matrices->TranslateLocal(character[a].x,57*character[a].height+(float)fabs(character[a].rx)*2*character[a].speed*18,character[a].z);
		matrices->RotateYawPitchRollLocal(-character[a].direction,0,0);
		matrices->ScaleLocal(character[a].height,character[a].height,character[a].height);


		matrices->Push();q=0;//ass
		matrices->TranslateLocal(character[a].bodypart_coords[q].x,character[a].bodypart_coords[q].y,character[a].bodypart_coords[q].z);
		matrices->RotateYawPitchRollLocal(character[a].bodypart_coords[q].rx,character[a].bodypart_coords[q].ry,character[a].bodypart_coords[q].rz);
		mallit[pictureaja].malli[q].sisus[0].texture2=charactertexture[d].bodypart[1];
		drawfast(&mallit[pictureaja].malli[q]);
		matrices->Pop();

		matrices->Push();q=2;//head
		matrices->TranslateLocal(character[a].bodypart_coords[q].x,character[a].bodypart_coords[q].y,character[a].bodypart_coords[q].z);
		matrices->RotateYawPitchRollLocal(character[a].bodypart_coords[q].rx,character[a].bodypart_coords[q].ry,character[a].bodypart_coords[q].rz);
		mallit[pictureaja].malli[q].sisus[0].texture2=charactertexture[d].bodypart[3];
		drawfast(&mallit[pictureaja].malli[q]);
		matrices->Pop();

		matrices->Push();q=1;//torso
		matrices->TranslateLocal(character[a].bodypart_coords[q].x,character[a].bodypart_coords[q].y,character[a].bodypart_coords[q].z);
		matrices->RotateYawPitchRollLocal(character[a].bodypart_coords[q].rx,character[a].bodypart_coords[q].ry,character[a].bodypart_coords[q].rz);
		mallit[pictureaja].malli[q].sisus[0].texture2=charactertexture[d].bodypart[0];
		drawfast(&mallit[pictureaja].malli[q]);

		matrices->Push();q=3;//left upper arm
		matrices->TranslateLocal(character[a].bodypart_coords[q].x,character[a].bodypart_coords[q].y,character[a].bodypart_coords[q].z);
		matrices->RotateYawPitchRollLocal(character[a].bodypart_coords[q].rx,character[a].bodypart_coords[q].ry,character[a].bodypart_coords[q].rz);
		mallit[pictureaja].malli[q].sisus[0].texture2=charactertexture[d].bodypart[2];
		drawfast(&mallit[pictureaja].malli[q]);

		matrices->Push();q=4;//left lower arm
		matrices->TranslateLocal(character[a].bodypart_coords[q].x,character[a].bodypart_coords[q].y,character[a].bodypart_coords[q].z);
		matrices->RotateYawPitchRollLocal(character[a].bodypart_coords[q].rx,character[a].bodypart_coords[q].ry,character[a].bodypart_coords[q].rz);
		mallit[pictureaja].malli[q].sisus[0].texture2=charactertexture[d].bodypart[2];
		drawfast(&mallit[pictureaja].malli[q]);

		matrices->Pop();
		matrices->Pop();
		matrices->Pop();

		matrices->Push();q=8;//right upper arm
		matrices->TranslateLocal(character[a].bodypart_coords[q].x,character[a].bodypart_coords[q].y,character[a].bodypart_coords[q].z);
		matrices->RotateYawPitchRollLocal(character[a].bodypart_coords[q].rx,character[a].bodypart_coords[q].ry,character[a].bodypart_coords[q].rz);
		mallit[pictureaja].malli[q].sisus[0].texture2=charactertexture[d].bodypart[2];
		drawfast(&mallit[pictureaja].malli[q]);

		matrices->Push();q=7;//right lower arm
		matrices->TranslateLocal(character[a].bodypart_coords[q].x,character[a].bodypart_coords[q].y,character[a].bodypart_coords[q].z);
		matrices->RotateYawPitchRollLocal(character[a].bodypart_coords[q].rx,character[a].bodypart_coords[q].ry,character[a].bodypart_coords[q].rz);
		mallit[pictureaja].malli[q].sisus[0].texture2=charactertexture[d].bodypart[2];
		drawfast(&mallit[pictureaja].malli[q]);


		matrices->Pop();
		matrices->Pop();


		//attackers have a gun
		if(!character[a].dying)
                        if(character[a].tactics==0){
                                matrices->Push();
                                matrices->TranslateLocal(30,30,0);
                                //matrices->RotateYawPitchRollLocal(character[a].bodypart_coords[q].rx,character[a].bodypart_coords[q].ry,character[a].bodypart_coords[q].rz);
                                drawfast(&mallit[2].malli[12]);
                                matrices->Pop();
                        }


		matrices->Push();q=5;//left upper leg
		matrices->TranslateLocal(character[a].bodypart_coords[q].x,character[a].bodypart_coords[q].y,character[a].bodypart_coords[q].z);
		matrices->RotateYawPitchRollLocal(character[a].bodypart_coords[q].rx,character[a].bodypart_coords[q].ry,character[a].bodypart_coords[q].rz);
		mallit[pictureaja].malli[q].sisus[0].texture2=charactertexture[d].bodypart[1];
		drawfast(&mallit[pictureaja].malli[q]);

		matrices->Push();q=6;//left lower leg
		matrices->TranslateLocal(character[a].bodypart_coords[q].x,character[a].bodypart_coords[q].y,character[a].bodypart_coords[q].z);
		matrices->RotateYawPitchRollLocal(character[a].bodypart_coords[q].rx,character[a].bodypart_coords[q].ry,character[a].bodypart_coords[q].rz);
		mallit[pictureaja].malli[q].sisus[0].texture2=charactertexture[d].bodypart[1];
		drawfast(&mallit[pictureaja].malli[q]);
		matrices->Pop();
		matrices->Pop();

		matrices->Push();q=9;//rigth upper leg
		matrices->TranslateLocal(character[a].bodypart_coords[q].x,character[a].bodypart_coords[q].y,character[a].bodypart_coords[q].z);
		matrices->RotateYawPitchRollLocal(character[a].bodypart_coords[q].rx,character[a].bodypart_coords[q].ry,character[a].bodypart_coords[q].rz);
		mallit[pictureaja].malli[q].sisus[0].texture2=charactertexture[d].bodypart[1];
		drawfast(&mallit[pictureaja].malli[q]);


		matrices->Push();q=10;//right lower leg
		matrices->TranslateLocal(character[a].bodypart_coords[q].x,character[a].bodypart_coords[q].y,character[a].bodypart_coords[q].z);
		matrices->RotateYawPitchRollLocal(character[a].bodypart_coords[q].rx,character[a].bodypart_coords[q].ry,character[a].bodypart_coords[q].rz);
		mallit[pictureaja].malli[q].sisus[0].texture2=charactertexture[d].bodypart[1];
		drawfast(&mallit[pictureaja].malli[q]);
		matrices->Pop();
		matrices->Pop();

	}
}

//font means after ammount of letters text is cut to lines
//void rendertext(INT x, INT y, INT fontti,CHAR teksti[100],LPDIRECTDRAWSURFACE7 pinta,LPDIRECTDRAWSURFACE7 font1)
void rendertext(INT x, INT y, INT fontti, const char teksti[100]) //write
{
	//RECT loota; //boxxy
	INT nume;
	int xplus=0;
	int yplus=0;
	float height,leveys;
	float u1,u2,v1,v2;
	int xk,yk;
	bool iso;
	BOOL lightenabled[2];
	//for (int i=0; i<4; i++)
        m_pDevice->SetMaterial( &mat[47] );
        matrices->LoadIdentity();
        m_pDevice->GetLightEnable(0,  &lightenabled[0]);
        m_pDevice->GetLightEnable(1,  &lightenabled[1]);
        m_pDevice->LightEnable(0, FALSE);
        m_pDevice->LightEnable(1, FALSE);
        m_pDevice->SetRenderState( D3DRENDERSTATE_AMBIENT, 0xFFFFFFFF);
        m_pDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, *matrices->GetTop());
        m_pDevice->SetRenderState( D3DRENDERSTATE_ZBIAS, 0);
        m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,TRUE);
        /*m_pDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE    );
          m_pDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE    );	*/
        m_pDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, FALSE);
        m_Projection = ProjectionMatrix(25.0f, maxvisible, (float)(80*pi/180)); // 60 visionfield
        m_pDevice->SetTransform(D3DTRANSFORMSTATE_PROJECTION, &m_Projection);


	for (int i=0; i<abs((int)strlen(teksti)); i++)
                //for (int i=0; i<4; i++)
	{


                nume=0;
//		teksti[i]=*CharLower(&teksti[i]);
                //kirj:=LowerCase(kirj);
                //if kirj= #32 then exit;
                iso=false;
		switch (teksti[i])
		{
                case ' ':{nume=-1;goto te;}
                case 'a':{nume=0;goto fa;}
                case 'b':{nume=1;goto fa;}
                case 'c':{nume=2;goto fa;}
                case 'd':{nume=3;goto fa;}
                case 'e':{nume=4;goto fa;}
                case 'f':{nume=5;goto fa;}
                case 'g':{nume=6;goto fa;}
                case 'h':{nume=7;goto fa;}
                case 'i':{nume=8;goto fa;}
                case 'j':{nume=9;goto fa;}
                case 'k':{nume=10;goto fa;}
                case 'l':{nume=11;goto fa;}
                case 'm':{nume=12;goto fa;}
                case 'n':{nume=13;goto fa;}
                case 'o':{nume=14;goto fa;}
                case 'p':{nume=15;goto fa;}
                case 'q':{nume=16;goto fa;}
                case 'r':{nume=17;goto fa;}
                case 's':{nume=18;goto fa;}
                case 't':{nume=19;goto fa;}
                case 'u':{nume=20;goto fa;}
                case 'v':{nume=21;goto fa;}
                case 'w':{nume=22;goto fa;}
                case 'x':{nume=23;goto fa;}
                case 'y':{nume=24;goto fa;}
                case 'z':{nume=25;goto fa;}
                case 'å':{nume=26;goto fa;}
                case 'ä':{nume=27;goto fa;}
                case 'ö':{nume=28;goto fa;}
                case '1':{nume=29;goto fa;}
                case '2':{nume=30;goto fa;}
                case '3':{nume=31;goto fa;}
                case '4':{nume=32;goto fa;}
                case '5':{nume=33;goto fa;}
                case '6':{nume=34;goto fa;}
                case '7':{nume=35;goto fa;}
                case '8':{nume=36;goto fa;}
                case '9':{nume=37;goto fa;}
                case '-':{nume=38;goto fa;}
                case '0':{nume=39;goto fa;}
                case '.':{nume=40;goto fa;}
                case '/':{nume=41;goto fa;}
                case ':':{nume=42;goto fa;}
                case '´':{nume=43;goto fa;}
                case '?':{nume=44;goto fa;}
                case ',':{nume=45;goto fa;}
                case '!':{nume=46;goto fa;}

                case 'A':{nume=0;goto fr;}
                case 'B':{nume=1;goto fr;}
                case 'C':{nume=2;goto fr;}
                case 'D':{nume=3;goto fr;}
                case 'E':{nume=4;goto fr;}
                case 'F':{nume=5;goto fr;}
                case 'G':{nume=6;goto fr;}
                case 'H':{nume=7;goto fr;}
                case 'I':{nume=8;goto fr;}
                case 'J':{nume=9;goto fr;}
                case 'K':{nume=10;goto fr;}
                case 'L':{nume=11;goto fr;}
                case 'M':{nume=12;goto fr;}
                case 'N':{nume=13;goto fr;}
                case 'O':{nume=14;goto fr;}
                case 'P':{nume=15;goto fr;}
                case 'Q':{nume=16;goto fr;}
                case 'R':{nume=17;goto fr;}
                case 'S':{nume=18;goto fr;}
                case 'T':{nume=19;goto fr;}
                case 'U':{nume=20;goto fr;}
                case 'V':{nume=21;goto fr;}
                case 'W':{nume=22;goto fr;}
                case 'X':{nume=23;goto fr;}
                case 'Y':{nume=24;goto fr;}
                case 'Z':{nume=25;goto fr;}
                case 'Å':{nume=26;goto fr;}
                case 'Ä':{nume=27;goto fr;}
                case 'Ö':{nume=28;goto fr;}
		}

          fr:
		iso=true;
          fa:

		//if(nume>-1){//if there is no space
                {

                        pvertex vertex[6];
                        height=70;
                        leveys=60;
                        yk=(int)(nume/8);
                        xk=nume-yk*8;
                        u1=(xk*16)/128.0f;
                        u2=(xk*16+16)/128.0f;
                        v1=(yk*18)/128.0f;
                        v2=(yk*18+18)/128.0f;

			vertex[0].position.x=0;
			vertex[0].position.y=0;
			vertex[0].position.z=0;
			vertex[0].u=u2;
			vertex[0].v=v2;

			vertex[1].position.x=leveys;
			vertex[1].position.y=height;
			vertex[1].position.z=0;
			vertex[1].u=u1;
			vertex[1].v=v1;

			vertex[2].position.x=0;
			vertex[2].position.y=height;
			vertex[2].position.z=0;
			vertex[2].u=u2;
			vertex[2].v=v1;

			vertex[3].position.x=0;
			vertex[3].position.y=0;
			vertex[3].position.z=0;
			vertex[3].u=u2;
			vertex[3].v=v2;

			vertex[4].position.x=leveys;
			vertex[4].position.y=0;
			vertex[4].position.z=0;
			vertex[4].u=u1;
			vertex[4].v=v2;

			vertex[5].position.x=leveys;
			vertex[5].position.y=height;
			vertex[5].position.z=0;
			vertex[5].u=u1;
			vertex[5].v=v1;



			if(iso)m_pDevice->SetTexture( 0, background[47] );
			else m_pDevice->SetTexture( 0, background[64] );

			//m_pDevice->SetTexture( 0, background[65] );

			//set camera to its place
			kamerax1=(x+xplus*(12.5f)-1024/2)*(3.28f)+42;
			kameray1=(y+yplus*(15.17f)-768/2)*(3.28f)+46;
			kameraz1=2000;
			kamerax2=kamerax1+3.7f;
			kameray2=kameray1+3.7f;
			kameraz2=0;
			m_View = ViewMatrix(D3DVECTOR(kamerax1,kameray1,kameraz1), D3DVECTOR(kamerax2,kameray2,kameraz2), D3DVECTOR(0,1,0), 0);
			m_pDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &m_View);


			m_pDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ZERO    );
			m_pDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND,	D3DBLEND_INVSRCCOLOR);
			m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST  ,
                                        D3DFVF_XYZ |D3DFVF_TEX1|D3DFVF_TEXCOORDSIZE2(0) ,vertex,6,NULL);

			//set camera to its place
			kamerax1=(x+xplus*(12.5f)-1024/2)*(3.28f)+42;
			kameray1=(y+yplus*(15.17f)-768/2)*(3.28f)+46;
			kameraz1=2000;
			kamerax2=kamerax1;
			kameray2=kameray1;
			kameraz2=0;
			m_View = ViewMatrix(D3DVECTOR(kamerax1,kameray1,kameraz1), D3DVECTOR(kamerax2,kameray2,kameraz2), D3DVECTOR(0,1,0), 0);
			m_pDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &m_View);


			m_pDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE    );
			m_pDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE    );
			m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST  ,
                                        D3DFVF_XYZ |D3DFVF_TEX1|D3DFVF_TEXCOORDSIZE2(0) ,vertex,6,NULL);


/*
  loota.left  =nume*13+1;
  loota.right =loota.left+12;
  loota.top   =1;
  loota.bottom=14;

  int textheight=13;
  pinta->BltFast(x+xplus*11, y+yplus*textheight,
  font1,
  &loota,
  DDBLTFAST_SRCCOLORKEY );
*/


		}
          te:
		xplus=xplus+1;

		//cutting it to lines
		if(fontti>0)
                        if((xplus>fontti)&&(nume==-1)){xplus=0;yplus=yplus+1;}



        }
        m_pDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE);
        m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,FALSE);
        m_pDevice->LightEnable(0, lightenabled[0]);
        m_pDevice->LightEnable(1, lightenabled[1]);

}


void render_game(void){//just renders some moped driving.

	int a,b,q,c,d;
	float kerroin;
	char row[200];
	char temprow[200];
	//gamephase2 		//gamephase2
	//0=normaali peli 	//normal game
	//1=loppudemo 		//end demo
	//2=paussi 		// pause
	//3=alkudemo 		//beginning demo
	//4=alkudemo 		//beginning demo
	//5=dyingma 		//death
	ase[2]._type=4;
	ase[3]._type=4;
	ase[4]._type=4;


	if(quake>7)quake=7;
	if(quake>0)quake=quake-0.03f*elapsed*gamespeed;//earthquake

	if(gamephase2==0){
		calculateCollisions();//does mopeds collide with anything
		laskemoped();//mopeds are rollin //calculatemopeds
		for (d=0; d<num_mopeds; d++){
			if(moped[d].inactive)continue;
			aja(&moped[d]);
		}
	}


	//engine is roaring
	int hertsi=(int)(1.66f*10000*(fabs(moped->speed)+2.5f))+randInt(-3000,3000);
	if(hertsi<100)hertsi=100;
	if(hertsi>100000)hertsi=100000;
	if(options[1]&&SOUNDS_LOADED)
		SndObjSetFrequency(voices[1],hertsi);
	//SndObjPlay(voices[1], DSBPLAY_LOOPING,options[1]&&SOUNDS_LOADED);


	//normal vision angle
	if(mapmode){
		//background is grey ; it is not needed if sky is renderet separetly
		m_pDevice->Clear( 0, NULL, D3DCLEAR_TARGET, 0x004C4C4C, 0, 0 );
		kerroin=1.0f;
                float kameraspeed;
                float fSinXY,fSinXZ,fCosXZ,ero;
                float xcam=moped[0].x1;
                float zcam=moped[0].z1;
                kameraspeed=0.006f;
                if(mapmode2!=mapmode)kameraspeed=1/elapsed;
                dx2=moped[0].direction*180/pi-180;
                fSinXY = sinf((dy/180*pi));
                fSinXZ = sinf(((dx+dx2)/180*pi));
                fCosXZ = cosf(((dx+dx2)/180*pi));
                ero=camx-(xcam + (fCosXZ - (float)fabs(fSinXY) * fCosXZ) * 200);
                camx = camx-ero*elapsed*kameraspeed;
                ero=camy-(90 + fSinXY * 300);//ero=camy-(character[0].uy + fSinXY * 500);
                camy = camy-ero*elapsed*kameraspeed;
                ero=camz-(zcam + (fSinXZ - (float)fabs(fSinXY) * fSinXZ) * 200);
                camz = camz-ero*elapsed*kameraspeed;

                if(sqrtf(sqr(moped[0].x1-camx)+sqr(moped[0].z1-camz))<250){
                        float kerroin=sqrtf(sqr(250)/(sqr(moped[0].z1-camz)+sqr(moped[0].x1-camx)));
                        camz=(camz-moped[0].z1)*kerroin+moped[0].z1;
                        camx=(camx-moped[0].x1)*kerroin+moped[0].x1;
                        //moped->x2=(moped->x2-moped->x1)*kerroin+moped->x1;

                }

                kamerax1=camx+1;
                kameray1=camy;
                kameraz1=camz+1;

                kamerax2=moped[0].x1;
                kameray2=100;
                kameraz2=moped[0].z1;

                m_View = ViewMatrix(D3DVECTOR(kamerax1,kameray1,kameraz1), D3DVECTOR(kamerax2,kameray2,kameraz2), D3DVECTOR(0,1,0), 0);
                //m_Projection = ProjectionMatrix(25.0f, maxvisible, (float)(80*pi/180)); // 60 vision field
                m_Projection = ProjectionMatrix(25.0f, maxvisible, (float)((80-moped[0].speed*0.4f)*pi/180));
                m_pDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &m_View);
                m_pDevice->SetTransform(D3DTRANSFORMSTATE_PROJECTION, &m_Projection);


//SetupVertexFog(0,200,0x004C4C4C, D3DFOG_LINEAR  , TRUE, 0);//fog
		/*	//sky
			m_pDevice->LightEnable(0, FALSE);
			m_pDevice->SetRenderState(D3DRENDERSTATE_ZENABLE,FALSE);
			matrices->LoadIdentity();
			matrices->TranslateLocal(camx,camy+20,camz);
			m_pDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, *matrices->GetTop());
			//m_View = ViewMatrix(D3DVECTOR(680,0,0), D3DVECTOR(0,0,0), D3DVECTOR(0,1,0), 0);
			//m_pDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &m_View);
			drawfast(&mallit[2].malli[11]);
			m_pDevice->SetRenderState(D3DRENDERSTATE_ZENABLE,TRUE);
			m_pDevice->LightEnable(0, TRUE);
                */
//SetupVertexFog(maxvisible-5000,maxvisible,0x004C4C4C, D3DFOG_LINEAR  , TRUE, 0);//sumu



	}


	//vision from above
	if(!mapmode){
                kerroin=0.45f;
                kamerax1=moped[0].x1+100;
                kameray1=10000;
                kameraz1=moped[0].z1;

                kamerax2=moped[0].x1+cosf(moped[0].direction)*1.5f;
                kameray2=0;
                kameraz2=moped[0].z1+sinf(moped[0].direction)*1.5f;

                m_View = ViewMatrix(D3DVECTOR(kamerax1,kameray1,kameraz1), D3DVECTOR(kamerax2,kameray2,kameraz2), D3DVECTOR(0,1,0), 0);
                m_Projection = ProjectionMatrix(4000, 11000, (float)(30*pi/180)); // 60 vision field
                m_pDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &m_View);
                m_pDevice->SetTransform(D3DTRANSFORMSTATE_PROJECTION, &m_Projection);
	}

	bullet_count=0;
	if(gamephase2==0){
		svolume(voices[1],DSBVOLUME_MAX, options[1]&&SOUNDS_LOADED);
		calculatecharacters();
		calculatebullets();
		calculatesmokes();
		laskemissiot(&moped[0]);
	}



	//is character dead
	if((moped[0].energy<0)&&(gamephase2!=5)){
		gamephase2=5;
		//moped[0].inactive=true;

		SndObjStop(voices[1]);//motor stops
                //smoke to air
                if(ase[1].smoke_filled!=0)
                        for (q=0; q<3; q++){
                                fromsmoke(1.0f,0.001f,true,3000,moped[0].x1,60,moped[0].z1,ase[1].smoke_filled,randDouble(pi,-pi),randDouble(pi,-pi),randDouble(pi,-pi));
                        }
                //explosion
                if(ase[1].explosion_size!=0){
                        quake=3;
                        for (q=0; q<100; q++){
                                shoot(-6667,-1,1,randDouble(100,300),moped,2,moped[0].x1,60,moped[0].z1,randDouble(-pi,pi),randDouble(-pi,pi),randDouble(-pi,pi));
                        }
                        fromsmoke(1.0f,0.01f,true,3000,moped[0].x1,60,moped[0].z1,3,0,0,0);
                        playsound(8,1,moped[0].x1,moped[0].z1);
                }


	}


	//is the character at workshop
	if(maps[moped[0].sektoriz][moped[0].sektorix]==6){

		float mopox=moped[0].x1-moped[0].sektorix*8000;
		float mopoz=moped[0].z1-moped[0].sektoriz*8000;

		moped[0].korjaamolla2=moped[0].korjaamolla;

		//it is at workshop area
		moped[0].korjaamolla=false;
		if((mopox>4834)&(mopox<5065)&(mopoz<6700)&(mopoz>6300))
			moped[0].korjaamolla=true;

		if((moped[0].korjaamolla==true)&(moped[0].korjaamolla2==false)){
			SndObjStop(voices[1]);
			gamephase=2;
			repair_cost=0;
			moped[0].direction=pi/2;
			moped[0].x1=(float)(moped[0].sektorix*8000+4950);
			moped[0].z1=(float)(moped[0].sektoriz*8000+6500);
			moped[0].x2=moped[0].x1+sinf(-moped[0].direction-pi/2)*70;
			moped[0].z2=moped[0].z1+cosf(-moped[0].direction-pi/2)*70;
			moped[0].speed=0.0f;
			moped[0].x3=moped[0].x1;
			moped[0].y3=moped[0].y1;
			moped[0].z3=moped[0].z1;
			moped[0].x4=moped[0].x2;
			moped[0].y4=moped[0].y2;
			moped[0].z4=moped[0].z2;
			moped[0].angle_pitch=0;
			moped[0].etudirection=0;
			for (a=0; a<100; a++)moped[0].osuma[a]=false;
		}
	}



	//headlight
	lights[0].valo.dvPosition.x = moped[0].x1;
	lights[0].valo.dvPosition.y = 100;
	lights[0].valo.dvPosition.z = moped[0].z1;
	lights[0].valo.dvRange = 4000;
	lights[0].valo.dvDirection=D3DVECTOR((float)cosf(moped[0].direction+moped[0].etudirection),(float)sinf(moped[0].angle_pitch),(float)sinf(moped[0].direction+moped[0].etudirection));
	lights[0].valo.dvFalloff=1.0f;
	lights[0].valo.dltType=D3DLIGHT_SPOT;
	lights[0].valo.dvTheta=0.0f;
	lights[0].valo.dvPhi =0.7f;
	lights[0].valo.dvAttenuation2=0.1f*0.00001f;
	m_pDevice->SetLight(0, &lights[0].valo);
	m_pDevice->LightEnable(0, TRUE);

	//light of world
	lights[1].valo.dvPosition.x = kamerax1;
	lights[1].valo.dvPosition.y = 5000;
	lights[1].valo.dvPosition.z = kameraz1;
	lights[1].valo.dvRange = maxvisible-4000;
	lights[1].valo.dcvDiffuse.r = 0.1f;
	lights[1].valo.dcvDiffuse.g = 0.1f;
	lights[1].valo.dcvDiffuse.b = 0.1f;
	lights[1].valo.dcvAmbient.r = 0.0f;
	lights[1].valo.dcvAmbient.g = 0.0f;
	lights[1].valo.dcvAmbient.b = 0.0f;
	lights[1].valo.dcvSpecular.r = 0.0f;
	lights[1].valo.dcvSpecular.g = 0.0f;
	lights[1].valo.dcvSpecular.b = 0.0f;
	lights[1].valo.dvDirection=D3DVECTOR(1.0f);
	lights[1].valo.dvFalloff=1.0f;
	lights[1].valo.dltType=D3DLIGHT_POINT;
	lights[1].valo.dvAttenuation0=0.05f;
	lights[1].valo.dvAttenuation1=0.1f*0.00001f;
	lights[1].valo.dvAttenuation2=0.1f*0.00000001f;
	m_pDevice->SetLight(1, &lights[1].valo);
	m_pDevice->LightEnable(1, TRUE);

        /*	lights[q].valo.dltType = D3DLIGHT_POINT;
                lights[q].valo.dcvDiffuse.r = 1.0f;
                lights[q].valo.dcvDiffuse.g = 1.0f;
                lights[q].valo.dcvDiffuse.b = 1.0f;
                lights[q].valo.dcvAmbient.r = 1.0f;
                lights[q].valo.dcvAmbient.g = 1.0f;
                lights[q].valo.dcvAmbient.b = 1.0f;
                lights[q].valo.dcvSpecular.r = 1.0f;
                lights[q].valo.dcvSpecular.g = 1.0f;
                lights[q].valo.dcvSpecular.b = 1.0f;
                lights[q].valo.dvDirection=1.0f;
                lights[q].valo.dvPosition.x = x;
                lights[q].valo.dvPosition.y = y;
                lights[q].valo.dvPosition.z = z;
                lights[q].valo.dvAttenuation0 = 0.5f;
                lights[q].valo.dvAttenuation1=0.0f;
                lights[q].valo.dvAttenuation2=0.0f;
                lights[q].valo.dvRange = 500;
        */
	//m_pDevice->SetRenderState( D3DRENDERSTATE_AMBIENT, 0xFFFFEEEE);
	m_pDevice->SetRenderState( D3DRENDERSTATE_AMBIENT, 0xFFFFFFFF);
	//m_pDevice->SetRenderState( D3DRENDERSTATE_AMBIENT, 0x00000000);
	m_pDevice->SetRenderState( D3DRENDERSTATE_ZBIAS, 0);//set zbias to 0 because of the bullet holes
	/*
          int e=0;
          int d;
          float lightsx[2000];
          float lightsz[2000];
          for (a=0; a<mapsz; a++){
          for (b=0; b<mapsx; b++){
          for (c=0; c<3; c++){
          for (d=0; d<3; d++){
          if((c==1)&&d==1) continue;
          e=e+1;
          lightsx[e]=a*8000+c*4000;
          lightsz[e]=b*8000+d*4000;
          }
          }
          }
          }

          //lamput
          e=0;
          for (a=0; a<mapsx*mapsz*8; a++){
          e=e+1;
          matrices->LoadIdentity();
          matrices->TranslateLocal(lightsx[e],0,lightsz[e]);

          drawfast(&mallit[2].malli[12]);

          }
	*/


	//maps
	//can you see it ?
	for (a=0; a<mapsz; a++){
		for (b=0; b<mapsx; b++){
			center_pointmap[a*mapsx+b].x=(float)b*8000+4000;
			center_pointmap[a*mapsx+b].y=0;
			center_pointmap[a*mapsx+b].z=(float)a*8000+4000;
			radiusmap[a*mapsx+b]=4000;
		}
	}
	matrices->LoadIdentity();
	m_pDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, *matrices->GetTop());
	m_pDevice->ComputeSphereVisibility(center_pointmap,radiusmap,mapsx*mapsz,0,visiblemap);//remember SetTransform



	//calculate distance between blocks
	float mapdistance[500];
	int maporder[500];
	int maporderx[500];
	int maporderz[500];
	int mapsvisible;
	for (q=0; q<500; q++)
		maporder[q]=499;
	for (a=0; a<mapsz; a++){
		for (b=0; b<mapsx; b++){
			//if(visiblemap[a*mapsx+b] &D3DSTATUS_CLIPINTERSECTIONALL){continue;}
			mapdistance[a*mapsx+b]=sqrtf(sqr(b*8000+4000-moped[0].x1)+sqr(a*8000+4000-moped[0].z1));
		}
	}

	//arrange first nearests
	mapdistance[499]=1000000;
	for (c=0; c<200; c++){
		for (a=0; a<mapsz; a++){
			for (b=0; b<mapsx; b++){
				if(visiblemap[a*mapsx+b] &D3DSTATUS_CLIPINTERSECTIONALL){continue;}
				if(mapdistance[a*mapsx+b]<mapdistance[maporder[c]])
				{
					maporder[c]=a*mapsx+b;
					maporderx[c]=b;
					maporderz[c]=a;
				}
			}
		}
		mapdistance[maporder[c]]=1000000;
		if(maporder[c]==499) {mapsvisible=c;break;}
	}

	//render nearest 6
	q=16;
	if(mapsvisible<q)q=mapsvisible;
	for (c=0; c<q; c++){
                //if(visiblemap[a*mapsx+b] &D3DSTATUS_CLIPINTERSECTIONALL){continue;}

                matrices->LoadIdentity();
                matrices->TranslateLocal((float)maporderx[c]*8000,0,(float)maporderz[c]*8000);
                matrices->ScaleLocal(1,kerroin,1);
                drawfast(&mallit[1].malli[maps[maporderz[c]][maporderx[c]]]);//map

                if((abs(moped[0].sektorix-maporderx[c])<2)&(abs(moped[0].sektoriz-maporderz[c])<2))
                        drawfast(&mallit[0].malli[5]);//base
                else drawfast(&mallit[0].malli[4]);//base

	}
/*
//render bases
for (a=1; a<mapsz-1; a++){
for (b=1; b<mapsx-1; b++){

if(visiblemap[a*mapsx+b] &D3DSTATUS_CLIPINTERSECTIONALL){continue;}

matrices->LoadIdentity();
matrices->TranslateLocal((float)b*8000,0,(float)a*8000);
if((abs(moped[0].sektorix-b)<2)&(abs(moped[0].sektoriz-a)<2))
drawfast(&mallit[0].malli[5]);//pohja
else drawfast(&mallit[0].malli[4]);//pohja
}
}
*/



	//bullets
	bullet_count=0;
	for (a=10; a<MAX_BULLETS; a++){//first 10 are for driving over people
		if(bullet[a].remove)continue;
		bullet_count=bullet_count+1;
		matrices->LoadIdentity();
		bullet_trace[bullet_count*2].position.x=bullet[a].place.x;
		bullet_trace[bullet_count*2].position.y=bullet[a].place.y;
		bullet_trace[bullet_count*2].position.z=bullet[a].place.z;

		bullet_trace[bullet_count*2+1].position.x=bullet[a].place_old.x;
		bullet_trace[bullet_count*2+1].position.y=bullet[a].place_old.y;
		bullet_trace[bullet_count*2+1].position.z=bullet[a].place_old.z;

		switch (ase[bullet[a].from_gun].bullet_picture)
		{


                case 0:{
			bullet_trace[bullet_count*2].u=0;
			bullet_trace[bullet_count*2].v=0.16f;
			bullet_trace[bullet_count*2+1].u=1;
			bullet_trace[bullet_count*2+1].v=0.16f;
			break;
                }

                case 1:{
			bullet_trace[bullet_count*2].u=0;
			bullet_trace[bullet_count*2].v=0.33f;
			bullet_trace[bullet_count*2+1].u=1;
			bullet_trace[bullet_count*2+1].v=0.33f;
			break;
                }

                case 2:{
			bullet_trace[bullet_count*2].u=0;
			bullet_trace[bullet_count*2].v=0.55f;
			bullet_trace[bullet_count*2+1].u=1;
			bullet_trace[bullet_count*2+1].v=0.55f;
			break;
                }

                case 3:{
			bullet_trace[bullet_count*2].u=0;
			bullet_trace[bullet_count*2].v=0.80f;
			bullet_trace[bullet_count*2+1].u=1;
			bullet_trace[bullet_count*2+1].v=0.80f;
			break;
                }
		}



	}

	m_pDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND,
                        D3DBLEND_ONE );
	m_pDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND,
                        D3DBLEND_ONE );
	m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,TRUE);
        m_pDevice->SetMaterial( &mat[30] );
        m_pDevice->SetTexture( 0, background[30] );
        m_pDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, *matrices->GetTop());
        m_pDevice->DrawPrimitive(D3DPT_LINELIST  ,
			D3DFVF_XYZ |D3DFVF_TEX1|D3DFVF_TEXCOORDSIZE2(0) ,bullet_trace,bullet_count*2,NULL);
        m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,FALSE);



	//are mopeds visible
	for (a=0; a<num_mopeds; a++){
                if(moped[a].inactive)continue;
                center_pointmap[a].x=moped[a].x1;
                center_pointmap[a].y=0;
                center_pointmap[a].z=moped[a].z1;
                radiusmap[a]=800;
        }
	matrices->LoadIdentity();
	m_pDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, *matrices->GetTop());
	m_pDevice->ComputeSphereVisibility(center_pointmap,radiusmap,num_mopeds,0,visiblemap);//remember SetTransform




	int e, mopopicture;


	//chasis
	if(gamephase2!=5)//if player is not dead
                for (d=0; d<num_mopeds; d++){
                        if(moped[d].inactive)continue;
                        moped[d].visible=true;
                        if(visiblemap[d] &D3DSTATUS_CLIPINTERSECTIONALL){moped[d].visible=false;continue;}

                        //if too far away othe mopeds are ugly
                        moped[d].distance=sqrtf(sqr(moped[d].x1-moped[0].x1)+sqr(moped[d].z1-moped[0].z1));

                        if(moped[d].mopona==0){
                                mopopicture=0;
                                if (moped[d].distance>2000) mopopicture=9;
                                if(!mapmode) mopopicture=9;
                        }
                        if(moped[d].mopona==1){
                                mopopicture=6;
                        }


                        if(mopopicture==0){
                                matrices->LoadIdentity();

                                matrices->TranslateLocal(moped[d].x2,moped[d].y2,moped[d].z2);
                                matrices->RotateYawPitchRollLocal(-moped[d].direction,moped[d].angle_roll,moped[d].angle_pitch);
                                drawfast(&mallit[mopopicture].malli[0]);
                        }
                        if(mopopicture==6){
                                matrices->LoadIdentity();
                                matrices->TranslateLocal(moped[d].x2,moped[d].y2+1.5f,moped[d].z2);
                                matrices->RotateYawPitchRollLocal(-moped[d].direction,moped[d].angle_roll,moped[d].angle_pitch);
                                drawfast(&mallit[mopopicture].malli[0]);
                        }
                        if(mopopicture==9){
                                matrices->LoadIdentity();
                                matrices->TranslateLocal(moped[d].x2,moped[d].y2+1.5f,moped[d].z2);
                                matrices->RotateYawPitchRollLocal(-moped[d].direction,moped[d].angle_roll,moped[d].angle_pitch);
                                drawfast(&mallit[mopopicture].malli[0]);
                        }
/*
  charactertexture[d].bodypart[0]=10;//torso
  charactertexture[d].bodypart[1]=11;//legs
  charactertexture[d].bodypart[2]=12;//hand
  charactertexture[d].bodypart[3]=14;//face
*/

                        //passanger
                        if(moped[d].mission._type==1)
                                if(moped[d].mission.status==0){
                                        matrices->Push();
                                        matrices->TranslateLocal(7,57,0);

                                        //select textures
                                        switch (moped[d].mission.asiakas[0].picture)
                                        {
                                        case 3:{
                                                e=0;
                                                break;
                                        }
                                        case 7:{
                                                e=2;
                                                break;
                                        }
                                        case 8:{
                                                e=3;
                                                break;
                                        }
                                        case 10:{
                                                e=4;
                                                break;
                                        }
                                        }

                                        matrices->Push();q=0;//ass
                                        matrices->TranslateLocal(moped[d].mission.asiakas[0].bodypart_coords[q].x,moped[d].mission.asiakas[0].bodypart_coords[q].y,moped[d].mission.asiakas[0].bodypart_coords[q].z);
                                        matrices->RotateYawPitchRollLocal(0,0,0);
                                        mallit[moped[d].mission.asiakas[0].picture].malli[q].sisus[0].texture2=charactertexture[e].bodypart[1];
                                        drawfast(&mallit[moped[d].mission.asiakas[0].picture].malli[q]);
                                        matrices->Pop();

                                        matrices->Push();q=1;//torso
                                        matrices->TranslateLocal(moped[d].mission.asiakas[0].bodypart_coords[q].x,moped[d].mission.asiakas[0].bodypart_coords[q].y,moped[d].mission.asiakas[0].bodypart_coords[q].z);
                                        matrices->RotateYawPitchRollLocal(0,0,-0.14f);
                                        mallit[moped[d].mission.asiakas[0].picture].malli[q].sisus[0].texture2=charactertexture[e].bodypart[0];
                                        drawfast(&mallit[moped[d].mission.asiakas[0].picture].malli[q]);

                                        matrices->Push();q=2;//head
                                        matrices->TranslateLocal(moped[d].mission.asiakas[0].bodypart_coords[q].x,moped[d].mission.asiakas[0].bodypart_coords[q].y,moped[d].mission.asiakas[0].bodypart_coords[q].z);
                                        matrices->RotateYawPitchRollLocal(0,0,0);
                                        mallit[moped[d].mission.asiakas[0].picture].malli[q].sisus[0].texture2=charactertexture[e].bodypart[3];
                                        drawfast(&mallit[moped[d].mission.asiakas[0].picture].malli[q]);
                                        matrices->Pop();

                                        matrices->Push();q=3;//left upper arm
                                        matrices->TranslateLocal(moped[d].mission.asiakas[0].bodypart_coords[q].x,moped[d].mission.asiakas[0].bodypart_coords[q].y,moped[d].mission.asiakas[0].bodypart_coords[q].z);
                                        matrices->RotateYawPitchRollLocal(0,0,pi*0.1f);
                                        mallit[moped[d].mission.asiakas[0].picture].malli[q].sisus[0].texture2=charactertexture[e].bodypart[2];
                                        drawfast(&mallit[moped[d].mission.asiakas[0].picture].malli[q]);

                                        matrices->Push();q=4;//left lower arm
                                        matrices->TranslateLocal(moped[d].mission.asiakas[0].bodypart_coords[q].x,moped[d].mission.asiakas[0].bodypart_coords[q].y,moped[d].mission.asiakas[0].bodypart_coords[q].z);
                                        matrices->RotateYawPitchRollLocal(0,0,pi*0.35f);
                                        mallit[moped[d].mission.asiakas[0].picture].malli[q].sisus[0].texture2=charactertexture[e].bodypart[2];
                                        drawfast(&mallit[moped[d].mission.asiakas[0].picture].malli[q]);

                                        matrices->Pop();
                                        matrices->Pop();

                                        matrices->Push();q=8;//rigth upper arm
                                        matrices->TranslateLocal(moped[d].mission.asiakas[0].bodypart_coords[q].x,moped[d].mission.asiakas[0].bodypart_coords[q].y,moped[d].mission.asiakas[0].bodypart_coords[q].z);
                                        matrices->RotateYawPitchRollLocal(0,0,pi*0.1f);
                                        mallit[moped[d].mission.asiakas[0].picture].malli[q].sisus[0].texture2=charactertexture[e].bodypart[2];
                                        drawfast(&mallit[moped[d].mission.asiakas[0].picture].malli[q]);

                                        matrices->Push();q=7;//rigth lower arm
                                        matrices->TranslateLocal(moped[d].mission.asiakas[0].bodypart_coords[q].x,moped[d].mission.asiakas[0].bodypart_coords[q].y,moped[d].mission.asiakas[0].bodypart_coords[q].z);
                                        matrices->RotateYawPitchRollLocal(0,0,pi*0.35f);
                                        mallit[moped[d].mission.asiakas[0].picture].malli[q].sisus[0].texture2=charactertexture[e].bodypart[2];
                                        drawfast(&mallit[moped[d].mission.asiakas[0].picture].malli[q]);

                                        matrices->Pop();
                                        matrices->Pop();
                                        matrices->Pop();


                                        matrices->Push();q=5;////left upper leg
                                        matrices->TranslateLocal(moped[d].mission.asiakas[0].bodypart_coords[q].x,moped[d].mission.asiakas[0].bodypart_coords[q].y,moped[d].mission.asiakas[0].bodypart_coords[q].z);
                                        matrices->RotateYawPitchRollLocal(0.26f,0,1.45f);
                                        mallit[moped[d].mission.asiakas[0].picture].malli[q].sisus[0].texture2=charactertexture[e].bodypart[1];
                                        drawfast(&mallit[moped[d].mission.asiakas[0].picture].malli[q]);

                                        matrices->Push();q=6;////left lower leg
                                        matrices->TranslateLocal(moped[d].mission.asiakas[0].bodypart_coords[q].x,moped[d].mission.asiakas[0].bodypart_coords[q].y,moped[d].mission.asiakas[0].bodypart_coords[q].z);
                                        matrices->RotateYawPitchRollLocal(0,0,-0.8f);
                                        mallit[moped[d].mission.asiakas[0].picture].malli[q].sisus[0].texture2=charactertexture[e].bodypart[1];
                                        drawfast(&mallit[moped[d].mission.asiakas[0].picture].malli[q]);
                                        matrices->Pop();
                                        matrices->Pop();

                                        matrices->Push();q=9;////rigth upper leg
                                        matrices->TranslateLocal(moped[d].mission.asiakas[0].bodypart_coords[q].x,moped[d].mission.asiakas[0].bodypart_coords[q].y,moped[d].mission.asiakas[0].bodypart_coords[q].z);
                                        matrices->RotateYawPitchRollLocal(-0.26f,0,1.45f);
                                        mallit[moped[d].mission.asiakas[0].picture].malli[q].sisus[0].texture2=charactertexture[e].bodypart[1];
                                        drawfast(&mallit[moped[d].mission.asiakas[0].picture].malli[q]);


                                        matrices->Push();q=10;////rigth lower leg
                                        matrices->TranslateLocal(moped[d].mission.asiakas[0].bodypart_coords[q].x,moped[d].mission.asiakas[0].bodypart_coords[q].y,moped[d].mission.asiakas[0].bodypart_coords[q].z);
                                        matrices->RotateYawPitchRollLocal(0,0,0-0.8f);
                                        mallit[moped[d].mission.asiakas[0].picture].malli[q].sisus[0].texture2=charactertexture[e].bodypart[1];
                                        drawfast(&mallit[moped[d].mission.asiakas[0].picture].malli[q]);
                                        matrices->Pop();
                                        matrices->Pop();
                                        matrices->Pop();
                                }
                        //muzzleflare and location of gun barrel
                        matrices->Push();
                        matrices->TranslateLocal(84,70,0);
                        matrices->RotateYawPitchRollLocal(0,randDouble(-pi,pi),0);
                        moped[d].piippu=*matrices->GetTop();
                        if(moped[d].has_muzzle_flare){
                                drawfast(&mallit[2].malli[15]);
                        }
                        matrices->Pop();

                        if(mopopicture==0){
                                //rear wheel
                                matrices->Push();
                                matrices->TranslateLocal(0,20,0);
                                matrices->RotateYawPitchRollLocal(0,0,moped[d].angle_yaw);
                                drawfast(&mallit[mopopicture].malli[3]);
                                matrices->Pop();
                                //frontside
                                matrices->TranslateLocal(70,0,0);
                                //matrices->RotateYawPitchRollLocal(-moped[d].direction,0,0);
                                matrices->RotateYawPitchRollLocal(-moped[d].etudirection,0,0);
                                drawfast(&mallit[mopopicture].malli[2]);
                                //frontwheel
                                matrices->TranslateLocal(40,20,0);
                                matrices->RotateYawPitchRollLocal(0,0,moped[d].angle_yaw);
                                drawfast(&mallit[mopopicture].malli[3]);
                        }
                        if(mopopicture==6){
                                //rearwheel
                                matrices->Push();
                                matrices->TranslateLocal(0,20,0);
                                matrices->RotateYawPitchRollLocal(0,0,moped[d].angle_yaw);
                                drawfast(&mallit[mopopicture].malli[2]);
                                matrices->Pop();
                                //front side
                                matrices->TranslateLocal(79,0,0);
                                matrices->RotateYawPitchRollLocal(-moped[d].etudirection,0,0);
                                drawfast(&mallit[mopopicture].malli[1]);
                                //front wheel
                                matrices->TranslateLocal(40,20,0);
                                matrices->RotateYawPitchRollLocal(0,0,moped[d].angle_yaw);
                                drawfast(&mallit[mopopicture].malli[2]);
                        }
                        if(mopopicture==9){
                                //rear wheel
                                matrices->Push();
                                matrices->TranslateLocal(0,20,0);
                                matrices->RotateYawPitchRollLocal(0,0,moped[d].angle_yaw);
                                drawfast(&mallit[mopopicture].malli[2]);
                                matrices->Pop();
                                //front side
                                matrices->TranslateLocal(79,0,0);
                                matrices->RotateYawPitchRollLocal(-moped[d].etudirection,0,0);
                                drawfast(&mallit[mopopicture].malli[1]);
                                //front wheel
                                matrices->TranslateLocal(40,20,0);
                                matrices->RotateYawPitchRollLocal(0,0,moped[d].angle_yaw);
                                drawfast(&mallit[mopopicture].malli[2]);
                        }

                }

	m_pDevice->LightEnable(1, FALSE);
	rendercharacters();
	m_pDevice->LightEnable(1, TRUE);

	//camera angle
	float camq=-atan2f(-kamerax2+kamerax1,-kameraz2+kameraz1);
	float camw=0;
	float came=-atan2f(-kameray2+kameray1,sqrtf((sqr(-kameraz2+kameraz1)+sqr(-kamerax2+kamerax1))));

	if(moped[0].target_character!=-6667){
                /*m_pDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND,
                  D3DBLEND_ONE );
                  m_pDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND,
                  D3DBLEND_ONE );
                  m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,FALSE);*/
                m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,TRUE);
                //rendering crosshair
                if(moped[0].target_character>=0){
                        matrices->LoadIdentity();
                        matrices->TranslateLocal(character[moped[0].target_character].x,57,character[moped[0].target_character].z);
                        matrices->RotateYawPitchRollLocal(-camq+pi/2,camw,came);
                        drawfast(&mallit[2].malli[0]);
                }
                //rendering crosshair
                if(moped[0].target_character<=1){
                        matrices->LoadIdentity();
                        matrices->TranslateLocal(moped[-moped[0].target_character-1].x1,57,moped[-moped[0].target_character-1].z1);
                        matrices->RotateYawPitchRollLocal(-camq+pi/2,camw,came);
                        drawfast(&mallit[2].malli[0]);
                }
                m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,FALSE);
	}

	//}


	//bulletholes
	//if(smoke_count>0)
	{
                m_pDevice->SetRenderState( D3DRENDERSTATE_ZBIAS, 1);//set zbias as 1 beacause of the bullet holes




                for (q=0; q<MAX_SMOKES; q++)
                {
                        if(smokes[q].inactive)continue;
                        //kappaletta=kappaletta+1;
                        radius[q]=100.01f;
                        center_point[q].x=smokes[q].place.x;
                        center_point[q].y=smokes[q].place.y;
                        center_point[q].z=smokes[q].place.z;
                }


                matrices->LoadIdentity();
                m_pDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, *matrices->GetTop());
                m_pDevice->ComputeSphereVisibility(center_point,radius,MAX_SMOKES,0,visible);//remember SetTransform
                m_pDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE,FALSE);//ei rendertext z-bufferiin, jotta smokest olisi läpinäkyvät
                //m_pDevice->SetRenderState(D3DRENDERSTATE_ZENABLE,FALSE);

                int kappaletta=0;//ammount of bullet holes


                for (q=0; q<MAX_SMOKES; q++){
                        if(smokes[q].inactive)continue;
                        if((visible[q] &D3DSTATUS_CLIPINTERSECTIONALL   ) ){continue;}


                        if(smokes[q]._type==0){//normal bullet hole
                                triangles[kappaletta*12+0].position.x=smokes[q].place.x-smokes[q].cos*-2.5f;//*smokes[q].size;
                                triangles[kappaletta*12+0].position.y=smokes[q].place.y+0;//*smokes[q].size;
                                triangles[kappaletta*12+0].position.z=smokes[q].place.z-smokes[q].sin*-2.5f;//*smokes[q].size;
                                triangles[kappaletta*12+0].u=0.0f;
                                triangles[kappaletta*12+0].v=1.0f;

                                triangles[kappaletta*12+1].position.x=smokes[q].place.x+smokes[q].cos*2.5f;//*smokes[q].size;
                                triangles[kappaletta*12+1].position.y=smokes[q].place.y+5;//*smokes[q].size;
                                triangles[kappaletta*12+1].position.z=smokes[q].place.z+smokes[q].sin*2.5f;//*smokes[q].size;
                                triangles[kappaletta*12+1].u=1.0f;
                                triangles[kappaletta*12+1].v=1.0f;

                                triangles[kappaletta*12+2].position.x=smokes[q].place.x+smokes[q].cos*-2.5f;//*smokes[q].size;
                                triangles[kappaletta*12+2].position.y=smokes[q].place.y+5;//*smokes[q].size;
                                triangles[kappaletta*12+2].position.z=smokes[q].place.z+smokes[q].sin*-2.5f;//*smokes[q].size;
                                triangles[kappaletta*12+2].u=0.0f;
                                triangles[kappaletta*12+2].u=1.0f;

                                triangles[kappaletta*12+3].position.x=smokes[q].place.x-smokes[q].cos*-2.5f;//*smokes[q].size;
                                triangles[kappaletta*12+3].position.y=smokes[q].place.y+0;//*smokes[q].size;
                                triangles[kappaletta*12+3].position.z=smokes[q].place.z-smokes[q].sin*-2.5f;//*smokes[q].size;
                                triangles[kappaletta*12+3].u=0.0f;
                                triangles[kappaletta*12+3].v=0.0f;

                                triangles[kappaletta*12+4].position.x=smokes[q].place.x+smokes[q].cos*-2.5f;//*smokes[q].size;
                                triangles[kappaletta*12+4].position.y=smokes[q].place.y+5;//*smokes[q].size;
                                triangles[kappaletta*12+4].position.z=smokes[q].place.z+smokes[q].sin*-2.5f;//*smokes[q].size;
                                triangles[kappaletta*12+4].u=1.0f;
                                triangles[kappaletta*12+4].v=1.0f;

                                triangles[kappaletta*12+5].position.x=smokes[q].place.x+smokes[q].cos*-2.5f;//*smokes[q].size;
                                triangles[kappaletta*12+5].position.y=smokes[q].place.y+0;//*smokes[q].size;
                                triangles[kappaletta*12+5].position.z=smokes[q].place.z+smokes[q].sin*-2.5f;//*smokes[q].size;
                                triangles[kappaletta*12+5].u=0.0f;
                                triangles[kappaletta*12+5].u=1.0f;




                                triangles[kappaletta*12+6].position.x=smokes[q].place.x-smokes[q].cos*+2.5f;//*smokes[q].size;
                                triangles[kappaletta*12+6].position.y=smokes[q].place.y+0;//*smokes[q].size;
                                triangles[kappaletta*12+6].position.z=smokes[q].place.z-smokes[q].sin*+2.5f;//*smokes[q].size;
                                triangles[kappaletta*12+6].u=0.0f;
                                triangles[kappaletta*12+6].v=1.0f;

                                triangles[kappaletta*12+7].position.x=smokes[q].place.x+smokes[q].cos*-2.5f;//*smokes[q].size;
                                triangles[kappaletta*12+7].position.y=smokes[q].place.y+5;//*smokes[q].size;
                                triangles[kappaletta*12+7].position.z=smokes[q].place.z+smokes[q].sin*-2.5f;//*smokes[q].size;
                                triangles[kappaletta*12+7].u=1.0f;
                                triangles[kappaletta*12+7].v=1.0f;

                                triangles[kappaletta*12+8].position.x=smokes[q].place.x+smokes[q].cos*+2.5f;//*smokes[q].size;
                                triangles[kappaletta*12+8].position.y=smokes[q].place.y+5;//*smokes[q].size;
                                triangles[kappaletta*12+8].position.z=smokes[q].place.z+smokes[q].sin*+2.5f;//*smokes[q].size;
                                triangles[kappaletta*12+8].u=0.0f;
                                triangles[kappaletta*12+8].u=1.0f;

                                triangles[kappaletta*12+9].position.x=smokes[q].place.x-smokes[q].cos*+2.5f;//*smokes[q].size;
                                triangles[kappaletta*12+9].position.y=smokes[q].place.y+0;//*smokes[q].size;
                                triangles[kappaletta*12+9].position.z=smokes[q].place.z-smokes[q].sin*+2.5f;//*smokes[q].size;
                                triangles[kappaletta*12+9].u=0.0f;
                                triangles[kappaletta*12+9].v=0.0f;

                                triangles[kappaletta*12+10].position.x=smokes[q].place.x+smokes[q].cos*+2.5f;//*smokes[q].size;
                                triangles[kappaletta*12+10].position.y=smokes[q].place.y+5;//*smokes[q].size;
                                triangles[kappaletta*12+10].position.z=smokes[q].place.z+smokes[q].sin*+2.5f;//*smokes[q].size;
                                triangles[kappaletta*12+10].u=1.0f;
                                triangles[kappaletta*12+10].v=1.0f;

                                triangles[kappaletta*12+11].position.x=smokes[q].place.x+smokes[q].cos*+2.5f;//*smokes[q].size;
                                triangles[kappaletta*12+11].position.y=smokes[q].place.y+0;//*smokes[q].size;
                                triangles[kappaletta*12+11].position.z=smokes[q].place.z+smokes[q].sin*+2.5f;//*smokes[q].size;
                                triangles[kappaletta*12+11].u=0.0f;
                                triangles[kappaletta*12+11].u=1.0f;
                                kappaletta=kappaletta+1;
                        }


                }




                //render bulletholes2

                if(kappaletta>0){
			m_pDevice->SetMaterial( &mat[15] );
			m_pDevice->SetTexture( 0, background[15] );
			m_pDevice->SetRenderState(D3DRENDERSTATE_COLORKEYENABLE ,TRUE);
			matrices->LoadIdentity();
			m_pDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, *matrices->GetTop());
			m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST  ,
                                        D3DFVF_XYZ |D3DFVF_TEX1|D3DFVF_TEXCOORDSIZE2(0) ,triangles,kappaletta*12,NULL);
			m_pDevice->SetRenderState(D3DRENDERSTATE_COLORKEYENABLE ,FALSE);
                }

                m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,TRUE);



                for (q=0; q<MAX_SMOKES; q++){
                        if(smokes[q].inactive)continue;
                        if((visible[q] &D3DSTATUS_CLIPINTERSECTIONALL   ) ){continue;}

                        //smokes towards camera
                        if(smokes[q].up!=0){
                                smokes[q].q=camq;
                                smokes[q].w=camw;
                                smokes[q].e=came;
                        }

                        switch(smokes[q]._type){

                        case 4:{//ball like smoke
                                matrices->LoadIdentity();
                                matrices->TranslateLocal(smokes[q].place.x,smokes[q].place.y,smokes[q].place.z);
                                matrices->RotateYawPitchRollLocal(-smokes[q].q+pi/2,smokes[q].w,smokes[q].e);
                                matrices->ScaleLocal(smokes[q].size,smokes[q].size,smokes[q].size);
                                //m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,TRUE);
                                m_pDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND,
                                                D3DBLEND_DESTCOLOR    );
                                m_pDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND,
                                                D3DBLEND_SRCALPHA     );
                                drawfast(&mallit[2].malli[10]);
                                //m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,FALSE);
                                break;
                        }

                        case 3:{//explosion
                                matrices->LoadIdentity();
                                matrices->TranslateLocal(smokes[q].place.x,smokes[q].place.y,smokes[q].place.z);
                                matrices->RotateYawPitchRollLocal(-smokes[q].q+pi/2,smokes[q].w,smokes[q].e);
                                matrices->ScaleLocal(smokes[q].size,smokes[q].size,smokes[q].size);
                                //m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,TRUE);
                                m_pDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND,
                                                D3DBLEND_ONE );
                                m_pDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND,
                                                D3DBLEND_ONE );
                                drawfast(&mallit[2].malli[5]);
                                //m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,FALSE);
                                break;
                        }

                        case 2:{//smoke
                                matrices->LoadIdentity();
                                matrices->TranslateLocal(smokes[q].place.x,smokes[q].place.y,smokes[q].place.z);
                                matrices->RotateYawPitchRollLocal(-smokes[q].q+pi/2,smokes[q].w,smokes[q].e);
                                matrices->ScaleLocal(smokes[q].size,smokes[q].size,smokes[q].size);
                                //m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,TRUE);
                                m_pDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND,
                                                D3DBLEND_SRCCOLOR );
                                m_pDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND,
                                                D3DBLEND_SRCALPHA );

                                //select randomly from two options
                                if(smokes[q].picture==0){
                                        drawfast(&mallit[2].malli[3]);
                                }
                                else{
                                        drawfast(&mallit[2].malli[7]);
                                }
                                //m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,FALSE);
                                break;
                        }

                        case 1:{//One big hell of a hole
                                matrices->LoadIdentity();
                                matrices->TranslateLocal(smokes[q].place.x,smokes[q].place.y,smokes[q].place.z);
                                matrices->RotateYawPitchRollLocal(-smokes[q].q+pi/2,smokes[q].w,smokes[q].e);
                                matrices->ScaleLocal(smokes[q].size,smokes[q].size,smokes[q].size);


                                m_pDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND,
                                                D3DBLEND_ONE );
                                m_pDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND,
                                                D3DBLEND_ONE );
                                drawfast(&mallit[2].malli[4]);

                                matrices->LoadIdentity();
                                matrices->TranslateLocal(smokes[q].place.x,smokes[q].place.y,smokes[q].place.z);
                                matrices->RotateYawPitchRollLocal(-smokes[q].q+pi/2,smokes[q].w,smokes[q].e);
                                matrices->ScaleLocal(smokes[q].size*0.6f,smokes[q].size*0.6f,smokes[q].size*0.6f);


                                m_pDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND,
                                                D3DBLEND_ZERO    );
                                m_pDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND,
                                                D3DBLEND_INVSRCCOLOR       );
                                drawfast(&mallit[2].malli[4]);

                                break;
                        }

                                /*	case 1:{//One big hell of a hole
					matrices->LoadIdentity();
					//m_pDevice->SetRenderState(D3DRENDERSTATE_ZFUNC,D3DCMP_EQUAL);
					//m_pDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, FALSE);
					matrices->TranslateLocal(smokes[q].place.x,smokes[q].place.y,smokes[q].place.z);
					matrices->RotateYawPitchRollLocal(-smokes[q].q+pi/2,smokes[q].w,smokes[q].e);
					matrices->ScaleLocal(smokes[q].size,smokes[q].size,smokes[q].size);
					m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,false);
					drawfast(&mallit[2].malli[16]);
					m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,true);
					//m_pDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE);
					//m_pDevice->SetRenderState(D3DRENDERSTATE_ZFUNC,D3DCMP_LESSEQUAL);
					break;
                                        }*/
			}

                }
                m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,FALSE);
                m_pDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE,TRUE);


	}



	//arrows and crosshairs related to mission
        m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,TRUE);
        m_pDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND,D3DBLEND_SRCCOLOR);
        m_pDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND,D3DBLEND_SRCALPHA);
        m_pDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE,FALSE);

	if(moped[0].mission.status==0){
		float kx,kz;//targets coordinates
		int f;
		//target
		for (f=0; f<moped[0].mission.kohteita; f++){
			matrices->LoadIdentity();
			if(moped[0].mission.target_type==0)//character //character
			{
				kx=character[moped[0].mission.target[f]].x;
				kz=character[moped[0].mission.target[f]].z;
			}
			if(moped[0].mission.target_type==1)//coordinates
			{
				kx=moped[0].mission.targetx[0];
				kz=moped[0].mission.targetz[0];
			}
			if(moped[0].mission.target_type==2)//moped
			{
				kx=moped[moped[0].mission.target[f]].x1;
				kz=moped[moped[0].mission.target[f]].z1;
			}
			matrices->TranslateLocal(kx,57,kz);
			matrices->RotateYawPitchRollLocal(-camq+pi/2,camw,came);
			drawfast(&mallit[2].malli[8]);


			//arrow
			matrices->LoadIdentity();
			matrices->TranslateLocal(moped[0].x1,10,moped[0].z1);
			matrices->RotateYawPitchRollLocal(-atan2f(moped[0].z1-kz,moped[0].x1-kx)+pi/2+pi,0,pi/2);
			drawfast(&mallit[2].malli[9]);
			if(moped[0].mission.target_type==1)//render first one of the coordinates
				if(f>=0){break;}
		}

		//timer
		if(moped[0].mission.timer>0){
			strcpy(row,"time left ");
			itoa((int)moped[0].mission.timer/1000,temprow,10);
			strcat(row,temprow);
			rendertext((int)(1024*0.03f),(int)(768*0.95f-30),0,row);
		}


		//mission brief text
                rendertext((int)(1024*0.03f),(int)(768*0.95f-15),0,moped[0].mission.briefing_short);
		/*//go and kill some one
                  if(moped[0].mission._type==0){
                  if(moped[0].mission.subtype==0){
                  rendertext((int)(1024*0.03f),(int)(768*0.95f-15),0,"kill him");
                  }
                  if(moped[0].mission.subtype==1){
                  rendertext((int)(1024*0.03f),(int)(768*0.95f-15),0,"kill him");
                  }
                  }
                  //taxi
                  if(moped[0].mission._type==1){
                  if(moped[0].mission.subtype==0){
                  rendertext((int)(1024*0.03f),(int)(768*0.95f-15),0,"take me there");
                  }
                  if(moped[0].mission.subtype==1){
                  rendertext((int)(1024*0.03f),(int)(768*0.95f-15),0,"take me there");
                  }
                  }
                */
	}

	m_pDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE,TRUE);

	if(moped[0].mission.status==1){
                rendertext((int)(1024*0.03f),(int)(768*0.95f-15),0,"mission accomplished");
	}

	if(moped[0].mission.status==2){
                rendertext((int)(1024*0.03f),(int)(768*0.95f-15),0,"mission failed");
	}

	if(moped[0].mission.status==3){
                rendertext((int)(1024*0.03f),(int)(768*0.95f-15),0,"no mission");
	}







	m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,FALSE);


	//end demo
	if(gamephase2==1){
		rendertext((int)(1024*0.08f),(int)(768*0.15f),60,missioninfo[20]);
	}
	//pause
	if(gamephase2==2){
		svolume(voices[1],DSBVOLUME_MIN, options[1]&&SOUNDS_LOADED);
		rendertext((int)(1024*0.15f),(int)(768*0.48f+15*0),70,"Bikez II is now paused");
		rendertext((int)(1024*0.15f),(int)(768*0.48f+15*1),70,"esc to return to game");
		rendertext((int)(1024*0.15f),(int)(768*0.48f+15*2),70,"f9 to exit");
	}
	//beginning demo
	if(gamephase2==3){
		rendertext((int)(1024*0.08f),(int)(768*0.15f),60,"You are a mercenary biker in a near future dark city. The local criminal faction, Bikez, has just signed a contract with you about completing a series of missions including a whole lot of killing and blood...");
		rendertext((int)(1024*0.08f),(int)(768*0.24f),60,"If you are new to Bikez press Enter to learn the basics. Otherwise press Esc to start playing.");
	}
	//beginning demo
	if(gamephase2==4){
		rendertext((int)(1024*0.08f),(int)(768*0.15f),60,"Keys: Put your right hand on the arrow keys and your left hand so that your little finger is on number 1 and your index finger on number 4. Use 5 to slow the game down. Shift between bird´s eye view and following camera by pressing the tab key. Space is hand brake.");
		rendertext((int)(1024*0.08f),(int)(768*0.30f),60,"When you are low on energy, in need of a weapons upgrade, or need to save your game, you should find a Bikez warehouse. These warehouses are brownish buildings with a Bikez sign. Enter below the sign.");
		rendertext((int)(1024*0.08f),(int)(768*0.43f),60,"To get a mission, you must find a man that looks like your character. After finding the guy you have to stop by him, a green circle is lit under him if everything is right. Then press enter to get a mission.");
	}
	//is dead
	if(gamephase2==5){
		bullet[0].remove=true;
		gamespeed=0.2f;
		calculatebullets();
		calculatesmokes();
		rendertext((int)(1024*0.15f),(int)(768*0.48f+15*0),70,"You are dead. All is lost.");
	}

	//press enter to ask for a mission
	if(moped[0].mission.status!=0){//there is no mission
		if(moped[0].nearestcharacter!=-1)
                        if(!character[moped[0].nearestcharacter].dying)
                                if(!character[moped[0].nearestcharacter].movement_type==0)
                                {
                                        if(fabs(moped[0].speed)<0.7f)
                                                rendertext((int)(1024*0.03f),(int)(768*0.95f),0,"press enter");

                                        if(fabs(moped[0].speed)>=0.7f)
                                                rendertext((int)(1024*0.03f),(int)(768*0.95f),0,"slow down");
                                }
	}
	//energy meter
        //set camera to its place
        kamerax1=0;
        kameray1=0;
        kameraz1=100;
        kamerax2=kamerax1;
        kameray2=kameray1;
        kameraz2=0;
        m_View = ViewMatrix(D3DVECTOR(kamerax1,kameray1,kameraz1), D3DVECTOR(kamerax2,kameray2,kameraz2), D3DVECTOR(0,1,0), 0);
        m_Projection = ProjectionMatrix(25.0f, maxvisible, (float)(80*pi/180)); // 60 vision field
        m_pDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &m_View);
        m_pDevice->SetTransform(D3DTRANSFORMSTATE_PROJECTION, &m_Projection);
        m_pDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, FALSE);

        //meter
        matrices->LoadIdentity();
        matrices->TranslateLocal(156-500,256-500,-4.199f*100);
        matrices->ScaleLocal(2.5f,2.5f,2.5f);
        matrices->RotateYawPitchRollLocal(0,4.5f,0.15f);
        drawfast(&mallit[2].malli[16]);
        //needle of meter
        if(moped[0].energy<0)moped[0].energy=0;
        float energymittari=-moped[0].energy/100*4.24f+2.120f;
        matrices->RotateYawPitchRollLocal(energymittari,0,0);
        drawfast(&mallit[2].malli[17]);

        m_pDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE);


        //money
        itoa((int)moped[0].money,row,10);
        rendertext(896,710,0,row);

/*
//energy meter
pvertex vertex[6];
float height=50;
vertex[0].position.x=-500;
vertex[0].position.y=-height;
vertex[0].position.z=0;
vertex[0].u=0;
vertex[0].v=1;

vertex[1].position.x=500;
vertex[1].position.y=height;
vertex[1].position.z=0;
vertex[1].u=1;
vertex[1].v=0;

vertex[2].position.x=-500;
vertex[2].position.y=height;
vertex[2].position.z=0;
vertex[2].u=0;
vertex[2].v=0;

vertex[3].position.x=-500;
vertex[3].position.y=-height;
vertex[3].position.z=0;
vertex[3].u=0;
vertex[3].v=1;

vertex[4].position.x=500;
vertex[4].position.y=-height;
vertex[4].position.z=0;
vertex[4].u=1;
vertex[4].v=1;

vertex[5].position.x=500;
vertex[5].position.y=height;
vertex[5].position.z=0;
vertex[5].u=1;
vertex[5].v=0;

//set camera to its place
kamerax1=0;
kameray1=0;
kameraz1=1660;
kamerax2=0;
kameray2=960;
kameraz2=0;
m_View = ViewMatrix(D3DVECTOR(kamerax1,kameray1,kameraz1), D3DVECTOR(kamerax2,kameray2,kameraz2), D3DVECTOR(0,1,0), 0);
m_Projection = ProjectionMatrix(25.0f, maxvisible, (float)(80*pi/180)); // 60 vision field
m_pDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &m_View);
m_pDevice->SetTransform(D3DTRANSFORMSTATE_PROJECTION, &m_Projection);

//render energy meter
m_pDevice->SetMaterial( &mat[45] );
m_pDevice->SetTexture( 0, background[45] );
matrices->LoadIdentity();
//matrices->TranslateLocal(moped[0].x1,0,moped[0].z1);
m_pDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, *matrices->GetTop());
m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,TRUE);
m_pDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND,D3DBLEND_ONE);
m_pDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND,D3DBLEND_ONE);
m_pDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, FALSE);
m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST  ,
D3DFVF_XYZ |D3DFVF_TEX1|D3DFVF_TEXCOORDSIZE2(0) ,vertex,6,NULL);
//m_pDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE);
//m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,FALSE);


vertex[0].position.x=-moped[0].energy/100*1000+500;
vertex[0].position.y=-height;
vertex[0].position.z=0;
vertex[0].u=1-moped[0].energy/100;
vertex[0].v=1;

vertex[1].position.x=500;
vertex[1].position.y=height;
vertex[1].position.z=0;
vertex[1].u=1;
vertex[1].v=0;

vertex[2].position.x=-moped[0].energy/100*1000+500;
vertex[2].position.y=height;
vertex[2].position.z=0;
vertex[2].u=1-moped[0].energy/100;
vertex[2].v=0;

vertex[3].position.x=-moped[0].energy/100*1000+500;
vertex[3].position.y=-height;
vertex[3].position.z=0;
vertex[3].u=1-moped[0].energy/100;
vertex[3].v=1;

vertex[4].position.x=500;
vertex[4].position.y=-height;
vertex[4].position.z=0;
vertex[4].u=1;
vertex[4].v=1;

vertex[5].position.x=500;
vertex[5].position.y=height;
vertex[5].position.z=0;
vertex[5].u=1;
vertex[5].v=0;

//render energy meter
m_pDevice->SetMaterial( &mat[46] );
m_pDevice->SetTexture( 0, background[46] );
m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST  ,
D3DFVF_XYZ |D3DFVF_TEX1|D3DFVF_TEXCOORDSIZE2(0) ,vertex,6,NULL);
m_pDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE);
m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,FALSE);
*/

        m_pDevice->LightEnable(1, FALSE);

}

void render_mission(void){//render mission briefing

	int a,b;
	char row[200],temprow[200];

	float kerroin=0.055f;
	//m_pDevice->Clear( 0, NULL, D3DCLEAR_TARGET, 0x00000000, 0, 0 );

	//m_View = ViewMatrix(D3DVECTOR(10,50000,10), D3DVECTOR(0,0,0), D3DVECTOR(0,1,0), 0);
	m_View = ViewMatrix(D3DVECTOR(mapsx*8000*0.5f*kerroin+100,10000,mapsz*8000*0.5f*kerroin), D3DVECTOR(mapsx*8000*0.5f*kerroin,0,mapsz*8000*0.5f*kerroin), D3DVECTOR(0,1,0), 0);
	m_Projection = ProjectionMatrix(4000, 11000, (float)(30*pi/180)); // 60 vision field

	m_pDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &m_View);
	m_pDevice->SetTransform(D3DTRANSFORMSTATE_PROJECTION, &m_Projection);
	/*
	//keyboard control
	//accept mission
	if((moped[0].enter2==false) & (moped[0].enter==true)){
        if(mission_is_read==1){
        gamephase=0;//back to riding
        moped[0].mission=moped[0].mission_random;
        //character tulee kyytiin
        if(moped[0].mission._type==1)
        character[moped->nearestcharacter].inactive=true;
        }
        mission_is_read=1;//mission briefing is readed
	}*/
	/*if((moped[0].esc2==false) & (moped[0].esc==true)){
          gamephase=0;//back to riding
          }*/




	//maps	- kartat
/*
//is it visible?
for (a=0; a<mapsz; a++){
for (b=0; b<mapsx; b++){
center_pointmap[a*mapsx+b].x=(float)b*8000+4000;
center_pointmap[a*mapsx+b].y=0;
center_pointmap[a*mapsx+b].z=(float)a*8000+4000;
radiusmap[a*mapsx+b]=4000;
}
}
matrices->LoadIdentity();
m_pDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, *matrices->GetTop());
m_pDevice->ComputeSphereVisibility(center_pointmap,radiusmap,mapsx*mapsz,0,visiblemap);//remember SetTransform
*/
	//rendering map
	for (a=0; a<mapsz; a++){
		for (b=0; b<mapsx; b++){

                        //	if(visiblemap[a*mapsx+b] &D3DSTATUS_CLIPINTERSECTIONALL){continue;}

			matrices->LoadIdentity();
			matrices->TranslateLocal((float)b*8000*kerroin,0,(float)a*8000*kerroin);
			matrices->ScaleLocal(kerroin,kerroin,kerroin);
			drawfast(&mallit[0].malli[4]);//base
			drawfast(&mallit[1].malli[maps[a][b]]);//map
		}
	}



	//location of moped
        m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,TRUE);
        m_pDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE    );
        m_pDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_SRCALPHA    );
        m_pDevice->SetRenderState(D3DRENDERSTATE_ZENABLE,FALSE);

        matrices->LoadIdentity();
        matrices->TranslateLocal(moped[0].x1*kerroin,100,moped[0].z1*kerroin);
        matrices->RotateYawPitchRollLocal(0,0,pi/2);
        drawfast(&mallit[2].malli[6]);


	//location of target
        int f;
        for (f=0; f<moped[0].mission_random.kohteita; f++){
                matrices->LoadIdentity();
                if(moped->mission_random.target_type==0)//character
			matrices->TranslateLocal(character[moped[0].mission_random.target[f]].x*kerroin,100,character[moped[0].mission_random.target[f]].z*kerroin);
                if(moped->mission_random.target_type==1)//coordinates
			matrices->TranslateLocal(moped->mission_random.targetx[f]*kerroin,100,moped->mission_random.targetz[f]*kerroin);
                if(moped->mission_random.target_type==2)//moped
			matrices->TranslateLocal(moped[moped[0].mission_random.target[f]].x1*kerroin,100,moped[moped[0].mission_random.target[f]].z1*kerroin);

                matrices->RotateYawPitchRollLocal(0,0,pi/2);
                //matrices->ScaleLocal(0.4f,0.4f,0.4f);
                drawfast(&mallit[2].malli[0]);
        }

        m_pDevice->SetRenderState(D3DRENDERSTATE_ZENABLE,TRUE);
        m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,FALSE);


        rendertext((int)(1024*0.03f),(int)(768*0.90f),0,"enter to continue");	//write
        //rendertext((int)(1024*0.03f),(int)(768*0.90f+13),0,"esc to reject");
        if(mission_is_read==1){
                rendertext((int)(1024*0.03f),(int)(768*0.10f+13*0),50,moped->mission_random.briefing_long);
                strcpy(temprow,"The pay is: ");
                itoa(moped->mission_random.bounty,row,10);
                strcat(temprow,row);
                rendertext((int)(1024*0.03f),(int)(768*0.5f),50,temprow);
        }
        if(mission_is_read==0){
                rendertext((int)(1024*0.03f),(int)(768*0.10f+13*0),50,missioninfo[moped->level]);
        }



}

void create_mission(bikebase *moped,int missionumero){ //randomize a mission.

	int f;
	float kx,kz,distance;
	//.type  		alatyypit
	// 0= kill some one    	0= no time limit   	1=timelimit
	// 1= taxi



	// .target type
	// 0= person
	// 1= coordinates
	// 2= moped

	if(missionumero==-1)moped->missionumero=randInt(0,missionlevel[moped->level].missions);
	else moped->missionumero=missionumero;
	moped->mission_random=missionlevel[moped->level].mission[moped->missionumero];
	//target is a character
	if(moped->mission_random.target_type==0){
		for (f=0; f<moped->mission_random.kohteita; f++){
			moped->mission_random.target[f]=randInt(0,characters);
			create_character(moped->mission_random.target[f]);
			character[moped->mission_random.target[f]].picture=moped->mission_random.asiakas[f].picture;
			character[moped->mission_random.target[f]].weapon_idx=moped->mission_random.asiakas[f].weapon_idx;
			character[moped->mission_random.target[f]].energy=moped->mission_random.asiakas[f].energy;
			character[moped->mission_random.target[f]].height=moped->mission_random.asiakas[f].height;
			character[moped->mission_random.target[f]].tactics=moped->mission_random.asiakas[f].tactics;
			character[moped->mission_random.target[f]].movement_type=moped->mission_random.asiakas[f].movement_type;
		}
	}

	//target is coordinates
	if(moped->mission_random.target_type==1){
                moped->mission_random.asiakas[0]=character[moped->nearestcharacter];//characer becomes passanger
		for (f=0; f<moped->mission_random.kohteita; f++){
			laskekoordinaatit(&moped->mission_random.targetx[f],&moped->mission_random.targetz[f]);//randomizes coordinates outside of houses
		}
	}

	//target is moped
	if(moped->mission_random.target_type==2){
		//num_mopeds=moped->mission_random.kohteita+1;
		for (f=0; f<moped->mission_random.kohteita; f++){
			//moped->mission_random.target=randInt(1,num_mopeds);
			moped->mission_random.target[f]=f+1;
			create_mopo(moped->mission_random.target[f]);
			moped[moped->mission_random.target[f]].mopona=moped->mission_random.asiakas[f].picture;
			moped[moped->mission_random.target[f]].ase[0]=moped->mission_random.asiakas[f].weapon_idx;
			moped[moped->mission_random.target[f]].energy=moped->mission_random.asiakas[f].energy;
			//moped[moped->mission_random.target].tactics=moped->mission_random.asiakas.tactics;
			//moped[moped->mission_random.target].movement_type=moped->mission_random.asiakas.movement_type;
		}
	}


	//timelimit
	moped->mission_random.timer=0;
	if(moped->mission_random.subtype==1){
		if(moped->mission_random.target_type==0)//character
                {
                        kx=character[moped->mission_random.target[0]].x;
                        kz=character[moped->mission_random.target[0]].z;
                }
		if(moped->mission_random.target_type==1)//coordinates
                {
                        kx=moped->mission_random.targetx[0];
                        kz=moped->mission_random.targetz[0];
                }
		if(moped->mission_random.target_type==2)//moped
                {
                        kx=moped[moped->mission_random.target[0]].x1;
                        kz=moped[moped->mission_random.target[0]].z1;
                }

		distance=sqrtf(sqr(kx-moped->x1)+sqr(kz-moped->z1));
		moped->mission_random.timer=randDouble((distance/1.7f),(distance/1.3f));
	}

}

void laskekoordinaatit(float *xa,float *za){//calculate coordinates

	int a,b,c;
	bool osuma=false;
	float osumax,osumaz;
  fa:

        *xa=randDouble(0,(float)mapsx*8000);
        *za=randDouble(0,(float)mapsz*8000);

        int mapx=(int)*xa/8000;
        int mapz=(int)*za/8000;


        a=maps[mapz][mapx];
        int wallhits=0;
        for (b=0; b<wallgroup[0].routes[a].route_count; b++){
                for (c=0; c<wallgroup[0].routes[a].route[b].line_count; c++){
                        if(linecollidesline(&osuma,&osumax,&osumaz,*xa-mapx*8000,*za-mapz*8000,*xa+10000-mapx*8000,*za+10000-mapz*8000,	wallgroup[0].routes[a].route[b].point[c].x1,wallgroup[0].routes[a].route[b].point[c].z1,wallgroup[0].routes[a].route[b].point[c].x2,wallgroup[0].routes[a].route[b].point[c].z2))
                                wallhits=wallhits+1;
                }
        }
        if((float)wallhits/2*1000!=((int)(wallhits/2))*1000)
		goto fa;
        if(sqrtf(sqr(*xa-moped[0].x1)+sqr(*za-moped[0].z1))<10000)
		goto fa;


}

void laskemissiot(bikebase *moped){ //calculate missions
	int q,f;
	bool kuollut=true;
	if(moped->mission.status!=0) return;
	//kill some one
	if(moped->mission._type==0){
		//remove dead ones from the list
		for (f=0; f<moped->mission.kohteita; f++){
			if(moped->mission.target_type==0){
				if(character[moped->mission.target[f]].dying){
					for (q=f; q<moped->mission.kohteita; q++){
						moped->mission.target[q]=moped->mission.target[q+1];
					}
					moped->mission.kohteita=moped->mission.kohteita-1;
				}
			}
			if(moped->mission.target_type==2){
				if(moped[moped->mission.target[f]].inactive){
					for (q=f; q<moped->mission.kohteita; q++){
						moped->mission.target[q]=moped->mission.target[q+1];
					}
					moped->mission.kohteita=moped->mission.kohteita-1;
				}
			}
		}
		//is everyone dead?
		for (f=0; f<moped->mission.kohteita; f++){
			if(moped->mission.target_type==0) if(!character[moped->mission.target[f]].dying) kuollut=false;
			if(moped->mission.target_type==2) if(!moped[moped->mission.target[f]].inactive) kuollut=false;
		}
		if(moped->mission.subtype==0){//no timelimit
			if(kuollut==true) moped->mission.status=1;//character killed
		}
		if(moped->mission.subtype==1){//with timelimit
			moped->mission.timer=moped->mission.timer-elapsed*gamespeed;
			if(moped->mission.timer<0) moped->mission.status=2;//mission failed
			if(kuollut==true) moped->mission.status=1;//character killed
		}
	}


	//taxi
	if(moped->mission._type==1){
		if(moped->mission.subtype==0){//no timelimit
			if(sqrtf(sqr(moped->mission.targetx[0]-moped->x1)+sqr(moped->mission.targetz[0]-moped->z1))<100)
				if(fabs(moped[0].speed)<0.7f){
					for (f=0; f<moped->mission.kohteita-1; f++){
						moped->mission.targetx[f]=moped->mission.targetx[f+1];
						moped->mission.targetz[f]=moped->mission.targetz[f+1];
					}
					moped->mission.kohteita=moped->mission.kohteita-1;
                                        if(moped->mission.kohteita==0){
                                                moped->mission.status=1;//we are there
                                                q=randInt(0,characters);
                                                character[q]=moped->mission.asiakas[0];
                                                character[q].x=moped->x2;
                                                character[q].z=moped->z2;
                                                character[q].speed=randDouble(0.02f,0.1f);
                                        }
				}
		}
		if(moped->mission.subtype==1){//with timelimit
			moped->mission.timer=moped->mission.timer-elapsed*gamespeed;
			if(moped->mission.timer<0) moped->mission.status=2;//mission failed
			if(sqrtf(sqr(moped->mission.targetx[0]-moped->x1)+sqr(moped->mission.targetz[0]-moped->z1))<100)
				if(fabs(moped[0].speed)<0.7f){
                                        moped->mission.status=1;//we are there
                                        q=randInt(0,characters);
                                        character[q]=moped->mission.asiakas[0];
                                        character[q].x=moped->x2;
                                        character[q].z=moped->z2;
                                        character[q].speed=randDouble(0.02f,0.1f);
				}
		}
	}

	/*//if failed
          if(moped->mission.status==2){
          moped->money=moped->money-100;
          if(moped->money<0)moped->money=0;
          }*/
	//if accomplished
	if(moped->mission.status==1){
		//money is payed
		moped->money=moped->money+moped->mission.bounty;
		//level up
		moped->level=moped->level+1;
		//read briefing
		mission_is_read=0;
		//if there is no more missions
		if(missionlevel[moped->level].missions==0){
			gamephase2=1;//game over
		}
	}

}

void create_character(int q){//create random character

	int b,ampuva,a;
	int prosentti;

        for (a=0; a<100; a++)character[q].osuma[a]=false;
        character[q].height=randDouble(0.9f,1.1f);
        character[q].walk_dir=1;
        character[q].menoajastin=0;
        character[q].dying=false;
        character[q].inactive=false;
        laskekoordinaatit(&character[q].x,&character[q].z);
        character[q].direction=randDouble(-pi,pi);
        character[q].speed=randDouble(0.05f,0.1f);
        character[q].lx=0;
        character[q].rx=0;
        character[q].leg=false;
        character[q].sektorix=(int)character[q].x/8000;
        character[q].sektoriz=(int)character[q].z/8000;
        moveparts(q);
        for (b=0; b<11; b++){
                character[q].bodypart_coords[b].gox=0;
                character[q].bodypart_coords[b].goy=0;
                character[q].bodypart_coords[b].goz=0;
        }

        //randomize character properties
        int a1=15;//character is at players side
        int a2=15;//enemy
        int a3=70;//passive
//character[q].picture=7;
        prosentti=randInt(0,100);
        //own
        if((prosentti>=0)&&(prosentti<a1)){
                character[q].picture=3;
                character[q].movement_type=0;
                character[q].weapon_idx=randInt(10,13);
                character[q].tactics=1;
                character[q].energy=randDouble(2.4f,3.3f);
        }
        //enemy
        if((prosentti>=a1)&&(prosentti<a1+a2)){
                character[q].picture=8;
                character[q].movement_type=2;
                character[q].weapon_idx=randInt(10,13);
                character[q].tactics=0;
                character[q].energy=randDouble(1.4f,2.5f);
        }
        //passive
        if((prosentti>=a1+a2)&&(prosentti<a1+a2+a3)){
                character[q].picture=randInt(0,2);

                if(character[q].picture==0)character[q].picture=7;
                if(character[q].picture==1)character[q].picture=10;

                character[q].movement_type=1;
                //Randomly select does it have a gun or not.
                character[q].weapon_idx=-1;
                ampuva=randInt(0,4);
                if(ampuva==0){
                        character[q].weapon_idx=randInt(10,13);
                }
                character[q].tactics=1;
                character[q].energy=randDouble(0.5f,1.7f);
        }

/*
  character[q].picture=randInt(0,2);
  switch (character[q].picture)
  {
  case 0:{
  character[q].picture=3;
  break;
  }
  case 1:{
  character[q].picture=7;
  break;
  }
  }
*/

}

void load_missions(void){ //read missions
        std::cout << "loading missions" << std::endl;

	FILE *fil;
	CHAR row[800];
	int q,f,level;

        for (q=0; q<10; q++){
		missionlevel[q].missions=0;
        }

        //load missions
        fil = fopen("data/mission.dat","rt");

	stripped_fgets(row,sizeof(row),fil);
        strcpy(missioninfo[0],row);
	stripped_fgets(row,sizeof(row),fil);
        strcpy(missioninfo[1],row);
	stripped_fgets(row,sizeof(row),fil);
        strcpy(missioninfo[2],row);
	stripped_fgets(row,sizeof(row),fil);
        strcpy(missioninfo[3],row);
	stripped_fgets(row,sizeof(row),fil);
        strcpy(missioninfo[4],row);
	stripped_fgets(row,sizeof(row),fil);
        strcpy(missioninfo[5],row);
	stripped_fgets(row,sizeof(row),fil);
        strcpy(missioninfo[6],row);
	stripped_fgets(row,sizeof(row),fil);
        strcpy(missioninfo[7],row);
	stripped_fgets(row,sizeof(row),fil);
        strcpy(missioninfo[8],row);
	stripped_fgets(row,sizeof(row),fil);
        strcpy(missioninfo[9],row);
	stripped_fgets(row,sizeof(row),fil);
        strcpy(missioninfo[10],row);
	stripped_fgets(row,sizeof(row),fil);
        strcpy(missioninfo[11],row);
	stripped_fgets(row,sizeof(row),fil);
        strcpy(missioninfo[12],row);
	stripped_fgets(row,sizeof(row),fil);
        strcpy(missioninfo[13],row);
	stripped_fgets(row,sizeof(row),fil);
        strcpy(missioninfo[14],row);
	stripped_fgets(row,sizeof(row),fil);
        strcpy(missioninfo[15],row);
	stripped_fgets(row,sizeof(row),fil);
        strcpy(missioninfo[16],row);
	stripped_fgets(row,sizeof(row),fil);
        strcpy(missioninfo[17],row);
	stripped_fgets(row,sizeof(row),fil);
        strcpy(missioninfo[18],row);
	stripped_fgets(row,sizeof(row),fil);
        strcpy(missioninfo[19],row);
	stripped_fgets(row,sizeof(row),fil);
        strcpy(missioninfo[20],row);

	stripped_fgets(row,sizeof(row),fil);
        level=atoi(row);
  lue:
	stripped_fgets(row,sizeof(row),fil);
        missionlevel[level].mission[missionlevel[level].missions]._type=atoi(row);
	stripped_fgets(row,sizeof(row),fil);
        missionlevel[level].mission[missionlevel[level].missions].target_type=atoi(row);
	stripped_fgets(row,sizeof(row),fil);
        missionlevel[level].mission[missionlevel[level].missions].subtype=atoi(row);
	stripped_fgets(row,sizeof(row),fil);
        missionlevel[level].mission[missionlevel[level].missions].kohteita=atoi(row);
	stripped_fgets(row,sizeof(row),fil);
        missionlevel[level].mission[missionlevel[level].missions].asiakas[0].picture=atoi(row);
	stripped_fgets(row,sizeof(row),fil);
        missionlevel[level].mission[missionlevel[level].missions].asiakas[0].weapon_idx=atoi(row);
	stripped_fgets(row,sizeof(row),fil);
        missionlevel[level].mission[missionlevel[level].missions].asiakas[0].energy=(float)atof(row);
	stripped_fgets(row,sizeof(row),fil);
        missionlevel[level].mission[missionlevel[level].missions].asiakas[0].height=(float)atof(row);
	stripped_fgets(row,sizeof(row),fil);
        missionlevel[level].mission[missionlevel[level].missions].asiakas[0].tactics=atoi(row);
	stripped_fgets(row,sizeof(row),fil);
        missionlevel[level].mission[missionlevel[level].missions].asiakas[0].movement_type=atoi(row);
	stripped_fgets(row,sizeof(row),fil);
        missionlevel[level].mission[missionlevel[level].missions].bounty=atoi(row);
	stripped_fgets(row,sizeof(row),fil);
        strcpy(missionlevel[level].mission[missionlevel[level].missions].briefing_short,row);
	stripped_fgets(row,sizeof(row),fil);
        strcpy(missionlevel[level].mission[missionlevel[level].missions].briefing_long,row);
	for (f=0; f<100; f++){
		missionlevel[level].mission[missionlevel[level].missions].asiakas[f]=missionlevel[level].mission[missionlevel[level].missions].asiakas[0];
	}

        missionlevel[level].missions=missionlevel[level].missions+1;

	//read next level, if it is 666666 file ends
	stripped_fgets(row,sizeof(row),fil);
        level=atoi(row);
        if(level!=666666)goto lue;

        fclose(fil);
}

void laskemoped(void){ //calculate mopeds
	int q,q2,d;
	float dq,temp1;
	int negaatio;
	int osumia;
	//if(num_mopeds==1)return;

	if(moped->mission.status!=0) return;
	for (d=1; d<num_mopeds; d++){
		if(moped[d].inactive)continue;

		if(moped[d].energy<0){moped[d].inactive=true;
                        //smoke to air
                        if(ase[1].smoke_filled!=0)
                                for (q=0; q<3; q++){
                                        fromsmoke(1.0f,0.001f,true,3000,moped[d].x1,60,moped[d].z1,ase[1].smoke_filled,randDouble(pi,-pi),randDouble(pi,-pi),randDouble(pi,-pi));
                                }
                        //explosion
                        if(ase[1].explosion_size!=0){
                                quake=3;
                                for (q2=0; q2<100; q2++){
                                        shoot(-6667,-1,1,randDouble(100,300),moped,3,moped[d].x1,60,moped[d].z1,randDouble(-pi,pi),randDouble(-pi,pi),randDouble(-pi,pi));
                                }
                                //for (q2=0; q2<1; q2++){
                                fromsmoke(1.0f,0.01f,true,4000,moped[d].x1,60,moped[d].z1,3,0,0,0);
                                //}
                        }
		}
		//if(moped[d].inactive==true) num_mopeds=1;//create_mopo(d);

		//angle towards player
		moped[d].player_angle=atan2f(moped[0].z1-moped[d].z1,moped[0].x1-moped[d].x1)+pi;

		//reset controls
		moped[d].enter2=moped[d].enter;
		moped[d].esc2=moped[d].esc;
		moped[d].up2=moped[d].up;
		moped[d].down2=moped[d].down;
		moped[d].left2=moped[d].left;
		moped[d].right2=moped[d].right;
		moped[d].one2=moped[d].one;
		moped[d].two2=moped[d].two;
		moped[d].three2=moped[d].three;
		moped[d].four2=moped[d].four;
		moped[d].space2=moped[d].space;
		moped[d].enter=false;
		moped[d].esc=false;
		moped[d].up=false;
		moped[d].down=false;
		moped[d].left=false;
		moped[d].right=false;
		moped[d].one=false;
		moped[d].two=false;
		moped[d].three=false;
		moped[d].four=false;
		moped[d].space=false;
		moped[d].directiontimer=moped[d].directiontimer+elapsed*gamespeed;
		moped[d].tacticstimer=moped[d].tacticstimer+elapsed*gamespeed;
		moped[d].walltimer=moped[d].walltimer-elapsed*gamespeed;
		if(moped[d].left2){moped[d].left3=moped[d].left3+1;if(moped[d].right3>0)moped[d].right3=moped[d].right3-1;}
		if(moped[d].right2){moped[d].right3=moped[d].right3+1;if(moped[d].left3>0)moped[d].left3=moped[d].left3-1;}
		if(moped[d].left3>30)moped[d].left3=30;
		if(moped[d].right3>30)moped[d].right3=30;
		if(moped[d].up2){moped[d].up3=moped[d].up3+1;if(moped[d].up3>0)moped[d].up3=moped[d].up3-1;}
		if(moped[d].down2){moped[d].down3=moped[d].down3+1;if(moped[d].down3>0)moped[d].down3=moped[d].down3-1;}
		if(moped[d].up3>30)moped[d].up3=30;
		if(moped[d].down3>30)moped[d].down3=30;

                //Continue away from a wall if it has collided with it.
                if(moped[d].walltimer>0){
			moped[d].up=moped[d].up2;
			moped[d].down=moped[d].down2;
			moped[d].left=moped[d].left2;
			moped[d].right=moped[d].right2;
                }

		//Artificial intelligence

                if(moped[d].walltimer<0){
                        //eager to use throttle
                        moped[d].up=true;

                        /*if(moped[d].distance<300){
                          moped[d].up=false;
                          moped[d].down=true;
                          }*/



                        //finds out is the bike at right or left side.
                        dq=atan2f(moped[d].z1-moped[0].z1,moped[d].x1-moped[0].x1)+pi;
                        temp1=moped[d].direction;
                        //if(dq>pi){dq=dq-2*pi;moped[d].direction=moped[d].direction-2*pi;}
                        //if(dq<pi){dq=dq+2*pi;moped[d].direction=moped[d].direction+2*pi;}
                        if(moped[d].direction-dq>pi)temp1=temp1-pi*2;
                        if(dq-moped[d].direction>pi)dq=dq-pi*2;

                        if(moped[d].up){
                                negaatio=1;
                                if (dq<temp1)
                                        negaatio=-1;
                        }
                        else{
                                negaatio=-1;
                                if (dq<temp1)
                                        negaatio=1;
                        }

                        //taktics
                        if(moped[d].tacticstimer>2000){
                                moped[d].tacticstimer=0;
                                moped[d].tactics=randInt(0,2);
                        }

                        //use hand brake
                        if((fabs(moped[d].direction-dq)>0.4f)&&(moped[d].down==false)&&(moped[d].speed>2)){
                                moped[d].space=true;
                        }
                        if(moped[d].angle_pitch>0.2f){
                                moped[d].space=true;
                        }

                        /*//player is ahead
                          if(fabs(moped[d].direction-dq)<0.1f){
                          moped[d].one=true;
                          //moped[d].two=true;
                          //if player near enough ahead do not use throttle
                          if(moped[d].distance<1500)
                          moped[d].up=false;
                          }*/

                        //Shoot
                        if(fabs(moped[d].direction-dq)<1.2f)
                                moped[d].one=true;



                        //attack
                        if(moped[d].tactics==0)
                        {
                                if(fabs(moped[d].direction-dq)>0.05f){


                                        //when turned enough choose new direction
                                        if(moped[d].directiontimer>1000)
                                        {
                                                moped[d].directiontimer=0;
                                                if(negaatio==-1)
                                                        moped[d].right=true;
                                                if(negaatio==1)
                                                        moped[d].left=true;
                                        }
                                        else{
                                                moped[d].right=moped[d].right2;
                                                moped[d].left=moped[d].left2;
                                        }
                                }
                        }

                        //escapes
                        if(moped[d].tactics==1){
                                if(fabs(moped[d].direction-dq)>0.3f){
                                        //when turned enough choose new direction
                                        if(moped[d].directiontimer>2000)
                                        {
                                                moped[d].directiontimer=0;
                                                if(negaatio==1)
                                                        moped[d].right=true;
                                                if(negaatio==-1)
                                                        moped[d].left=true;
                                        }
                                        else{
                                                moped[d].right=moped[d].right2;
                                                moped[d].left=moped[d].left2;
                                        }
                                }
                        }

                        osumia=0;
                        //if cant get off the wall
                        for (q=0; q<100; q++){
                                if(moped[d].osuma[q])
                                        osumia=osumia+1;
                        }

                        //if it is clearly in the wall
                        if(moped[d].osuma[0]){
                                moped[d].walltimer=(float)(osumia+20)*30;
                                //if it was going straigth ahaed use reverse
                                if(moped[d].up3>moped[d].down3){
                                        moped[d].down=false;
                                        moped[d].up=true;
                                }
                                //and viseversa
                                if(moped[d].up3<moped[d].down3){
                                        moped[d].down=true;
                                        moped[d].up=false;
                                }
                                //do not go left
                                if(moped[d].left3>moped[d].right3){
                                        moped[d].directiontimer=0;
                                        moped[d].left=false;
                                        moped[d].right=true;
                                }
                                //do not go rigth either
                                if(moped[d].left3<moped[d].right3){
                                        moped[d].directiontimer=0;
                                        moped[d].left=true;
                                        moped[d].right=false;
                                }
                        }


			if((osumia>90)&&(moped[d].visible==false)){

				laskekoordinaatit(&moped[d].x1,&moped[d].z1);

			}

                }


        }
}

void create_mopo(int d){ //randomize moped
	int a;

	moped[d].etudirection=0;
	moped[d].ase[0]=0;
	moped[d].ase[1]=0;
	moped[d].ase[2]=0;
	moped[d].ase[3]=0;
	moped[d].timesparks=-1;
	moped[d].mission.status=3;
	moped[d].mopona=0;
	moped[d].numero=d;
	moped[d].energy=100;
	moped[d].level=0;
	moped[d].direction=pi*0.25f;
	laskekoordinaatit(&moped[d].x1,&moped[d].z1);
	moped[d].x2=moped[d].x1+sinf(moped[d].direction)*70;
	moped[d].z2=moped[d].z1+cosf(moped[d].direction)*70;
	moped[d].speed=0.01f;
	moped[d].sektorix=(int)moped[d].x1/8000;
	moped[d].sektoriz=(int)moped[d].z1/8000;
	moped[d].inactive=false;
	for (a=0; a<100; a++)moped[d].osuma[a]=false;
	moped[d].directiontimer=0;
	moped[d].tacticstimer=0;
	moped[d].visible=true;
	moped[d].x3=moped[d].x1;
	moped[d].y3=moped[d].y1;
	moped[d].z3=moped[d].z1;
	moped[d].x4=moped[d].x2;
	moped[d].y4=moped[d].y2;
	moped[d].z4=moped[d].z2;

}

void render_workshop(void){//render workshop
	RECT     rcSource, rcDest, loota;
	int a,b;
	int is_selecteda,is_selectedb,is_selectedc;
	char row[200],temprow[200];
	float nop;



	gamespeed=1;

	//background picture
	rcSource.top = 0;
	rcSource.left = 0;
	rcSource.bottom = 768;
	rcSource.right = 1024;
	rcDest.top = 0;
	rcDest.left = 0;
	rcDest.bottom = SCREEN_HEIGHT;
	rcDest.right = SCREEN_WIDTH;

	taka->Blt(&rcDest, pictures[0], &rcSource, 0, NULL);
	is_selecteda=-2;
	is_selectedb=-2;
	is_selectedc=-2;

	float pricetaso=1.05f;
	//advantages and disadvantages
	for (a=0; a<4; a++){
		ase[moped[0].ase[a]].price=(int)(sqr(ase[moped[0].ase[a]].prate_of_fire+ase[moped[0].ase[a]].pspeed+ase[moped[0].ase[a]].pdamage+ase[moped[0].ase[a]].homing*5)*pricetaso);
		ase[moped[0].ase[a]].price2=(int)(sqr(ase[moped[0].ase[a]].prate_of_fire+ase[moped[0].ase[a]].pspeed+ase[moped[0].ase[a]].pdamage+ase[moped[0].ase[a]].homing*5-1)*pricetaso);
		ase[moped[0].ase[a]].pricehoming=0;
		for (b=0; b<5; b++){
			ase[moped[0].ase[a]].pricehoming=ase[moped[0].ase[a]].pricehoming+(int)(sqr(ase[moped[0].ase[a]].prate_of_fire+ase[moped[0].ase[a]].pspeed+ase[moped[0].ase[a]].pdamage+b)*pricetaso);
		}
		for (b=0; b<4; b++){

			//disadvantage
			rcSource.top = 0;
			rcSource.left = 0;
			rcSource.bottom = 28;
			rcSource.right = 28;
			rcDest.top = (125+a*29)*SCREEN_HEIGHT/768;
			rcDest.left = (228+b*180)*SCREEN_WIDTH/1024;
			rcDest.bottom = rcDest.top+28*SCREEN_HEIGHT/768;
			rcDest.right = rcDest.left+28*SCREEN_WIDTH/1024;
			if((mousex<rcDest.right)&&(mousex>rcDest.left)&&(mousey>rcDest.top)&&(mousey<rcDest.bottom))
			{
				is_selecteda=a;
				is_selectedb=b;
				is_selectedc=-1;
				if(mousestate.rgbButtons[0]){
                                        rcSource.top = 28;
                                        rcSource.bottom = 56;
				}
			}
			taka->Blt(&rcDest, pictures[2], &rcSource, 0, NULL);


			//advantage
			rcSource.top = 0;
			rcSource.left = 28;
			rcSource.bottom = 28;
			rcSource.right = 56;
			rcDest.top = (125+a*29)*SCREEN_HEIGHT/768;
			rcDest.left = (228+b*180+71)*SCREEN_WIDTH/1024;
			rcDest.bottom = rcDest.top+28*SCREEN_HEIGHT/768;
			rcDest.right = rcDest.left+28*SCREEN_WIDTH/1024;
			if((mousex<rcDest.right)&&(mousex>rcDest.left)&&(mousey>rcDest.top)&&(mousey<rcDest.bottom))
			{
				is_selecteda=a;
				is_selectedb=b;
				is_selectedc=1;
				if(mousestate.rgbButtons[0]){
                                        rcSource.top = 28;
                                        rcSource.bottom = 56;
				}
			}
			taka->Blt(&rcDest, pictures[2], &rcSource, 0, NULL);

			switch (a)
			{
                        case 0:{
                                itoa(ase[moped[0].ase[b]].pdamage,row,10);
                                break;
                        }
                        case 1:{
                                itoa(ase[moped[0].ase[b]].prate_of_fire,row,10);
                                break;
                        }
                        case 2:{
                                itoa(ase[moped[0].ase[b]].pspeed,row,10);
                                break;
                        }
                        case 3:{
                                itoa(ase[moped[0].ase[b]].homing*5,row,10);
                                break;
                        }
			}

			//gun points
			//strcpy(row,":");
			//itoa((int)moped[0].mission.timer/1000,row,10);
			//strcat(row,temprow);
			rendertext((212+b*180+60),(125+a*29+10),0,row);

		}
		//price
		itoa((int)ase[moped[0].ase[a]].price,row,10);
		rendertext((212+a*180+50),(125+4*29+10),0,row);
	}
	//repair moped
	if((moped[0].korjaamolla2==false)&&(moped[0].korjaamolla==true)){
		repair_cost=int(100-moped[0].energy)*((moped[0].level+2)/2);
		if(repair_cost>moped[0].money)repair_cost=moped[0].money;
		moped[0].energy=moped[0].energy+repair_cost/((moped[0].level+2)/2);
		moped[0].money=moped[0].money-repair_cost;
	}

	//money
        itoa((int)moped[0].money,row,10);
        rendertext((200),(125+5*29+10),0,row);

	//moped fixed
        if(repair_cost>0){
                strcpy(row,"bike repaired for ");
                itoa((int)repair_cost,temprow,10);
                strcat(row,temprow);
                rendertext((190),(76),0,row);
        }

	//key is pressed. //translator note: could be understood as "a brat is f*cked".
	if ((mousestate2.rgbButtons[0])&&(!mousestate.rgbButtons[0]))
                if ((is_selecteda!=-2)&&(is_selectedb!=-2)&&(is_selectedc!=-2)){
                        switch (is_selecteda)
                        {
                        case 0:{
                                if(is_selectedc==1)
                                        if(ase[moped[0].ase[is_selectedb]].pdamage<10)
						if(moped[0].money>=ase[moped[0].ase[is_selectedb]].price)
						{
							SndObjPlay(voices[18], 0, options[1]&&SOUNDS_LOADED);
							ase[moped[0].ase[is_selectedb]].pdamage=ase[moped[0].ase[is_selectedb]].pdamage+1;
							moped[0].money=moped[0].money-ase[moped[0].ase[is_selectedb]].price;
						}
                                if(is_selectedc==-1)
                                        if(ase[moped[0].ase[is_selectedb]].pdamage>1)
                                        {
                                                SndObjPlay(voices[19], 0, options[1]&&SOUNDS_LOADED);
                                                ase[moped[0].ase[is_selectedb]].pdamage=ase[moped[0].ase[is_selectedb]].pdamage-1;
                                                moped[0].money=moped[0].money+ase[moped[0].ase[is_selectedb]].price2;
                                        }
                                break;
                        }
                        case 1:{
                                if(is_selectedc==1)
                                        if(ase[moped[0].ase[is_selectedb]].prate_of_fire<10)
						if(moped[0].money>=ase[moped[0].ase[is_selectedb]].price)
						{
							SndObjPlay(voices[18], 0, options[1]&&SOUNDS_LOADED);
							ase[moped[0].ase[is_selectedb]].prate_of_fire=ase[moped[0].ase[is_selectedb]].prate_of_fire+1;
							moped[0].money=moped[0].money-ase[moped[0].ase[is_selectedb]].price;
						}
                                if(is_selectedc==-1)
                                        if(ase[moped[0].ase[is_selectedb]].prate_of_fire>1)
                                        {
                                                SndObjPlay(voices[19], 0, options[1]&&SOUNDS_LOADED);
                                                ase[moped[0].ase[is_selectedb]].prate_of_fire=ase[moped[0].ase[is_selectedb]].prate_of_fire-1;
                                                moped[0].money=moped[0].money+ase[moped[0].ase[is_selectedb]].price2;
                                        }
                                break;
                        }
                        case 2:{
                                if(is_selectedc==1)
                                        if(ase[moped[0].ase[is_selectedb]].pspeed<10)
						if(moped[0].money>=ase[moped[0].ase[is_selectedb]].price)
						{
							SndObjPlay(voices[18], 0, options[1]&&SOUNDS_LOADED);
							ase[moped[0].ase[is_selectedb]].pspeed=ase[moped[0].ase[is_selectedb]].pspeed+1;
							moped[0].money=moped[0].money-ase[moped[0].ase[is_selectedb]].price;
						}
                                if(is_selectedc==-1)
                                        if(ase[moped[0].ase[is_selectedb]].pspeed>1)
                                        {
                                                SndObjPlay(voices[19], 0, options[1]&&SOUNDS_LOADED);
                                                ase[moped[0].ase[is_selectedb]].pspeed=ase[moped[0].ase[is_selectedb]].pspeed-1;
                                                moped[0].money=moped[0].money+ase[moped[0].ase[is_selectedb]].price2;
                                        }
                                break;
                        }
                        case 3:{
                                if(is_selectedc==1)
                                        if(ase[moped[0].ase[is_selectedb]].homing==false)
						if(moped[0].money>=ase[moped[0].ase[is_selectedb]].pricehoming)
						{
							SndObjPlay(voices[18], 0, options[1]&&SOUNDS_LOADED);
							ase[moped[0].ase[is_selectedb]].homing=true;
							moped[0].money=moped[0].money-ase[moped[0].ase[is_selectedb]].pricehoming;
						}
                                if(is_selectedc==-1)
                                        if(ase[moped[0].ase[is_selectedb]].homing==true)
                                        {
                                                SndObjPlay(voices[19], 0, options[1]&&SOUNDS_LOADED);
                                                ase[moped[0].ase[is_selectedb]].homing=false;
                                                moped[0].money=moped[0].money+ase[moped[0].ase[is_selectedb]].pricehoming;
                                        }
                                break;
                        }
                        }
                }
	//exit
        rcSource.top = 0;
        rcSource.left = 0;
        rcSource.bottom = 40;
        rcSource.right = 80;
        rcDest.top = (700)*SCREEN_HEIGHT/768;
        rcDest.left = (900)*SCREEN_WIDTH/1024;
        rcDest.bottom = rcDest.top+40*SCREEN_HEIGHT/768;
        rcDest.right = rcDest.left+80*SCREEN_WIDTH/1024;
        if((mousex<rcDest.right)&&(mousex>rcDest.left)&&(mousey>rcDest.top)&&(mousey<rcDest.bottom))
        {
                //key is pressed countinuosly
                if (mousestate.rgbButtons[0]){
                        rcSource.top = 40;
                        rcSource.bottom = 80;
                }
                //key is pressed one time
                if ((mousestate2.rgbButtons[0])&&(!mousestate.rgbButtons[0])){
                        SndObjPlay(voices[1], DSBPLAY_LOOPING,options[1]&&SOUNDS_LOADED);
                        gamephase=0;
                        gamephase2=0;
                }
        }
        taka->Blt(&rcDest, pictures[3], &rcSource, 0, NULL);

	//load
        rcSource.top = 0;
        rcSource.left = 160;
        rcSource.bottom = 40;
        rcSource.right = 240;
        rcDest.top = (40)*SCREEN_HEIGHT/768;
        rcDest.left = (800)*SCREEN_WIDTH/1024;
        rcDest.bottom = rcDest.top+40*SCREEN_HEIGHT/768;
        rcDest.right = rcDest.left+80*SCREEN_WIDTH/1024;
        if((mousex<rcDest.right)&&(mousex>rcDest.left)&&(mousey>rcDest.top)&&(mousey<rcDest.bottom))
        {
                //key is pressed countinuosly
                if (mousestate.rgbButtons[0]){
                        rcSource.top = 40;
                        rcSource.bottom = 80;
                }
                //key is pressed one time
                if ((mousestate2.rgbButtons[0])&&(!mousestate.rgbButtons[0])){
                        readsaves();//read saves
                        gamephase=4;
                        gamephase2=1;
                        gamephase_old=2;
                }
        }
        taka->Blt(&rcDest, pictures[3], &rcSource, 0, NULL);

	//save
        rcSource.top = 0;
        rcSource.left = 80;
        rcSource.bottom = 40;
        rcSource.right = 160;
        rcDest.top = (40)*SCREEN_HEIGHT/768;
        rcDest.left = (900)*SCREEN_WIDTH/1024;
        rcDest.bottom = rcDest.top+40*SCREEN_HEIGHT/768;
        rcDest.right = rcDest.left+80*SCREEN_WIDTH/1024;
        if((mousex<rcDest.right)&&(mousex>rcDest.left)&&(mousey>rcDest.top)&&(mousey<rcDest.bottom))
        {
                //key is pressed continuosly
                if (mousestate.rgbButtons[0]){
                        rcSource.top = 40;
                        rcSource.bottom = 80;
                }
                //key is pressed one time
                if ((mousestate2.rgbButtons[0])&&(!mousestate.rgbButtons[0])){
                        readsaves();//read saves
                        gamephase2=2;
                        gamephase=4;
                        is_saved=false;
                        gamephase_old=2;
                }
        }
        taka->Blt(&rcDest, pictures[3], &rcSource, 0, NULL);

	//mouse
        loota.left  =0;
        loota.right =25;
        loota.top   =0;
        loota.bottom=25;

        if(int(mousex)+11>SCREEN_WIDTH)
                loota.right=SCREEN_WIDTH-int(mousex);
        if(int(mousey)+19>SCREEN_HEIGHT)
                loota.bottom=SCREEN_HEIGHT-int(mousey);

        taka->BltFast(
                        int(mousex)
                        ,int(mousey)
                        ,pictures[1],
                        &loota,
                        DDBLTFAST_SRCCOLORKEY);

	//calculate weapon properties
	for (b=0; b<4; b++){
		ase[moped[0].ase[b]].damage=ase[moped[0].ase[b]].pdamage*0.1f+(ase[moped[0].ase[b]].pdamage-1)*0.7f;
		ase[moped[0].ase[b]].speed=ase[moped[0].ase[b]].pspeed*3.7f+(ase[moped[0].ase[b]].pspeed-1)*1.44f;
		ase[moped[0].ase[b]].bullets_per_shot=1;
		ase[moped[0].ase[b]]._type=0;
		ase[moped[0].ase[b]].dispersion=0.01f+ase[moped[0].ase[b]].prate_of_fire*0.01f;
		nop=(float)ase[moped[0].ase[b]].prate_of_fire;
		if((ase[moped[0].ase[b]].prate_of_fire>5)&&(ase[moped[0].ase[b]].prate_of_fire)<8){ase[moped[0].ase[b]]._type=2; nop=2;ase[moped[0].ase[b]].bullets_per_shot=(int)(7*(ase[moped[0].ase[b]].prate_of_fire-3));ase[moped[0].ase[b]].damage=ase[moped[0].ase[b]].damage/20;ase[moped[0].ase[b]].dispersion=ase[moped[0].ase[b]].dispersion*4;}
		if(ase[moped[0].ase[b]].prate_of_fire>7)ase[moped[0].ase[b]]._type=1;

		//if((ase[moped[0].ase[b]].prate_of_fire>3)&&(ase[moped[0].ase[b]].prate_of_fire)<8){ase[b]._type=2; nop=(float)ase[moped[0].ase[b]].prate_of_fire/(5*(8-ase[moped[0].ase[b]].prate_of_fire));ase[moped[0].ase[b]].bullets_per_shot=(int)(5*(8-ase[moped[0].ase[b]].prate_of_fire));}
		ase[moped[0].ase[b]].rate_of_fire=(int)(710+78-nop*78);

		ase[moped[0].ase[b]].smoke_filled=0;
		if(ase[moped[0].ase[b]].homing){
			//ase[moped[0].ase[b]].num_bounces=0;
			ase[moped[0].ase[b]].smoke_filled=2;
			ase[moped[0].ase[b]].smoke_count=10;
		}
		else {
			ase[moped[0].ase[b]].num_bounces=ase[moped[0].ase[b]].pdamage;
			ase[moped[0].ase[b]].smoke_count=0;
		}
		ase[moped[0].ase[b]].weight=ase[moped[0].ase[b]].pdamage*0.00001f;
		ase[moped[0].ase[b]].explosion_size=0;
		ase[moped[0].ase[b]].decal_picture=0;
		if(ase[moped[0].ase[b]].pdamage>6){
			ase[moped[0].ase[b]]._type=3;
			ase[moped[0].ase[b]].num_bounces=0;
			ase[moped[0].ase[b]].explosion_size=ase[moped[0].ase[b]].pdamage-6;
			ase[moped[0].ase[b]].smoke_filled=2;
			ase[moped[0].ase[b]].smoke_duration=1000;
			ase[moped[0].ase[b]].decal_picture=1;
		}
		ase[moped[0].ase[b]].smoke_size=ase[moped[0].ase[b]].pdamage*0.1f;


	}


	moped[0].korjaamolla2=moped[0].korjaamolla;


}

void readkey_game(void){

	//mopep control
	moped[0].enter2=moped[0].enter;
	moped[0].esc2=moped[0].esc;
	moped[0].up2=moped[0].up;
	moped[0].down2=moped[0].down;
	moped[0].left2=moped[0].left;
	moped[0].right2=moped[0].right;
	moped[0].one2=moped[0].one;
	moped[0].two2=moped[0].two;
	moped[0].three2=moped[0].three;
	moped[0].four2=moped[0].four;
	moped[0].space2=moped[0].space;
	mapmode2=mapmode;

	moped[0].enter=false;
	moped[0].esc=false;
	moped[0].up=false;
	moped[0].down=false;
	moped[0].left=false;
	moped[0].right=false;
	moped[0].one=false;
	moped[0].two=false;
	moped[0].three=false;
	moped[0].four=false;
	moped[0].space=false;


	if (KEYDOWN(buffer, DIK_RETURN))
		moped[0].enter=true;
	if (KEYDOWN(buffer, DIK_ESCAPE))
		moped[0].esc=true;
	/*if (KEYDOWN(buffer, DIK_UP))
          moped[0].up=true;
          if (KEYDOWN(buffer, DIK_DOWN))
          moped[0].down=true;
          if (KEYDOWN(buffer, DIK_LEFT))
          moped[0].left=true;
          if (KEYDOWN(buffer, DIK_RIGHT))
          moped[0].right=true;
          if (KEYDOWN(buffer, DIK_1))
          moped[0].one=true;
          if (KEYDOWN(buffer, DIK_2))
          moped[0].two=true;
          if (KEYDOWN(buffer, DIK_3))
          moped[0].three=true;
          if (KEYDOWN(buffer, DIK_4))
          moped[0].four=true;
          if (KEYDOWN(buffer, DIK_SPACE))
          moped[0].space=true;
	*/
	if (buffer[key[1]]& 0x80)
		moped[0].up=true;
	if (buffer[key[2]]& 0x80)
		moped[0].down=true;
	if (buffer[key[3]]& 0x80)
		moped[0].left=true;
	if (buffer[key[4]]& 0x80)
		moped[0].right=true;
	if (buffer[key[5]]& 0x80)
		moped[0].one=true;
	if (buffer[key[6]]& 0x80)
		moped[0].two=true;
	if (buffer[key[7]]& 0x80)
		moped[0].three=true;
	if (buffer[key[8]]& 0x80)
		moped[0].four=true;
	if (buffer[key[11]]& 0x80)
		moped[0].space=true;

        //skip demo by pressing enter
        if (!KEYDOWN(buffer,  DIK_RETURN )&&KEYDOWN(buffer2,  DIK_RETURN)){
                if(gamephase2==3)gamephase2=4;
                else if(gamephase2==4)gamephase2=0;
                if(gamephase2==5){gamephase2=0; gamephase=4;}
                if(gamephase2==1){gamephase2=0; gamephase=4;}

        }

        //pause by pressing esc
        if (!KEYDOWN(buffer,  DIK_ESCAPE )&&KEYDOWN(buffer2,  DIK_ESCAPE))
        {
                if (gamephase2==0) gamephase2=2;
                else if (gamephase2==2) gamephase2=0;
                if (gamephase2==3) gamephase2=0;
                if (gamephase2==4) gamephase2=0;
        }

        //exit
        if (!KEYDOWN(buffer,  DIK_F9 )&&KEYDOWN(buffer2,  DIK_F9))
        {
                gamephase=4;
                gamephase2=0;
                //SendMessage( hWnd, WM_CLOSE, 0, 0 );
        }

        //slow the game down
        if (buffer[key[9]]& 0x80)
        {
                if(gamespeed>0.2f)
                        gamespeed=gamespeed-0.5f*0.01f*elapsed;
        }
        else
                if(gamespeed<0.9f+0.1f*game_difficulty)
                        gamespeed=gamespeed+0.5f*0.01f*elapsed;

        if(gamespeed>0.9f+0.1f*game_difficulty)
                gamespeed=0.9f+0.1f*game_difficulty;
        if(gamespeed<0.2f)
                gamespeed=0.2f;

        //changching camera mode
        if (buffer[key[10]]& 0x80)
                if (!(buffer2[key[10]]& 0x80))
                {
                        if(!mapmode)mapmode=true;
                        else mapmode=false;
                }

        //controlling camera
        float MOTION_SPEED=0.1f;//camera speed
        if (KEYDOWN(buffer,  DIK_END))
        {
                dy=dy-MOTION_SPEED*elapsed;
                if (dy<=-5) dy=-5;
        }
        if (KEYDOWN(buffer,  DIK_HOME))
        {
                dy=dy+MOTION_SPEED*elapsed;
                if (dy>=43) dy=43;
        }
        if (KEYDOWN(buffer,  DIK_DELETE))
        {
                dx=dx-MOTION_SPEED*elapsed;
        }
        if (KEYDOWN(buffer,  DIK_NEXT))
        {
                dx=dx+MOTION_SPEED*elapsed;
        }




        //when getting in menu play music
        if(gamephase==4){

                SndObjStop(voices[1]);
        }
}

void readsaves(void){ // read saves
	int		i;
	char	name[256];
	FILE	*f;

	for (i=0 ; i<10 ; i++)
	{
		//strcpy (m_filenames[i], "--- Unused Slot ---");
		strcpy (m_filenames[i], " -Unused-");
		loadable[i] = false;
		sprintf (name, "save/s%i.sav", i);
		f = fopen (name, "r");
		if (!f)
			continue;
		stripped_fgets(name,sizeof(name),f);
		strcpy (m_filenames[i], name);
		loadable[i] = true;
		stripped_fgets(name,sizeof(name),f);
		letters_in_file_names[i]=atoi(name);
		fclose (f);
	}
}
void game_load(void){//load game
	FILE *fil;
        int q,d,a,b;
        char temprow[300];
        char tallennusrow[300];
        float kx,kz;

        if(!loadable[savegame_slot]) return;//exit if not right

        itoa(savegame_slot,temprow,10);
        strcpy(tallennusrow,"save/s");
        strcat(tallennusrow,temprow);
        strcat(tallennusrow,".sav");


        fil = fopen(tallennusrow,"rb");



        game_new();
        repair_cost=0;
        moped[0].korjaamolla2=false;
        moped[0].korjaamolla=true;
        gamephase2=0;
        gamephase=2;


        //stripped_fgets(temprow,sizeof(temprow),fil);//temprow
        //fgets(temprow,sizeof(temprow),fil);nextmatsi=atoi(temprow);

        //name
        fgets(temprow,sizeof(temprow),fil);
        fgets(temprow,sizeof(temprow),fil);

        //diffucultylevel
        fgets(temprow,sizeof(temprow),fil); game_difficulty=atoi(temprow);
        //weapons change accordin to diffucultylevel
        q=10;
        //police gun 0 pistol
        if(game_difficulty==0) ase[q].damage=3.5f;
        if(game_difficulty==1) ase[q].damage=4.5f;
        if(game_difficulty==2) ase[q].damage=5.5f;
        ase[q]._type=0;

        q=11;
        //police gun 1 machinegun
        if(game_difficulty==0) ase[q].damage=0.5f;
        if(game_difficulty==1) ase[q].damage=0.8f;
        if(game_difficulty==2) ase[q].damage=1.1f;
        ase[q]._type=1;

        q=12;
        //police gun 2 missile
        if(game_difficulty==0) ase[q].damage=5;
        if(game_difficulty==1) ase[q].damage=7;
        if(game_difficulty==2) ase[q].damage=10;
        ase[q]._type=3;

        //field
        fgets(temprow,sizeof(temprow),fil); mapsx=atoi(temprow);
        fgets(temprow,sizeof(temprow),fil); mapsz=atoi(temprow);
        for (a=0; a<mapsz; a++){
                for (b=0; b<mapsx; b++){
                        fgets(temprow,sizeof(temprow),fil); maps[a][b]=atoi(temprow);
                }
        }
        //dont randomize characters until fiel is randomized
        characters=1000;
        moped[0].x1=-10000;//moped is not noticed while randomizing character locations
        moped[0].z1=-10000;
        for (q=0; q<1000; q++){
                create_character(q);
        }
        //frontwheel coordinates
        fgets(temprow,sizeof(temprow),fil); moped[0].x1=(float)atof(temprow);
        fgets(temprow,sizeof(temprow),fil); moped[0].z1=(float)atof(temprow);

        //rearwheel
        fgets(temprow,sizeof(temprow),fil); moped[0].x2=(float)atof(temprow);
        fgets(temprow,sizeof(temprow),fil); moped[0].z2=(float)atof(temprow);
        //direction
        fgets(temprow,sizeof(temprow),fil); moped[0].direction=(float)atof(temprow);
        //ammount of money
        fgets(temprow,sizeof(temprow),fil); moped[0].money=atoi(temprow);
        //weapon properties
        for (q=0; q<4; q++){
                fgets(temprow,sizeof(temprow),fil); ase[moped[0].ase[q]].pdamage=atoi(temprow);
                fgets(temprow,sizeof(temprow),fil); ase[moped[0].ase[q]].pspeed=atoi(temprow);
                fgets(temprow,sizeof(temprow),fil); ase[moped[0].ase[q]].prate_of_fire=atoi(temprow);
                fgets(temprow,sizeof(temprow),fil);
                if(atoi(temprow)==0) ase[moped[0].ase[q]].homing=false;
                else ase[moped[0].ase[q]].homing=true;
        }
        //energy
        fgets(temprow,sizeof(temprow),fil); moped[0].energy=(float)atof(temprow);
        //what level missions are given
        fgets(temprow,sizeof(temprow),fil); moped[0].level=atoi(temprow);
        //what mission from this level has been given
        fgets(temprow,sizeof(temprow),fil); moped[0].missionumero=atoi(temprow);
	//mission
        create_mission(&moped[0],moped[0].missionumero);
        moped[0].mission=moped[0].mission_random;
        //how many similiar targets

        fgets(temprow,sizeof(temprow),fil); moped[0].mission.kohteita=atoi(temprow);
        //targets coordinates
        for (q=0; q<moped[0].mission.kohteita; q++){
                fgets(temprow,sizeof(temprow),fil); kx=(float)atof(temprow);
                fgets(temprow,sizeof(temprow),fil); kz=(float)atof(temprow);
                if(moped[0].mission.target_type==0)//character
                {
                        character[moped[0].mission.target[q]].x=kx;
                        character[moped[0].mission.target[q]].z=kz;
                }
                if(moped[0].mission.target_type==1)//coordinates
                {
                        moped[0].mission.targetx[q]=kx;
                        moped[0].mission.targetz[q]=kz;
                }
                if(moped[0].mission.target_type==2)//moped
                {
                        moped[moped[0].mission.target[q]].x1=kx;
                        moped[moped[0].mission.target[q]].z1=kz;
                }
        }
        //is it accomplished
        fgets(temprow,sizeof(temprow),fil); moped[0].mission.status=atoi(temprow);
        //time
        fgets(temprow,sizeof(temprow),fil); moped[0].mission.timer=(float)atof(temprow);

	//customer
        create_character(10);
        moped[0].mission.asiakas[0]=character[10];
        //what picture on character
        fgets(temprow,sizeof(temprow),fil); moped[0].mission.asiakas[0].picture=atoi(temprow);
        //energy
        fgets(temprow,sizeof(temprow),fil); moped[0].mission.asiakas[0].energy=(float)atof(temprow);

        fclose(fil);

        for (d=0; d<num_mopeds; d++){
                if(moped[d].inactive)continue;
                aja(&moped[d]);
        }


}
void game_save(void){//save game

        FILE *fil;
        int q,a,b;
        is_saved=true;
        char temprow[300];
        char tallennusrow[300];
        float kx,kz;

        itoa(savegame_slot,temprow,10);
        strcpy(tallennusrow,"save/s");
        strcat(tallennusrow,temprow);
        strcat(tallennusrow,".sav");

        repair_cost=0;


        fil = fopen(tallennusrow,"wb");

        if(letters_in_name==0)
		strcpy(temprow,"no name");
        else
		strcpy(temprow,savefilename);

        //name
        fprintf(fil, "%s\n", temprow);
        fprintf(fil, "%d\n", letters_in_name);
        //diffyculty
        fprintf(fil, "%d\n", game_difficulty);
        //field
        fprintf(fil, "%d\n", mapsx);
        fprintf(fil, "%d\n", mapsz);
        for (a=0; a<mapsz; a++){
                for (b=0; b<mapsx; b++){
                        fprintf(fil, "%d\n", maps[a][b]);
                }
        }
        //frontwheel coordinates
        fprintf(fil, "%f\n", moped[0].x1);
        fprintf(fil, "%f\n", moped[0].z1);
        //rearwheel
        fprintf(fil, "%f\n", moped[0].x2);
        fprintf(fil, "%f\n", moped[0].z2);
        //direction
        fprintf(fil, "%f\n", moped[0].direction);
        //ammount of money
        fprintf(fil, "%d\n", moped[0].money);
        //gun properties
        for (q=0; q<4; q++){
                fprintf(fil, "%d\n", ase[moped[0].ase[q]].pdamage);
                fprintf(fil, "%d\n", ase[moped[0].ase[q]].pspeed);
                fprintf(fil, "%d\n", ase[moped[0].ase[q]].prate_of_fire);
                fprintf(fil, "%d\n", ase[moped[0].ase[q]].homing);
        }
        //energy
        fprintf(fil, "%f\n", moped[0].energy);
        //level of missions that will be given.
        fprintf(fil, "%d\n", moped[0].level);
        //what mission from this level has been given
        fprintf(fil, "%d\n", moped[0].missionumero);
	//mission
        //ammount of similiar targets
        fprintf(fil, "%d\n", moped[0].mission.kohteita);
        //targets coordinates
        for (q=0; q<moped[0].mission.kohteita; q++){
                if(moped[0].mission.target_type==0)//characters
                {
                        kx=character[moped[0].mission.target[q]].x;
                        kz=character[moped[0].mission.target[q]].z;
                }
                if(moped[0].mission.target_type==1)//coordinates
                {
                        kx=moped[0].mission.targetx[q];
                        kz=moped[0].mission.targetz[q];
                }
                if(moped[0].mission.target_type==2)//moped
                {
                        kx=moped[moped[0].mission.target[q]].x1;
                        kz=moped[moped[0].mission.target[q]].z1;
                }
                fprintf(fil, "%f\n", kx);
                fprintf(fil, "%f\n", kz);
        }
        //is it accomplished?
        fprintf(fil, "%d\n", moped[0].mission.status);
        //time
        fprintf(fil, "%f\n", moped[0].mission.timer);
	//customer
        //what picture on character
        fprintf(fil, "%d\n", moped[0].mission.asiakas[0].picture);
        //energy
        fprintf(fil, "%f\n", moped[0].mission.asiakas[0].energy);

/*		float x1,z1;//front wheel coordinates
		float x2,z2;//rear wheel
		int money;//ammount of money left
		float energy;//energy
		int level;//level of missions that will be given.
		int missionumero;//what mission from this level has been given

		int kohteita;//ammount of similiar targets
		int target[100];//possible target (kill some one?)
		float targetx[100], targetz[100];//targets coordinates (go to location x?)
		float timer;//time
		int status;//0=not accomplished 1=accomplished2=failed 3=there is no mission


		//person asiakas[100];//as a passanger in a taxi
                int picture;//what picture is on character
                int weapon_idx;//wich weapon does it have -1=no weapon
                float energy;//energy
                int tactics;//what will it do. 0=pursues 1=walks normally 2=escapes
                int movement_type;//0=friend 1=passive 2=enemy
*/

        fclose(fil);
}
void render_menu(void){//renders the menu
        RECT     rcSource, rcDest, loota;
	char menuteksti[40][256];
	char row[200],temprow[200];
	int tex,tey;
	int q;
	int space;

	gamespeed=1;
	quake=0;
	m_pDevice->LightEnable(0, FALSE);
	m_pDevice->SetRenderState( D3DRENDERSTATE_AMBIENT, 0xFFFFFFFF);
	m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,FALSE);


	//m_pDevice->GetRenderTarget(&taka);




	//cusor
	cursor_timer=cursor_timer-elapsed;
	if(cursor_timer<-500)cursor_timer=500;


	//wallpaper
	rcSource.top = 0;
	rcSource.left = 0;
	rcSource.bottom = 768;
	rcSource.right = 1024;
	rcDest.top = 0;
	rcDest.left = 0;
	rcDest.bottom = SCREEN_HEIGHT;
	rcDest.right = SCREEN_WIDTH;

	taka->Blt(&rcDest, pictures[4], &rcSource, 0,NULL);

	rendertext(340,738,0,"game version 1.21");


	if(gamephase2==0){//headmenu
		space=40;
		strcpy(menuteksti[0],"New Game");
		strcpy(menuteksti[1],"Load Game");
		strcpy(menuteksti[2],"Options");
		strcpy(menuteksti[3],"Exit");
	}
	if((gamephase2==1)||(gamephase2==2)||(gamephase2==3)){//load and save
		space=20;
		strcpy(menuteksti[0]," ");
		strcpy(menuteksti[11]," ");
		strcpy(menuteksti[12],"Back");
		for (q=0; q<10; q++){
			strcpy(menuteksti[q+1],m_filenames[q]);
			//menuteksti[q]=savefilename[q]
		}
	}
	if(gamephase2==4){//options
		space=20;
		strcpy(menuteksti[0]," ");
		strcpy(menuteksti[1],"Sounds");
		if(options[1]&&!SOUNDS_ON)strcpy(menuteksti[1],"Sounds  unable to play");//if sounds cannot be played
		strcpy(menuteksti[2]," ");
		strcpy(menuteksti[3]," ");
		strcpy(menuteksti[4]," ");
		strcpy(menuteksti[5]," ");
		strcpy(menuteksti[6]," ");
		strcpy(menuteksti[7]," ");
		strcpy(menuteksti[8]," ");
		strcpy(menuteksti[9]," ");
		strcpy(menuteksti[10]," ");
		strcpy(menuteksti[11],"Set Keys");
		strcpy(menuteksti[12],"Back");
	}
	if(gamephase2==5){//new game
		space=40;
		strcpy(menuteksti[0],"Easy");
		strcpy(menuteksti[1],"Normal");
		strcpy(menuteksti[2],"Hard");
		strcpy(menuteksti[3],"Back");
	}
	if(gamephase2==6){//set keys
		space=20;
                strcpy(menuteksti[0]," ");
                strcpy(menuteksti[1],"Up           ");
                strcpy(menuteksti[2],"Down         ");
                strcpy(menuteksti[3],"Left         ");
                strcpy(menuteksti[4],"Right        ");
                strcpy(menuteksti[5],"Shoot 1      ");
                strcpy(menuteksti[6],"Shoot 2      ");
                strcpy(menuteksti[7],"Shoot 3      ");
                strcpy(menuteksti[8],"Shoot 4      ");
                strcpy(menuteksti[9],"Slow´Mo      ");
		strcpy(menuteksti[10],"Chance View  ");
		strcpy(menuteksti[11],"Hand Brake   ");
		strcpy(menuteksti[12],"Back");
		for (q=1; q<12; q++){
			itoa(key[q],temprow,10);
			strcat(menuteksti[q],temprow);
		}
	}



        tex=270;tey=220+0*space;
        if(gamephase2==1)strcpy(row,"Load");
        if(gamephase2==2){
                if(!is_saved)
                        strcpy(row,"Save");
                else
                        strcpy(row,"Game saved");
        }
        if(gamephase2==3){
                strcpy(row,"Enter a name");
                strcpy(menuteksti[menu_selection],savefilename);
        }
        if(gamephase2==4)strcpy(row,"Options");
        if(gamephase2==6)strcpy(row,"Set Keys");

        if((gamephase2==1)||(gamephase2==2)||(gamephase2==3)||(gamephase2==4)||(gamephase2==6))
                rendertext((int)(tex),(int)(tey),0,row);




	//menu_selection=-1;

	for (q=0; q<menuja[gamephase2]; q++){
		rendertext(210,220+q*space,0,menuteksti[q]);
		rcDest.top = (210+q*space)*SCREEN_HEIGHT/768;
		rcDest.left = (205)*SCREEN_WIDTH/1024;
		rcDest.bottom = rcDest.top+space*SCREEN_HEIGHT/768;
		rcDest.right = rcDest.left+230*SCREEN_WIDTH/1024;
		//thing selected while saving cannot be changed.
		if((gamephase2!=3)&&((gamephase2!=6)||(is_selected==false)))
                        if((mousex<rcDest.right)&&(mousex>rcDest.left)&&(mousey>rcDest.top)&&(mousey<rcDest.bottom)){
                                menu_selection=q;
                        }

		if((q==menu_selection)&&((gamephase2!=4)||(q>10)))
			rendertext(210,220+q*space,0,menuteksti[q]);
		if(((q<10)&&(q>0))&&((gamephase2==4)&&(options[q])))
			rendertext(210,220+q*space,0,menuteksti[q]);

                //cursor
		if((menu_selection<11)&&(menu_selection>0))
		{
                        if((gamephase2==3)&&(menu_selection==q)&&(cursor_timer<0)&&(letters_in_name<49))
				rendertext(int(210+(letters_in_name)*12.5f),(220+q*space),0,":");
		}
	}





	//render moped
        //set camera to its place
        float kamerax1=0;
        float kameray1=1.6f*100;
        float kameraz1=2000;
        float kamerax2=kamerax1;
        float kameray2=kameray1-1.05f*1000;
        float kameraz2=0;

        m_View = ViewMatrix(D3DVECTOR(kamerax1,kameray1,kameraz1), D3DVECTOR(kamerax2,kameray2,kameraz2), D3DVECTOR(0,1,0), 0);
        m_pDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &m_View);


        lights[1].valo.dltType = D3DLIGHT_POINT;
        lights[1].valo.dcvDiffuse.r = 1.0f;
        lights[1].valo.dcvDiffuse.g = 1.0f;
        lights[1].valo.dcvDiffuse.b = 1.0f;
        lights[1].valo.dcvAmbient.r = 1.0f;
        lights[1].valo.dcvAmbient.g = 1.0f;
        lights[1].valo.dcvAmbient.b = 1.0f;
        lights[1].valo.dcvSpecular.r = 1.0f;
        lights[1].valo.dcvSpecular.g = 1.0f;
        lights[1].valo.dcvSpecular.b = 1.0f;
        lights[1].valo.dvDirection=D3DVECTOR(1.0f);
        lights[1].valo.dvPosition.x = 0;
        lights[1].valo.dvPosition.y = 0;
        lights[1].valo.dvPosition.z = 0;
        lights[1].valo.dvAttenuation0 = 0.5f;
        lights[1].valo.dvAttenuation1=0.0f;
        lights[1].valo.dvAttenuation2=0.0f;
        lights[1].valo.dvRange = 500;
        m_pDevice->LightEnable(1, TRUE);
        m_pDevice->SetLight(1, &lights[1].valo);


        int mopopicture=6;
        int d=7;
        moped[d].x2=0;
        moped[d].y2=0;
        moped[d].z2=0;
        moped[d].direction=moped[d].direction+0.002f*elapsed*gamespeed;
        moped[d].angle_roll=0;
        moped[d].angle_pitch=0;


        if(mopopicture==0){
                matrices->LoadIdentity();
                matrices->TranslateLocal(moped[d].x2,moped[d].y2,moped[d].z2);
                matrices->RotateYawPitchRollLocal(-moped[d].direction,moped[d].angle_roll,moped[d].angle_pitch);
                drawfast(&mallit[mopopicture].malli[0]);
        }
        if(mopopicture==6){
                matrices->LoadIdentity();
                matrices->TranslateLocal(moped[d].x2,moped[d].y2+1.5f,moped[d].z2);
                matrices->RotateYawPitchRollLocal(-moped[d].direction,moped[d].angle_roll,moped[d].angle_pitch);
                drawfast(&mallit[mopopicture].malli[0]);
        }
        if(mopopicture==9){
                matrices->LoadIdentity();
                matrices->TranslateLocal(moped[d].x2,moped[d].y2+1.5f,moped[d].z2);
                matrices->RotateYawPitchRollLocal(-moped[d].direction,moped[d].angle_roll,moped[d].angle_pitch);
                drawfast(&mallit[mopopicture].malli[0]);
        }

	if(mopopicture==0){
		//rear wheel
		matrices->Push();
		matrices->TranslateLocal(0,20,0);
		matrices->RotateYawPitchRollLocal(0,0,moped[d].angle_yaw);
		drawfast(&mallit[mopopicture].malli[3]);
		matrices->Pop();
		//front side
		matrices->TranslateLocal(70,0,0);
		//matrices->RotateYawPitchRollLocal(-moped[d].direction,0,0);
		matrices->RotateYawPitchRollLocal(-moped[d].etudirection,0,0);
		drawfast(&mallit[mopopicture].malli[2]);
		//front wheel
		matrices->TranslateLocal(40,20,0);
		matrices->RotateYawPitchRollLocal(0,0,moped[d].angle_yaw);
		drawfast(&mallit[mopopicture].malli[3]);
	}
	if(mopopicture==6){
		//rear wheel
		matrices->Push();
		matrices->TranslateLocal(0,20,0);
		matrices->RotateYawPitchRollLocal(0,0,moped[d].angle_yaw);
		drawfast(&mallit[mopopicture].malli[2]);
		matrices->Pop();
		//front side
		matrices->TranslateLocal(79,0,0);
		matrices->RotateYawPitchRollLocal(-moped[d].etudirection,0,0);
		drawfast(&mallit[mopopicture].malli[1]);
		//front wheel
		matrices->TranslateLocal(40,20,0);
		matrices->RotateYawPitchRollLocal(0,0,moped[d].angle_yaw);
		drawfast(&mallit[mopopicture].malli[2]);
	}
	if(mopopicture==9){
		//rear wheel
		matrices->Push();
		matrices->TranslateLocal(0,20,0);
		matrices->RotateYawPitchRollLocal(0,0,moped[d].angle_yaw);
		drawfast(&mallit[mopopicture].malli[2]);
		matrices->Pop();
		//front side
		matrices->TranslateLocal(79,0,0);
		matrices->RotateYawPitchRollLocal(-moped[d].etudirection,0,0);
		drawfast(&mallit[mopopicture].malli[1]);
		//front wheel
		matrices->TranslateLocal(40,20,0);
		matrices->RotateYawPitchRollLocal(0,0,moped[d].angle_yaw);
		drawfast(&mallit[mopopicture].malli[2]);
	}

	m_pDevice->LightEnable(1, FALSE);




	//mouse
        loota.left  =0;
        loota.right =25;
        loota.top   =0;
        loota.bottom=25;

        if(int(mousex)+11>SCREEN_WIDTH)
                loota.right=SCREEN_WIDTH-int(mousex);
        if(int(mousey)+19>SCREEN_HEIGHT)
                loota.bottom=SCREEN_HEIGHT-int(mousey);

        taka->BltFast(
                        int(mousex)
                        ,int(mousey)
                        ,pictures[1],
                        &loota,
                        DDBLTFAST_SRCCOLORKEY);


}

void game_new(void){ //new game

	int a,b,d,q;
	float nop;



	SndObjPlay(voices[1], DSBPLAY_LOOPING,options[1]&&SOUNDS_LOADED);


	q=6;
	ase[q].picture=0;//moped gun 0
	ase[q].speed=45;
	ase[q].dispersion=0.2f;
	ase[q].rate_of_fire=711;
	ase[q].decal_picture=0;
	ase[q].bullet_picture=0;
	ase[q].smoke_filled=0;
	ase[q].smoke_duration=5000;
	ase[q].weight=0.00001f;
	ase[q].explosion_size=0;
	ase[q].smoke_count=0;
	ase[q].num_bounces=2;
	ase[q].damage=0.1f;
	ase[q].homing=false;
	ase[q].pdamage=2;
	ase[q].pspeed=2;
	ase[q].prate_of_fire=2;
	ase[q].bullets_per_shot=1;

	q=7;
	ase[q].picture=0;//moped gun1
	ase[q].speed=45;
	ase[q].dispersion=0.2f;
	ase[q].rate_of_fire=711;
	ase[q].decal_picture=0;
	ase[q].bullet_picture=0;
	ase[q].smoke_filled=0;
	ase[q].smoke_duration=5000;
	ase[q].weight=0.00001f;
	ase[q].explosion_size=0;
	ase[q].smoke_count=0;
	ase[q].num_bounces=2;
	ase[q].damage=0.1f;
	ase[q].homing=false;
	ase[q].pdamage=2;
	ase[q].pspeed=2;
	ase[q].prate_of_fire=2;
	ase[q].bullets_per_shot=1;

	q=8;
	ase[q].picture=0;//moped gun2
	ase[q].speed=45;
	ase[q].dispersion=0.2f;
	ase[q].rate_of_fire=711;
	ase[q].decal_picture=0;
	ase[q].bullet_picture=0;
	ase[q].smoke_filled=0;
	ase[q].smoke_duration=5000;
	ase[q].weight=0.00001f;
	ase[q].explosion_size=0;
	ase[q].smoke_count=0;
	ase[q].num_bounces=2;
	ase[q].damage=0.1f;
	ase[q].homing=false;
	ase[q].pdamage=2;
	ase[q].pspeed=2;
	ase[q].prate_of_fire=2;
	ase[q].bullets_per_shot=1;

	q=9;
	ase[q].picture=0;//moped gun3
	ase[q].speed=45;
	ase[q].dispersion=0.2f;
	ase[q].rate_of_fire=711;
	ase[q].decal_picture=0;
	ase[q].bullet_picture=0;
	ase[q].smoke_filled=0;
	ase[q].smoke_duration=5000;
	ase[q].weight=0.00001f;
	ase[q].explosion_size=0;
	ase[q].smoke_count=0;
	ase[q].num_bounces=2;
	ase[q].damage=0.1f;
	ase[q].homing=false;
	ase[q].pdamage=2;
	ase[q].pspeed=2;
	ase[q].prate_of_fire=2;
	ase[q].bullets_per_shot=1;



	//ramdomize map //before randomizing characters
	mapsz=12;
	mapsx=10;
	for (a=0; a<mapsz; a++){
		for (b=0; b<mapsx; b++){
			maps[a][b]=4;
			while((maps[a][b]==4)|(maps[a][b]==5))
                                maps[a][b]=randInt(0,objnum1);
		}
	}

	//atleast one house is a workshop
	maps[randInt(1,mapsz-1)][randInt(1,mapsx-1)]=6;

	//headquartes location //NOTE! this may have same coordinates as the only workshop that is generated.
	headquarter_posx=randInt(1,mapsz-1);
	headquarter_posz=randInt(1,mapsx-1);
	maps[headquarter_posx][headquarter_posz]=5;


	//map edges
	for (a=0; a<mapsz; a++) {maps[a][0]=4;maps[a][mapsx-1]=4;}
	for (a=0; a<mapsx; a++) {maps[0][a]=4;maps[mapsz-1][a]=4;}





	//generate characters
	characters=1000;
	moped[0].x1=-10000;//moped is not noticed while generating these places
	moped[0].z1=-10000;
	for (q=0; q<1000; q++){
		create_character(q);
	}



	//initialize mopeds
	num_mopeds=10;
	initMopeds();
	for (q=1; q<100; q++){
		moped[q].inactive=true;
	}

	quake=0;//at the beginning there will be no erthquakes
	mission_is_read=0;//read introduction
	mapmode=true;
	dx=0;//camera
	dy=13;//camera
	bullet_count=0;//at the beginning there will be not a single bullet
	smoke_count=0;




	gamespeed=1.0f;
	gamephase=0;

	for (d=0; d<num_mopeds; d++){
		if(moped[d].inactive)continue;
		aja(&moped[d]);
	}

	for (q=0; q<MAX_BULLETS; q++){
		bullet[q].remove=true;
	}
	for (q=0; q<MAX_SMOKES; q++){
		smokes[q].inactive=true;
	}

	//calculate gun properties
	for (b=0; b<12; b++){
		if((b==2)||(b==3)||(b==4))continue;//blood and sparks are not changed
		ase[b].damage=ase[b].pdamage*0.1f+(ase[b].pdamage-1)*0.7f;
		ase[b].speed=ase[b].pspeed*3.7f+(ase[b].pspeed-1)*1.44f;
		ase[b].bullets_per_shot=1;
		ase[b]._type=0;
		nop=(float)ase[b].prate_of_fire;
		//if((ase[b].prate_of_fire>3)&&(ase[b].prate_of_fire)<8){ase[b]._type=2; nop=(float)ase[b].prate_of_fire/(5*(8-ase[b].prate_of_fire));ase[b].bullets_per_shot=(int)(5*(8-ase[b].prate_of_fire));}
		if((ase[b].prate_of_fire>5)&&(ase[b].prate_of_fire)<8){ase[b]._type=2; nop=2;ase[b].bullets_per_shot=(int)(7*(ase[b].prate_of_fire-3));ase[b].damage=ase[b].damage/20;ase[b].dispersion=ase[b].dispersion*4;}
		if(ase[b].prate_of_fire>7)ase[b]._type=1;

		ase[b].rate_of_fire=(int)(710+78-nop*78);
		ase[b].dispersion=0.01f+ase[b].prate_of_fire*0.01f;
		ase[b].smoke_filled=0;
		if(ase[b].homing){
			//ase[b].num_bounces=0;
			ase[b].smoke_filled=2;
			ase[b].smoke_count=10;
		}
		else {
			ase[b].num_bounces=ase[b].pdamage;
			ase[b].smoke_count=0;
		}
		ase[b].weight=ase[b].pdamage*0.00001f;
		ase[b].explosion_size=0;
		ase[b].decal_picture=0;
		if(ase[b].pdamage>6){
			ase[b]._type=3;
			ase[b].num_bounces=0;
			ase[b].explosion_size=ase[b].pdamage-6;
			ase[b].smoke_filled=2;
			ase[b].smoke_duration=1000;
			ase[b].decal_picture=1;
		}
		ase[b].smoke_size=ase[b].pdamage*0.1f;
	}

	//guns changed by diffyculty level
	q=10;
	//police gun 0 pistol
	if(game_difficulty==0) ase[q].damage=3.5f;
	if(game_difficulty==1) ase[q].damage=4.5f;
	if(game_difficulty==2) ase[q].damage=5.5f;
	ase[q]._type=0;

	q=11;
	//police gun 1 machinegun
	if(game_difficulty==0) ase[q].damage=0.5f;
	if(game_difficulty==1) ase[q].damage=0.8f;
	if(game_difficulty==2) ase[q].damage=1.1f;
	ase[q]._type=1;

	q=12;
	//police gun 2 missile
	if(game_difficulty==0) ase[q].damage=5;
	if(game_difficulty==1) ase[q].damage=7;
	if(game_difficulty==2) ase[q].damage=10;
	ase[q]._type=3;



	//light bulb is connected
	m_pDevice->LightEnable(0, TRUE);

	//render one screen before beginning demo
	gamephase2=0;
	render_game();
	gamephase2=3;



}
void sounds_start(){
        std::cout << "initializing sound" << std::endl;

	//sounds
	if((!options[1])&&(!options[2])){return;}

	//if((options[1])||(options[2]))
        if(!SOUNDS_LOADED){
                if(DirectSoundCreate(NULL, &lpDS, NULL)!=DS_OK){SOUNDS_ON=false;return;}

        }
	if(SOUNDS_ON){
		if(!SOUNDS_LOADED){
			IDirectSound_SetCooperativeLevel( lpDS,hWnd, DSSCL_PRIORITY);

			/*
                          DSBUFFERDESC dsBD = {0};
                          dsBD.dwSize = sizeof(dsBD);
                          dsBD.dwFlags = DSBCAPS_STATIC | DSBCAPS_CTRLVOLUME | DSBCAPS_GETCURRENTPOSITION2;


                          IDirectSound_CreateSoundBuffer(lpDS,&dsBD,&pDSB,NULL);
			*/
		}

		if((options[1])&&(!SOUNDS_LOADED)){
			voices[0]=SndObjCreate(lpDS, "#140", 1);//menu1 //remember SAMPLE_NUMBER
			voices[1]=SndObjCreate(lpDS, "#145", 1);//motor
			voices[2]=SndObjCreate(lpDS, "#146", 4);//pistol
			voices[3]=SndObjCreate(lpDS, "#147", 3);//bazooka
			voices[4]=SndObjCreate(lpDS, "#148", 2);//shotgun
			voices[5]=SndObjCreate(lpDS, "#149", 5);//machinegun
			voices[6]=SndObjCreate(lpDS, "#150", 1);//wall1
			voices[7]=SndObjCreate(lpDS, "#151", 1);//wall2
			voices[8]=SndObjCreate(lpDS, "#152", 2);//explosion
			voices[9]=SndObjCreate(lpDS, "#153", 2);//bounce1
			voices[10]=SndObjCreate(lpDS, "#154", 2);//bounce2
			voices[11]=SndObjCreate(lpDS, "#155", 2);//bounce3
			voices[12]=SndObjCreate(lpDS, "#156", 2);//bounce4
			voices[13]=SndObjCreate(lpDS, "#157", 2);//die0
			voices[14]=SndObjCreate(lpDS, "#158", 2);//die1
			voices[15]=SndObjCreate(lpDS, "#159", 2);//die2
			voices[16]=SndObjCreate(lpDS, "#160", 2);//die3
			voices[17]=SndObjCreate(lpDS, "#161", 2);//die4
			voices[18]=SndObjCreate(lpDS, "#162", 2);//upgrade
			voices[19]=SndObjCreate(lpDS, "#163", 2);//downgrade
			/*voices[1]=SndObjCreate(lpDS, "#143", 1);
                          voices[2]=SndObjCreate(lpDS, "#144", 1);
                          voices[3]=SndObjCreate(lpDS, "#145", 1);
                          voices[4]=SndObjCreate(lpDS, "#146", 1);//meat
                          voices[5]=SndObjCreate(lpDS, "#147", 1);
                          voices[6]=SndObjCreate(lpDS, "#148", 1);
                          voices[7]=SndObjCreate(lpDS, "#149", 1);
                          voices[8]=SndObjCreate(lpDS, "#150", 1);
                          voices[9]=SndObjCreate(lpDS, "#151", 2);//cloth
                          voices[10]=SndObjCreate(lpDS, "#152", 1);
                          voices[11]=SndObjCreate(lpDS, "#153", 1);//menu1
                          voices[12]=SndObjCreate(lpDS, "#154", 1);//aah
                          voices[13]=SndObjCreate(lpDS, "#155", 1);//yohe
                          voices[14]=SndObjCreate(lpDS, "#156", 2);//walk1
                          voices[15]=SndObjCreate(lpDS, "#157", 2);//walk2
                          voices[16]=SndObjCreate(lpDS, "#158", 2);//walk3*/
			SAMPLE_NUMBER=2;
			SOUNDS_LOADED=true;
		}


	}

}

void cfg_save(void){
        FILE *fil;
        int q;

        fil = fopen("cfg.cfg","wt");
        for (q=0; q<10; q++){
                fprintf(fil, "%d\n", options[q]);
        }
        for (q=0; q<13; q++){
                fprintf(fil, "%d\n", key[q]);
        }


        fclose(fil);
        if(options[1]&&!SOUNDS_LOADED)sounds_start();
}

void cfg_load(void){
        std::cout << "loading config" << std::endl;
        FILE *fil;
        int q,b;
        char temprow[300];


        fil = fopen("cfg.cfg","rt");

        for (q=0; q<10; q++){
                fgets(temprow,sizeof(temprow),fil);b=atoi(temprow);
                if(b==0)options[q]=false;
                else options[q]=true;
        }
        for (q=0; q<13; q++){
                fgets(temprow,sizeof(temprow),fil);key[q]=atoi(temprow);
        }

        fclose(fil);

        //SOUNDS_ON=options[1];

}
void playsound(int samplenumero,float volume,float placex,float placez){ //play a sound
	if(soundtimer[samplenumero]<40)return;
	if(!(options[1]&&SOUNDS_LOADED))return;

        // TODO: use Mix_SetPosition here instead
	float distance=sqrtf(sqr(placex-moped[0].x1)+sqr(placez-moped[0].z1));
	if(distance<10000)
	{
		//finds out is the bike at rigth or left side
                float dq=atan2f(moped[0].z1-placez,moped[0].x1-placex)+pi;
                float temp1=moped[0].direction;
                if(moped[0].direction-dq>pi)temp1=temp1-pi*2;
                if(dq-moped[0].direction>pi)dq=dq-pi*2;
                int negaatio=1;
                if (dq<temp1)
                        negaatio=-1;

                /*if(moped[0].up){
                  negaatio=1;
                  if (dq<temp1)
                  negaatio=-1;
                  }
                  else{
                  negaatio=-1;
                  if (dq<temp1)
                  negaatio=1;
                  }*/

		//float voluumi=-(distance*distance*0.0001f-10000)/10000-(1-volume);
		float voluumi=(10000-distance)/10000-(1-volume);
		soundtimer[samplenumero]=0;
		SndObjPlay(voices[samplenumero], 0, options[1]&&SOUNDS_LOADED);
		svolume(voices[samplenumero],(int)((1-voluumi)*(-6000-DSBVOLUME_MAX)), options[1]&&SOUNDS_LOADED);
		//DSBPLAY_LOOPING   DSBVOLUME_MIN
		float pan=(float)(negaatio/10000*distance);
		SndObjSetPan(voices[samplenumero],pan);


	}
}
void clearzbuffer(void){
	//if(!options[3]){
        m_pDevice->Clear( 0, NULL, D3DCLEAR_ZBUFFER , 0x00000000, 1, 0 );
	/*}
          else{
          DDBLTFX ddbltfx;
          memset(&ddbltfx, 0, sizeof(ddbltfx));
          ddbltfx.dwSize = sizeof(DDBLTFX);
          ddbltfx.dwFillDepth=0x00FFFFFF;
          zbuffer->Blt(NULL,NULL,NULL,DDBLT_DEPTHFILL,&ddbltfx);
          }*/

}
