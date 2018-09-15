#ifndef _VEC_4F_
#define _VEC_4F_

#include "vec3f.hpp"

class Vec4f{
public:
  Vec4f(): x(), y(), z(), w(){}
  Vec4f(float s, float _w): x(s), y(s), z(s), w(_w){}
  Vec4f(float _x, float _y, float _z, float _w): x(_x), y(_y), z(_z), w(_w){}
  Vec4f(const Vec3f & v, float _w): x(v.x), y(v.y), z(v.z), w(_w){}
  Vec4f(const Vec4f & v): x(v.x), y(v.y), z(v.z), w(v.w){}

  Vec4f operator/(float s){float d = 1.f/s; return Vec4f(x*d, y*d, z*d, w*d);}
  Vec4f & operator/=(float s){float d = 1.f/s; x *= d; y *= d; z *= d; w *= d; return *this;}

  Vec3f xyz() const{return Vec3f(x,y,z);}

  float x, y, z, w;
};

inline std::ostream & operator<<(std::ostream & os, const Vec4f & v){
  return os << "{" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << "}";
}

#endif
