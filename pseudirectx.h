#pragma once

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <glm/ext.hpp>
#include <GL/gl.h>
#include <stack>
#include <exception>

#define WINAPI

typedef int INT;
typedef bool BOOL;
typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef uint32_t LONG;
typedef char CHAR, TCHAR;
typedef float FLOAT;
typedef double DOUBLE;
typedef unsigned int UINT;
typedef DWORD* LPDWORD;
typedef void VOID;
typedef const char* HSTR;

typedef uint32_t GUID, HINSTANCE, WPARAM, LPARAM, HBRUSH, D3DVALUE;
typedef SDL_Window* HWND;
typedef const char *LPSTR, *LPCSTR, *LPCTSTR;
typedef SDL_Event MSG;
typedef Mix_Chunk* HSNDOBJ;

typedef struct RECT {
        int top, bottom, left, right;
} *LPRECT;

class __ANY__ {};

#define CALLBACK

typedef int DDCAPS, DDSURFACEDESC2, HRESULT, ATOM, LRESULT, HACCEL, D3DX_SURFACEFORMAT, LPDIRECTDRAWPALETTE, D3DX_FILTERTYPE;

struct RGB { float r, g, b, a; };
/*struct D3DVECTOR {
        D3DVECTOR(float x=0) :
                        x(x), y(x), z(x) {};
        D3DVECTOR(float x, float y, float z) :
                        x(x), y(y), z(z) {};
        float x, y, z;
        };*/
typedef glm::vec3 D3DVECTOR;
typedef glm::vec3 D3DXVECTOR3;

struct D3DLIGHT7 {
        RGB dcvDiffuse, dcvAmbient, dcvSpecular;
        D3DVECTOR dvDirection, dvPosition;
        float dvAttenuation0, dvAttenuation1, dvAttenuation2, dvRange;
        float dvFalloff, dltType, dvTheta, dvPhi;
};
struct DIMOUSESTATE {
        int rgbButtons[3];
        int lX, lY;
};

// TODO: replace by glm::mat
typedef glm::mat4 D3DMATRIX;
/*struct D3DMATRIX {
        union {
                //struct { float _11, _12, _13, _14, _21, _22, _23, _24, _31, _32, _33, _34, _41, _42, _43, _44; };
                struct { float m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33, m40, m41, m42, m43; };
                float m[4][4];
        };
        };*/
