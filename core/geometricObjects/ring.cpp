#include "ring.hpp"
#include "../geometry/ray.hpp"
#include "../geometry/transform.hpp"
#include "../utilities/constants.hpp"
#include "../utilities/intersection.hpp"

Ring::Ring(): Disk(), r1(0.){}

Ring::Ring(const Vec3d & _p, const Vec3d & _n, double _r, double _r1, Material * m): Disk(_p, _n, _r, m), r1(_r1){
  if(r1 > r)
    std::swap(r1, r);
}

Ring::Ring(const Ring & r): Disk(r), r1(r.r1){}

Ring & Ring::operator=(const Ring & r){Disk::operator=(r); r1 = r.r1; return *this;}

bool Ring::hit(const Ray & ray, Intersection & hit){
  double t = ((p - ray.o)*n)/(ray.d*n);
  double d = (ray(t) - p).lengthSq();
  if(t > EPS && d >= r1*r1 && d <= r*r && t < hit.t){
    hit.t = t;
    hit.hit = true;
    hit.obj_ptr = this;
    return true;
  }
  else
    return false;
}

void Ring::applyTransform(Transform * tr){
  Disk::applyTransform(tr);
  double s = std::max(tr->m->operator()(0,0), tr->m->operator()(1,1));
  s = std::max(s, tr->m->operator()(2,2));
  r1 *= s;
}

std::ostream & operator<<(std::ostream & os, const Ring & r){
  return os << "Ring : { " << r.p << ", " << r.n
            << "\nr1 : " << r.r << ", r2 : " << r.r1
            << "\nmin: " << r.min << ", max: " << r.max << " }";
}
