#ifndef _VEC_3F_
#define _VEC_3F_

#include <iostream>
#include <math.h>

class Vec3f{
public:
  Vec3f(): x(), y(), z(){}
  Vec3f(float s): x(s), y(s), z(s){}
  Vec3f(float _x, float _y, float _z): x(_x), y(_y), z(_z){}
  Vec3f(const Vec3f & v): x(v.x), y(v.y), z(v.z){}

  Vec3f operator+(const Vec3f & v) const{return Vec3f(x+v.x, y+v.y, z+v.z);}
  Vec3f & operator+=(const Vec3f & v){x += v.x; y += v.y; z += v.z; return *this;}
  Vec3f operator-(const Vec3f & v) const{return Vec3f(x-v.x, y-v.y, z-v.z);}
  Vec3f & operator-=(const Vec3f & v){x -= v.x; y -= v.y; z -= v.z; return *this;}
  Vec3f operator*(float s) const{return Vec3f(x*s, y*s, z*s);}
  Vec3f & operator*=(float s){x *= s; y *= s; z *= s; return *this;}
  float operator*(const Vec3f & v) const{return x*v.x + y*v.y + z*v.z;}
  Vec3f operator^(const Vec3f & v) const{return Vec3f(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);}
  Vec3f operator%(const Vec3f & v) const{return Vec3f(x*v.x, y*v.y, z*v.z);}
  Vec3f operator/(float s) const{float d = 1.f/s; return Vec3f(x*d, y*d, z*d);}
  Vec3f & operator/=(float s){float d = 1.f/s; x *= d; y *= d; z *= d; return *this;}
  Vec3f operator-() const{return Vec3f(-x, -y, -z);}
  bool operator==(const Vec3f & v) const{return x == v.x && y == v.y && z == v.z;}
  bool operator!=(const Vec3f & v) const{return x != v.x || y != v.y || z != v.z;}
  bool operator>(const Vec3f & v){return x > v.x && y > v.y && z > v.z;}
  bool operator<(const Vec3f & v){return x < v.x && y < v.y && z < v.z;}
  Vec3f & operator=(const Vec3f & v){x = v.x; y = v.y; z = v.z; return *this;}
  float operator[](int i) const{return (&x)[i];}
  float & operator[](int i) {return (&x)[i];}

  float lengthSq() const{return x*x + y*y + z*z;}
  float length() const{return sqrtf(lengthSq());}
  Vec3f hat() const{return (*this)/length();}
  Vec3f & normalize(){return (*this)/=length();}
  Vec3f reflect(const Vec3f & n) const{return *this - n*((*this)*n)*2.f;}
  Vec3f & reflect(const Vec3f & n){return *this -= n*((*this)*n)*2.f;}

  std::string toString() const{
    return "{ "+std::to_string(x)+", "+std::to_string(y)+", "+std::to_string(z)+"}";
  }

  float x, y, z;
};

inline Vec3f operator*(float s, const Vec3f & v){return v*s;}
inline std::ostream & operator<<(std::ostream & os, const Vec3f & v){
  return os << "{" << v.x << ", " << v.y << ", " << v.z << "}";
}

#endif