typedef D3DMATRIX D3DXMATRIX;
struct ID3DXMatrixStack {
        void RotateYawPitchRollLocal(float yaw, float pitch, float roll);
        void Push();
        void Pop();
        void TranslateLocal(float x, float y, float z);
        void LoadIdentity();
        void ScaleLocal(float, float, float);
        const D3DMATRIX* GetTop();
        std::stack<D3DMATRIX> _stack;
};
struct DDPIXELFORMAT {
        DWORD dwZBufferBitDepth;
        DWORD dwFlags;
};
const int DS_OK = 0;
typedef void* LPVOID;
//const int FAILED = -1;
#define FAILED(x) (x == -1)
int D3DFVF_TEXCOORDSIZE2(int);
enum { DIK_F9, DIK_END, DIK_HOME, DIK_DELETE, DIK_NEXT, DIK_ESCAPE, DIK_RETURN, DIK_ADD, DIK_SUBTRACT, DIK_DOWN, DIK_UP };
enum { FALSE=0, TRUE=1 };
const char* const WM_QUIT="quit";
const char* const WM_CLOSE="close";
const char* const IDI_ICON1="icon1";
enum { DSSCL_PRIORITY, DSBVOLUME_MAX, DSBPLAY_LOOPING, DDBLTFALST_SRCCOLORKEY, DIRECTINPUT_VERSION, DDBLT_WAIT, DDCKEY_SRCBLT, DISCL_FOREGROUND, DISCL_NONEXCLUSIVE, DISCL_EXCLUSIVE, IDC_ARROW, WS_POPUPWINDOW, WS_VISIBLE, PM_NOREMOVE, PM_REMOVE, DSBVOLUME_MIN, DDBLTFAST_SRCCOLORKEY, CS_HREDRAW, CS_VREDRAW, WM_ACTIVATE, WM_CHAR, WM_DESTROY, GUID_SysKeyboard, GUID_SysMouse, BLACK_BRUSH, CW_USEDEFAULT, IID_IDirectInput8, c_dfDIKeyboard, c_dfDIMouse };
// TODO: These have no corresponding GL value
enum {
  D3DRENDERSTATE_SHADEMODE, D3DRENDERSTATE_FOGTABLEMODE, D3DRENDERSTATE_FOGVERTEXMODE, D3DRENDERSTATE_COLORKEYENABLE, D3DRENDERSTATE_CULLMODE, D3DRENDERSTATE_RANGEFOGENABLE, D3DFVF_NORMAL, D3DFVF_TEX1, D3DFVF_XYZ, D3DLIGHT_POINT, D3DLIGHT_SPOT, D3DPRASTERCAPS_FOGRANGE, D3DPRASTERCAPS_FOGVERTEX, D3DPTFILTERCAPS_MAGFANISOTROPIC, D3DPTFILTERCAPS_MAGFLINEAR, D3DPTFILTERCAPS_MINFANISOTROPIC, D3DPTFILTERCAPS_MINFLINEAR, D3DSTATUS_CLIPINTERSECTIONALL, D3DTADDRESS_MIRROR, D3DTFG_ANISOTROPIC, D3DTFG_LINEAR, D3DTFN_ANISOTROPIC, D3DTRANSFORMSTATE_PROJECTION, D3DTRANSFORMSTATE_VIEW, D3DTRANSFORMSTATE_WORLD, D3DTSS_ADDRESS, D3DTSS_MAXANISOTROPY, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2, D3DX_CONTEXT_FULLSCREEN, D3DX_DEFAULT, D3DX_FT_DEFAULT, D3DX_FT_POINT, D3DX_SF_UNKNOWN, D3DENUMRET_OK, D3DENUMRET_CANCEL, DDPF_ZBUFFER, D3DCLEAR_TARGET, D3DCLEAR_ZBUFFER, D3DRENDERSTATE_ZWRITEENABLE };

#define D3DBLEND_DESTCOLOR GL_DST_COLOR
#define D3DBLEND_SRCCOLOR GL_SRC_COLOR
#define D3DBLEND_INVSRCCOLOR GL_ONE_MINUS_SRC_COLOR
#define D3DBLEND_ONE GL_ONE
#define D3DBLEND_SRCALPHA GL_SRC_ALPHA
#define D3DBLEND_ZERO GL_ZERO
#define D3DRENDERSTATE_FOGCOLOR GL_FOG_COLOR
#define D3DRENDERSTATE_FOGDENSITY GL_FOG_DENSITY
#define D3DRENDERSTATE_FOGENABLE GL_FOG
#define D3DRENDERSTATE_FOGEND GL_FOG_END
#define D3DRENDERSTATE_FOGSTART GL_FOG_START
#define D3DFOG_LINEAR GL_LINEAR
#define D3DFOG_EXP GL_EXP
#define D3DFOG_EXP2 GL_EXP2
#define D3DTSS_MINFILTER GL_TEXTURE_MIN_FILTER
#define D3DTSS_MAGFILTER GL_TEXTURE_MAG_FILTER

#define D3DSHADE_GOURAUD GL_SMOOTH

#define D3DRENDERSTATE_ALPHABLENDENABLE GL_BLEND


#define D3DRENDERSTATE_AMBIENT GL_AMBIENT
#define D3DRENDERSTATE_LIGHTING GL_LIGHTING
#define D3DRENDERSTATE_SRCBLEND GL_BLEND_SRC
#define D3DRENDERSTATE_DESTBLEND GL_BLEND_DST
#define D3DRENDERSTATE_TEXTUREPERSPECTIVE GL_PERSPECTIVE_CORRECTION_HINT
#define D3DRENDERSTATE_ZBIAS GL_DEPTH_BIAS
#define D3DRENDERSTATE_ZENABLE GL_DEPTH_TEST
#define D3DCULL_CW GL_CW
#define D3DCULL_CCW GL_CCW

