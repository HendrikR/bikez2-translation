#include "pseudirectx.h"

D3DMATRIX ID3DXMatrixStack::RotateYawPitchRollLocal(float yaw, float pitch, float roll) {
}
D3DMATRIX ID3DXMatrixStack::Push() {
}
        D3DMATRIX ID3DXMatrixStack::Pop() {
}
        D3DMATRIX ID3DXMatrixStack::TranslateLocal(float x, float y, float z) {
}
        D3DMATRIX ID3DXMatrixStack::LoadIdentity() {
}
        const D3DMATRIX* ID3DXMatrixStack::GetTop() {
}
        D3DMATRIX ID3DXMatrixStack::ScaleLocal(float, float, float) {
}
int D3DFVF_TEXCOORDSIZE2(int) {
}

HRESULT DIRECTINPUTDEVICE8::Acquire() {
}
HRESULT DIRECTINPUTDEVICE8::GetDeviceState(size_t, void*) {
}
HRESULT DIRECTINPUTDEVICE8::SetDataFormat(DIRECTINPUTDEVICE8**) {
}
HRESULT DIRECTINPUTDEVICE8::SetCooperativeLevel(HWND&, int) {
}
void DIRECTINPUTDEVICE8::Unacquire() {
}
void DIRECTINPUTDEVICE8::Release() {
}

void DIRECTSOUND::Release() {
}

HRESULT DIRECTINPUT8::CreateDevice(int, DIRECTINPUTDEVICE8**, void*) {
}
void DIRECTINPUT8::Release() {
}

void DIRECTDRAW7::Release() {
}

void DIRECT3D7::Release() {
}

        HRESULT DIRECTDRAWSURFACE7::Blt(LPRECT destRect, DIRECTDRAWSURFACE7*& src, LPRECT srcRect, DWORD dwFlags, void*) {
}
        HRESULT DIRECTDRAWSURFACE7::BltFast(DWORD x, DWORD y, DIRECTDRAWSURFACE7*& src, LPRECT srcRect, DWORD dwTrans) {
}
        void DIRECTDRAWSURFACE7::SetColorKey(int, DDCOLORKEY*) {
}
        void DIRECTDRAWSURFACE7::Release() {
}

void DIRECT3DDEVICE7::SetRenderState(int, int mode) {
}
        void DIRECT3DDEVICE7::SetTransform(UINT enum_transformStateType, const D3DMATRIX*) {
}
        void DIRECT3DDEVICE7::SetTransform(UINT enum_transformStateType, const D3DMATRIX) {
}
        void DIRECT3DDEVICE7::LightEnable(int, bool) {
}
        void DIRECT3DDEVICE7::Clear(int, void*, int, int, int, int) {
}
        void DIRECT3DDEVICE7::SetTexture(int, DIRECTDRAWSURFACE7*&) {
}
        void DIRECT3DDEVICE7::DrawPrimitive(UINT enum_PrimitiveType, UINT start_vertex, UINT primitive_count) {
}
        void DIRECT3DDEVICE7::DrawPrimitive(UINT enum_PrimitiveType, UINT primitive_count, const void* data, UINT stride, void*) {
}
        //void DIRECT3DDEVICE7::DrawPrimitive(enum primitive_type, UINT start_vertex, UINT primitive_count) {}
        void DIRECT3DDEVICE7::SetMaterial(D3DMATERIAL7*) {
}
        void DIRECT3DDEVICE7::ComputeSphereVisibility(D3DVECTOR*, float*, int, int, DWORD*) {
}
        void DIRECT3DDEVICE7::SetLight(int, D3DLIGHT7*) {
}
        void DIRECT3DDEVICE7::SetTextureStageState(DWORD, int, DWORD) {
}
        void DIRECT3DDEVICE7::GetRenderTarget(LPDIRECTDRAWSURFACE7*) {
}
        void DIRECT3DDEVICE7::SetViewport(D3DVIEWPORT7*) {
}
        int  DIRECT3DDEVICE7::GetCaps(D3DDEVICEDESC7*) {
}
        void DIRECT3DDEVICE7::Release() {
}
        void DIRECT3DDEVICE7::BeginScene() {
}
        void DIRECT3DDEVICE7::EndScene() {
}
        bool DIRECT3DDEVICE7::GetLightEnable(int, BOOL*) {
}

        void D3DXCONTEXT::UpdateFrame(int) {
}
        LPDIRECT3D7 D3DXCONTEXT::GetD3D() {
}
        LPDIRECTDRAW7 D3DXCONTEXT::GetDD() {
}
        LPDIRECTDRAWSURFACE7 D3DXCONTEXT::GetPrimary() {
}
        LPDIRECT3DDEVICE7 D3DXCONTEXT::GetD3DDevice() {
}

