#include "disk.hpp"
#include "../geometry/ray.hpp"
#include "../geometry/transform.hpp"
#include "../utilities/constants.hpp"
#include "../utilities/intersection.hpp"

Disk::Disk(): Plane(), r(0.){}

Disk::Disk(const Vec3d & _p, const Vec3d & _n, double _r, Material * m): Plane(_p, _n, m), r(_r){
  setBVertex();
}

Disk::Disk(const Disk & d): Plane(d), r(d.r){}

Disk & Disk::operator=(const Disk & d){Plane::operator=(d); r = d.r; return *this;}

bool Disk::hit(const Ray & ray, Intersection & hit){
  double t = ((p - ray.o)*n)/(ray.d*n);
  double d = (ray(t) - p).lengthSq();
  if(t > D_EPS && d <= r*r && t < hit.t){
    hit.t = t;
    hit.hit = true;
    hit.obj_ptr = this;
    return true;
  }
  else
    return false;
}

void Disk::applyTransform(Transform * tr){
  Plane::applyTransform(tr);
  double s = std::max(tr->m->operator()(0,0), tr->m->operator()(1,1));
  s = std::max(s, tr->m->operator()(2,2));
  r *= s;
  setBVertex();
}

std::ostream & operator<<(std::ostream & os, const Disk & d){
  return os << "Disk : { " << d.p << ", " << d.n << ", r : " << d.r << " }";
}
