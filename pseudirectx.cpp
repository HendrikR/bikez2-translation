#include "pseudirectx.h"

// TODO: remove error supression after refactoring
#pragma GCC diagnostic ignored "-Wreturn-type"

void ID3DXMatrixStack::RotateYawPitchRollLocal(float yaw, float pitch, float roll) {
  // TODO: use quaternions
  //_stack.top *= glm::rotate(glm::vec3(0,1,0), yaw);
  //_stack.top *= glm::rotate(glm::vec3(1,0,0), pitch);
  //_stack.top *= glm::rotate(glm::vec3(0,0,1), roll);
  glRotatef(yaw, 0, 1, 0);
  glRotatef(pitch, 1, 0, 0);
  glRotatef(roll, 0, 0, 1);
}
void ID3DXMatrixStack::Push() {
  // TODO: use glm or or glPushMatrix/PopMatrix/LoadIdentity?
  //_stack.push(glm::identity<glm::mat4>());
  glPushMatrix();
}
void ID3DXMatrixStack::Pop() {
  glPopMatrix();
  //_stack.pop();
}
void ID3DXMatrixStack::TranslateLocal(float x, float y, float z) {
  glTranslatef(x, y, z);
  //_stack.top = glm::translate(_stack.top, glm::vec3(x, y, z));
}
void ID3DXMatrixStack::LoadIdentity() {
  glLoadIdentity();
}
const D3DMATRIX* ID3DXMatrixStack::GetTop() {
  // TODO
  //return _stack.top;
}
void ID3DXMatrixStack::ScaleLocal(float x, float y, float z) {
  glScalef(x, y, z);
}
int D3DFVF_TEXCOORDSIZE2(int) {
}

HRESULT DIRECTINPUTDEVICE8::Acquire() {
  return true;
}
HRESULT DIRECTINPUTDEVICE8::GetDeviceState(size_t, void*) {
  return true;
}
HRESULT DIRECTINPUTDEVICE8::SetDataFormat(DIRECTINPUTDEVICE8**) {
  return true;
}
HRESULT DIRECTINPUTDEVICE8::SetCooperativeLevel(HWND&, int) {
  // TODO: does not like relativemouse
  SDL_CaptureMouse(SDL_TRUE);
  SDL_SetRelativeMouseMode(SDL_TRUE);
  return 1;
}
void DIRECTINPUTDEVICE8::Unacquire() {
}
void DIRECTINPUTDEVICE8::Release() {
  // NOPE
}

void DIRECTSOUND::Release() {
}

HRESULT DIRECTINPUT8::CreateDevice(int, LPDIRECTINPUTDEVICE8* lpdid, void*) {
  *lpdid = new DIRECTINPUTDEVICE8();
  return true;
}
void DIRECTINPUT8::Release() {
}

void DIRECTDRAW7::Release() {
}

void DIRECT3D7::Release() {
}

