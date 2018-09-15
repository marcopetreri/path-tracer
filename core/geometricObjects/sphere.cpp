#include "sphere.hpp"
#include "../geometry/ray.hpp"
#include "../geometry/transform.hpp"
#include "../utilities/constants.hpp"

Sphere::Sphere(): Primitive(), c(), r(0.){}

Sphere::Sphere(const Vec3d & _c, double _r, Material * m): Primitive(m), c(_c), r(_r){
  setBVertex();
}

Sphere::Sphere(const Sphere & s): Primitive(s), c(s.c), r(s.r){}

Sphere & Sphere::operator=(const Sphere & s){
  Primitive::operator=(s); c = s.c; r = s.r; min = s.min; max = s.max;
  return *this;
}

bool Sphere::hit(const Ray & ray, Intersection & hit){
  double r2 = r*r;
  Vec3d l = c - ray.o;
  double s = l*ray.d;
  double l2 = l.lengthSq();
  if(s < 0. && l2 > r2)
    return false;
  double m2 = l2 - s*s;
  if(m2 > r2)
    return false;
  double q = sqrt(r2 - m2);
  double t = (l2 > r2) ? s - q - D_EPS : s + q + D_EPS;
  if(t > D_EPS && t < hit.t){
    hit.t = t;
    hit.hit = true;
    hit.obj_ptr = this;
    return true;
  }
  return false;
}

// bool Sphere::hit(const Ray & ray, Intersection & hit){
//   Vec3d w = ray.o - c;
//   double beta = 2*ray.d*w;
//   double gamma = w.lengthSq() - r*r;
//   double t1 = 0, t2 = 0;
//
//   if(solveQuadratic(1.f, beta, gamma, t1, t2) != 0){
//     if(t2 > D_EPS && t2 < hit.t){
//       hit.t = t2;
//       hit.hit = true;
//       hit.obj_ptr = this;
//       return true;
//     }
//     else if(t1 > D_EPS && t1 < hit.t){
//       hit.t = t1;
//       hit.hit = true;
//       hit.obj_ptr = this;
//       return true;
//     }
//   }
//   hit.hit = false;
//   return false;
// }

Vec3d Sphere::calcTangent(Intersection & hit) const{
  Vec3d up = fabs(hit.normal.z) < 0.999 ? Vec3d(0.0,0.0,1.0) : Vec3d(1,0,0);
  return (up^hit.normal).hat();
}


Vec3d Sphere::calcTexture(Intersection & hit) const{
  return Vec3d(.5 + atan2(hit.normal.x,hit.normal.y)*invTWO_PI
              ,.5 - asin(hit.normal.z)*invPI
              ,1.);
}

void Sphere::applyTransform(Transform * tr){
  double s = std::max(tr->m->operator()(0,0), tr->m->operator()(1,1));
  s = std::max(s, tr->m->operator()(2,2));
  c = (tr->m->operator*(Vec4d(c,1.))).xyz();
  r *= s;
  setBVertex();
}

std::ostream & operator<<(std::ostream & os, const Sphere & sp){
  return os << "Sphere : { " << sp.c << ", " << sp.r << ", " << sp.min << ", " << sp.max << " }";
}
