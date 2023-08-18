#include "pseudirectx.h"
#include <iostream>

void ID3DXMatrixStack::Push() {
  // TODO: use glm or or glPushMatrix/PopMatrix/LoadIdentity?
  //_stack.push(glm::identity<glm::mat4>());
  glPushMatrix();
}

void ID3DXMatrixStack::Pop() {
  glPopMatrix();
  //_stack.pop();
}

const D3DMATRIX* ID3DXMatrixStack::GetTop() {
  // TODO
  GLfloat m[16];
  glGetFloatv(GL_MODELVIEW_MATRIX, m);
  D3DMATRIX* mat = new D3DMATRIX(m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8], m[9], m[10], m[11], m[12], m[13], m[14], m[15]);
  return mat;
}

void ID3DXMatrixStack::LoadIdentity() {
  glMatrixMode(GL_MODELVIEW); // TODO: good? bad?
  glLoadIdentity();
}

void ID3DXMatrixStack::TranslateLocal(float x, float y, float z) {
  glMatrixMode(GL_MODELVIEW); // TODO: good? bad?
  glTranslatef(x, y, z);
  //_stack.top = glm::translate(_stack.top, glm::vec3(x, y, z));
}

void ID3DXMatrixStack::RotateYawPitchRollLocal(float yaw, float pitch, float roll) {
  // TODO: use quaternions
  //_stack.top *= glm::rotate(glm::vec3(0,1,0), yaw);
  //_stack.top *= glm::rotate(glm::vec3(1,0,0), pitch);
  //_stack.top *= glm::rotate(glm::vec3(0,0,1), roll);
  glMatrixMode(GL_MODELVIEW); // TODO: good? bad?
  glRotatef(yaw, 0, 1, 0);
  glRotatef(pitch, 1, 0, 0);
  glRotatef(roll, 0, 0, 1);
}

void ID3DXMatrixStack::ScaleLocal(float x, float y, float z) {
  glMatrixMode(GL_MODELVIEW); // TODO: good? bad?
  glScalef(x, y, z);
}

int D3DFVF_TEXCOORDSIZE2(int) {
  // TODO: probably not needed at all.
  return 0;
}

