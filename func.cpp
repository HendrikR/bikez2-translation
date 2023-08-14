#include "func.h"

// TODO: remove error supression after refactoring
#pragma GCC diagnostic ignored "-Wreturn-type"

bool linecollidesline(bool *osuma,float *osumax,float *osumaz,float piste1x,float piste1z,float piste2x,float piste2z,float piste3x,float piste3z,float piste4x,float piste4z) {
}//does a line collide with another

LPDIRECTDRAWSURFACE7 loadPicture(LPDIRECTDRAW7 m_pDD, char name[200], BOOL hardware) {
  // TODO: consider https://dev.to/noah11012/using-sdl2-optimizing-surface-blitting-38f8
  // TODO!: this loads indexed palette format, need to convert it before using
  SDL_Surface* surface = SDL_LoadBMP(name);
  if (surface == nullptr) {
    throw MyEx("Error creating surface");
    return nullptr;
  }

  SDL_Surface* s2 = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_ARGB8888, 0);
  GLuint tex;

  glGenTextures(1, &tex);
  glBindTexture(GL_TEXTURE_2D, tex);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, s2->pixels);

  DIRECTDRAWSURFACE7* out = new DIRECTDRAWSURFACE7();
  out->texture = tex;
  out->w = s2->w;
  out->h = s2->h;

  SDL_FreeSurface(surface);
  SDL_FreeSurface(s2);
  //out->surface = surface;
  return out;
}//loadpicture

LPDIRECTDRAWSURFACE7 loadTexture(int screenmode,D3DDEVICEINFO info, LPDIRECT3DDEVICE7 *m_pDevice,LPDIRECTDRAW7 m_pDD,char name[200], BOOL hardware) {
  // TODO: not needed
}//loadtexture
LPDIRECTDRAWSURFACE7 loadWall(int screenmode,D3DDEVICEINFO info, LPDIRECT3DDEVICE7 *m_pDevice,LPDIRECTDRAW7 m_pDD,char name[200], BOOL hardware) {
  // TODO: not needed.
}//loadtexture

int randInt( int low, int high ) {
  return low + std::rand() % (high-low+1);
}
float randDouble( float low, float high ) {
  return low + (std::rand() / (float)RAND_MAX) * (high-low);
}
bool intersect(RECT a, RECT b) {
  return ((a.top  < b.top  && b.top  < a.bottom) || (b.top  < a.top  && a.top  < b.bottom))
     &&  ((a.left < b.left && b.left < a.right)  || (b.left < a.left && a.left < b.right));
}
char *stripped_fgets(char *s, int n, FILE *f) {
  // TODO: remove whitespace and ‘;‘-prefixed line comments
  char* ret = fgets(s,n,f);
  return fgets(s, n, f);
}
D3DMATRIX IdentityMatrix() {
  return glm::identity<glm::mat4>();
}
D3DMATRIX ZeroMatrix() {
  return D3DMATRIX{ 0,0,0,0,
                    0,0,0,0,
                    0,0,0,0,
                    0,0,0,0};
}
D3DMATRIX MatrixMult(const D3DMATRIX a, const D3DMATRIX b) {
  // TODO: replace by glm::mat::operator*
  D3DMATRIX result;

  return result;
}

D3DMATRIX ViewMatrix(const D3DVECTOR from,const D3DVECTOR at, const D3DVECTOR world_up, const float roll) {
  // TODO: this does not respect @roll
  return glm::lookAt(at, from, world_up);
}

D3DMATRIX ProjectionMatrix(const float near_plane, const float far_plane, const float fov) {
  return glm::perspective<float>(fov, 4.0/3.0, near_plane, far_plane);
}
