#include "box.hpp"
#include "../geometry/ray.hpp"
#include "../geometry/transform.hpp"
#include "../utilities/intersection.hpp"
#include "../utilities/constants.hpp"

Box::Box(): Primitive(), c(){
              min = -std::numeric_limits<double>::max();
              max = std::numeric_limits<double>::max();
            }

Box::Box(const Vec3d & v, Material * m): Primitive(m), c(){
  min = -v; max = v;
  if(min > max){
    min = v;
    max = -v;
  }
}

Box::Box(const Vec3d & _min, const Vec3d & _max, Material * m): Primitive(m){
  min = _min; max = _max;
  if(min > max){
    min = _max;
    max = _min;
  }
  c = calcCenter();
}

Box::Box(const Box & b): Primitive(b), c(b.c){}

Box & Box::operator=(const Box & b){
  Primitive::operator=(b);
  c = b.c;
  return *this;
}

bool Box::hit(const Ray & ray, Intersection & hit){
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
  if(tmin < hit.t){
    hit.t = tmin;
    hit.hit = true;
    hit.obj_ptr = this;
    return true;
  }
  return false;
}

Vec3d Box::calcNormal(Intersection & hit) const{ //FIXME:: da rivedere!!
  Vec3d d = hit.hitPoint - c;
  double max = abs(d.x);
  int j = 0, sgn = (D_EPS < d.x) - (d.x < -D_EPS);
  for(int i = 1; i < 3; ++i){
    double val = abs(d[i]);
    if(val > max){
      max = val; j = i; sgn = (D_EPS < d[i]) - (d[i] < -D_EPS);
    }
  }
  Vec3d n;
  n[j] = sgn;
  return n;
}

void Box::applyTransform(Transform * tr){
  min = (tr->m->operator*(Vec4d(min,1.))).xyz();
  max = (tr->m->operator*(Vec4d(max,1.))).xyz();
  c = (tr->m->operator*(Vec4d(c,1.))).xyz();
}


std::ostream & operator<<(std::ostream & os, const Box & b){
  return os << "Box : { " << b.min << ", " << b.max << ", " << b.c << " }";
}
