#ifndef _VEC_3D_
#define _VEC_3D_

#include <iostream>
#include <math.h>
#include <assimp/vector3.h>

class Vec3d{
public:
  Vec3d(): x(), y(), z(){}
  Vec3d(double s): x(s), y(s), z(s){}
  Vec3d(double _x, double _y, double _z): x(_x), y(_y), z(_z){}
  Vec3d(const Vec3d & v): x(v.x), y(v.y), z(v.z){}
  Vec3d(const aiVector3D & v): x(v.x), y(v.y), z(v.z){}

  Vec3d operator+(const Vec3d & v) const{return Vec3d(x+v.x, y+v.y, z+v.z);}
  Vec3d & operator+=(const Vec3d & v){x += v.x; y += v.y; z += v.z; return *this;}
  Vec3d operator-(const Vec3d & v) const{return Vec3d(x-v.x, y-v.y, z-v.z);}
  Vec3d & operator-=(const Vec3d & v){x -= v.x; y -= v.y; z -= v.z; return *this;}
  Vec3d operator*(double s) const{return Vec3d(x*s, y*s, z*s);}
  Vec3d & operator*=(double s){x *= s; y *= s; z *= s; return *this;}
  double operator*(const Vec3d & v) const{return x*v.x + y*v.y + z*v.z;}
  Vec3d operator^(const Vec3d & v) const{return Vec3d(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);}
  Vec3d operator%(const Vec3d & v) const{return Vec3d(x*v.x, y*v.y, z*v.z);}
  Vec3d operator/(double s) const{double d = 1./s; return Vec3d(x*d, y*d, z*d);}
  Vec3d & operator/=(double s){double d = 1./s; x *= d; y *= d; z *= d; return *this;}
  Vec3d operator-() const{return Vec3d(-x, -y, -z);}
  bool operator==(const Vec3d & v) const{return x == v.x && y == v.y && z == v.z;}
  bool operator!=(const Vec3d & v) const{return x != v.x || y != v.y || z != v.z;}
  bool operator>(const Vec3d & v) const{return x > v.x && y > v.y && z > v.z;}
  bool operator>=(const Vec3d & v) const{return x >= v.x && y >= v.y && z >= v.z;}
  bool operator<(const Vec3d & v) const{return x < v.x && y < v.y && z < v.z;}
  bool operator<=(const Vec3d & v) const{return x <= v.x && y <= v.y && z <= v.z;}
  Vec3d & operator=(const Vec3d & v){x = v.x; y = v.y; z = v.z; return *this;}
  Vec3d & operator=(const aiVector3D & v){x = v.x; y = v.y; z = v.z; return *this;}
  double operator[](int i) const{return (&x)[i];}
  double & operator[](int i) {return (&x)[i];}

  double lengthSq() const{return x*x + y*y + z*z;}
  double length() const{return sqrt(lengthSq());}
  Vec3d hat() const{return (*this)/length();}
  Vec3d & normalize(){return (*this)/=length();}
  Vec3d reflect(const Vec3d & n) const{return *this - n*((*this)*n)*2.;}
  Vec3d & reflect(const Vec3d & n){return *this -= n*((*this)*n)*2.;}
  Vec3d floorVec() const{return Vec3d(floor(x),floor(y),floor(z));}
  Vec3d & floorVec(){x = floor(x); y = floor(y); z = floor(z); return *this;}

  std::string toString() const{
    return "{ "+std::to_string(x)+", "+std::to_string(y)+", "+std::to_string(z)+"}";
  }

  double x, y, z;
};

inline Vec3d operator*(double s, const Vec3d & v){return v*s;}
inline std::ostream & operator<<(std::ostream & os, const Vec3d & v){
  return os << "{" << v.x << ", " << v.y << ", " << v.z << "}";
}

#endif