HRESULT DIRECTDRAWSURFACE7::Blt(LPRECT destRect, DIRECTDRAWSURFACE7*& src, LPRECT srcRect, DWORD dwFlags, void* blt_fx) {
  SDL_Rect srcRect2{srcRect->top,
                    srcRect->left,
                    srcRect->right - srcRect->left,
                    srcRect->bottom - srcRect->top};
  SDL_Rect destRect2{destRect->top,
                    destRect->left,
                    destRect->right - destRect->left,
                    destRect->bottom - destRect->top};
  SDL_BlitSurface(src->surface, &srcRect2, this->surface, &destRect2);
}
HRESULT DIRECTDRAWSURFACE7::BltFast(int x, int y, DIRECTDRAWSURFACE7*& src, LPRECT srcRect, DWORD dwTrans) {
  SDL_Rect srcRect2{srcRect->top,
                    srcRect->left,
                    srcRect->right - srcRect->left,
                    srcRect->bottom - srcRect->top};
  SDL_Rect destRect{x, y, srcRect2.w, srcRect2.h};
  SDL_BlitSurface(src->surface, &srcRect2, this->surface, &destRect);
  
}
void DIRECTDRAWSURFACE7::SetColorKey(int key, DDCOLORKEY* flag) {
  SDL_SetColorKey(this->surface, SDL_TRUE, key);
}
void DIRECTDRAWSURFACE7::Release() {
  SDL_FreeSurface(this->surface);
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
void DIRECT3DDEVICE7::GetRenderTarget(LPDIRECTDRAWSURFACE7* surf) {
  *surf = this->render_surface;
  // TODO
}
void DIRECT3DDEVICE7::SetViewport(D3DVIEWPORT7* vp) {
  glViewport(vp->dwX, vp->dwY, vp->dwWidth, vp->dwHeight);
  glFrustum(vp->dwX, vp->dwX + vp->dwWidth,
            vp->dwY, vp->dwY + vp->dwHeight,
            vp->dvMinZ, vp->dvMaxZ);
}
int  DIRECT3DDEVICE7::GetCaps(D3DDEVICEDESC7*) {
  // TODO
  return 0;
}
void DIRECT3DDEVICE7::Release() {
}
void DIRECT3DDEVICE7::BeginScene() {
}
void DIRECT3DDEVICE7::EndScene() {
}
bool DIRECT3DDEVICE7::GetLightEnable(int light, BOOL* state) {
  // TODO
  return state;
}

void D3DXCONTEXT::UpdateFrame(int) {
}
LPDIRECTDRAW7 D3DXCONTEXT::GetDD() {
  return this->ddraw7;
}
LPDIRECT3DDEVICE7 D3DXCONTEXT::GetD3DDevice() {
  return this->d3ddevice7;
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
  return true;
}
HRESULT DirectInput8Create(HINSTANCE hinst, int enum1, int enum2, LPDIRECTINPUT8* lpdi, void* unk) {
  lpdi = new LPDIRECTINPUT8();
  return true;
}


HSTR LoadCursor(void*, int) {
  return "";
}
void ShowCursor(bool) {
}
void SetCursor(const char*) {
}
uint64_t GetTickCount() {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (uint64_t)(ts.tv_nsec / 1000000) + ((uint64_t)ts.tv_sec * 1000ull);
}

HSTR LoadIcon(HINSTANCE hinst, LPCTSTR name) {
  return "";
}

char* itoa(int value, char* str, int base) {
  return SDL_itoa(value, str, base);
}
char* ltoa(long value, char* str, int base) {
  return SDL_ltoa(value, str, base);
}
HRESULT D3DXCreateContext(DWORD deviceIndex, DWORD flags, HWND hwnd, DWORD width, DWORD height, LPD3DXCONTEXT* ppCtx) {
  // TODO: Do I need this? The gl_context is immediately thrown away.
  SDL_GLContext gl_context = SDL_GL_CreateContext(hwnd);
  LPD3DXCONTEXT ptr = new D3DXCONTEXT();
  ptr->ddraw7 = new DIRECTDRAW7();
  ptr->d3ddevice7 = new DIRECT3DDEVICE7();
  ptr->d3ddevice7->render_surface = new DIRECTDRAWSURFACE7();
  ptr->d3ddevice7->render_surface->surface = SDL_CreateRGBSurface(0, width, height, 32, 0x0F00, 0x00F0, 0x000F, 0xF000);
  *ppCtx = ptr;
  return 1;
}
HRESULT D3DXCreateMatrixStack(DWORD flags, ID3DXMatrixStack **stack) {
  // TODO
  return 1;
}
HRESULT D3DXCreateTextureFromFile(LPDIRECT3DDEVICE7 pd3dDevice, LPDWORD pFlags, LPDWORD pWidth, LPDWORD pHeight, D3DX_SURFACEFORMAT* pPixelFormat,
                LPDIRECTDRAWPALETTE pDDPal, LPDIRECTDRAWSURFACE7* ppDDSurf, LPDWORD pNumMipMaps, LPSTR pSrcName, D3DX_FILTERTYPE filterType) {
  // TODO
  return 1;
}
HRESULT D3DXInitialize() {
  // TODO: remove. Cannot call SDL_Init _after_ window creation.
  //SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
  return 1;
}
HRESULT D3DXUninitialize() {
  SDL_Quit();
}
HRESULT D3DXVec3Add(D3DXVECTOR3 *pOut, const D3DXVECTOR3 *pV1, const D3DXVECTOR3 *pV2) {
}
HRESULT D3DXVec3Scale( D3DXVECTOR3 *pOut, const D3DXVECTOR3 *pV, FLOAT s) {
}

bool PeekMessage(MSG* event, void*, int, int, int) {
  return SDL_PollEvent(event) == 1;
}
bool GetMessage(MSG* event, void*, int, int) {
  // TODO: what‘s the difference to PeekMessage? Do I need both?
  return SDL_PollEvent(event) == 1;
}
void TranslateMessage(MSG*) {
}
void DispatchMessage(MSG*) {
}
void SendMessage(HWND, HSTR, int, int) {
}

HWND CreateWindow(const char* wndclass, const char* title,
                int flags, int flags2, int unk1, int width, int height,
                void* unk2, void* unk3, HINSTANCE hinst, void* unk4) {
  return SDL_CreateWindow(title, 0, 0, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
}
void ShowWindow(HWND wnd, int) {
  SDL_ShowWindow(wnd);
}
void PostQuitMessage(int) {
  SDL_Quit();
}
int RegisterClassEx(WNDCLASSEX*) {
  // TODO:  set icon
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
  return 1;
}
DWORD timeGetTime() {
  return GetTickCount();
}
void ZeroMemory(void* mem, size_t len) {
  memset(mem, 1, len);
}
int DefWindowProc(HWND, UINT, int, int) {
}
int GetStockObject(int x) {
  return x;
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