#define D3DPT_LINELIST GL_LINES
#define D3DPT_TRIANGLELIST GL_TRIANGLES

struct vvertex {
        D3DVECTOR position;
        D3DVECTOR normal;
        float     u, v;//, w;
};

struct pvertex {
        D3DVECTOR position;
        float     u, v;
};

struct DDCOLORKEY {
        DWORD dwColorSpaceHighValue, dwColorSpaceLowValue;
};
struct TODO_TriCaps {
        DWORD dwRasterCaps;
        DWORD dwTextureFilterCaps;
};

struct D3DDEVICEDESC7 {
        TODO_TriCaps dpcTriCaps;
};
typedef struct DIRECTINPUTDEVICE8 {
        HRESULT Acquire();
        HRESULT GetDeviceState(size_t, void*);
        HRESULT SetDataFormat(DIRECTINPUTDEVICE8**);
        HRESULT SetCooperativeLevel(HWND&, int);
        void Unacquire();
        void Release();
} *LPDIRECTINPUTDEVICE8;
typedef struct DIRECTSOUND {
        void Release();
} *LPDIRECTSOUND;
typedef struct DIRECTINPUT8 {
        HRESULT CreateDevice(int, DIRECTINPUTDEVICE8**, void*);
        void Release();
} *LPDIRECTINPUT8;
typedef struct DIRECTDRAW7 {
        void Release();
} *LPDIRECTDRAW7;
typedef struct DIRECT3D7 {
        void Release();
} *LPDIRECT3D7;


