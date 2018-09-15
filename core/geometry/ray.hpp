#ifndef _RAY_
#define _RAY_

#include "vec3d.hpp"
#include "../utilities/constants.hpp"

class Ray{
public:
  Ray(): o(), d(), dInv(), s(){}
  Ray(const Vec3d & _o, const Vec3d & _d): o(_o), d(_d.hat()), dInv(1./d.x, 1./d.y, 1./d.z){
    s[0] = dInv.x < D_EPS; s[1] = dInv.y < D_EPS; s[2] = dInv.z < D_EPS;
  }
  Ray(const Ray & r): o(r.o), d(r.d), dInv(r.dInv), s{r.s[0],r.s[1],r.s[2]}{}

  Ray & operator=(const Ray & r){
    o = r.o; d = r.d; dInv = r.dInv;
    s[0] = r.s[0]; s[1] = r.s[1]; s[2] = r.s[2];
    return *this;
  }
  Vec3d operator()(double t) const{return o + d*t;}

  void refresh(){
    dInv = Vec3d(1./d.x, 1./d.y, 1./d.z);
    s[0] = dInv.x < D_EPS; s[1] = dInv.y < D_EPS; s[2] = dInv.z < D_EPS;
  }

  Vec3d o, d, dInv;
  bool s[3];
};

inline std::ostream & operator<<(std::ostream & os, const Ray & r){
  return os << "R : { " << r.o << ", " << r.d << ", " << r.dInv
            << ", { " << r.s[0] << ", " << r.s[1] << ", " << r.s[2] << "} }";
}

#endif
