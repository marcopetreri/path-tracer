
#ifndef _MATHEMATICS
#define _MATHEMATICS

#include "constants.hpp"
#include <math.h>

inline float toRad(float deg){
  return deg*PI_ON_180;
}

inline float toDeg(float rad){
  return rad/PI_ON_180;
}

inline Vec3d to01(double r, double g, double b){
  return Vec3d(r, g, b)/255;
}

inline Vec3d to255(const Vec3d & c){
  return c*255;
}

inline int clamp(int n, int a, int b){
  return n <= a ? a : n >= b ? b : n;
}

inline double clamp(double n, double a, double b){
  return n <= a ? a : n >= b ? b : n;
}

inline Vec3d clamp(const Vec3d & v, double a, double b){
  Vec3d u;
  for(int i = 0; i < 3; ++i){
    u[i] = clamp(v[i], a, b);
  }
  return u;
}

inline bool isZero(double val){
  return val > -D_EPS && val < D_EPS;
}

inline bool isValue(double n, double val ){
  return n > val - D_EPS && n < val + D_EPS;
}

inline int solveQuadratic(double a, double b, double c, double & x1, double & x2){
  double delta = b*b - 4*a*c;
  double aInv = 1./(2*a);
  if(delta < 0){
    return 0;
  }
  else if(isZero(delta)){
    x1 = -b*aInv;
    return 1;

  }
  else{
    x1 = (-b + sqrt(delta))*aInv;
    x2 = -2*b*aInv - x1;
    return 2;
  }
}


inline float halton(u_int n, u_int b){
  float val = 0.f;
  u_int _n = n;
  float baseInv = 1.f/b;
  float _bInv = baseInv;
  while(_n > 0.f){
    u_int d = _n%b;
    val += d*_bInv;
    _n = (_n >> 1);
    _bInv *= baseInv;
  }
  return val;
}

inline u_int permute(u_int i, u_int l, u_int p){
  u_int w = l - 1;
  w |= w >> 1;
  w |= w >> 2;
  w |= w >> 4;
  w |= w >> 8;
  w |= w >> 16;
  do{
    i ^= p; i *= 0xe170893d;
    i ^= p >> 16;
    i ^= (i & w) >> 4;
    i ^= p >> 8; i *= 0x0929eb3f;
    i ^= p >> 23;
    i ^= (i & w) >> 1; i *= 1 | p >> 27;
    i *= 0x6935fa69;
    i ^= (i & w) >> 11; i *= 0x74dcb303;
    i ^= (i & w) >> 2; i *= 0x9e501cc3;
    i ^= (i & w) >> 2; i *= 0xc860a3df;
    i &= w;
    i ^= i >> 5;
 }
 while (i >= l);
 return (i + p)%l;
}

inline float randfloat(u_int i, u_int p) {
  i ^= p;
  i ^= i >> 17;
  i ^= i >> 10; i *= 0xb36534e5;
  i ^= i >> 12;
  i ^= i >> 21; i *= 0x93fc4795;
  i ^= 0xdf6e307f;
  i ^= i >> 17; i *= 1 | p >> 18;
  return i * (1.0f / 4294967808.0f);
}

inline Vec3f toDisk(const Vec3f & smp){
  float phi, r, piq = PI*.25;
  float a = 2*smp.x-1;
  float b = 2*smp.y-1;
  if(a > -b){
    if(a > b){
      r = a;
      phi = (piq)*(b/a);
    }
    else{
      r = b;
      phi = (piq)*(2 - (a/b));
    }
  }
  else{
    if(a < b){
      r = -a;
      phi = (piq) * (4 + (b/a));
    }
    else{
      r = -b;
      if(b != 0){
        phi = (piq)*(6 - (a/b));
      }
      else{
        phi = 0;
      }
    }
  }
  return Vec3f(r*cos(phi), r*sin(phi), 0.f);
}

inline Vec3d toHemisphere(const Vec3f & s){
  Vec3f smp = toDisk(s);
  double r = sqrt(2. - smp.lengthSq());
  return Vec3d(smp.x*r, smp.y*r, 1. - smp.lengthSq());
}

inline Vec3d toCosineHemisphere(const Vec3f & s){
  Vec3f smp = toDisk(s);
  return Vec3d(smp.x, smp.y, sqrt(1 - smp.x*smp.x - smp.y*smp.y));
}

inline Vec3d buildTangent(const Vec3d & dp1, const Vec3d & dp2, const Vec3d & du1, const Vec3d & du2){
  double r = 1./(du1.x*du2.y - du1.y*du2.x);
  return (dp1*du2.y - dp2*du1.y)*r;
}

#endif