HRESULT DirectSoundCreate(int* guid, LPDIRECTSOUND* ds, void* unkOuter) {
}
BOOL IDirectSound_SetCooperativeLevel(LPDIRECTSOUND, HWND hwnd, DWORD level) {
}
BOOL SndObjPlay(HSNDOBJ obj, DWORD playFlags, BOOL todo_something) {
}
BOOL SndObjStop(HSNDOBJ obj) {
}
HSNDOBJ SndObjCreate(LPDIRECTSOUND ds, HSTR name, int concurrent) {
}
BOOL SndObjSetPan(HSNDOBJ obj, DOUBLE pan) {
}
BOOL SndObjDestroy(HSNDOBJ) {
}
BOOL SndObjSetFrequency(HSNDOBJ obj, float freq) {
}

//HRESULT DirectInput8Create(LPDIRECTINPUT8*, int version) {}
HRESULT DirectInput8Create(HINSTANCE hinst, int version) {
}
HRESULT DirectInput8Create(HINSTANCE hinst, int enum1, int enum2, void**, void*) {
}


HSTR LoadCursor(void*, int) {
}
void ShowCursor(bool) {
}
void SetCursor(const char*) {
}
int GetTickCount() {
}
HSTR LoadIcon(HINSTANCE hinst, LPCTSTR name) {
}

char* itoa(int value, char* str, int base) {
}
char* ltoa(long value, char* str, int base) {
}
HRESULT D3DXCreateContext(DWORD deviceIndex, DWORD flags, HWND hwnd, DWORD width, DWORD height, LPD3DXCONTEXT* ppCtx) {
}
HRESULT D3DXCreateMatrixStack(DWORD flags, ID3DXMatrixStack **stack) {
}
HRESULT D3DXCreateTextureFromFile(LPDIRECT3DDEVICE7 pd3dDevice, LPDWORD pFlags, LPDWORD pWidth, LPDWORD pHeight, D3DX_SURFACEFORMAT* pPixelFormat,
                LPDIRECTDRAWPALETTE pDDPal, LPDIRECTDRAWSURFACE7* ppDDSurf, LPDWORD pNumMipMaps, LPSTR pSrcName, D3DX_FILTERTYPE filterType) {
}
HRESULT D3DXInitialize() {
}
HRESULT D3DXUninitialize() {
}
HRESULT D3DXVec3Add(D3DXVECTOR3 *pOut, const D3DXVECTOR3 *pV1, const D3DXVECTOR3 *pV2) {
}
HRESULT D3DXVec3Scale( D3DXVECTOR3 *pOut, const D3DXVECTOR3 *pV, FLOAT s) {
}

void LoadString(HINSTANCE, const char*, void*, int) {
}
bool PeekMessage(MSG*, void*, int, int, int) {
}
int LoadAccelerators(HINSTANCE, LPCTSTR) {
}
bool GetMessage(MSG*, void*, int, int) {
}
void TranslateMessage(MSG*) {
}
void DispatchMessage(MSG*) {
}
void SendMessage(HWND, HSTR, int, int) {
}

HWND CreateWindow(const char*, const char*,
                int, int, int, int, int,
                void*, void*, HINSTANCE, void*) {
}
void ShowWindow(HWND, int) {
}
void PostQuitMessage(int) {
}
int RegisterClassEx(WNDCLASSEX*) {
}
int timeGetTime() {
}
void ZeroMemory(void* mem, size_t len) {
}
int DefWindowProc(HWND, UINT, int, int) {
}
int GetStockObject(int) {
}




/* TODO: Here be dragons
   Structures in here should actually be defined in bikez2.h, bikez2.cpp or some elusive header. They are here just temporarily. */
/*struct pvertex {
  D3DVECTOR position {
}
  float     u, v {
}
  } {
}*/
void lataa(const char*, void*, bool, bool) {
}
//                    pvertex*
void svolume(int, int, void*, int, int) {
}
void svolume(int, int, bool) {
}
