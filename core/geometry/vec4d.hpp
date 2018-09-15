#ifndef _VEC_4D_
#define _VEC_4D_

#include "vec3d.hpp"
#include <assimp/vector3.h>

class Vec4d{
public:
  Vec4d(): x(), y(), z(), w(){}
  Vec4d(double s, double _w): x(s), y(s), z(s), w(_w){}
  Vec4d(double _x, double _y, double _z, double _w): x(_x), y(_y), z(_z), w(_w){}
  Vec4d(const Vec3d & v, double _w): x(v.x), y(v.y), z(v.z), w(_w){}
  Vec4d(const aiVector3D & v, double _w): x(v.x), y(v.y), z(v.z), w(_w){}
  Vec4d(const Vec4d & v): x(v.x), y(v.y), z(v.z), w(v.w){}

  Vec4d operator/(double s){double d = 1./s; return Vec4d(x*d, y*d, z*d, w*d);}
  Vec4d & operator/=(double s){double d = 1./s; x *= d; y *= d; z *= d; w *= d; return *this;}

  Vec3d xyz() const{return Vec3d(x,y,z);}

  double x, y, z, w;
};

inline std::ostream & operator<<(std::ostream & os, const Vec4d & v){
  return os << "{" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << "}";
}

#endif