HRESULT DIRECTINPUTDEVICE8::GetDeviceState(size_t memsize, DIMOUSESTATE* mouse) {
  SDL_GetMouseState(&mouse->lX, &mouse->lY);
  mouse->rgbButtons[0] = SDL_BUTTON(SDL_BUTTON_LEFT);
  mouse->rgbButtons[1] = SDL_BUTTON(SDL_BUTTON_MIDDLE);
  mouse->rgbButtons[2] = SDL_BUTTON(SDL_BUTTON_RIGHT);
  return true;
}
HRESULT DIRECTINPUTDEVICE8::GetDeviceState(size_t memsize, char* keybuffer) {
  SDL_PumpEvents();
  int sdlkeys_len;
  const Uint8* sdlkeys = SDL_GetKeyboardState(&sdlkeys_len);
  for(int i=0; i<256;i++) {
    keybuffer[i] = sdlkeys[i] == 1 ? 0x80 : 0x00;
  }
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
HRESULT DIRECTINPUTDEVICE8::Acquire() {
  return true;
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

HRESULT DIRECTDRAWSURFACE7::Blt(LPRECT dstRect, DIRECTDRAWSURFACE7*& src, LPRECT srcRect, DWORD dwFlags, void* blt_fx) {
  /*SDL_Rect srcRect2{srcRect->top,
                    srcRect->left,
                    srcRect->right - srcRect->left,
                    srcRect->bottom - srcRect->top};
  SDL_Rect destRect2{destRect->top,
                    destRect->left,
                    destRect->right - destRect->left,
                    destRect->bottom - destRect->top};
  int status = SDL_BlitSurface(src->surface, &srcRect2, this->surface, &destRect2);*/
  // TODO: a feeble try to simulate blitting -- won‘t work, because screen might be turned to some arbitrary position
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0,1024, 0, 768, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, src->texture);
  glBegin(GL_QUADS);
  glTexCoord2f(srcRect->left/src->w,  1.0-srcRect->top/src->h);    glVertex2f(dstRect->left,  dstRect->top);
  glTexCoord2f(srcRect->right/src->w, 1.0-srcRect->top/src->h);    glVertex2f(dstRect->right, dstRect->top);
  glTexCoord2f(srcRect->right/src->w, 1.0-srcRect->bottom/src->h); glVertex2f(dstRect->right, dstRect->bottom);
  glTexCoord2f(srcRect->left/src->w,  1.0-srcRect->bottom/src->h); glVertex2f(dstRect->left,  dstRect->bottom);
  glEnd();

  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  return 1;
}
HRESULT DIRECTDRAWSURFACE7::BltFast(int x, int y, DIRECTDRAWSURFACE7*& src, LPRECT srcRect, DWORD dwTrans) {
  RECT* dstRect = new RECT();
  dstRect->top = x;
  dstRect->left = y;
  dstRect->right = srcRect->right - srcRect->left + y;
  dstRect->bottom = srcRect->bottom - srcRect->top + y;
  this->Blt(dstRect, src, srcRect, dwTrans, nullptr);
  delete dstRect;
  return 1;
}
void DIRECTDRAWSURFACE7::SetColorKey(int key, DDCOLORKEY* flag) {
  //SDL_SetColorKey(this->surface, SDL_TRUE, key);
}
void DIRECTDRAWSURFACE7::Release() {
  //SDL_FreeSurface(this->surface);
}

void DIRECT3DDEVICE7::SetRenderState(int key, DWORD value) {
  switch(key) {
  case D3DRENDERSTATE_LIGHTING:
  case D3DRENDERSTATE_AMBIENT:
  case D3DRENDERSTATE_FOGENABLE:
  case D3DRENDERSTATE_ALPHABLENDENABLE:
  case D3DRENDERSTATE_ZENABLE:
    value == TRUE ? glEnable(key) : glDisable(key);
    break;
  case D3DRENDERSTATE_COLORKEYENABLE: break; // TODO: GL supports no colorkey
    //case D3DTRANSFORMSTATE_WORLD: break; // TODO
  case D3DRENDERSTATE_FOGCOLOR:
    {
      GLint colors[] = {(GLint)(value >> 16 & 0xFF),
                        (GLint)(value >> 8 & 0xFF),
                        (GLint)(value >> 0 & 0xFF),
                        (GLint)(value >> 24 & 0xFF)}; // ARGB-->RGBA (TODO: verify)
      glFogiv(key, colors);
    }
    break;
  case D3DRENDERSTATE_FOGSTART:
  case D3DRENDERSTATE_FOGEND:
    glFogf(key, *(float*)(&value));
    break;
  case D3DRENDERSTATE_FOGDENSITY:
    glFogf(GL_FOG_DENSITY, *(float*)(&value));
    break;
  case D3DRENDERSTATE_FOGTABLEMODE:
  case D3DRENDERSTATE_FOGVERTEXMODE:
    glFogi(GL_FOG_MODE, value); break;
  case D3DRENDERSTATE_RANGEFOGENABLE:
    glHint(GL_FOG_HINT, value == TRUE ? GL_NICEST : GL_FASTEST);
    break;
  case D3DRENDERSTATE_CULLMODE:
    glFrontFace(value); break;
  case D3DRENDERSTATE_SHADEMODE:
    glShadeModel(value); break;
  case D3DRENDERSTATE_TEXTUREPERSPECTIVE:
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, value == TRUE ? GL_NICEST : GL_FASTEST);
    break;
  case D3DRENDERSTATE_SRCBLEND:
    {
      GLint old;
      glGetIntegerv(GL_BLEND_DST, &old);
      glBlendFunc(value, old);
    }
    break;
  case D3DRENDERSTATE_DESTBLEND:
    {
      GLint old;
      glGetIntegerv(GL_BLEND_SRC, &old);
      glBlendFunc(old, value);
    }
    break;
  case D3DRENDERSTATE_ZBIAS:
    glPixelTransferf(GL_DEPTH_BIAS, value); break;
  case D3DRENDERSTATE_ZWRITEENABLE:
    glDepthMask(value == TRUE ? GL_TRUE : GL_FALSE); break;
  default: throw MyEx("unknown key for SetRenderState");
  }
}
void DIRECT3DDEVICE7::SetTransform(UINT enum_transformStateType, const D3DMATRIX* mat) {
  SetTransform(enum_transformStateType, *mat);
}
void DIRECT3DDEVICE7::SetTransform(UINT enum_transformStateType, const D3DMATRIX mat) {
  GLint which;
  switch (enum_transformStateType) {
  case D3DTRANSFORMSTATE_PROJECTION: which = GL_PROJECTION; return; break;
  case D3DTRANSFORMSTATE_VIEW: which = GL_MODELVIEW; break;
  case D3DTRANSFORMSTATE_WORLD: which = GL_MODELVIEW; return; break;
  }
  /*std::cout << "set matrix "<< which <<" to ";
  for(int i=0;i<4;i++) {
          std::cout << "\n  ";
          for(int j=0;j<4;j++) {
                  std::cout << mat[j][i] << " ";
          }
  }
  std::cout << std::endl;*/
  glMatrixMode(which);
  glLoadIdentity();
  // TODO: this is a bit dangerous
  glMultMatrixf((GLfloat*)(&mat));
  glMatrixMode(GL_MODELVIEW);
}
void DIRECT3DDEVICE7::LightEnable(int which, bool state) {
  int gl_which = GL_LIGHT0+which;
  if (state == TRUE) glEnable(which);
  else               glDisable(which);
}
void DIRECT3DDEVICE7::Clear(int, void*, int, int, int, int) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void DIRECT3DDEVICE7::SetTexture(int num, DIRECTDRAWSURFACE7*& surf) {
  // TODO this goes to initialization
  glBindTexture(GL_TEXTURE_2D, surf->texture);
}
void DIRECT3DDEVICE7::DrawPrimitive(UINT primitiveType, DWORD texflags, const vvertex* data, UINT count, void* unk) {
  glBegin(primitiveType);
  for (UINT i=0; i<count; ++i) {
    glTexCoord2f(data[i].u, data[i].v);
    glNormal3fv((float*)(&data[i].normal));
    glVertex3fv((float*)(&data[i].position));
  }
  glEnd();
}

