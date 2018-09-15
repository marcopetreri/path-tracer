#ifndef _AABB_
#define _AABB_

#include <limits>
#include <iostream>
#include "../geometry/vec3d.hpp"
#include "../geometry/ray.hpp"
#include "../utilities/math.hpp"


class AABB{
public:
  AABB(): min(-std::numeric_limits<double>::max()), max(std::numeric_limits<double>::max()){}
  AABB(const Vec3d & v): min(-v), max(v){
    if(min > max){
      min = v;
      max = -v;
    }
  }
  AABB(const Vec3d & _min, const Vec3d _max): min(_min), max(_max){
    if(min > max){
      min = _max;
      max = _min;
    }
  }
  AABB(const AABB & b): min(b.min), max(b.max){}

  AABB operator+(const AABB & b) const{
    Vec3d tmin, tmax;
    for(int i = 0; i < 3; ++i){
      tmin[i] = b.min[i] < min[i] ? b.min[i] : min[i];
      tmax[i] = b.max[i] > max[i] ? b.max[i] : max[i];
    }
    return AABB(tmin, tmax);
  }
  AABB operator+(const std::initializer_list<Vec3d> & b) const{
    return *this + AABB(*b.begin(), *b.end());
  }
  AABB & operator+=(const AABB & b){
    for(int i = 0; i < 3; ++i){
      min[i] = min[i] < b.min[i] ? min[i] : b.min[i];
      max[i] = max[i] > b.max[i] ? max[i] : b.max[i];
    }
    return *this;
  }
  AABB & operator+=(const std::initializer_list<Vec3d> & b){
    return *this += AABB(*b.begin(), *b.end());
  }
  AABB & operator=(const AABB & b){min = b.min; max = b.max; return *this;}

  Vec3d diag() const{
    return max - min;
  }

  bool hit(const Ray & ray, double & tN, double & tF) const{
    double tmin = D_EPS, tmax = std::numeric_limits<double>::max();
    for(int i = 0; i < 3; ++i){
      double t0 = (min[i] - ray.o[i])*ray.dInv[i];
      double t1 = (max[i] - ray.o[i])*ray.dInv[i];
      if(ray.s[i]){
        double temp = t0;
        t0 = t1; t1 = temp;
      }
      tmin = t0 > tmin ? t0 : tmin;
      tmax = t1 < tmax ? t1 : tmax;
      if(tmax <= tmin)
        return false;
    }
    tN = tmin; tF = tmax;
    return true;
  }

// bool hit(const Ray & ray, double & tN, double & tF) const{
//   double tmin, tmax, tymin, tymax, tzmin, tzmax;
//   tmin = (min[0] - ray.o[0])*ray.dInv[0];
//   tmax = (max[0] - ray.o[0])*ray.dInv[0];
//   tymin = (min[1] - ray.o[1])*ray.dInv[1];
//   tymax = (max[1] - ray.o[1])*ray.dInv[1];
//   if(tmin > tymax || tymin > tmax)
//     return false;
//   if(tymin > tmin)
//     tmin = tymin;
//   if(tymax < tmax)
//     tmax = tymax;
//   tzmin = (min[2] - ray.o[2])*ray.dInv[2];
//   tzmax = (max[2] - ray.o[2])*ray.dInv[2];
//   if(tmin > tzmax || tzmin > tmax)
//     return false;
//   if(tzmin > tmin)
//     tmin = tzmin;
//   if(tzmax < tmax)
//     tmax = tzmax;
//   tN = tmin; tF = tmax;
//   return true;
// }

  std::string toString() const{
    return "[ " + min.toString() + ", " + max.toString() + ", Extention: " + diag().toString() + "]";
  }


  Vec3d min, max;
};


inline std::ostream & operator<<(std::ostream & os, const AABB & b){
  return os << "AABB : { " << b.min << ", " << b.max << " }";
}

#endif
