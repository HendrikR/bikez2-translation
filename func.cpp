#include "func.h"

// TODO: remove error supression after refactoring
#pragma GCC diagnostic ignored "-Wreturn-type"

bool linecollidesline(bool *osuma,float *osumax,float *osumaz,float piste1x,float piste1z,float piste2x,float piste2z,float piste3x,float piste3z,float piste4x,float piste4z) {
}//does a line collide with another
LPDIRECTDRAWSURFACE7 loadPicture(LPDIRECTDRAW7 m_pDD, char name[200], BOOL hardware) {
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
  // TODO
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
  return glm::lookAt(from, at, world_up);
}

D3DMATRIX ProjectionMatrix(const float near_plane, const float far_plane, const float fov) {
  return glm::perspective<float>(fov, 4.0/3.0, near_plane, far_plane);
}