void DIRECT3DDEVICE7::DrawPrimitive(UINT primitiveType, DWORD texflags, const pvertex* data, UINT count, void* unk) {
  glBegin(primitiveType);
  for (UINT i=0; i<count; ++i) {
    glTexCoord2f(data[i].u, data[i].v);
    glVertex3fv((float*)(&data[i].position));
  }
  glEnd();
}

void DIRECT3DDEVICE7::DrawPrimitive(UINT primitiveType, DWORD texflags, const void* data, UINT count, void* unk) {
  float* fdata = (float*)(data);
  glBegin(primitiveType);
  for (UINT i=0; i<count; i+=3) {
    glVertex3f(fdata[i], fdata[i+1], fdata[i+2]);
  }
  glEnd();
}

//void DIRECT3DDEVICE7::DrawPrimitive(enum primitive_type, UINT start_vertex, UINT primitive_count) {}
void DIRECT3DDEVICE7::SetMaterial(D3DMATERIAL7* m) {
  glMaterialfv(GL_FRONT | GL_BACK, GL_AMBIENT,   (GLfloat*)(&m->dcvAmbient));
  glMaterialfv(GL_FRONT | GL_BACK, GL_DIFFUSE,   (GLfloat*)(&m->dcvDiffuse));
  glMaterialfv(GL_FRONT | GL_BACK, GL_SPECULAR,  (GLfloat*)(&m->dcvSpecular));
  glMaterialf(GL_FRONT | GL_BACK, GL_SHININESS, m->dvPower);
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
  // TODO: perspective, not ortho
  std::cout << "setting viewport to " << vp->dwWidth <<"x"<< vp->dwHeight <<" @ "<< vp->dwX <<"x"<< vp->dwY << std::endl;
  glViewport(vp->dwX, vp->dwY, vp->dwWidth, vp->dwHeight);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-(int)vp->dwWidth, vp->dwWidth, -1.8*(int)vp->dwHeight, vp->dwHeight, -1.0f, 1.0f);
  //glOrtho(-0.5*vp->dwWidth, vp->dwWidth/2, -0.5*vp->dwHeight, vp->dwHeight/2, -1.0f, 1.0f);
  glFrustum(vp->dwX, vp->dwX + vp->dwWidth,
            vp->dwY, vp->dwY + vp->dwHeight,
            vp->dvMinZ, vp->dvMaxZ);
  glMatrixMode(GL_MODELVIEW);
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
void DIRECT3DDEVICE7::GetLightEnable(int light, BOOL* state) {
  GLint v;
  glGetIntegerv(GL_LIGHT0, &v);
  *state = (v != 0);
}

void D3DXCONTEXT::UpdateFrame(int) {
  SDL_GL_SwapWindow(this->wnd);
}
LPDIRECTDRAW7 D3DXCONTEXT::GetDD() {
  return this->ddraw7;
}
LPDIRECT3DDEVICE7 D3DXCONTEXT::GetD3DDevice() {
  return this->d3ddevice7;
}