typedef LRESULT (*WNDPROC)(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
struct WNDCLASSEX {
        int cbSize, style, cbClsExtra, cbWndExtra;
        WNDPROC lpfnWndProc;
        HINSTANCE hInstance;
        HSTR hIcon, hIconSm, hCursor, lpszMenuName, lpszClassName;
        HBRUSH hbrBackground;
};

struct D3DMATERIAL7 {
        RGB dcvAmbient, dcvDiffuse, dcvSpecular;
        float dvPower;
};
struct D3DVIEWPORT7 {
        uint32_t dwX, dwY, dwWidth, dwHeight;
        float dvMinZ, dvMaxZ;
};

typedef struct DIRECTDRAWSURFACE7 {
        HRESULT Blt(LPRECT destRect, DIRECTDRAWSURFACE7*& src, LPRECT srcRect, DWORD dwFlags, void*);
        HRESULT BltFast(int x, int y, DIRECTDRAWSURFACE7*& src, LPRECT srcRect, DWORD dwTrans);
        void SetColorKey(int, DDCOLORKEY*);
        void Release();
        SDL_Surface* surface;
        GLuint texture;
} *LPDIRECTDRAWSURFACE7;

typedef struct DIRECT3DDEVICE7 {
        void SetRenderState(int, DWORD value);
        void SetTransform(UINT enum_transformStateType, const D3DMATRIX*);
        void SetTransform(UINT enum_transformStateType, const D3DMATRIX);
        void LightEnable(int, bool);
        void Clear(int, void*, int, int, int, int);
        void SetTexture(int, DIRECTDRAWSURFACE7*&);
        void DrawPrimitive(UINT primitiveType, DWORD flags, const vvertex* data, UINT count, void* unk);
        void DrawPrimitive(UINT primitiveType, DWORD flags, const pvertex* data, UINT count, void* unk);
        void DrawPrimitive(UINT primitiveType, DWORD flags, const void* data, UINT count, void* unk);
        void SetMaterial(D3DMATERIAL7*);
        void ComputeSphereVisibility(D3DVECTOR*, float*, int, int, DWORD*);
        void SetLight(int, D3DLIGHT7*);
        void SetTextureStageState(DWORD, int, DWORD);
        void GetRenderTarget(LPDIRECTDRAWSURFACE7*);
        void SetViewport(D3DVIEWPORT7*);
        int GetCaps(D3DDEVICEDESC7*);
        void Release();
        void BeginScene();
        void EndScene();
        void GetLightEnable(int, BOOL*);
        DIRECTDRAWSURFACE7* render_surface;
} *LPDIRECT3DDEVICE7;

typedef struct D3DXCONTEXT {
        void UpdateFrame(int);
        LPDIRECTDRAW7 GetDD();
        LPDIRECT3DDEVICE7 GetD3DDevice();
        LPDIRECTDRAW7 ddraw7;
        LPDIRECT3DDEVICE7 d3ddevice7;
        HWND wnd;
} *LPD3DXCONTEXT;


HRESULT DirectSoundCreate(int* guid, LPDIRECTSOUND* ds, void* unkOuter);
BOOL IDirectSound_SetCooperativeLevel(LPDIRECTSOUND, HWND hwnd, DWORD level);
BOOL SndObjPlay(HSNDOBJ obj, DWORD playFlags, BOOL todo_something);
BOOL SndObjStop(HSNDOBJ obj);
HSNDOBJ SndObjCreate(LPDIRECTSOUND ds, HSTR name, int concurrent);
BOOL SndObjSetPan(HSNDOBJ obj, DOUBLE pan);
BOOL SndObjDestroy(HSNDOBJ);
BOOL SndObjSetFrequency(HSNDOBJ obj, float freq);

//HRESULT DirectInput8Create(LPDIRECTINPUT8*, int version);
HRESULT DirectInput8Create(HINSTANCE hinst, int version);
HRESULT DirectInput8Create(HINSTANCE hinst, int enum1, int enum2, LPDIRECTINPUT8* lpdi, void*);


HSTR LoadCursor(void*, int);
void ShowCursor(bool);
void SetCursor(const char*);
uint64_t GetTickCount();
HSTR LoadIcon(HINSTANCE hinst, LPCTSTR name);

char* itoa(int value, char* str, int base);
char* ltoa(long value, char* str, int base);
HRESULT D3DXCreateContext(DWORD deviceIndex, DWORD flags, HWND hwnd, DWORD width, DWORD height, LPD3DXCONTEXT* ppCtx);
HRESULT D3DXCreateMatrixStack(DWORD flags, ID3DXMatrixStack **stack);
HRESULT D3DXCreateTextureFromFile(LPDIRECT3DDEVICE7 pd3dDevice, LPDWORD pFlags, LPDWORD pWidth, LPDWORD pHeight, D3DX_SURFACEFORMAT* pPixelFormat,
                LPDIRECTDRAWPALETTE pDDPal, LPDIRECTDRAWSURFACE7* ppDDSurf, LPDWORD pNumMipMaps, LPSTR pSrcName, D3DX_FILTERTYPE filterType);
HRESULT D3DXInitialize();
HRESULT D3DXUninitialize();
HRESULT D3DXVec3Add(D3DXVECTOR3 *pOut, const D3DXVECTOR3 *pV1, const D3DXVECTOR3 *pV2);
HRESULT D3DXVec3Scale( D3DXVECTOR3 *pOut, const D3DXVECTOR3 *pV, FLOAT s);

bool PeekMessage(MSG*, void*, int, int, int);
bool GetMessage(MSG*, void*, int, int);
void TranslateMessage(MSG*);
void DispatchMessage(MSG*);
void SendMessage(HWND, HSTR, int, int);

HWND CreateWindow(const char*, const char*,
                int, int, int, int, int,
                void*, void*, HINSTANCE, void*);
void ShowWindow(HWND, int);
void PostQuitMessage(int);
int RegisterClassEx(WNDCLASSEX*);
DWORD timeGetTime();
void ZeroMemory(void* mem, size_t len);
int DefWindowProc(HWND, UINT, int, int);
int GetStockObject(int);




// I added an exception class to have better error handling while porting / fixing things
class MyEx : public std::exception {
private:
  const char* msg;
public:
  MyEx(const char* _msg) : msg(_msg) {}
  const char* what() const noexcept {
    return msg;
  }
};



/* TODO: Here be dragons
   Structures in here should actually be defined in bikez2.h, bikez2.cpp or some elusive header. They are here just temporarily. */
/*struct pvertex {
  D3DVECTOR position;
  float     u, v;
  };*/
void lataa(const char*, void*, bool, bool);
//                    pvertex*
void svolume(HSNDOBJ, int, void*, int, int);
void svolume(HSNDOBJ, int, bool);


