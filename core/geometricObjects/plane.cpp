#include "plane.hpp"
#include "../geometry/ray.hpp"
#include "../geometry/transform.hpp"
#include "../utilities/constants.hpp"
#include "../utilities/intersection.hpp"

Plane::Plane(): Primitive(), p(), n(){}

Plane::Plane(const Vec3d _p, const Vec3d & _n, Material * m): Primitive(m), p(_p), n(_n.hat()){}

Plane::Plane(const Plane & pl): Primitive(pl), p(pl.p), n(pl.n){}

Plane & Plane::operator=(const Plane & pl){
  Primitive::operator=(pl);
  p = pl.p; n = pl.n;
  return *this;
}

bool Plane::hit(const Ray & ray, Intersection & hit){
  double t = ((p - ray.o)*n)/(ray.d*n);
  if(t > D_EPS && t < hit.t){
    hit.t = t;
    hit.hit = true;
    hit.obj_ptr = this;
    return true;
  }
  else
    return false;
}

void Plane::applyTransform(Transform * tr){
  p = (tr->m->operator*(Vec4d(p,1.))).xyz();
  n = (tr->mTrInv->operator*(Vec4d(n,0.))).xyz();
}

void Plane::setBVertex(){}

std::ostream & operator<<(std::ostream & os, const Plane & pl){
  return os << "Plane : { " << pl.p << ", " << pl.n << " }";
}