HRESULT DirectSoundCreate(int* guid, LPDIRECTSOUND* ds, void* unkOuter) {
  //Initialize SDL_mixer
  if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
    throw MyEx(Mix_GetError());
  }

  // TODO: number of channels is arbitrary. See SndObjStop also.
  if( Mix_AllocateChannels(4) < 0 ) {
    throw MyEx(Mix_GetError());
  }
  return DS_OK;
}
BOOL IDirectSound_SetCooperativeLevel(LPDIRECTSOUND, HWND hwnd, DWORD level) {
  return true;
}
BOOL SndObjPlay(HSNDOBJ obj, DWORD playFlags, BOOL todo_something) {
  // TODO
  Mix_PlayChannel(-1, obj, 0);
  return true;
}
BOOL SndObjStop(HSNDOBJ obj) {
  // TODO: Bad fit. SDL2-mixer uses channels; this expects individual sound objects
  // One way to do it would be for each HSNDOBJ to have its own channel.
  Mix_HaltChannel(-1);
  return true;
}
HSNDOBJ SndObjCreate(LPDIRECTSOUND ds, HSTR name, int concurrent) {
  return Mix_LoadWAV(name);
}
BOOL SndObjSetPan(HSNDOBJ obj, DOUBLE pan) {
  // pan \in [-1,1], Mix_SetPanning expects 0..255
  int right = (pan+1.0)*128;
  for (int channel=0; channel<4; channel++) {
    Mix_SetPanning(channel, 255-right, right);
  }
  return true;
}
BOOL SndObjDestroy(HSNDOBJ snd) {
  Mix_FreeChunk(snd);
  return true;
}
BOOL SndObjSetFrequency(HSNDOBJ obj, float freq) {
  // TODO: SDL2-mixer does not support this
  return true;
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
  return SDL_GetTicks();
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
  unsigned int rmask, gmask, bmask, amask;
  int bpp;
  uint32_t pixel_format = SDL_GetWindowPixelFormat(hwnd);
  SDL_PixelFormatEnumToMasks(pixel_format, &bpp, &rmask, &gmask, &bmask, &amask);
  SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, bpp, rmask, gmask, bmask, amask);
  if (!surface) {
    throw MyEx("could not create SDL surface");
  }
  LPD3DXCONTEXT ptr = new D3DXCONTEXT();
  ptr->wnd = hwnd;
  ptr->ddraw7 = new DIRECTDRAW7();
  ptr->d3ddevice7 = new DIRECT3DDEVICE7();
  ptr->d3ddevice7->render_surface = new DIRECTDRAWSURFACE7();
  //ptr->d3ddevice7->render_surface->surface = surface;
  *ppCtx = ptr;

  glEnable(GL_TEXTURE_2D);
  glEnable(GL_COLOR_MATERIAL);

  return 1;
}
HRESULT D3DXCreateMatrixStack(DWORD flags, ID3DXMatrixStack **stack) {
  // TODO
  return 1;
}
HRESULT D3DXCreateTextureFromFile(LPDIRECT3DDEVICE7 pd3dDevice, LPDWORD pFlags, LPDWORD pWidth, LPDWORD pHeight, D3DX_SURFACEFORMAT* pPixelFormat,
                LPDIRECTDRAWPALETTE pDDPal, LPDIRECTDRAWSURFACE7* ppDDSurf, LPDWORD pNumMipMaps, LPSTR pSrcName, D3DX_FILTERTYPE filterType) {
  DIRECTDRAWSURFACE7* surf = new DIRECTDRAWSURFACE7();
  *ppDDSurf = surf;
  SDL_Surface* surface = SDL_LoadBMP(pSrcName);
  if (surface == nullptr) {
    delete surf;
    throw MyEx("Error creating surface");
  }
  SDL_Surface* s2 = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_ARGB8888, 0);
  surf->w = s2->w;
  surf->h = s2->h;

  glGenTextures(1, &surf->texture);
  glBindTexture(GL_TEXTURE_2D, surf->texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, s2->pixels);
  SDL_FreeSurface(surface);
  SDL_FreeSurface(s2);
  return 1;
}

HRESULT D3DXInitialize() {
  // TODO: remove. Cannot call SDL_Init _after_ window creation.
  //SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
  return 1;
}
HRESULT D3DXUninitialize() {
  SDL_Quit();
  return TRUE;
}
HRESULT D3DXVec3Add(D3DXVECTOR3 *pOut, const D3DXVECTOR3 *pV1, const D3DXVECTOR3 *pV2) {
  // TODO: use glm operator+
  glm::vec3 v1(*pV1);
  glm::vec3 v2(*pV2);
  //glm::vec3 v3 = v1 + v2;
  *pOut = D3DXVECTOR3(v1+v2);
  return TRUE;
}
HRESULT D3DXVec3Scale( D3DXVECTOR3 *pOut, const D3DXVECTOR3 *pV, FLOAT s) {
  glm::vec3 v(*pV);
  *pOut = D3DXVECTOR3(v*s);
  return TRUE;
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
  HWND wnd = SDL_CreateWindow(title, 0, 0, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
  SDL_GLContext context = SDL_GL_CreateContext(wnd);
  SDL_GL_MakeCurrent(wnd, context);
  return wnd;
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
  return SDL_GetTicks();
}
void ZeroMemory(void* mem, size_t len) {
  memset(mem, 1, len);
}
int DefWindowProc(HWND, UINT, int, int) {
  // TODO
  return 0;
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
void svolume(HSNDOBJ, int, void*, int, int) {
}
void svolume(HSNDOBJ, int, bool) {
}
