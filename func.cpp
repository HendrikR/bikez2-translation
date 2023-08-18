#include "func.h"

bool linecollidesline(bool *osuma,float *osumax,float *osumay,float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4) {
  float div = ((y4-y3)*(x2-x1)) - ((x4-x3)*(y2-y1));
  float num1= ((x4-x3)*(y1-y3)) - ((y4-y3)*(x1-x3));
  float num2= ((x2-x1)*(y1-y3)) - ((y2-y1)*(x1-x3));

  if (div == 0) {
    *osuma = false;
  } else {
    float u1 = num1/div, u2 = num2/div;
    *osumax = x1 + (u1 * (x2-x1));
    *osumay = y1 + (u1 * (y2-y1));
    *osuma = true;
  }
  return *osuma;
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
